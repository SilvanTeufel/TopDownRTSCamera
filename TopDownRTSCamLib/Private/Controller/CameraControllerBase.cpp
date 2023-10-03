// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.
#include "Controller/CameraControllerBase.h"


#include "Application/SlateApplicationBase.h"
#include "Widgets/SWindow.h"
#include "GenericPlatform/GenericWindow.h"

ACameraControllerBase::ACameraControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACameraControllerBase::BeginPlay()
{
	Super::BeginPlay();
	HUDBase = Cast<AHUDBase>(GetHUD());
	ExtendedCameraBase = Cast<AExtendedCameraBase>(GetPawn());
	if(ExtendedCameraBase)GetViewPortScreenSizes(ExtendedCameraBase->GetViewPortScreenSizesState);
	//if(CompassCamera)GetViewPortScreenSizes(CompassCamera->GetViewPortScreenSizesState);
	
}

void ACameraControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ACameraControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RotateCam(DeltaSeconds);
	CameraBaseMachine(DeltaSeconds);


	
	//SetResolutionTick(CompassCamera->GetViewPortScreenSizesState);
}

void ACameraControllerBase::SetResolutionTick(int x)
{
	switch (x)
	{
	case 2:
		{
		
			ExtendedCameraBase->ScreenSizeX = GSystemResolution.ResX;
			ExtendedCameraBase->ScreenSizeY = GSystemResolution.ResY;
		}
		break;
	}
}

void ACameraControllerBase::GetViewPortScreenSizes(int x)
{
	switch (x)
	{
	case 1:
		{
			GetViewportSize(ExtendedCameraBase->ScreenSizeX, ExtendedCameraBase->ScreenSizeY);
		}
		break;
	case 2:
		{
		
			ExtendedCameraBase->ScreenSizeX = GSystemResolution.ResX;
			ExtendedCameraBase->ScreenSizeY = GSystemResolution.ResY;
		}
		break;
	}
}


FVector ACameraControllerBase::GetCameraPanDirection() {
	float MousePosX = 0;
	float MousePosY = 0;
	float CamDirectionX = 0;
	float CamDirectionY = 0;

	GetMousePosition(MousePosX, MousePosY);
	
	const float CosYaw = FMath::Cos(ExtendedCameraBase->SpringArmRotator.Yaw*PI/180);
	const float SinYaw = FMath::Sin(ExtendedCameraBase->SpringArmRotator.Yaw*PI/180);
	
	if (MousePosX <= ExtendedCameraBase->Margin)
	{
		CamDirectionY = -CosYaw;
		CamDirectionX = SinYaw;
	}
	if (MousePosY <= ExtendedCameraBase->Margin)
	{
		CamDirectionX = CosYaw;
		CamDirectionY = SinYaw;
	}
	if (MousePosX >= ExtendedCameraBase->ScreenSizeX - ExtendedCameraBase->Margin)
	{
		CamDirectionY = CosYaw;
		CamDirectionX = -SinYaw;
	}
	if (MousePosY >= ExtendedCameraBase->ScreenSizeY - ExtendedCameraBase->Margin)
	{
		CamDirectionX = -CosYaw;
		CamDirectionY = -SinYaw;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}

void ACameraControllerBase::RotateCam(float DeltaTime)
{
	if(!MiddleMouseIsPressed) return;
	
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);

	if(ExtendedCameraBase)
	{
		float MouseX, MouseY;
		if (GetMousePosition(MouseX, MouseY))
		{
			ExtendedCameraBase->RotateFree(FVector(MouseX, MouseY, 0.f));
		}
	}
}

