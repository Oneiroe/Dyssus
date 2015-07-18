// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "ColorableFactory.h"
#include "UnrealString.h"

ACube::ACube()
{
	CanBeDestroyed = false;

	BaseDamage = 100.f;
	DamageRadius = 20.f;
	ImpulseStrength = 15.f;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	Timeout = 2.f;
}

void ACube::OnConstruction(const FTransform& Transform)
{
	if (CanBeDestroyed) SetCubeMesh();
	else SetCubeMesh();
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

	if (!GetComponentByClass(UDestructibleComponent::StaticClass())) 
	{
		FTransform compTransform = CubeMesh->GetComponentTransform();
		RootComponent->SetWorldTransform(compTransform);
		SetCubeMesh();
	}
	
	Cast<UDestructibleComponent>(CubeMesh)->ApplyRadiusDamage(BaseDamage, HitLocation, DamageRadius, ImpulseStrength, false);

	if (!UseStartingTransformOnRespawn)
	{
		RespawnLocation = RootComponent->GetComponentLocation();
		RespawnRotation = RootComponent->GetComponentRotation();
	}

	if(Respawnable) GetWorldTimerManager().SetTimer(this, &ACube::RespawnCube, Timeout);
	else GetWorldTimerManager().SetTimer(this, &ACube::EraseCube, Timeout);
}


void ACube::RespawnCube()
{
	ACube::OnConstruction(FTransform::Identity);
	
	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
}

void ACube::SetColor(DTypes::DCOLOR dColor)
{
	DColor = dColor;

	if (CubeMesh && CubeMaterials.Num() > DColor)
	{
		Material = CubeMaterials[DColor];
		CubeMesh->SetMaterial(0, Material);
	}
}

DTypes::DCOLOR ACube::GetColor()
{
	return DColor;
}

void ACube::EraseCube()
{
	Destroy();
}

void ACube::SetCubeMesh()
{
	if (CubeMesh)
	{
		CubeMesh->UnregisterComponent();
		CubeMesh->DestroyComponent();
	}

	if (CanBeDestroyed)
	{
		CubeMesh = ConstructObject<UDestructibleComponent>(UDestructibleComponent::StaticClass(), this, TEXT("DestructibleMesh"));
		Cast<UDestructibleComponent>(CubeMesh)->SetDestructibleMesh(DMesh);
	}
	else
	{
		CubeMesh = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("StaticMesh"));
		Cast<UStaticMeshComponent>(CubeMesh)->SetStaticMesh(SMesh);
	}

	CubeMesh->OnComponentCreated();
	if (CubeMesh->bWantsInitializeComponent) CubeMesh->InitializeComponent();
	CubeMesh->RegisterComponent();

	CubeMesh->bGenerateOverlapEvents = true;

	CubeMesh->SetRelativeLocation(FVector::ZeroVector);
	CubeMesh->SetRelativeRotation(FRotator::ZeroRotator);
	CubeMesh->AttachTo(RootComponent);

	SetColor(DColor);
}