// Fill out your copyright notice in the Description page of Project Settings.


#include "Launch.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "TimerManager.h"
#include "Projectile.h"

// Sets default values
ALaunch::ALaunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShootCountTime = 3;
	GameCountTime = 60;
	visible = false;
	//LaunchBody = CreateDefaultSubobject<USpringArmComponent>(TEXT("LaunchBody"));
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ALaunch::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_TimeCount, this, &ALaunch::CutTime, 1.0f, true, 1.0f);

}

// Called every frame
void ALaunch::Tick(float DeltaTime)
{
	
}

void ALaunch::Shoot() {
	AProjectile* Projectile1 = GetWorld()->SpawnActor<AProjectile>(        //第七种方法
		ProjectileType,
		GetActorLocation(),   //FireLocation是生成子弹地方的Socket 
		//FRotator(0, 60, 180)
		GetActorRotation()
		);
	Projectile1->LaunchProjectile(0);
}

void ALaunch::CutTime() {
	//UE_LOG(LogTemp, Warning, TEXT("shoottime: %s"), *FString::SanitizeFloat(ShootCountTime));
	if (GameCountTime <= 0) {
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		return;
	}
	--ShootCountTime;
	--GameCountTime;
	if (GameCountTime==0) {
		visible = true;
	}
	
	if (ShootCountTime == 0) {
		ShootCountTime = 3;
		Shoot();
	}
}

void ALaunch::ShowNumber() {
	//UE_LOG(LogTemp, Warning, TEXT("gametime: %s"), *FString::SanitizeFloat(GameCountTime));
	
}
