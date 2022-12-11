#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/Items/Str_Items.h"
#include "JSONParser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UJSONParser : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJSONParser();

public:
	FORCEINLINE void SetObjectData(FString InObjectString) { ObjectString = InObjectString; }

public:
	void Parser(FItemData& OutItemData, TArray<FString>& OutStringPathArray, TArray<uint8>& OutEnumValueArray);

private:
	FString ObjectString;
};
