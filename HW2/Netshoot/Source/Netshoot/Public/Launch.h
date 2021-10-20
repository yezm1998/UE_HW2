// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launch.generated.h"
class USpringArmComponent;
class AProjectile;

UCLASS()
class NETSHOOT_API ALaunch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY(VisibleAnywhere, Category = "Body")
		//USpringArmComponent* LaunchBody;
	UPROPERTY(Replicated,BlueprintReadOnly, Category = "UI")
	int ShootCountTime;
	UPROPERTY(Replicated,BlueprintReadOnly, Category = "UI")
	int GameCountTime;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	bool visible;
	FTimerHandle TimerHandle_TimeCount;
	void CutTime();
	void Shoot();
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileType;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ShowNumber(AProjectile* a);
};
