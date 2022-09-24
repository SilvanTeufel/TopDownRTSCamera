// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Controller/ControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


AControllerBase::AControllerBase() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void AControllerBase::BeginPlay() {
	HUDPtr = Cast<AHUDBase>(GetHUD());
	CameraPtr = Cast<ACameraBase>(GetPawn());
}


void AControllerBase::SetupInputComponent() {

	Super::SetupInputComponent();
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AControllerBase::LeftClickPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AControllerBase::LeftClickReleased);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AControllerBase::RightClickPressed);
	InputComponent->BindAction("Shift", IE_Pressed, this, &AControllerBase::ShiftPressed);
	InputComponent->BindAction("Shift", IE_Released, this, &AControllerBase::ShiftReleased);
	InputComponent->BindAction("Space", IE_Pressed, this, &AControllerBase::SpacePressed);
	InputComponent->BindAction("Space", IE_Released, this, &AControllerBase::SpaceReleased);

	InputComponent->BindAction("Q", IE_Pressed, this, &AControllerBase::QPressed);
	InputComponent->BindAction("W", IE_Pressed, this, &AControllerBase::WPressed);
	InputComponent->BindAction("A", IE_Pressed, this, &AControllerBase::APressed);
	InputComponent->BindAction("A", IE_Released, this, &AControllerBase::AReleased);
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AControllerBase::JumpCamera);
	InputComponent->BindAction("Strg", IE_Pressed, this, &AControllerBase::StrgPressed);
	InputComponent->BindAction("Strg", IE_Released, this, &AControllerBase::StrgReleased);

	InputComponent->BindAction("S", IE_Pressed, this, &AControllerBase::ZoomOut);
	InputComponent->BindAction("W", IE_Pressed, this, &AControllerBase::ZoomIn);
	InputComponent->BindAction("S", IE_Released, this, &AControllerBase::ZoomStop);
	InputComponent->BindAction("W", IE_Released, this, &AControllerBase::ZoomStop);
	InputComponent->BindAction("E", IE_Released, this, &AControllerBase::CamRight);
	InputComponent->BindAction("Q", IE_Released, this, &AControllerBase::CamLeft);
	InputComponent->BindAction("G", IE_Released, this, &AControllerBase::ToggleLockCameraToCharacter);

	InputComponent->BindAction("W", IE_Pressed, this, &AControllerBase::CameraPawnForward);
	InputComponent->BindAction("S", IE_Pressed, this, &AControllerBase::CameraPawnBackward);
	InputComponent->BindAction("A", IE_Pressed, this, &AControllerBase::CameraPawnLeft);
	InputComponent->BindAction("D", IE_Pressed, this, &AControllerBase::CameraPawnRight);

	InputComponent->BindAction("W", IE_Released, this, &AControllerBase::CameraPawnForwardR);
	InputComponent->BindAction("S", IE_Released, this, &AControllerBase::CameraPawnBackwardR);
	InputComponent->BindAction("A", IE_Released, this, &AControllerBase::CameraPawnLeftR);
	InputComponent->BindAction("D", IE_Released, this, &AControllerBase::CameraPawnRightR);

	InputComponent->BindAction("Tab", IE_Released, this, &AControllerBase::TabReleased);
	InputComponent->BindAction("Tab", IE_Pressed, this, &AControllerBase::TabPressed);

}




void AControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	HUDPtr->MoveActorsThroughWayPoints(MovingActors);

	for (int32 i = 0; i < SelectedActors.Num(); i++) {

		if (LockCameraToCharacter)
			CameraPtr->LockOnCharacter(SelectedActors[0]);

		switch (SelectedActors[i]->CharAnimState)
		{
		case Idle:
		{
			ControllDirectionToMouse(SelectedActors[i]);
			SelectedActors[i]->CreateIconNormalRadius();
		}
		break;
		case Run:
		{

		}
		break;
		}
	}
}


void AControllerBase::ShiftPressed()
{
	IsShiftPressed = true;
}

