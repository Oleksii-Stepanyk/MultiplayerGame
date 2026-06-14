// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	FString ActorName = GetActorLabel();
	FString RoleString = HasAuthority() ? TEXT("Authority") : TEXT("Proxy");
	FString Message = FString::Printf(TEXT("%s spawned with role: %s"), *ActorName, *RoleString);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, Message);
	}
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		FString ActorName = GetActorLabel();
		ENetRole CurrentLocalRole = GetLocalRole();
		ENetRole CurrentRemoteRole = GetRemoteRole();

		FString LocalRoleStr = UEnum::GetValueAsString(CurrentLocalRole);
		FString RemoteRoleStr = UEnum::GetValueAsString(CurrentRemoteRole);

		FString Message = FString::Printf(TEXT("Label: %s | Local: %s | Remote: %s"), *ActorName, *LocalRoleStr, *RemoteRoleStr);

		GEngine->AddOnScreenDebugMessage((uint64)GetUniqueID(), 0.0f, FColor::Cyan, Message);
	}
}

void APickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (HasAuthority())
	{
		if (GEngine) {
			FString ActorName = GetActorLabel();
			FString CollidedActor = OtherActor->GetActorLabel();
			FString Message = FString::Printf(TEXT("%s collided with %s"), *CollidedActor, *ActorName);
			GEngine->AddOnScreenDebugMessage((uint64)GetUniqueID(), 5.0f, FColor::Red, Message);
		}
		Destroy();
	}
}

