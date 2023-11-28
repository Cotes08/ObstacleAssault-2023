// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay : %s"), *Name);

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if (ShouldPlatformReturn()){

		//Obtenemos la direccion de movimiento normalizada
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		//Calculamos la nueva posicion inicial sumando la direccion de movimiento por la distancia de movimiento
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		//Debemos actualizar la velocidad despues de haber actualizado la posicion
		PlatformVelocity = -PlatformVelocity;

	}else{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime; //DeltaTime hace que el movimiento sea independiente de los frames y se mueva a la misma velocidad en todos los ordenadores
		SetActorLocation(CurrentLocation);
	}
}


void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const//Dentro de la funcion const solo se pueden llamar a otras funciones const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const 
{
	//Send platform back if gone too far
		//Check how far weve moved
	return FVector::Dist(StartLocation, GetActorLocation());
}