void AControllerBase::ShiftReleased()
{
	IsShiftPressed = false;
	if (SelectedActors.Num() && SelectedActors[0]->MoveArray.Num()) {
		HUDPtr->StartMovingActors(SelectedActors);
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			MovingActors.Add(SelectedActors[i]);
		}
	}

}

void AControllerBase::LeftClickPressed()
{

	if (AIsPressed) {
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location;
			SelectedActors[i]->ForwardVector = MoveLocation;
		}
	}
	else {

		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

		if (Hit.bBlockingHit)
		{
			ACharacterBase* CharacterFound = Cast<ACharacterBase>(Hit.GetActor());
			if (CharacterFound)
				HUDPtr->setZeroActor(CharacterFound);
			else {
				HUDPtr->InitialPoint = HUDPtr->GetMousePos2D();
				HUDPtr->bStartSelecting = true;
			}
		}
	}

}

void AControllerBase::LeftClickReleased()
{

	HUDPtr->bStartSelecting = false;
	SelectedActors = HUDPtr->FoundActors;
}


void AControllerBase::RightClickPressed()
{
	if (IsShiftPressed) {
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			if (SelectedActors[i]->CharAnimState == Idle || SelectedActors[i]->CharAnimState == Action || SelectedActors[i]->CharAnimState == Run) {
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
				FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
				SelectedActors[i]->MoveArray.Add(MoveLocation);
				DrawDebugSphere(GetWorld(), MoveLocation, 15, 5, FColor::Green, false, 1.5, 0, 1);
				SelectedActors[i]->MoveEndLocation = MoveLocation;
			}
		}
	}
	else {
		for (int32 i = 0; i < SelectedActors.Num(); i++) {
			if (SelectedActors[i]->CharAnimState == Idle || SelectedActors[i]->CharAnimState == Action || SelectedActors[i]->CharAnimState == Run) {
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
				FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);


				if (SelectedActors[i]->CharAnimState == Idle || SelectedActors[i]->CharAnimState == Run) {
					DrawDebugSphere(GetWorld(), MoveLocation, 15, 5, FColor::Green, false, 1.5, 0, 1);
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
					SelectedActors[i]->setAnimState(Run);
					SelectedActors[i]->MoveArray.Empty();
					SelectedActors[i]->MoveArrayIterator = 0;
					SelectedActors[i]->MoveEndLocation = MoveLocation;

				}


				SelectedActors[i]->ForwardVector = MoveLocation;
			}
		}
	}

}

void AControllerBase::SpacePressed()
{
	IsSpacePressed = true;
	CameraPtr->ZoomOutToPosition();
}

void AControllerBase::SpaceReleased()
{
	CameraPtr->ZoomInToPosition();
	IsSpacePressed = false;
}

void AControllerBase::QPressed()
{

	for (int32 i = 0; i < SelectedActors.Num(); i++) {
		if (SelectedActors[i]->DoubleJumpCounter <= 1) {
			SelectedActors[i]->LaunchCharacter(FVector(0, 0, SelectedActors[i]->JumpHeight), false, true);
			SelectedActors[i]->DoubleJumpCounter++;
		}
	}
}

void AControllerBase::WPressed()
{
	for (int32 i = 0; i < SelectedActors.Num(); i++) {

		FVector ChargeDirection = SelectedActors[i]->LastDirection * FVector(900.0f, 900.0f, 1.0f);
		SelectedActors[i]->LaunchCharacter(ChargeDirection, false, true);
		SelectedActors[i]->DoubleJumpCounter++;

	}
}


void AControllerBase::APressed()
{
	AIsPressed = true;
	for (int32 i = 0; i < SelectedActors.Num(); i++) {
		if (SelectedActors[i]->CharAnimState == Idle || SelectedActors[i]->CharAnimState == Run) {
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), SelectedActors[i]->GetActorLocation());
			SelectedActors[i]->setAnimState(Action);
		}
	}
}

void AControllerBase::AReleased()
{

	for (int32 i = 0; i < SelectedActors.Num(); i++) {
		if (SelectedActors[i]->CharAnimState == Action) {
			SelectedActors[i]->setAnimState(Idle);
		}
	}
	AIsPressed = false;
}

