// Copyright 2021 Yoshito Nakaue. All rights reserved.


#include "LevelManageComponent.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULevelManageComponent::ULevelManageComponent()
	: LoadingNum(0)
{
	PrimaryComponentTick.bCanEverTick = true;

	lai.CallbackTarget = this;
	lai.ExecutionFunction = "CompleteLoading";
	lai_UUID = 0;
	lai.Linkage = 0;
}

// Called when the game starts
void ULevelManageComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadedLevels.AddUnique(FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

// Called every frame
void ULevelManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Load one level
void ULevelManageComponent::LoadLevel(const FName& Level)
{
	if (!LoadedLevels.Contains(Level))
	{
		++LoadingNum;
		++lai_UUID;
		lai.UUID = lai_UUID;
		LatentActionInfo.Add(lai);
		UGameplayStatics::LoadStreamLevel(this, Level, true, false, LatentActionInfo.Last());
	}
	LoadedLevels.AddUnique(Level);
}

// Load multiple levels
void ULevelManageComponent::LoadLevels(const TArray<FName> Levels)
{
	for (FName level : Levels)
	{
		LoadLevel(level);
	}
}

// Unload one level
void ULevelManageComponent::UnloadLevel(const FName& Level)
{
	if (LoadedLevels.Contains(Level))
	{
		++LoadingNum;
		++lai_UUID;
		lai.UUID = lai_UUID;
		LatentActionInfo.Add(lai);
		UGameplayStatics::UnloadStreamLevel(this, Level, LatentActionInfo.Last(), false);
		LoadedLevels.Remove(Level);
	}
}

// Unload multiple levels
void ULevelManageComponent::UnloadLevels(const TArray<FName> Levels)
{
	for (FName level : Levels)
	{
		UnloadLevel(level);
	}
}

