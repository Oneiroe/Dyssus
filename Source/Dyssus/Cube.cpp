// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "ColorableFactory.h"
#include "UnrealString.h"

ACube::ACube()
{
	BaseDamage = 100.f;
	DamageRadius = 20.f;
	ImpulseStrength = 15.f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	SetColor(DColor);

	Timeout = 2.f;

	HasDM = false;
}

void ACube::OnConstruction(const FTransform& Transform)
{
	if (HasDM)
	{
		if (StaticMesh)
		{
			StaticMesh->UnregisterComponent();
			StaticMesh->DestroyComponent();
		}

		DestructibleMesh = ConstructObject<UDestructibleComponent>(UDestructibleComponent::StaticClass(), this, TEXT("DestructibleMesh"));

		DestructibleMesh->OnComponentCreated();
		if (DestructibleMesh->bWantsInitializeComponent) DestructibleMesh->InitializeComponent();
		DestructibleMesh->RegisterComponent();

		DestructibleMesh->SetWorldTransform(Transform);

		SetRootComponent(DestructibleMesh);
		
		DestructibleMesh->SetDestructibleMesh(DMesh);
		SetColor(DColor);

		SetLifeSpan(Timeout);
	}
	else StaticMesh->SetStaticMesh(SMesh);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = RootComponent->GetComponentTransform().GetLocation();
	StartingRotation = RootComponent->GetComponentTransform().GetRotation().Rotator();

	if (UseStartingTransformOnRespawn == true)
	{
		RespawnLocation = StartingLocation;
		RespawnRotation = StartingRotation;
	}
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TEnumAsByte<DTypes::DCOLOR> ACube::GetDefaultColor()
{
	return DDefaultColor;
}

void ACube::SetDefaultColor(DTypes::DCOLOR color)
{
	DDefaultColor = color;
}

void ACube::InterfacedDestroy()
{
	this->Destroy();

	if (Respawnable) RespawnCube();
}

void ACube::InterfacedDestroy(FVector HitLocation, FVector NormalImpulse)
{
	if (!CanBeDestroyed) return;

	const FVector newLocation = GetActorLocation();
	const FRotator newRotation = GetActorRotation();
	const FTransform newTransform = GetTransform();

	ACube* cube = GetWorld()->SpawnActorDeferred<ACube>(ACube::StaticClass(), newLocation, newRotation);
	
	cube->HasDM = true;
	cube->SMesh = SMesh;
	cube->DMesh = DMesh;
	cube->BaseDamage = BaseDamage;
	cube->DamageRadius = DamageRadius;
	cube->ImpulseStrength = ImpulseStrength;
	
	cube->FinishSpawning(newTransform);
	cube->DestructibleMesh->ApplyRadiusDamage(BaseDamage, HitLocation, DamageRadius, ImpulseStrength, false);

	if (!UseStartingTransformOnRespawn)
	{
		RespawnLocation = RootComponent->GetComponentLocation();
		RespawnRotation = RootComponent->GetComponentRotation();
	}

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetVisibility(false);

	if(Respawnable) GetWorldTimerManager().SetTimer(this, &ACube::RespawnCube, Timeout);
	else Destroy();
}


void ACube::RespawnCube()
{
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetVisibility(true);

	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
}

void ACube::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;

	if (CubeMaterials.Num() > DColor)
	{
		Material = CubeMaterials[DColor];
		if(HasDM) DestructibleMesh->SetMaterial(0, Material);
		else StaticMesh->SetMaterial(0, Material);
	}
}

DTypes::DCOLOR ACube::GetColor()
{
	return DColor;
}