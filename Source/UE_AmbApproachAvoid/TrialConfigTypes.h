#pragma once

#include "CoreMinimal.h"
#include "TrialConfigTypes.generated.h"

/**
 * Landmark categories. The JSON "type" string must match one of these
 * enumerator names exactly (e.g. "Tree", "Rock", "Pit").
 */
UENUM(BlueprintType)
enum class ELandmarkType : uint8
{
	Tree,
	Rock,
	Pit
};


USTRUCT(BlueprintType)
struct FMeshPart
{
	GENERATED_BODY()

	// Lists all individual components in completed mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ComponentTag; // e.g. "Base", "Lid"

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MeshKey; // key into MeshLibrary, e.g. "SM_Oak"
};

/** One landmark to place in a trial. */
USTRUCT(BlueprintType)
struct FLandmarkConfig
{
	GENERATED_BODY()

	// Unique identifier you can reference elsewhere (e.g. from a chest).
	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FString Id;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	ELandmarkType Type = ELandmarkType::Tree;
	
	
	
	// Split into Location + Rotation (instead of a full FTransform) so the
	// JSON stays human-editable. Build the FTransform at spawn time in BP.
	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FRotator Rotation = FRotator::ZeroRotator;


	// Name to get specific mesh type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMeshPart> MeshParts;

	//Editable boolean value to apply scare property to given mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trial Config")
	int32 Scare = 0;

	//Editable selector for scare type applied to mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trial Config")
	FName ScareType = FName(TEXT("Spider"));
};

/** One treasure chest to place in a trial. */
USTRUCT(BlueprintType)
struct FChestConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FString Id;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FRotator Rotation = FRotator::ZeroRotator;

	// Optional: which landmark this chest is associated with (by Id).
	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FString LandmarkId;

	// Name to get specific chest mesh type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMeshPart> MeshParts;

	//Editable reward value associated with chest type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trial Config")
	int32 Reward = 0;
};

/** A single trial: a full set of landmarks + chests. */
USTRUCT(BlueprintType)
struct FTrialConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	FString TrialId;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	TArray<FLandmarkConfig> Landmarks;

	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	TArray<FChestConfig> Chests;
};

/** Top-level config: the ordered list of trials + experiment-wide settings. */
USTRUCT(BlueprintType)
struct FExperimentConfig
{
	GENERATED_BODY()

	// How many chests must be opened before advancing to the next trial.
	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	int32 ChestsToAdvance = 1;

	// Trials are run in this order (fixed, file-driven).
	UPROPERTY(BlueprintReadWrite, Category = "Trial Config")
	TArray<FTrialConfig> Trials;
};


