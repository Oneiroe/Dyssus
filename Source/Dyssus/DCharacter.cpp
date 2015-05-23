#include "Dyssus.h"
#include "DCharacter.h"
#include "DProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "DStaticLibrary.h"

ADCharacter::ADCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(70.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Player can shoot by default when game starts
	canShoot = true;

	// By default, Walk Speed is the one already in use for the Character Movement Component
	walkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// By default, Sprint Speed is twice Walk Speed
	sprintSpeed = walkSpeed * 2;

	// By default, character is wielding its gun
	interactState = ObjectInteractionState::GUN;

	grabDistance = 2000.f;
	armLength = 1500.f;
	dropImpulseMultiplier = 500000.f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent); 

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Run", IE_Pressed, this, &ADCharacter::Run);
	InputComponent->BindAction("Run", IE_Released, this, &ADCharacter::StopRunning);

	InputComponent->BindAction("Take/Leave", IE_Pressed, this, &ADCharacter::GrabDropObject);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADCharacter::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &ADCharacter::OnFire);
	}

	InputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ADCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ADCharacter::LookUpAtRate);
}

void ADCharacter::Tick(float DeltaSeconds)
{
	CarryObject();
}

void ADCharacter::CarryObject()
{
	if (grabbedObject)
	{
		FRotator newRotation = GetControlRotation();
		FVector newLocation = 
			GetActorLocation() +
			GetActorForwardVector() * armLength + 
			GetActorRightVector() * armOffsetH + 
			GetActorUpVector() * armOffsetV;

		grabbedObject->SetActorLocationAndRotation(newLocation, newRotation);
	}
}

void ADCharacter::GrabDropObject()
{
	switch (interactState)
	{
		// If Take/Leave button is pressed while gun is being held, the character puts it back
		case ObjectInteractionState::GUN:
			interactState = ObjectInteractionState::NONE;
			Mesh1P->SetVisibility(false);

			break;

		// Character drops grabbed object
		case ObjectInteractionState::OBJECT:
			DropObject();
			
			break;

		// Check whether line trace intersects a 'grabbable' object. If so, character grabs it.
		case ObjectInteractionState::NONE:
		default:
			//location the PC is focused on
			const FVector Start = GetActorLocation();
			const FVector End = Start + GetControlRotation().Vector() * grabDistance;

			// Trace data is stored here
			FHitResult HitData(ForceInit);

			if (UDStaticLibrary::Trace(GetWorld()->GetFirstPlayerController()->GetPawn(), Start, End, HitData))
			{

				AActor* hitActor = HitData.GetActor();
				if (hitActor && hitActor->Implements<UGrabbableInterface>())
				{
					// GrabObject(InterfaceCast<UGrabbableInterface>(hitActor));
					GrabObject(hitActor);
				}
			}

			break;
	}
}

void ADCharacter::GrabObject(AActor* hitActor)
{
	grabbedObject = hitActor;
	
	UPrimitiveComponent* objectMesh = (UPrimitiveComponent*)grabbedObject->GetComponentsByClass(UPrimitiveComponent::StaticClass())[0];
	objectMesh->SetSimulatePhysics(false);
	
	interactState = ObjectInteractionState::OBJECT;
}

void ADCharacter::DropObject()
{
	UPrimitiveComponent* objectMesh = (UPrimitiveComponent*)grabbedObject->GetComponentsByClass(UPrimitiveComponent::StaticClass())[0];
	objectMesh->SetSimulatePhysics(true);

	FVector forceVector = GetControlRotation().Vector() * dropImpulseMultiplier;
	objectMesh->AddForce(forceVector);

	grabbedObject = nullptr;
	interactState = ObjectInteractionState::NONE;
}

void ADCharacter::Run()
{
	// Smooth interpolation to faster run speed
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, sprintSpeed, GetWorld()->GetDeltaSeconds(), runWalkInterpSpeed);
}

void ADCharacter::StopRunning()
{
	// Smooth interpolation to slower walk speed
	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, walkSpeed, GetWorld()->GetDeltaSeconds(), runWalkInterpSpeed);
}

void ADCharacter::OnFire()
{
	// Check whether gun timeout is over
	if (!canShoot || interactState == ObjectInteractionState::OBJECT) return;

	// If character was not holding any object, he can pick his gun again
	else if (interactState == ObjectInteractionState::NONE) 
	{
		interactState = ObjectInteractionState::GUN;
		Mesh1P->SetVisibility(true);

		return;
	}

	// Start timer for gun cooldown
	canShoot = false;
	GetWorldTimerManager().SetTimer(this, &ADCharacter::enableFiring, gunTimeout);
	
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<ADProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void ADCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ADCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void ADCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (ScaledDelta.X != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (ScaledDelta.Y != 0.0f)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y* BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void ADCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ADCharacter::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADCharacter::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &ADCharacter::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADCharacter::TouchUpdate);
	}
	return bResult;
}

void ADCharacter::enableFiring()
{
	canShoot = true;
}
