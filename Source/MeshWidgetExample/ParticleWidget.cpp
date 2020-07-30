// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MeshWidgetExample.h"
#include "Slate/SMeshWidget.h"
#include "Slate/SlateVectorArtInstanceData.h"

#include "ParticleWidget.h"

struct FSimpleParticle
{
	FVector2D Origin;
	FVector2D Position;
	FVector2D Velocity;
	float Life;

	void SetVelocity(float Angle, float Speed)
	{
		Velocity.X = FMath::Cos(FMath::DegreesToRadians(Angle)) * Speed;
		Velocity.Y = -FMath::Sin(FMath::DegreesToRadians(Angle)) * Speed;
	}

	void Update(float DeltaTime)
	{
		Position += Velocity * DeltaTime;
	}
};

struct FSimpleEmitter
{
	int32 ActiveParticles;
	TArray<FSimpleParticle> Particles;
	
	FSimpleEmitter()
		: ActiveParticles(0)
		, Particles()
		, Position(0, 0)
	{
	}

	FSimpleEmitter(int MaxParticleCount)
		: ActiveParticles(0)
		, Particles()
		, Position(0, 0)
	{
		Particles.AddZeroed(MaxParticleCount);
	}

	void SetPosition(FVector2D InPosition)
	{
		Position = InPosition;
	}

	void Update(float DeltaTime)
	{
		while ( NeedToSpawnParticles() )
		{
			EmitParticle();
		}

		for ( int i = 0; i < ActiveParticles; i++ )
		{
			FSimpleParticle& Particle = Particles[i];

			Particle.Life -= DeltaTime;

			if ( Particle.Life > 0 )
			{
				Particle.Update(DeltaTime);
			}
			else
			{
				// Return the particle to the pool, swap it with a functioning one.
				ActiveParticles--;
				Particles.Swap(i, ActiveParticles);
				i--;
			}
		}
	}

private:

	bool NeedToSpawnParticles() const
	{
		return ActiveParticles < Particles.Num();
	}

	void EmitParticle()
	{
		FSimpleParticle& Particle = Particles[ActiveParticles];
		Particle.Origin = Position;
		Particle.Position = FVector2D(0, 0);
		Particle.Life = FMath::RandRange(0.5f, 3.0f);
		Particle.SetVelocity(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(1.0f, 75.0f));

		ActiveParticles++;
	}

private:
	FVector2D Position;
};

class SParticleMeshWidget : public SMeshWidget
{
public:
	SLATE_BEGIN_ARGS(SParticleMeshWidget) { }
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& Args, UParticleWidget& InThis)
	{
		This = &InThis;
		Emitter = FSimpleEmitter(128);
	}

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const float Scale = AllottedGeometry.Scale;

		// Trail
		if ( This->TrailMeshId != -1 )
		{
			FVector2D TrailOriginWindowSpace = AllottedGeometry.LocalToAbsolute(AllottedGeometry.GetLocalSize() * 0.5f);

			TSharedPtr<FSlateInstanceBufferUpdate> PerInstaceUpdate = BeginPerInstanceBufferUpdateConst(This->TrailMeshId);
			PerInstaceUpdate->GetData().Empty();

			//const FVector2D TrailMeshExtentMin = This->TrailMeshAsset->GetExtentMin();
			//const FVector2D TrailMeshExtentMax = This->TrailMeshAsset->GetExtentMax();
			Emitter.SetPosition(TrailOriginWindowSpace);
			Emitter.Update(Args.GetDeltaTime());

			for ( int32 i = 0; i < Emitter.ActiveParticles; ++i )
			{
				const FSimpleParticle& Particle = Emitter.Particles[i];

				FSlateVectorArtInstanceData ParticleData;
				ParticleData.SetPosition(Particle.Origin + Particle.Position * Scale);
				ParticleData.SetScale(Scale);

				PerInstaceUpdate->GetData().Add(ParticleData.GetData());
			}

			FSlateInstanceBufferUpdate::CommitUpdate(PerInstaceUpdate);
		}

		return SMeshWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}

public:
	UParticleWidget* This;

	mutable FSimpleEmitter Emitter;
};

UParticleWidget::UParticleWidget()
	: TrailMeshId(-1)
{
}

void UParticleWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if ( TrailMeshAsset )
	{
		const int32 MAX_PARTICLES = 128;
		TrailMeshId = MyMesh->AddMesh(*TrailMeshAsset);
		MyMesh->EnableInstancing(TrailMeshId, MAX_PARTICLES);
	}
}

void UParticleWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyMesh.Reset();
}

TSharedRef<SWidget> UParticleWidget::RebuildWidget()
{
	MyMesh = SNew(SParticleMeshWidget, *this);
	return MyMesh.ToSharedRef();
}
