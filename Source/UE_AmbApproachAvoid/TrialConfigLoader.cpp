#include "TrialConfigLoader.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

bool UTrialConfigLoader::LoadExperimentConfig(const FString& FilePath, FExperimentConfig& OutConfig)
{
	// Allow either an absolute path or one relative to the project directory.
	FString ResolvedPath = FilePath;
	if (FPaths::IsRelative(ResolvedPath))
	{
		ResolvedPath = FPaths::Combine(FPaths::ProjectDir(), ResolvedPath);
	}

	// Read the raw text off disk.
	FString JsonRaw;
	if (!FFileHelper::LoadFileToString(JsonRaw, *ResolvedPath))
	{
		UE_LOG(LogTemp, Error,
			TEXT("[TrialConfig] Could not read file: %s"), *ResolvedPath);
		return false;
	}

	// Deserialize directly into the struct. Field matching is case-insensitive,
	// so JSON can use camelCase while the C++ members are PascalCase.
	// CheckFlags = 0, SkipFlags = 0 (Transient properties are skipped by default).
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(JsonRaw, &OutConfig, 0, 0))
	{
		UE_LOG(LogTemp, Error,
			TEXT("[TrialConfig] Failed to parse JSON: %s"), *ResolvedPath);
		return false;
	}

	UE_LOG(LogTemp, Log,
		TEXT("[TrialConfig] Loaded %d trial(s) from %s"),
		OutConfig.Trials.Num(), *ResolvedPath);
	return true;
}
