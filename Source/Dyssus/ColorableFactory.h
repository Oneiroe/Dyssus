// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DStaticLibrary.h"
#include "ColorableFactory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DYSSUS_API UColorableFactory : public UBlueprintFunctionLibrary
{

public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> BarrierMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	TArray<UMaterial*> CubeMaterials;

	UFUNCTION(BlueprintCallable, Category = Colors)
    AActor* Instantiate(UWorld* World,
                               UClass* ClassToSpawn,
                               UMaterial* Material,
                               DTypes::DCOLOR dColor);

	UFUNCTION(BlueprintCallable, Category = Colors)
	void GetMaterialFromColorAndClass(UClass* targetClass, 
								UMaterial* material, 
								DTypes::DCOLOR dColor);

	UFUNCTION(BlueprintCallable, Category = Colors)
	bool CompareColors(AActor* a, AActor* b);	
};
