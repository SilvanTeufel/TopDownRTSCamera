// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Characters/CameraBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "UnrealEngine.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACameraBase::ACameraBase(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateCameraComp();

	if (RootComponent == nullptr) {
		RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	}

	ControlWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("ControlWidget"));
	ControlWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ACameraBase::BeginPlay()
{
	Super::BeginPlay();
	if (!DisableBeginPlay) {
		GetViewPortScreenSizes(GetViewPortScreenSizesState);
		SpawnControllWidget();
	}
}

// Called every frame
void ACameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!DisableTick) {
		PanMoveCamera(GetCameraPanDirection() * CamSpeed);
		CamRotationTick();
		CamMoveAndZoomTick();
	}
}


void ACameraBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACameraBase::CreateCameraComp()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(SpringArmRotator);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArm);
}


void ACameraBase::GetViewPortScreenSizes(int x)
{
	PC = Cast<APlayerController>(GetController());
	switch (x)
	{
	case 1:
	{
		PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
	}
	break;
	case 2:
	{
		ScreenSizeX = GSystemResolution.ResX;
		ScreenSizeY = GSystemResolution.ResY;
	}
	break;
	}
}

void ACameraBase::SpawnControllWidget()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform SpellTransform;
	SpellTransform.SetLocation(FVector(500, 0, 0));
	SpellTransform.SetRotation(FQuat(FRotator::ZeroRotator));


	if (ControlWidgetComp) {
		FRotator NewRotation = ControlWidgetRotation;
		FQuat QuatRotation = FQuat(NewRotation);
		ControlWidgetComp->SetRelativeRotation(QuatRotation, false, 0, ETeleportType::None);
		ControlWidgetComp->SetRelativeLocation(ControlWidgetLocation);
	}
}

