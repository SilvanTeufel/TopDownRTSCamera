// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/DataTX.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SelectedIcon.generated.h"

UCLASS()
class TOPDOWNRTSCAMLIB_API ASelectedIcon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASelectedIcon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSCamLib)
		UStaticMeshComponent* IconMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSCamLib)
		UMaterialInterface* BlueMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSCamLib)
		UMaterialInterface* ActionMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TopDownRTSCamLib)
		UMaterialInstanceDynamic* DynMaterial;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeMaterialColour(FVector4d Colour);
	void ChangeMaterialToAction();

};