void ACameraControllerBase::CameraBaseMachine(float DeltaTime)
{
	//HUDBase->MoveActorsThroughWayPoints(MovingActors);

	if(!ExtendedCameraBase) return;
	
	if (ExtendedCameraBase && SelectedUnits.Num() && LockCameraToUnit)
	{
		ExtendedCameraBase->LockOnUnit(SelectedUnits[0]);
		LockCameraToCharacter = true;
	}

	if(ExtendedCameraBase->BlockControls) return;
	
	FVector PanDirection = GetCameraPanDirection();
	
	if(ExtendedCameraBase)
	{
		switch (ExtendedCameraBase->GetCameraState())
		{
		case CameraData::UseScreenEdges:
			{
				//UE_LOG(LogTemp, Warning, TEXT("UseScreenEdges"));
				if(!ExtendedCameraBase->DisableEdgeScrolling)
					ExtendedCameraBase->PanMoveCamera(FVector(ExtendedCameraBase->Inverter*PanDirection*ExtendedCameraBase->EdgeScrollCamSpeed));
				
				if(AIsPressedState || DIsPressedState || WIsPressedState || SIsPressedState) ExtendedCameraBase->SetCameraState(CameraData::MoveWASD);
				else if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
			}
			break;
		case CameraData::MoveWASD:
			{
				//UE_LOG(LogTemp, Warning, TEXT("MoveWASD"));
				LockCameraToCharacter = false;
				
				if(AIsPressedState == 1) ExtendedCameraBase->MoveCamToLeft(DeltaTime);
				if(DIsPressedState == 1) ExtendedCameraBase->MoveCamToRight(DeltaTime);
				if(WIsPressedState == 1) ExtendedCameraBase->MoveCamToForward(DeltaTime);
				if(SIsPressedState == 1) ExtendedCameraBase->MoveCamToBackward(DeltaTime);

				if(AIsPressedState == 2) ExtendedCameraBase->MoveCamToLeft(DeltaTime, true);
				if(DIsPressedState == 2) ExtendedCameraBase->MoveCamToRight(DeltaTime, true);
				if(WIsPressedState == 2) ExtendedCameraBase->MoveCamToForward(DeltaTime, true);
				if(SIsPressedState == 2) ExtendedCameraBase->MoveCamToBackward(DeltaTime, true);

				if(ExtendedCameraBase->CurrentCamSpeed.X == 0.0f && WIsPressedState == 2) WIsPressedState = 0;
				if(ExtendedCameraBase->CurrentCamSpeed.X == 0.0f && SIsPressedState == 2) SIsPressedState = 0;
				if(ExtendedCameraBase->CurrentCamSpeed.Y == 0.0f && DIsPressedState == 2) DIsPressedState = 0;
				if(ExtendedCameraBase->CurrentCamSpeed.Y == 0.0f && AIsPressedState == 2) AIsPressedState = 0;

				if(CamIsRotatingLeft) ExtendedCameraBase->RotateCamLeft(ExtendedCameraBase->AddCamRotation, !CamIsRotatingLeft);
				if(CamIsRotatingRight) ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation, !CamIsRotatingRight);
				
				if(ExtendedCameraBase->CurrentCamSpeed.X == 0.0f &&
					ExtendedCameraBase->CurrentCamSpeed.Y == 0.0f &&
					ExtendedCameraBase->CurrentRotationValue == 0.0f)
				{
					ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}

			}
			break;
		case CameraData::ZoomIn:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomIn"));
				if(CamIsZoomingInState == 1)ExtendedCameraBase->ZoomIn(1.f);
				if(CamIsZoomingInState == 2)ExtendedCameraBase->ZoomIn(1.f, true);
				if(CamIsZoomingInState != 1 && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f) CamIsZoomingInState = 0;

				if(CamIsZoomingInState != 1 && CamIsZoomingOutState == 1)ExtendedCameraBase->SetCameraState(CameraData::ZoomOut);
				
				if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				else if(!CamIsZoomingInState) ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				
			}
			break;
		case CameraData::ZoomOut:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomOut"));
				if(CamIsZoomingOutState == 1)ExtendedCameraBase->ZoomOut(1.f);
				if(CamIsZoomingOutState == 2)ExtendedCameraBase->ZoomOut(1.f, true);
				if(CamIsZoomingOutState != 1 && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f) CamIsZoomingOutState = 0;

				if(CamIsZoomingOutState != 1 && CamIsZoomingInState == 1)ExtendedCameraBase->SetCameraState(CameraData::ZoomIn);
				
				if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				else if(!CamIsZoomingOutState) ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
			}
			break;
		case CameraData::ScrollZoomIn:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ScrollZoomIn %f"), ScrollZoomCount);
				//CameraBase->ZoomIn(0.5f);
				if(ScrollZoomCount > 0.f)
				{
					ExtendedCameraBase->ZoomIn(1.f);
					ExtendedCameraBase->RotateSpringArm();
					SetCameraZDistance(0);
				}
				if(ScrollZoomCount <= 0.f)
				{
					ExtendedCameraBase->ZoomIn(1.f, true);
					ExtendedCameraBase->RotateSpringArm();
					SetCameraZDistance(0);
				}
				
				if(ScrollZoomCount > 0.f)
					ScrollZoomCount -= 0.25f;
				
				if(ScrollZoomCount < 0.f && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f)
				{
					ExtendedCameraBase->SetCameraState(CameraData::ScrollZoomOut);
				}else if(ScrollZoomCount == 0.f && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f)
				{
					if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
					else if(!CamIsZoomingInState) ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}

				if(LockCameraToCharacter)
				{
					LockCamToCharacter(0);
					//CameraBase->SetCameraState(CameraData::LockOnCharacter);
					//CameraBase->CameraDistanceToCharacter = (CameraBase->GetActorLocation().Z - SelectedUnits[0]->GetActorLocation().Z);
				}
			}
			break;
		case CameraData::ScrollZoomOut:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ScrollZoomOut %f"), ScrollZoomCount);
	
				if(ScrollZoomCount < 0.f)
				{
					ExtendedCameraBase->ZoomOut(1.f);
					ExtendedCameraBase->RotateSpringArm(true);
					SetCameraZDistance(0);
				}
				if(ScrollZoomCount >= 0.f)
				{
					ExtendedCameraBase->ZoomOut(1.f, true);
					ExtendedCameraBase->RotateSpringArm(true);
					SetCameraZDistance(0);
				}
					
				if(ScrollZoomCount < 0.f)
					ScrollZoomCount += 0.25f;
				
		
				if(ScrollZoomCount > 0.f && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f)
				{
					ExtendedCameraBase->SetCameraState(CameraData::ScrollZoomIn);
				}else if(ScrollZoomCount == 0.f && ExtendedCameraBase->CurrentCamSpeed.Z == 0.f)
				{
					if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
					else if(!CamIsZoomingOutState) ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}

				if(LockCameraToCharacter)
				{
					LockCamToCharacter(0);
				}
			}
			break;
		case CameraData::ZoomOutPosition:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomOutPosition"));
				ZoomOutToPosition = true;
				ExtendedCameraBase->ZoomOutToPosition(ExtendedCameraBase->ZoomOutPosition);
				ExtendedCameraBase->RotateSpringArm(true);
				ExtendedCameraBase->RotateSpringArm(true);
			}
			break;
		case CameraData::ZoomInPosition:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomInPosition"));
				
				ZoomOutToPosition = false;
				ZoomInToPosition = true;
				
				if(ExtendedCameraBase->ZoomInToPosition(ExtendedCameraBase->ZoomPosition))
				{
					SetCameraZDistance(0);
					ZoomInToPosition = false;
					if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
					else ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}
			}
			break;
		case CameraData::HoldRotateLeft:
			{
				//UE_LOG(LogTemp, Warning, TEXT("HoldRotateLeft"));
				CamIsRotatingRight = false;
				if(LockCameraToCharacter)
				{
					ExtendedCameraBase->CurrentRotationValue = 0.f;
					ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				}
				
				ExtendedCameraBase->RotateCamLeft(ExtendedCameraBase->AddCamRotation, !CamIsRotatingLeft); // CameraBase->AddCamRotation
				
				if(!CamIsRotatingLeft && ExtendedCameraBase->CurrentRotationValue == 0.f)
				{
					ExtendedCameraBase->CurrentRotationValue = 0.f;
					ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}
				
			}
			break;
		case CameraData::HoldRotateRight:
			{

				//UE_LOG(LogTemp, Warning, TEXT("HoldRotateRight"));
				CamIsRotatingLeft = false;

				if(LockCameraToCharacter)
				{
					ExtendedCameraBase->CurrentRotationValue = 0.f;
					ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				}
				
				ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation, !CamIsRotatingRight); // CameraBase->AddCamRotation
		
				if(!CamIsRotatingRight  && ExtendedCameraBase->CurrentRotationValue == 0.f)
				{
					ExtendedCameraBase->CurrentRotationValue = 0.f;
					ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}
				
			}
			break;
		case CameraData::RotateLeft:
			{
				CamIsRotatingRight = false;
				CamIsRotatingLeft = true;
				//UE_LOG(LogTemp, Warning, TEXT("RotateLeft"));

				if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				
				if(ExtendedCameraBase->RotateCamLeft(ExtendedCameraBase->AddCamRotation)) // CameraBase->AddCamRotation
				{
					CamIsRotatingLeft = false;
					if(!LockCameraToCharacter)ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}
				
			}
			break;
		case CameraData::RotateRight:
			{
				CamIsRotatingLeft = false;
				CamIsRotatingRight = true;
				//UE_LOG(LogTemp, Warning, TEXT("RotateRight"));

				if(LockCameraToCharacter) ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
				if(ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation)) // CameraBase->AddCamRotation
				{
					CamIsRotatingRight = false;
					if(!LockCameraToCharacter)ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
				}
				
			}
			break;
		case CameraData::LockOnCharacter:
			{
				//UE_LOG(LogTemp, Warning, TEXT("LockOnCharacter"));
				LockCamToCharacter(0);
			}
			break;
		case CameraData::ZoomToNormalPosition:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomToNormalPosition"));
				
				if(ExtendedCameraBase->ZoomOutToPosition(ExtendedCameraBase->ZoomPosition))
				{
					if(ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation))
					{
						CamIsRotatingRight = false;
						CamIsRotatingLeft = false;
						if(!LockCameraToCharacter)ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
						else ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
					}
				};
			}
			break;
		case CameraData::ZoomToThirdPerson:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ZoomToThirdPerson"));
				
				if( SelectedUnits.Num())
				{
					FVector SelectedActorLocation = SelectedUnits[0]->GetActorLocation();
				
					ExtendedCameraBase->LockOnUnit(SelectedUnits[0]);
					if (!ExtendedCameraBase->IsCameraInAngle())
					{
						ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation);
					}else if(ExtendedCameraBase->ZoomInToThirdPerson(SelectedActorLocation))
					{
						LockCameraToCharacter = false;
						ExtendedCameraBase->CameraDistanceToCharacter = (ExtendedCameraBase->GetActorLocation().Z - SelectedUnits[0]->GetActorLocation().Z);
						ExtendedCameraBase->SetCameraState(CameraData::ThirdPerson);
					}
		
				}
			}
			break;
		case CameraData::ThirdPerson:
			{
				//UE_LOG(LogTemp, Warning, TEXT("ThirdPerson"));
				if( SelectedUnits.Num())
				{
					float YawActor = SelectedUnits[0]->GetActorRotation().Yaw;
					float YawCamera = ExtendedCameraBase->GetActorRotation().Yaw;
	
					ExtendedCameraBase->LockOnUnit(SelectedUnits[0]);
					
					if(YawCamera-YawActor < -90)
						ExtendedCameraBase->RotateCamRightTo(YawActor, ExtendedCameraBase->AddCamRotation/3);
					else if(YawCamera-YawActor > 90)
						ExtendedCameraBase->RotateCamRightTo(YawActor, ExtendedCameraBase->AddCamRotation/3);
					else if(YawCamera-YawActor < -25)
						ExtendedCameraBase->RotateCamLeftTo(YawActor, ExtendedCameraBase->AddCamRotation/3);
					else if(YawCamera-YawActor > 25)
						ExtendedCameraBase->RotateCamRightTo(YawActor, ExtendedCameraBase->AddCamRotation/3);
					
					//LockZDistanceToCharacter();
					
				}
			}
			break;
		default:
			{
				//UE_LOG(LogTemp, Warning, TEXT("default"));
				ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
			}
			break;
		}
	}
}