FVector ACameraBase::GetCameraPanDirection() {
	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;

	PC->GetMousePosition(MousePosX, MousePosY);

	switch (CamAngle)
	{
	case 0:
	{
		if (MousePosX <= Margin) {
			CamDirectionY = -1;
		}

		if (MousePosY <= Margin) {
			CamDirectionX = 1;
		}

		if (MousePosX >= ScreenSizeX - Margin) {
			CamDirectionY = 1;
		}

		if (MousePosY >= ScreenSizeY - Margin) {
			CamDirectionX = -1;
		}
	}
	break;
	case 90:
	{
		if (MousePosX <= Margin) {
			CamDirectionX = 1;
		}

		if (MousePosY <= Margin) {
			CamDirectionY = 1;
		}

		if (MousePosX >= ScreenSizeX - Margin) {
			CamDirectionX = -1;
		}

		if (MousePosY >= ScreenSizeY - Margin) {
			CamDirectionY = -1;
		}
	}
	break;
	case 180:
	{
		if (MousePosX <= Margin) {
			CamDirectionY = 1;
		}

		if (MousePosY <= Margin) {
			CamDirectionX = -1;
		}

		if (MousePosX >= ScreenSizeX - Margin) {
			CamDirectionY = -1;
		}

		if (MousePosY >= ScreenSizeY - Margin) {
			CamDirectionX = 1;
		}
	}
	break;
	case 270:
	{
		if (MousePosX <= Margin) {
			CamDirectionX = -1;
		}

		if (MousePosY <= Margin) {
			CamDirectionY = -1;
		}

		if (MousePosX >= ScreenSizeX - Margin) {
			CamDirectionX = 1;
		}

		if (MousePosY >= ScreenSizeY - Margin) {
			CamDirectionY = 1;
		}
	}
	break;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}

void ACameraBase::PanMoveCamera(const FVector& PanDirection) {
	if (PanDirection == FVector::ZeroVector) {
		return;
	}
	else {
		//AddActorWorldOffset(GetCameraPanDirection() * CamSpeed * GetActorLocation().Z * 0.001);
		AddActorWorldOffset(PanDirection * GetActorLocation().Z * 0.001);
	}
}

void ACameraBase::ZoomOut() {

	ZoomCamOut = true;
	ZoomCamIn = false;

}

void ACameraBase::CamLeft()
{
	RollCamRight = false;
	RollCamLeft = true;
}

void ACameraBase::CamRight()
{
	RollCamLeft = false;
	RollCamRight = true;
}

void ACameraBase::CamStop()
{
	RollCamRight = false;
	RollCamLeft = false;

}

void ACameraBase::CamRotationTick()
{
	if (RollCamRight) {
		YawValue -= 1.f;

		if (YawValue >= 270.f) {
			AddActorWorldOffset(FVector(+11.5, +11.5, 0));
		}
		else if (YawValue >= 180.f) {
			AddActorWorldOffset(FVector(+11.5, -11.5, 0));
		}
		else if (YawValue >= 90.f) {
			AddActorWorldOffset(FVector(-11.5, -11.5, 0));
		}
		else if (YawValue >= 0.f) {
			AddActorWorldOffset(FVector(-11.5, +11.5, 0));
		}

		if (YawValue == 0.f || YawValue == 360.f) {
			RollCamRight = false;
			CamAngle = 0;
		}
		else if (YawValue == 90.f) {
			RollCamRight = false;
			CamAngle = 90;
		}
		else if (YawValue == 180.f) {
			RollCamRight = false;
			CamAngle = 180;
		}
		else if (YawValue == 270.f) {
			RollCamRight = false;
			CamAngle = 270;
		}
		if (YawValue < 0.f) YawValue += 360.f;
	}

	if (RollCamLeft) {
		YawValue += 1.f;

		if (YawValue <= 90.f) {
			AddActorWorldOffset(FVector(+11.5, -11.5, 0));
		}
		else if (YawValue <= 180.f) {
			AddActorWorldOffset(FVector(+11.5, +11.5, 0));
		}
		else if (YawValue <= 270.f) {
			AddActorWorldOffset(FVector(-11.5, +11.5, 0));
		}
		else if (YawValue <= 360.f) {
			AddActorWorldOffset(FVector(-11.5, -11.5, 0));
		}

		if (YawValue == 0.f || YawValue == 360.f) {
			RollCamLeft = false;
			CamAngle = 0;
		}
		else if (YawValue == 90.f) {
			RollCamLeft = false;
			CamAngle = 90;
		}
		else if (YawValue == 180.f) {
			RollCamLeft = false;
			CamAngle = 180;
		}
		else if (YawValue == 270.f) {
			RollCamLeft = false;
			CamAngle = 270;
		}

		if (YawValue > 360.f) YawValue -= 360.f;
	}

	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


void ACameraBase::ZoomIn() {

	ZoomCamOut = false;
	ZoomCamIn = true;
}


void ACameraBase::ZoomStop() {
	ZoomCamOut = false;
	ZoomCamIn = false;
}

FVector2D ACameraBase::GetMousePos2D()
{
	float PosX;
	float PosY;
	PC->GetMousePosition(PosX, PosY);

	return FVector2D(PosX, PosY);
}


void ACameraBase::Zoom()
{
	FHitResult Hit;
	FVector2D MPosition = GetMousePos2D();
	FVector ActorLocation = GetActorLocation();
	SetActorLocation(FVector(MPosition.X, MPosition.Y, ActorLocation.Z));
}

void ACameraBase::ZoomOutToPosition()
{
	ZoomCamOutToPosition = true;
}

void ACameraBase::CamMoveAndZoomTick()
{
	FVector ALocation = GetActorLocation();

	if (ZoomCamOutToPosition) {
		if (ALocation.Z < ZoomOutPosition) {
			if (YawValue == 0.f || YawValue == 360.f) {
				AddActorWorldOffset(FVector(-4.25, 0, 6) * CamSpeed);
			}
			else if (YawValue == 90.f) {
				AddActorWorldOffset(FVector(0, -4.25, 6) * CamSpeed);
			}
			else if (YawValue == 180.f) {
				AddActorWorldOffset(FVector(4.25, 0, 6) * CamSpeed);
			}
			else if (YawValue == 270.f) {
				AddActorWorldOffset(FVector(0, 4.25, 6) * CamSpeed);
			}
		}

	}
	else if (!ZoomCamOut) {
		if (ALocation.Z > ZoomPosition) {
			if (YawValue == 0.f || YawValue == 360.f) {
				AddActorWorldOffset(FVector(4.25, 0, -6) * CamSpeed);
			}
			else if (YawValue == 90.f) {
				AddActorWorldOffset(FVector(0, 4.25, -6) * CamSpeed);
			}
			else if (YawValue == 180.f) {
				AddActorWorldOffset(FVector(-4.25, 0, -6) * CamSpeed);
			}
			else if (YawValue == 270.f) {
				AddActorWorldOffset(FVector(0, -4.25, -6) * CamSpeed);
			}
		}
	}

	if (ZoomCamOut)
		AddActorWorldOffset(FVector(0, 0, 0.3) * CamSpeed);

	if (ZoomCamIn)
		AddActorWorldOffset(FVector(0, 0, -0.3) * CamSpeed);

	if (MoveCamForward)
		AddActorWorldOffset(FVector(0.3, 0, 0) * CamSpeed);

	if (MoveCamBackward)
		AddActorWorldOffset(FVector(-0.3, 0, 0) * CamSpeed);

	if (MoveCamLeft)
		AddActorWorldOffset(FVector(0, -0.3, 0) * CamSpeed);

	if (MoveCamRight)
		AddActorWorldOffset(FVector(0, 0.3, 0) * CamSpeed);
}

void ACameraBase::ZoomInToPosition()
{
	ZoomCamOutToPosition = false;
}

void ACameraBase::LockOnCharacter(ACharacter* SelectedActor)
{
	if (SelectedActor && !RollCamLeft && !RollCamRight) {

		FVector SelectedActorLocation = SelectedActor->GetActorLocation();
		FVector CurrentCameraPawnLocation = GetActorLocation();
		FVector NewPawnLocation;

		switch (CamAngle)
		{
		case 0:
		{
			NewPawnLocation = FVector(SelectedActorLocation.X - CurrentCameraPawnLocation.Z * 0.7, SelectedActorLocation.Y, CurrentCameraPawnLocation.Z); // 1000.0f
		}
		break;
		case 90:
		{
			NewPawnLocation = FVector(SelectedActorLocation.X, SelectedActorLocation.Y - CurrentCameraPawnLocation.Z * 0.7, CurrentCameraPawnLocation.Z); // 1000.0f
		}
		break;
		case 180:
		{
			NewPawnLocation = FVector(SelectedActorLocation.X + CurrentCameraPawnLocation.Z * 0.7, SelectedActorLocation.Y, CurrentCameraPawnLocation.Z); // 1000.0f
		}
		break;
		case 270:
		{
			NewPawnLocation = FVector(SelectedActorLocation.X, SelectedActorLocation.Y + CurrentCameraPawnLocation.Z * 0.7, CurrentCameraPawnLocation.Z); // 1000.0f
		}
		break;

		}

		SetActorLocation(NewPawnLocation);
	}
}

void ACameraBase::HideControlWidget()
{
	if (ControlWidgetComp)
		ControlWidgetComp->SetRelativeLocation(ControlWidgetHideLocation);
}

void ACameraBase::ShowControlWidget()
{
	if (ControlWidgetComp)
		ControlWidgetComp->SetRelativeLocation(ControlWidgetLocation);
}


void ACameraBase::JumpCamera(FHitResult Hit)
{

	FVector MoveLocation;
	FVector ActorLocation = GetActorLocation();

	switch (CamAngle)
	{
	case 0:
	{
		MoveLocation = FVector(Hit.Location.X - ActorLocation.Z * 0.7, Hit.Location.Y, ActorLocation.Z);
	}
	break;
	case 90:
	{
		MoveLocation = FVector(Hit.Location.X, Hit.Location.Y - ActorLocation.Z * 0.7, ActorLocation.Z);
	}
	break;
	case 180:
	{
		MoveLocation = FVector(Hit.Location.X + ActorLocation.Z * 0.7, Hit.Location.Y, ActorLocation.Z);
	}
	break;
	case 270:
	{
		MoveLocation = FVector(Hit.Location.X, Hit.Location.Y + ActorLocation.Z * 0.7, ActorLocation.Z);
	}
	break;
	}

	SetActorLocation(MoveLocation);
}