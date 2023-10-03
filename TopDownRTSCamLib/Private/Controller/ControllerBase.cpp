 // Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#include "Controller/ControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"


AControllerBase::AControllerBase() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void AControllerBase::BeginPlay() {
		HUDBase = Cast<AHUDBase>(GetHUD());
		ExtendedCameraBase = Cast<AExtendedCameraBase>(GetPawn());
		
}


void AControllerBase::SetupInputComponent() {

	Super::SetupInputComponent();

}




void AControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
	SelectedUnitCount = SelectedUnits.Num();
	//if(LeftClickIsPressed)
	//{
	//	FHitResult Hit_CPoint;
	//	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit_CPoint);
	//	HUDBase->CPoint = Hit_CPoint.Location;
	//}
	
	//FHitResult Hit;
	//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	
	FHitResult Hit_Pawn;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit_Pawn);
	/*
	if(ExtendedCameraBase)
	{
		UUnitWidgetSelector* Selector = Cast<UUnitWidgetSelector>(ExtendedCameraBase->WidgetSelector);
		if(Selector)
		{
			Selector->SetVisibleButtonCount(SelectedUnits.Num());
			Selector->SetButtonLabelCount(SelectedUnits.Num());
		}
	}*/
	
	if(LeftClickIsPressed)
	{
		//FHitResult Hit_CPoint;
		//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit_CPoint);
		//HUDBase->CPoint = Hit_Pawn.Location;
	}
		

	LockCamTick();


}


void AControllerBase::LockCamTick()
{
	if (ExtendedCameraBase && SelectedUnits.Num() && LockCameraToUnit)
		ExtendedCameraBase->LockOnUnit(SelectedUnits[0]);
}


void AControllerBase::ShiftPressed()
{
	IsShiftPressed = true;
}

void AControllerBase::ShiftReleased()
{
	IsShiftPressed = false;
}

void AControllerBase::LeftClickPressed()
{
	
	LeftClickIsPressed = true;
	
	if (AttackToggled) {
		for (int32 i = 0; i < SelectedUnits.Num(); i++)
		{
			ACharacterBase* ExtendedUnitBase = Cast<ACharacterBase>(SelectedUnits[i]);
			
			if (SelectedUnits[i] && !ExtendedUnitBase) {     
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);


				FHitResult Hit_Pawn;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit_Pawn);

				if (Hit_Pawn.bBlockingHit)
				{

						/// A-Move Units ///
						FVector RunLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
						DrawDebugSphere(GetWorld(), RunLocation, 15, 5, FColor::Green, false, 1.5, 0, 1);

				
				
				}
				
			}
			
		}
		
	}
	else {

		FHitResult Hit_IPoint;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit_IPoint);
	
		
		FHitResult Hit_Pawn;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit_Pawn);
		
		if (Hit_Pawn.bBlockingHit)
		{
			ACharacterBase* UnitBase = Cast<ACharacterBase>(Hit_Pawn.GetActor());
	
			
			if (UnitBase)
			{
				//HUDBase->SetUnitSelected(UnitBase);
			}
			else {
				HUDBase->InitialPoint = HUDBase->GetMousePos2D();
				HUDBase->bStartSelecting = true;
			}
		}
	}

}

void AControllerBase::LeftClickReleased()
{
	LeftClickIsPressed = false;
	HUDBase->bStartSelecting = false;
	SelectedUnits = HUDBase->SelectedUnits;
}
void AControllerBase::SelectUnit(int Index)
{
	for (int32 i = 0; i < SelectedUnits.Num(); i++)
	{
		if(SelectedUnits[i] && i != Index) SelectedUnits[i]->SetDeselected();
	}
	SelectedUnits.Empty();
	SelectedUnits.Add(HUDBase->SelectedUnits[Index]);

}



void AControllerBase::RightClickPressed()
{
	if (IsShiftPressed) {
		for (int32 i = 0; i < SelectedUnits.Num(); i++) {
			if (SelectedUnits[i]->CharAnimState == CharacterData::Idle || SelectedUnits[i]->CharAnimState == CharacterData::Run) {
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
				FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
				SelectedUnits[i]->MoveArray.Add(MoveLocation);
				DrawDebugSphere(GetWorld(), MoveLocation, 15, 5, FColor::Green, false, 1.5, 0, 1);
				SelectedUnits[i]->MoveEndLocation = MoveLocation;
			}
		}
	}
	else {
		for (int32 i = 0; i < SelectedUnits.Num(); i++) {
			if (SelectedUnits[i]->CharAnimState == CharacterData::Idle || SelectedUnits[i]->CharAnimState == CharacterData::Run) {
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
				FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);


				if (SelectedUnits[i]->CharAnimState == CharacterData::Idle || SelectedUnits[i]->CharAnimState == CharacterData::Run) {
					DrawDebugSphere(GetWorld(), MoveLocation, 15, 5, FColor::Green, false, 1.5, 0, 1);
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedUnits[i]->GetController(), MoveLocation);
					SelectedUnits[i]->setAnimState(CharacterData::Run);
					SelectedUnits[i]->MoveArray.Empty();
					SelectedUnits[i]->MoveArrayIterator = 0;
					SelectedUnits[i]->MoveEndLocation = MoveLocation;

				}


				SelectedUnits[i]->ForwardVector = MoveLocation;
			}
		}
	}
	
}

 void AControllerBase::RightClickReleased()
 {
	IsRightClickPressed = false;
 }


void AControllerBase::APressed()
{

}


void AControllerBase::AReleased()
{

}

void AControllerBase::SReleased()
{

}

void AControllerBase::RPressed()
{


}

void AControllerBase::FPressed()
{
	
}

void AControllerBase::CPressed()
{
	
}

 void AControllerBase::DPressed()
 {
	DIsPressed = true;
	

 }



void AControllerBase::DReleased()
{
	DIsPressedState = 1;
	DIsPressed = false;
	

}

 void AControllerBase::EPressed()
{

}

void AControllerBase::XPressed()
{

}

void AControllerBase::WPressed()
{

}

 void AControllerBase::WReleased()
 {

 }

 void AControllerBase::YPressed()
{
	
}

void AControllerBase::TPressed()
{
	
	



}


void AControllerBase::QPressed()
{
	QIsPressed = true;
}

void AControllerBase::QReleased()
{
	QIsPressed = false;
}

void AControllerBase::JumpCamera()
{
	if (ExtendedCameraBase && (IsStrgPressed || IsSpacePressed))
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		ExtendedCameraBase->JumpCamera(Hit);

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
	if (ExtendedCameraBase && IsStrgPressed)
	{
		ExtendedCameraBase->ZoomIn(1.f);
	}
}

void AControllerBase::ZoomOut()
{
	if (ExtendedCameraBase && IsStrgPressed)
	{
		ExtendedCameraBase->ZoomOut(1.f);
	}
}





void AControllerBase::AltPressed()
{
	AltIsPressed = true;
}

void AControllerBase::AltReleased()
{
	AltIsPressed = false;
}