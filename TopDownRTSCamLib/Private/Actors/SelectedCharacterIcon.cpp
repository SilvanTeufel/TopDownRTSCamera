// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Actors/SelectedCharacterIcon.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASelectedCharacterIcon::ASelectedCharacterIcon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    IconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    IconMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // QueryAndPhysics
    IconMesh->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Plane"));
    if (SphereMeshAsset.Succeeded())
    {
        IconMesh->SetStaticMesh(SphereMeshAsset.Object);
        IconMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));

        static ConstructorHelpers::FObjectFinder<UMaterial>MaterialBlue(_T("Material'/TopDownRTSCamLib/Materials/M_Ring_Aura.M_Ring_Aura'")); // "Material'/Plugins/TopDownRTSCamLib/Content/Materials/M_Ring_Aura.M_Ring_Aura'"
        static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAction(_T("Material'/TopDownRTSCamLib/Materials/M_Ring_Aura_Red.M_Ring_Aura_Red'"));

        if (MaterialBlue.Object != NULL)
        {
            BlueMaterial = (UMaterial*)MaterialBlue.Object;
            IconMesh->SetMaterial(0, BlueMaterial);
        }

        if (MaterialAction.Object != NULL)
        {
            ActionMaterial = (UMaterial*)MaterialAction.Object;
            IconMesh->SetMaterial(0, ActionMaterial);
        }
    }
}

// Called when the game starts or when spawned
void ASelectedCharacterIcon::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASelectedCharacterIcon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ASelectedCharacterIcon::ChangeMaterialColour(FVector4d Colour)
{
    DynMaterial = UMaterialInstanceDynamic::Create(BlueMaterial, this);
    DynMaterial->SetVectorParameterValue(TEXT("Emissive Color"), Colour);
    IconMesh->SetMaterial(0, DynMaterial);
}

void ASelectedCharacterIcon::ChangeMaterialToAction()
{
    DynMaterial = UMaterialInstanceDynamic::Create(ActionMaterial, this);
    IconMesh->SetMaterial(0, DynMaterial);
}
