#pragma once

#include "GrabbableInterface.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UInputComponent;

UCLASS(config = Game)
class ADCharacter : public ACharacter  
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ADCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ADProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Minimum time interval between consecutive firings */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float gunTimeout;

	/** Character's walking speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float walkSpeed;

	/** Character's running speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float sprintSpeed;

	/** Interpolation speed for transitioning between walk and run speeds and viceversa */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float runWalkInterpSpeed;

	// Max distance for grabbing objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float grabDistance;

	// Distance of grabbed object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float armLength;

	// Horizontal offset of grabbed object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float armOffsetH;

	// Vertical offset of grabbed object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float armOffsetV;

	// How much grabbed object gets pushed away
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dropImpulseMultiplier;

protected:

	/** Reference to the object grabbed by the player */
	AActor* grabbedObject;

	/** Whether player can shoot a projectile */
	bool canShoot;

	/** Sets canShoot to true. It is called when gun cooldown expires */
	void enableFiring();

	/** Handle object interaction */
	void GrabDropObject();
	void GrabObject(AActor* hitActor);
	void DropObject();
	void CarryObject();

	/** Fires a projectile. */
	void OnFire();

	/** Character walks sprintScale times its normal walk speed */
	void Run();

	/** Character walks at normal walk speed */
	void StopRunning();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

	enum ObjectInteractionState
	{
		GUN,
		OBJECT,
		NONE
	};
	ObjectInteractionState interactState;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	* Configures input for touchscreen devices if there is a valid touch interface for doing so
	*
	* @param	InputComponent	The input component pointer to bind controls to
	* @returns true if touch controls were enabled.
	*/
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

