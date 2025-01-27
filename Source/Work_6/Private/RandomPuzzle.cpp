// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPuzzle.h"
#include "BasePad.h"
#include "PopPad.h"
#include "Components/BoxComponent.h"
#include "Flash.h"
#include <algorithm>

// Sets default values
ARandomPuzzle::ARandomPuzzle()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	SpawnExtent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SpawnExtent->SetupAttachment(SceneRoot);
	SpawnExtent->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	SpawnExtent->SetCollisionProfileName(TEXT("NoCollision"));

	SpawnClass = AActor::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	CourseLength = 1;
	CourseWidth = 1;
	Interval = 100.0f;

	MoveLocation = FVector(0.0f, 0.0f, 0.0f);


	PrevRand = 0;
	RandNum = 0;
	SpawnNumber = 0;
}

// Called when the game starts or when spawned
void ARandomPuzzle::BeginPlay()
{
	Super::BeginPlay();

	SetRandomCourse();
}

void ARandomPuzzle::SetRandomCourse()
{	
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FMath::RandInit(FPlatformTime::Cycles());
	while (SpawnNumber <= CourseLength)
	{
		if (SpawnNumber == 0)
		{
			RandNum = FMath::RandRange(0, CourseWidth - 1);
			SpawnLocation = GetActorLocation() + FVector(RandNum * Interval, 0.0f, 0.0f);
			GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			SpawnNumber++;
			PrevRand = RandNum;
		}
		else
		{
			int Min = max(0, PrevRand - 1);
			int Max = min(CourseWidth - 1, PrevRand + 1);
			RandNum = FMath::RandRange(PrevRand - 1, PrevRand + 1);
			SpawnLocation = GetActorLocation() + FVector(RandNum * Interval, Interval * SpawnNumber, 0.0f);
			GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLocation, FRotator(0.0f, 0.0f, 0.0f));
			SpawnNumber++;
			PrevRand = RandNum;
		}
	}
}
