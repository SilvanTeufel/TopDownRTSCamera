// Copyright 2022 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#include "Controller/Input/AssetManagerBase.h"
#include "Controller/Input/GameplayTags.h"

UAssetManagerBase::UAssetManagerBase()
{

}

UAssetManagerBase& UAssetManagerBase::Get()
{

	/*
	check(GEngine);
	
	UAssetManagerBase* MyAssetManager = Cast<UAssetManagerBase>(GEngine->AssetManager);
	return *MyAssetManager;
	*/
	
	UAssetManager& AssetManager = UAssetManager::Get();
	return static_cast<UAssetManagerBase&>(AssetManager);
}

void UAssetManagerBase::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FGameplayTags::InitializeNativeTags();
}