#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrialConfigTypes.h"
#include "TrialConfigLoader.generated.h"

/**
 * Blueprint-callable helpers for loading the experiment config from a JSON
 * file on disk into an FExperimentConfig struct.
 */
UCLASS()
class UE_AMBAPPROACHAVOID_API UTrialConfigLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Reads a JSON file and parses it into an FExperimentConfig.
	 *
	 * @param FilePath  Absolute path, or relative to the project directory
	 *                  (e.g. "Configs/trials.json").
	 * @param OutConfig The parsed config (only valid if the call returns true).
	 * @return          True on success; false if the file is missing or the
	 *                  JSON is malformed (details are written to the log).
	 */
	UFUNCTION(BlueprintCallable, Category = "Trial Config")
	static bool LoadExperimentConfig(const FString& FilePath, FExperimentConfig& OutConfig);
};
