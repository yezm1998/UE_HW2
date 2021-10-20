// Fill out your copyright notice in the Description page of Project Settings.


#include "Launch.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "Net/UnrealNetwork.h"
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
	bReplicates = true;


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
	if (GetLocalRole() == ROLE_Authority) {
		AProjectile* Projectile1 = GetWorld()->SpawnActor<AProjectile>(        //�����ַ���
			ProjectileType,
			GetActorLocation(),   //FireLocation�������ӵ��ط���Socket 
			//FRotator(0, 60, 180)
			GetActorRotation()
			);
		//Projectile1->SetLaunch(this);
		Projectile1->LaunchProjectile(1);
		
	}
	
}

void ALaunch::CutTime() {
	//UE_LOG(LogTemp, Warning, TEXT("shoottime: %s"), *FString::SanitizeFloat(ShootCountTime));
	if (GameCountTime <= 0) {
		GetWorldTimerManager().ClearTimer(TimerHandle_TimeCount);
		return;
	}
	//if (GetLocalRole() == ROLE_Authority) {
		--ShootCountTime;
		--GameCountTime;
	//}
	if (GameCountTime==0) {
		visible = true;
	}
	
	if (ShootCountTime == 0) {
		ShootCountTime = 3;
		Shoot();
	}
}

void ALaunch::ShowNumber(AProjectile* a) {
	//UE_LOG(LogTemp, Warning, TEXT("gametime: %s"), *FString::SanitizeFloat(GameCountTime));
	a->Destroy(); //Destroy(a);
}

void ALaunch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALaunch, ShootCountTime);
	DOREPLIFETIME(ALaunch, GameCountTime);
	//DOREPLIFETIME_CONDITION(ALaunch, ShootCountTime, COND_InitialOnly);
}
