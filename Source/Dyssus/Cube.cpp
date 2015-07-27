// Fill out your copyright notice in the Description page of Project Settings.

#include "Dyssus.h"
#include "Cube.h"
#include "ColorableFactory.h"
#include "UnrealString.h"

ACube::ACube()
{
	// Parameters driving cube explosion -- we may consider tune these depending on projectile speed
	BaseDamage = 100.f;
	DamageRadius = 20.f;
	ImpulseStrength = 15.f;

	DColor = DDefaultColor;

	// Respawn timeout
	Timeout = 2.f;

	// Whether or not this cube has a Destructible Mesh Component
	HasDM = false;
}

void ACube::OnConstruction(const FTransform& Transform)
{
	// Initialize component with Destructible Mesh as root
	if (HasDM && !DestructibleMesh)
	{
		DestructibleMesh = ConstructObject<UDestructibleComponent>(UDestructibleComponent::StaticClass(), this, TEXT("DestructibleMesh"));
		DestructibleMesh->OnComponentCreated();
		if (DestructibleMesh->bWantsInitializeComponent) DestructibleMesh->InitializeComponent();
		DestructibleMesh->RegisterComponent();
		SetRootComponent(DestructibleMesh);
		DestructibleMesh->SetWorldTransform(Transform);
		DestructibleMesh->SetDestructibleMesh(DMesh);

		SetLifeSpan(Timeout);
	}
	// Or with Static Mesh
	else if (!StaticMesh)
	{
		StaticMesh = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, TEXT("StaticMesh"));
		StaticMesh->OnComponentCreated();
		if (StaticMesh->bWantsInitializeComponent) StaticMesh->InitializeComponent();
		StaticMesh->RegisterComponent();
		SetRootComponent(StaticMesh);
		StaticMesh->SetWorldTransform(Transform);
		StaticMesh->SetStaticMesh(SMesh);
		StaticMesh->SetSimulatePhysics(true);
	}

	// Paint cube
	SetColor(DColor);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = RootComponent->GetComponentTransform().GetLocation();
	StartingRotation = RootComponent->GetComponentTransform().GetRotation().Rotator();

	// Save transform if this cube is to respawn in the start location
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
	
	// This cube will be spawned just to show explosion effect, with lifespan = Timeout
	cube->HasDM = true;
	cube->SMesh = SMesh;
	cube->DMesh = DMesh;
	cube->BaseDamage = BaseDamage;
	cube->DamageRadius = DamageRadius;
	cube->ImpulseStrength = ImpulseStrength;
	cube->DColor = DColor;
	
	cube->FinishSpawning(newTransform);
	cube->DestructibleMesh->ApplyRadiusDamage(BaseDamage, HitLocation, DamageRadius, ImpulseStrength, false);

	if (!UseStartingTransformOnRespawn)
	{
		RespawnLocation = RootComponent->GetComponentLocation();
		RespawnRotation = RootComponent->GetComponentRotation();
	}

	// Cube is invisible until is to be respawned
	UPrimitiveComponent* root = Cast<UPrimitiveComponent>(RootComponent);
	root->SetSimulatePhysics(false);
	root->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	root->SetVisibility(false);

	// 'Respawn' after Timeout if Respawnable
	if(Respawnable) GetWorldTimerManager().SetTimer(this, &ACube::RespawnCube, Timeout);
	else Destroy();
}

void ACube::RespawnCube()
{
	// Revert Collision and Visibility parameters on respawn
	UPrimitiveComponent* root = Cast<UPrimitiveComponent>(RootComponent);
	root->SetSimulatePhysics(true);
	root->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	root->SetVisibility(true);

	if (!MaintainColorOnRespawn) SetColor(DDefaultColor);

	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
}

void ACube::SetColor(DTypes::DCOLOR dColor)
{
	if (!CanChangeColor) return;

	DColor = dColor;

	if (CubeMaterials.Num() > DColor)
	{
		Material = CubeMaterials[DColor];
		Cast<UPrimitiveComponent>(RootComponent)->SetMaterial(0, Material);
	}
}

DTypes::DCOLOR ACube::GetColor()
{
	return DColor;
}