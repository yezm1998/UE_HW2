// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"        //蓝图中也可以找到ProjectileMovement这个组件
#include "Components/SphereComponent.h"
#include "Launch.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));//生成组件Projectile
	ProjectileMovementComponent->bAutoActivate = false;		//自动飞行调成false

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(100);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;
	//SetReplicates(true);
	//SetReplicateMovement(true);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::LaunchProjectile(float Speed) {
	FVector fv(-100, 0, 100);
	ProjectileMovementComponent->SetVelocityInLocalSpace(fv * Speed);	//设置速度，因为是矢量所以乘向前的向量
	ProjectileMovementComponent->Activate();	//可以飞行了
}

void AProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("shoot!!!"));
		if(OtherComp->ComponentHasTag("ground"))
			Destroy();
	}
}

void AProjectile::Finish(){
	l->ShowNumber(this);
}

void AProjectile::SetLaunch(ALaunch* ll) {
	l = ll;
}