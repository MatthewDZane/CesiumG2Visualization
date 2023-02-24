// Fill out your copyright notice in the Description page of Project Settings.


#include "G2Node.h"

UG2Node::UG2Node() {

}

UG2Node::UG2Node(FString IDIn, FString InfoIn, FString NameIn, FString IPIn,
	float LatitudeIn, float LongitudeIn, bool PrimaryIn, int MTUIn) {
	ID = IDIn;
	Info = InfoIn;
	Name = NameIn;
	IP = IPIn;

	Latitude = LatitudeIn;
	Longitude = LongitudeIn;

	Primary = PrimaryIn;

	MTU = MTUIn;
}

UG2Node::~UG2Node() {

}