void AControllerBase::JumpCamera()
{
	if (CameraPtr && (IsStrgPressed || IsSpacePressed))
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		CameraPtr->JumpCamera(Hit);

	}
}


void AControllerBase::StrgPressed() {
	IsStrgPressed = true;
}

void AControllerBase::StrgReleased() {
	IsStrgPressed = false;
}

void AControllerBase::ZoomIn()
{
	if (CameraPtr && IsStrgPressed)
	{
		CameraPtr->ZoomIn();
	}
}

void AControllerBase::ZoomOut()
{
	if (CameraPtr && IsStrgPressed)
	{
		CameraPtr->ZoomOut();
	}
}

void AControllerBase::ZoomStop()
{
	if (CameraPtr)
	{
		CameraPtr->ZoomStop();
	}
}

void AControllerBase::CamLeft()
{
	if (CameraPtr && IsStrgPressed)
	{
		CameraPtr->CamLeft();
	}
}

void AControllerBase::CamRight()
{
	if (CameraPtr && IsStrgPressed)
	{
		CameraPtr->CamRight();
	}
}



void AControllerBase::ControllDirectionToMouse(ACharacterBase* SelectedActor)
{
	FVector CharacterDirectionVector = SelectedActor->GetActorForwardVector();
	FVector ActorLocation = SelectedActor->GetActorLocation();

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	float AngleDiff = SelectedActor->CalcAngle(CharacterDirectionVector, Hit.Location - ActorLocation);
	FQuat QuadRotation;

	if ((AngleDiff > 2.f && AngleDiff < 179) || (AngleDiff <= -179.f && AngleDiff > -359.f)) {
		AngleDiff > 50.f || AngleDiff < -50.f ? QuadRotation = FQuat(FRotator(0.f, -10.0f, 0.f)) : QuadRotation = FQuat(FRotator(0.f, -4.0f, 0.f));

		SelectedActor->AddActorLocalRotation(QuadRotation, false, 0, ETeleportType::None);
	}
	else if ((AngleDiff < -2.f && AngleDiff > -179.f) || (AngleDiff >= 180.f && AngleDiff < 359.f)) {
		AngleDiff > 50.f || AngleDiff < -50.f ? QuadRotation = FQuat(FRotator(0.f, 10.0f, 0.f)) : QuadRotation = FQuat(FRotator(0.f, 4.0f, 0.f));
		SelectedActor->AddActorLocalRotation(QuadRotation, false, 0, ETeleportType::None);
	}
}

void AControllerBase::ToggleLockCameraToCharacter()
{
	LockCameraToCharacter = !LockCameraToCharacter;
}

void AControllerBase::TabPressed()
{
	CameraPtr->ShowControlWidget();
}

void AControllerBase::TabReleased()
{
	CameraPtr->HideControlWidget();
}

void AControllerBase::CameraPawnForward()
{
	if (CameraPtr && IsShiftPressed) {
		CameraPtr->MoveCamForward = true;
	}
}

void AControllerBase::CameraPawnBackward()
{
	if (CameraPtr && IsShiftPressed) {
		CameraPtr->MoveCamBackward = true;
	}
}

void AControllerBase::CameraPawnLeft()
{
	if (CameraPtr && IsShiftPressed) {
		CameraPtr->MoveCamLeft = true;
	}
}

void AControllerBase::CameraPawnRight()
{
	if (CameraPtr && IsShiftPressed) {
		CameraPtr->MoveCamRight = true;
	}
}

void AControllerBase::CameraPawnForwardR()
{
	if (CameraPtr) {
		CameraPtr->MoveCamForward = false;
	}
}


void AControllerBase::CameraPawnBackwardR()
{
	if (CameraPtr) {
		CameraPtr->MoveCamBackward = false;
	}
}

void AControllerBase::CameraPawnLeftR()
{
	if (CameraPtr) {
		CameraPtr->MoveCamLeft = false;
	}
}

void AControllerBase::CameraPawnRightR()
{
	if (CameraPtr) {
		CameraPtr->MoveCamRight = false;
	}
}