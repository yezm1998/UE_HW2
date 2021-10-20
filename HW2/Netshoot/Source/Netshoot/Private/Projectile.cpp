// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"        //��ͼ��Ҳ�����ҵ�ProjectileMovement������
#include "Components/SphereComponent.h"
#include "Launch.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));//�������Projectile
	ProjectileMovementComponent->bAutoActivate = false;		//�Զ����е���false

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
	ProjectileMovementComponent->SetVelocityInLocalSpace(fv * Speed);	//�����ٶȣ���Ϊ��ʸ�����Գ���ǰ������
	ProjectileMovementComponent->Activate();	//���Է�����
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