// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Slate/SlateVectorArtData.h"

#include "ParticleWidget.generated.h"

UCLASS(minimalapi)
class UParticleWidget : public UWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Particle")
	USlateVectorArtData* TrailMeshAsset;

public:
	UParticleWidget();

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface

private:
	TSharedPtr<class SParticleMeshWidget> MyMesh;

	int32 TrailMeshId;

	friend class SParticleMeshWidget;
};
