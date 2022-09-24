// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM()
enum CharacterStatus
{
	Idle     UMETA(DisplayName = "Idle"),
	Run     UMETA(DisplayName = "Run"),
	Climb   UMETA(DisplayName = "Climb"),
	Crouch   UMETA(DisplayName = "Crouch"),
	Fire  UMETA(DisplayName = "Fire"),
	Action  UMETA(DisplayName = "Action"),
	IsHit  UMETA(DisplayName = "IsHit"),
	StartTeleport UMETA(DisplayName = "StartTeleport"),
	StopTeleport UMETA(DisplayName = "StopTeleport"),
	Dead UMETA(DisplayName = "Dead"),
};

UENUM()
enum IconColor
{
	Blue     UMETA(DisplayName = "Blue"),
	Red     UMETA(DisplayName = "Red"),
};