void ACameraControllerBase::SetCameraZDistance(int Index)
{
	if(SelectedUnits.Num() && SelectedUnits[Index])
	{
		float Distance = (ExtendedCameraBase->GetActorLocation().Z - SelectedUnits[0]->GetActorLocation().Z);

		if(Distance >= 50.f)
		{
			ExtendedCameraBase->CameraDistanceToCharacter = Distance;
			
		}else
		{
			ExtendedCameraBase->CameraDistanceToCharacter = 50.f;
		}
	}
}

void ACameraControllerBase::ToggleLockCamToCharacter()
{
	if(IsStrgPressed)
	{
		LockCameraToCharacter = !LockCameraToCharacter;
	
		if(LockCameraToCharacter)
			ExtendedCameraBase->SetCameraState(CameraData::LockOnCharacter);
		else
		{
			ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
		}
	}
}
void ACameraControllerBase::UnlockCamFromCharacter()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit)
	{
		ACharacterBase* CharacterFound = Cast<ACharacterBase>(Hit.GetActor());

		if(!CharacterFound){
			ExtendedCameraBase->SetCameraState(CameraData::UseScreenEdges);
			LockCameraToCharacter = false;
		}
	}
	
}


void ACameraControllerBase::LockCamToSpecificUnit(ACharacterBase* SUnit)
{
		LockCameraToCharacter = !LockCameraToCharacter;
		ExtendedCameraBase->SetCameraState(CameraData::ZoomInPosition);
}

