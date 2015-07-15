// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DYSSUS_API UDStaticLibrary : public UObject
{
public:
	GENERATED_UCLASS_BODY()

    // Trace a RayCast ignoring ActorToIgnore, from Start to End,
    // filling HitOut with data related to the hit
	static bool Trace(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false
		);

    // Print debug messages on the top left corner
    // of the screen. The default color fo the text is white
    static void Print(FString Message, FColor TextColor = FColor::White);
};

UENUM(BlueprintType, Category = "Gameplay")
namespace DTypes
{
	enum DCOLOR
	{
		WHITE			UMETA(DisplayName = "White"),
		BLACK			UMETA(DisplayName = "Black"),
		YELLOW			UMETA(DisplayName = "Yellow"),
		GREEN			UMETA(DisplayName = "Green"),
		RED				UMETA(DisplayName = "Red"),
		BLUE			UMETA(DisplayName = "Blue"),
		PURPLE			UMETA(DisplayName = "Purple"),
		NONE			UMETA(DisplayName = "None") // None is just a trick to get enum size, should always be left as last element
	};

}