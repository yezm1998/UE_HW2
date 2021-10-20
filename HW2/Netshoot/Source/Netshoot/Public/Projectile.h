// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile.generated.h"
class UProjectileMovementComponent;
UCLASS()
class NETSHOOT_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "sphere")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;    //声明这个组件
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* MyCollisionSphere;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LaunchProjectile(float Speed);
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
