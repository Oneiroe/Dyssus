// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "ColorableFactory.h"
#include "Colorable.h"
#include "Cube.h"
#include "DBarrier.h"



AActor* UColorableFactory::Instantiate(UWorld* World,
                                       UClass* ClassToSpawn,
                                       UMaterial* Material,
                                       DTypes::DCOLOR Color)
{
    if(World){
        
        FActorSpawnParameters fp;
        AActor* ActorToSpawn;
        
        //Consider IColorable interface instead of non-scalable if-else statements
        if(ClassToSpawn->IsChildOf(ACube::StaticClass())){
            
            ACube* CubeToSpawn = World->SpawnActor<ACube>(ClassToSpawn, fp);
            CubeToSpawn->setCurrentColor(Material, Color);
            
            ActorToSpawn = CubeToSpawn;
            
//        Can barriers change color? When they will, work on the following commented code
//        }else if(ClassToSpawn->IsChildOf(ADBarrier::StaticClass())){
//        
//            ADBarrier* BarrierToSpawn = World->SpawnActor<ADBarrier>(ClassToSpawn, fp);
//            
//            
//            ActorToSpawn = BarrierToSpawn;
//        
        }else{
        
            UDStaticLibrary::Print("Unkown instantiation behavior for class: " + ClassToSpawn->GetName());
            ActorToSpawn = NULL;
        
        }
        
        return ActorToSpawn;
    
    }else{
    
        UDStaticLibrary::Print("Cannot instantiate Actor of class " + ClassToSpawn->GetName());
        return NULL;
    
    }
}

void UColorableFactory::GetMaterialFromColorAndClass(UClass* targetClass, UMaterial* material, DTypes::DCOLOR color)
{
	if (targetClass == ACube::StaticClass())
	{
		if (color == DTypes::WHITE) material = whiteCubeMaterial;
		else if (color == DTypes::BLACK) material = blackCubeMaterial;
		else if (color == DTypes::YELLOW) material = yellowCubeMaterial;
		else if (color == DTypes::GREEN) material = greenCubeMaterial;
		else if (color == DTypes::RED) material = redCubeMaterial;
		else if (color == DTypes::BLUE) material = blueCubeMaterial;
		else if (color == DTypes::PURPLE) material = purpleCubeMaterial;
	}
	else if (targetClass == ADBarrier::StaticClass())
	{
		if (color == DTypes::WHITE) material = whiteBarrierMaterial;
		else if (color == DTypes::BLACK) material = blackBarrierMaterial;
		else if (color == DTypes::YELLOW) material = yellowBarrierMaterial;
		else if (color == DTypes::GREEN) material = greenBarrierMaterial;
		else if (color == DTypes::RED) material = redBarrierMaterial;
		else if (color == DTypes::BLUE) material = blueBarrierMaterial;
		else if (color == DTypes::PURPLE) material = purpleBarrierMaterial;
	}
}

bool UColorableFactory::CompareColors(AActor* a, AActor* b)
{
	if (!a->Implements<UColorable>() || !b->Implements<UColorable>()) return false;

	UMaterial* matA = (UMaterial*)(Cast<UStaticMeshComponent>(a->GetComponentByClass(UStaticMeshComponent::StaticClass())))->GetMaterial(0);
	UMaterial* matB = (UMaterial*)(Cast<UStaticMeshComponent>(b->GetComponentByClass(UStaticMeshComponent::StaticClass())))->GetMaterial(0);

	UMaterial* _matA = NULL;
	UMaterial* _matB = NULL;

	GetMaterialFromColorAndClass(a->GetActorClass(), _matA, Cast<UColorable>(a)->DColor);
	GetMaterialFromColorAndClass(b->GetActorClass(), _matB, Cast<UColorable>(b)->DColor);

	return matA->GetName() ==  _matA->GetName() && matB->GetName() == _matB->GetName();
}

