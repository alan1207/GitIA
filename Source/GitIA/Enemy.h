// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EBehavioursEnemy :uint8
{
	Follow UMETA(DisplayName = "Follow Target"),
	LookPlayer UMETA(DisplayName = "Look Target"),
	Avoidance UMETA(DisplayName = "Avoidance"),
	PursuitTarget UMETA(DisplayName = "Pursuit Target"),
};

UCLASS()
class GITIA_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere)
		AActor* target;

	UPROPERTY(EditAnywhere, Category = Enum)
		EBehavioursEnemy current;

	UPROPERTY(EditAnywhere)
		float speed;

	UPROPERTY(EditAnywhere)
		float speedRot;

	UPROPERTY(EditAnywhere)
		float avoidWeight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		AActor* closestObstacle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FollowTarget(float deltaTime);
	void LookTarget();
	void AvoidObstacle(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void MyBeginOverlap(AActor* overlapActor);

};


