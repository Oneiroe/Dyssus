// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "ColorableFactory.h"
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

