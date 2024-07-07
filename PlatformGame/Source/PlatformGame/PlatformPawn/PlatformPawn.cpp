#include "PlatformPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlatformGame/ActorsFolder/IHittable.h"
#include "PlatformGame/SaveSystemFolder/CustomGameInstance.h"

APlatformPawn::APlatformPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	this->MovementComponentInstance = CreateDefaultSubobject<UCustomMovementComponent>(TEXT("PlatformerMovementComponent"));
	this->SkeletalMeshComponentInstance = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlatformerSkeletalMeshComponent"));
}

void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString SkeletalMeshPath = "/Game/Meshes/SM_PlatformMesh.SM_PlatformMesh";
	USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (Mesh)
	{
		this->SkeletalMeshComponentInstance->SetSkeletalMesh(Mesh);
	}

	//Add Input Mapping Context	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}



void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTimerShoot>0)
	{
		CurrentTimerShoot -= DeltaTime;
	}
}

void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlatformPawn::Jump);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformPawn::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlatformPawn::StopMove);
		// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlatformPawn::Look);
		EnhancedInputComponent->BindAction(SaveAction, ETriggerEvent::Triggered, this, &APlatformPawn::Save);
		EnhancedInputComponent->BindAction(LoadAction, ETriggerEvent::Triggered, this, &APlatformPawn::Load);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlatformPawn::Shoot);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlatformPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		float AngleRadians = FMath::Atan2(MovementVector.Y, MovementVector.X);
		float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);
		FRotator NewRotation(0.0f, AngleDegrees *(-1), 0.0f);
		
		this->SetActorRotation(NewRotation);
		//SetWorldRotation(NewRotation);
		
		MovementComponentInstance->MovePawn(ForwardDirection , MovementVector.Y * 500);
		MovementComponentInstance->MovePawn(RightDirection, MovementVector.X*500);
		
	}
}

void APlatformPawn::Jump(const FInputActionValue& Input)
{
	if( !MovementComponentInstance->bIsGrounded) return;
	MovementComponentInstance->Jump(400.0f);
}

void APlatformPawn::StopMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector == FVector2D::Zero())
	{
		MovementComponentInstance->StopPawn();
	}
}
void APlatformPawn::Save(const FInputActionValue& Value)
{
	UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SaveGame();
	}
}

void APlatformPawn::Load(const FInputActionValue& Value)
{
	UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->LoadGame();
	}
}

void APlatformPawn::Shoot(const FInputActionValue& Value)
{
	ShootLogic(GetActorLocation(), GetActorLocation() + GetActorRightVector() * 1000, ECC_GameTraceChannel1);
}


bool APlatformPawn::ShootLogic(FVector StartPoint, FVector EndPoint, ECollisionChannel CollisionChannel)
{
	if (CurrentTimerShoot>0.f)
	{
		return false;
	}
	CurrentTimerShoot= CooldownShoot;
	UWorld* World = GetWorld();
	DrawDebugLine(World, StartPoint, EndPoint, FColor::Green);

	FHitResult HitResult;

	bool bHasRis = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, CollisionChannel);
	if (bHasRis) 
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if (HitComponent)
		{
			if(HitResult.GetActor()->GetClass()->ImplementsInterface(UIHittable::StaticClass()))
			{
				UE_LOG(LogTemp,Warning,TEXT("Hit something hittable"));
				IIHittable::Execute_Hit(HitResult.GetActor());
			}
			if (HitComponent->IsSimulatingPhysics())
			{
				FVector Impulse = EndPoint - StartPoint;
				Impulse.Normalize();
				Impulse *= ImpulseIntensity;
				HitComponent->AddImpulseAtLocation(Impulse, HitComponent->GetCenterOfMass());	//always in the middle of the object
			}
		}
	}
	return bHasRis;
}
