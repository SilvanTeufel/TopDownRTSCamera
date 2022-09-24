// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.


#include "Hud/HUDBase.h"
#include "Blueprint/UserWidget.h"
#include "DrawDebugHelpers.h"


void AHUDBase::DrawHUD()
{
	FVector2D LineCenterPointA;
	FVector2D LineCenterPointB;
	FVector2D InitialSelectionPoint;
	FVector2D CurrentSelectionPoint;

	if (bStartSelecting) {

		for (int32 i = 0; i < FoundActors.Num(); i++) {
			FoundActors[i]->SetDeselected();
		}

		FoundActors.Empty();
		CurrentPoint = GetMousePos2D();

		if (abs(InitialPoint.X - CurrentPoint.X) >= 2) {

			DrawRect(FLinearColor(0, 0, 1, .15f),
				InitialPoint.X,
				InitialPoint.Y,
				CurrentPoint.X - InitialPoint.X,
				CurrentPoint.Y - InitialPoint.Y);

			float LengthLineA = abs(InitialPoint.Y - CurrentPoint.Y);
			float LengthLineB = abs(InitialPoint.X - CurrentPoint.X);

			if (InitialPoint.Y < CurrentPoint.Y && InitialPoint.X < CurrentPoint.X) {
				LineCenterPointA.X = InitialPoint.X;
				LineCenterPointB.Y = CurrentPoint.Y;

				LineCenterPointA.Y = InitialPoint.Y + (LengthLineA / 2);
				LineCenterPointB.X = CurrentPoint.X - (LengthLineB / 2);

				InitialSelectionPoint.X = LineCenterPointB.X - ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				InitialSelectionPoint.Y = LineCenterPointA.Y - ((LengthLineA * RectangleScaleSelectionFactor) / 2);

				CurrentSelectionPoint.X = LineCenterPointB.X + ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				CurrentSelectionPoint.Y = LineCenterPointA.Y + ((LengthLineA * RectangleScaleSelectionFactor) / 2);

			}
			else if (InitialPoint.Y < CurrentPoint.Y && InitialPoint.X > CurrentPoint.X) {

				LineCenterPointA.X = InitialPoint.X;
				LineCenterPointB.Y = CurrentPoint.Y;

				LineCenterPointA.Y = InitialPoint.Y + (LengthLineA / 2);
				LineCenterPointB.X = CurrentPoint.X + (LengthLineB / 2);

				InitialSelectionPoint.X = LineCenterPointB.X + ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				InitialSelectionPoint.Y = LineCenterPointA.Y - ((LengthLineA * RectangleScaleSelectionFactor) / 2);

				CurrentSelectionPoint.X = LineCenterPointB.X - ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				CurrentSelectionPoint.Y = LineCenterPointA.Y + ((LengthLineA * RectangleScaleSelectionFactor) / 2);

			}
			else if (InitialPoint.Y > CurrentPoint.Y && InitialPoint.X < CurrentPoint.X) {
				LineCenterPointA.X = InitialPoint.X;
				LineCenterPointB.Y = CurrentPoint.Y;

				LineCenterPointA.Y = InitialPoint.Y - (LengthLineA / 2);
				LineCenterPointB.X = CurrentPoint.X - (LengthLineB / 2);

				InitialSelectionPoint.X = LineCenterPointB.X - ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				InitialSelectionPoint.Y = LineCenterPointA.Y - ((LengthLineA * RectangleScaleSelectionFactor) / 2);

				CurrentSelectionPoint.X = LineCenterPointB.X + ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				CurrentSelectionPoint.Y = LineCenterPointA.Y + ((LengthLineA * RectangleScaleSelectionFactor) / 2);
			}
			else if (InitialPoint.Y > CurrentPoint.Y && InitialPoint.X > CurrentPoint.X) {
				LineCenterPointA.X = InitialPoint.X;
				LineCenterPointB.Y = CurrentPoint.Y;

				LineCenterPointA.Y = InitialPoint.Y - (LengthLineA / 2);
				LineCenterPointB.X = CurrentPoint.X + (LengthLineB / 2);

				InitialSelectionPoint.X = LineCenterPointB.X + ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				InitialSelectionPoint.Y = LineCenterPointA.Y - ((LengthLineA * RectangleScaleSelectionFactor) / 2);

				CurrentSelectionPoint.X = LineCenterPointB.X - ((LengthLineB * RectangleScaleSelectionFactor) / 2);
				CurrentSelectionPoint.Y = LineCenterPointA.Y + ((LengthLineA * RectangleScaleSelectionFactor) / 2);
			}


			DrawRect(FLinearColor(0, 1, 0, .15f),
				InitialSelectionPoint.X,
				InitialSelectionPoint.Y,
				CurrentSelectionPoint.X - InitialSelectionPoint.X,
				CurrentSelectionPoint.Y - InitialSelectionPoint.Y);

			GetActorsInSelectionRectangle<ACharacterBase>(InitialSelectionPoint, CurrentSelectionPoint, FoundActors, false, false);

			for (int32 i = 0; i < FoundActors.Num(); i++) {
				FoundActors[i]->SetSelected();

			}
		}

	}

}

void AHUDBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


FVector2D AHUDBase::GetMousePos2D()
{
	float PosX;
	float PosY;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}

void AHUDBase::AimToMouse()
{
	float PosX;
	float PosY;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	FVector Start;
	FVector End;

	for (int32 i = 0; i < FoundActors.Num(); i++) {
		Start = FoundActors[i]->GetActorLocation();
		End = FVector(Start.Z, PosX, PosY);
		DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);
	}

}


void AHUDBase::MoveActorsThroughWayPoints(TArray <ACharacterBase*> Actors)
{
	int32 z = 0;

	for (int32 i = 0; i < Actors.Num(); i++) {

		if (Actors[i]->MoveArray.Num()) {
			FVector CharacterPosition = Actors[i]->GetActorLocation();
			if (CharacterPosition.Equals(Actors[i]->MoveArray[Actors[i]->MoveArrayIterator], 100)) {

				Actors[i]->MoveArrayIterator++;
				if (Actors[i]->MoveArrayIterator < Actors[i]->MoveArray.Num()) {
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(Actors[i]->GetController(), Actors[i]->MoveArray[Actors[i]->MoveArrayIterator]);
					Actors[i]->setAnimState(Run);
				}
				else {
					Actors[i]->MoveArray.Empty();
					Actors[i]->MoveArrayIterator = 0;
				}
			}
		}


	}
}


void AHUDBase::StartMovingActors(TArray<ACharacterBase*> Actors)
{
	for (int32 i = 0; i < Actors.Num(); i++) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Actors[i]->GetController(), Actors[i]->MoveArray[0]);
		Actors[i]->setAnimState(Run);
	}
}

void AHUDBase::setZeroActor(ACharacterBase* Actor)
{
	for (int32 i = 0; i < FoundActors.Num(); i++) {
		FoundActors[i]->SetDeselected();
	}

	FoundActors.Empty();
	FoundActors.Add(Actor);

	for (int32 i = 0; i < FoundActors.Num(); i++) {
		FoundActors[i]->SetSelected();
	}
}