void ACameraControllerBase::LockCamToCharacter(int Index)
{
	if( SelectedUnits.Num() && SelectedUnits[Index])
	{
		FVector SelectedActorLocation = SelectedUnits[Index]->GetActorLocation();
		
		ExtendedCameraBase->LockOnUnit(SelectedUnits[Index]);

		if(ScrollZoomCount > 0.f)
		{
			ExtendedCameraBase->SetCameraState(CameraData::ScrollZoomIn);
		}else if(ScrollZoomCount < 0.f)
		{
			ExtendedCameraBase->SetCameraState(CameraData::ScrollZoomOut);
		}
		
		if(CamIsRotatingRight)
		{
			CamIsRotatingLeft = false;
			ExtendedCameraBase->RotateCamRight(ExtendedCameraBase->AddCamRotation); // CameraBase->AddCamRotation
		}
		
		if(CamIsRotatingLeft)
		{
			CamIsRotatingRight = false;
			ExtendedCameraBase->RotateCamLeft(ExtendedCameraBase->AddCamRotation); // CameraBase->AddCamRotation
		}
	}else
	{
		LockCameraToCharacter = !LockCameraToCharacter;
		ExtendedCameraBase->SetCameraState(CameraData::ZoomInPosition);
	}
}

void ACameraControllerBase::LockZDistanceToCharacter()
{
	if(ZoomInToPosition == false &&
		ZoomOutToPosition == false &&
		CamIsZoomingInState == 0 &&
		CamIsZoomingOutState == 0 &&
		ExtendedCameraBase &&
		SelectedUnits.Num())
	{
		
		const FVector SelectedActorLocation = SelectedUnits[0]->GetActorLocation();
		const FVector CameraBaseLocation = ExtendedCameraBase->GetActorLocation();
		
		const float NewCameraDistanceToCharacter = (CameraBaseLocation.Z - SelectedActorLocation.Z);
		float ZChange = ExtendedCameraBase->CameraDistanceToCharacter - NewCameraDistanceToCharacter;
		
		const float CosYaw = FMath::Cos(ExtendedCameraBase->SpringArmRotator.Yaw*PI/180);
		const float SinYaw = FMath::Sin(ExtendedCameraBase->SpringArmRotator.Yaw*PI/180);
		const FVector NewPawnLocation = FVector(SelectedActorLocation.X - ExtendedCameraBase->CameraDistanceToCharacter * 0.7*CosYaw, SelectedActorLocation.Y - ExtendedCameraBase->CameraDistanceToCharacter * 0.7*SinYaw, CameraBaseLocation.Z+ZChange);

		ExtendedCameraBase->SetActorLocation(NewPawnLocation);
		ExtendedCameraBase->CameraDistanceToCharacter = (ExtendedCameraBase->GetActorLocation().Z - SelectedUnits[0]->GetActorLocation().Z);
	}
}
