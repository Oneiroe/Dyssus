// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Cube.generated.h"
#include "Destroyable.h" 
#include "Grabbable.h"

UCLASS()
class DYSSUS_API ACube : public AActor, public Destroyable, public Grabbable
{
	GENERATED_BODY()

private:
	FColor default_color;
	FColor current_color;
	bool can_change_color;
	FVector starting_position;
	FVector respawn_position;
	bool respawnable;
	bool change_color_on_respawn;
	bool change_position_on_respawn;
	Mesh mesh;

	void respawn();

public:	
	// Sets default values for this actor's properties
	ACube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Costructors
	Cube(FColor default_color, FVector starting_position);
	Cube(FColor default_color, FVector starting_position, bool respawnable, bool change_color_on_respawn, bool change_position_on_respawn);
	permanent_Cube(FColor default_color, FVector starting_position);
	permanent_Cube(FColor default_color, FVector starting_position, bool respawnable, bool change_color_on_respawn, bool change_position_on_respawn);
	
	FColor get_default_color();
	void set_default_color(FColor new_default_color);
	FColor get_current_color();
	void set_current_color(FColor new_current_color);
	bool get_can_change_color();
	void set_can_change_color(bool change_behaviour);
	FVector get_starting_position();
	void set_starting_position(FVector new_starting_position);
	FVector get_respawn_position();
	void set_respawn_position(FVector new_position);
	bool get_respawnable();
	void set_respawnable(bool change_behaviour);
	bool get_change_color_on_respawn();
	void set_change_color_on_respawn(bool change_behaviour);
	bool get_change_position_on_respawn();
	void set_change_position_on_respawn(bool change_behaviour);
	Mesh get_mesh();
	void set_mesh(Mesh new_mesh);

	void destroy(Collision_object collision);
	
};
