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

	// Barrier materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* whiteBarrierMaterial;
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* blackBarrierMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* yellowBarrierMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* greenBarrierMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* redBarrierMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* blueBarrierMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* purpleBarrierMaterial;

	// Cube materials
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* whiteCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* blackCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* yellowCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* greenCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* redCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* blueCubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colors)
	UMaterial* purpleCubeMaterial;

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
