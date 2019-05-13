// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!target) return;

	switch (current)
	{
		case EBehavioursEnemy::Follow:
			FollowTarget(DeltaTime);
			break;
		case EBehavioursEnemy::LookPlayer:
			LookTarget();
			break;
		case EBehavioursEnemy::Avoidance:
			AvoidObstacle(DeltaTime);
			break;
		case EBehavioursEnemy::PursuitTarget:
			Pursuit();
			break;
	}
}

void AEnemy::FollowTarget(float deltaTime)
{

	LookTarget();
	SetActorLocation(GetActorLocation() + GetActorForwardVector()*speed*deltaTime);
}

void AEnemy::LookTarget()
{
	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rot = dir.Rotation();
	SetActorRotation(rot);
}

void AEnemy::AvoidObstacle(float deltaTime)
{
	if (!closestObstacle)
	{
		FollowTarget(deltaTime);
		return;
	}

	FVector direction = GetActorLocation() - closestObstacle->GetActorLocation();

	direction = (target->GetActorLocation() - GetActorLocation()).GetSafeNormal() + (direction.GetSafeNormal()*avoidWeight);

	direction.Z = 0;
	FVector rot =FMath::Lerp(GetActorForwardVector(), (direction), deltaTime*speedRot);

	SetActorRotation(rot.Rotation());
	SetActorLocation(GetActorLocation() + GetActorForwardVector()*speed*deltaTime);
}

void AEnemy::MyBeginOverlap(AActor * overlapActor)
{
	if (overlapActor == this || overlapActor == target)
		return;

	if (closestObstacle)
	{
		FVector distA = closestObstacle->GetActorLocation() - GetActorLocation();
		FVector distB = overlapActor->GetActorLocation() - GetActorLocation();

		if (distB.Size() < distA.Size())
			closestObstacle = overlapActor;

	}
	else
	{
		closestObstacle = overlapActor;
	}
}


