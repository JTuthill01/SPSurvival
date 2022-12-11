#include "JSONParser/JSONParser.h"
#include "JsonUtilities.h"

// Sets default values for this component's properties
UJSONParser::UJSONParser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UJSONParser::Parser(FItemData& OutItemData, TArray<FString>& OutStringPathArray, TArray<uint8>& OutEnumValueArray)
{
	/* Creates a string ref to wherever the json file(s) are */
	const FString JsonFilePath = FPaths::ProjectContentDir() + "/Json_Files/ItemDataTable.json";
	FString JsonString; /* Json converted to FString */

	FFileHelper::LoadFileToString(JsonString, *JsonFilePath); /* Remember to dereference file path */

	/* Create a json object to store the information from the json string */
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	/* The json reader is used to deserialize the json object later on */
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		/* Gets whatever "object" from the json file you choose */
		TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField(ObjectString);

		OutItemData.bIsStackable = DataObject->GetBoolField("bIsStackable");

		OutItemData.bUsesAmmo = DataObject->GetBoolField("bUsesAmmo");

		OutItemData.ItemID = DataObject->GetIntegerField("ItemID");

		OutItemData.ItemQuanity = DataObject->GetIntegerField("ItemQuanity");

		OutItemData.ItemDamage = DataObject->GetIntegerField("ItemDamage");

		OutItemData.ItemCurrentHP = DataObject->GetIntegerField("ItemCurrentHP");

		OutItemData.ItemMaxHP = DataObject->GetIntegerField("ItemMaxHP");

		OutItemData.StackSize = DataObject->GetIntegerField("StackSize");

		OutItemData.MaxAmmo = DataObject->GetIntegerField("MaxAmmo");

		OutItemData.CurrentAmmo = DataObject->GetIntegerField("CurrentAmmo");

		OutItemData.ItemName = FText::FromString(*DataObject->GetStringField("ItemName"));

		OutItemData.ItemDescription = FText::FromString(*DataObject->GetStringField("ItemDescription"));

		FString IconPath = DataObject->GetStringField("ItemIcon");

		FString ItemBasePath = DataObject->GetStringField("ItemBaseRef");

		uint8 ItemRarity = DataObject->GetIntegerField("ItemRarity");

		uint8 ItemType = DataObject->GetIntegerField("ItemType");

		uint8 ArmourType = DataObject->GetIntegerField("ArmourType");

		OutStringPathArray.Insert(IconPath, 0);
		OutStringPathArray.Insert(ItemBasePath, 1);

		OutEnumValueArray.Insert(ItemRarity, 0);
		OutEnumValueArray.Insert(ItemType, 1);
		OutEnumValueArray.Insert(ArmourType, 2);
	}
}


