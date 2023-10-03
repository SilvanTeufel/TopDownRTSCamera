// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM()
namespace CharacterData
{
	enum CharacterState
	{
		Idle     UMETA(DisplayName = "Idle"),
		Run     UMETA(DisplayName = "Run")
	};
}

UENUM()
namespace CameraData
{
	enum CameraState
	{
		UseScreenEdges     UMETA(DisplayName = "UseScreenEdges"),
		MoveWASD  UMETA(DisplayName = "MoveWASD"),
		RotateToStart  UMETA(DisplayName = "RotateToStart"),
		MoveToPosition  UMETA(DisplayName = "MoveToPosition"),
		OrbitAtPosition  UMETA(DisplayName = "OrbitAtPosition"),
		ZoomIn  UMETA(DisplayName = "ZoomIn"),
		ZoomOut  UMETA(DisplayName = "ZoomOut"),
		ScrollZoomIn  UMETA(DisplayName = "ScrollZoomIn"),
		ScrollZoomOut  UMETA(DisplayName = "ScrollZoomOut"),
		ZoomOutPosition  UMETA(DisplayName = "ZoomOutPosition"),
		ZoomInPosition  UMETA(DisplayName = "ZoomInPosition"),
		HoldRotateLeft UMETA(DisplayName = "HoldRotateLeft"),
		HoldRotateRight UMETA(DisplayName = "HoldRotateRight"),
		RotateLeft UMETA(DisplayName = "RotateLeft"),
		RotateRight UMETA(DisplayName = "RotateRight"),
		LockOnCharacter UMETA(DisplayName = "LockOnCharacter"),
		LockOnSpeaking UMETA(DisplayName = "LockOnSpeaking"),
		ZoomToNormalPosition  UMETA(DisplayName = "ZoomToNormalPosition"),
		ThirdPerson UMETA(DisplayName = "ThirdPerson"),
		ZoomToThirdPerson UMETA(DisplayName = "RotateBeforeThirdPerson"),
	};
}