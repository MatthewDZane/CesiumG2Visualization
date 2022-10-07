// Fill out your copyright notice in the Description page of Project Settings.


#include "G2Snapshot.h"

UG2Snapshot::UG2Snapshot() {

}

UG2Snapshot::~UG2Snapshot() {

}

void UG2Snapshot::CopyData(UG2Snapshot* G2SnapshotIn) {
	IDToNodeMap.Empty();
	for (TPair<FString, UG2Node*> IDToNodePair : G2SnapshotIn->IDToNodeMap) {
		IDToNodeMap.Add(IDToNodePair.Key, IDToNodePair.Value);
	}

	Links.Empty();
	for (FG2Link Link : G2SnapshotIn->Links) {
		Links.Add(Link);
	}

	Flows.Empty();
	for (FFlow Flow : G2SnapshotIn->Flows) {
		Flows.Add(Flow);
	}

	ID = G2SnapshotIn->ID;
	TimeStamp = G2SnapshotIn->TimeStamp;
}