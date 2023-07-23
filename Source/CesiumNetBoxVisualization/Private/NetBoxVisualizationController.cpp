// Fill out your copyright notice in the Description page of Project Settings.


#include "NetBoxVisualizationController.h"
#include "CesiumNetBoxVisualizationRequestLibrary.h"
#include "ReztlyFunctionLibrary.h"
#include "JsonObjectConverter.h"
#include "FlowInfo.h"

// Sets default values
ANetBoxVisualizationController::ANetBoxVisualizationController() {
	PrimaryActorTick.bCanEverTick = false;
}

ANetBoxVisualizationController::~ANetBoxVisualizationController() {

}

// Called when the game starts or when spawned
void ANetBoxVisualizationController::BeginPlay() {
	Super::BeginPlay();

	Snapshot = NewObject<UG2Snapshot>();
}

// Called every frame
void ANetBoxVisualizationController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UG2Snapshot* ANetBoxVisualizationController::GetSnapshot() {
	return Snapshot;
}

void ANetBoxVisualizationController::RequestVisualizationData() {
	G2Enabled ?
		RequestBearerToken() :
		AsyncTask(ENamedThreads::GameThread, [this]()
			{
				MakeClientsRequestUE4DataUtilsData();
			});
}

void ANetBoxVisualizationController::RequestBearerToken() {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnBearerTokenResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestBearerToken(
		G2Username, 
		G2Password, 
		G2APIURL, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnBearerTokenResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Login Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);
		EReztlyResult Result;
		UReztlyJsonObject* JsonObject = UReztlyFunctionLibrary::StringToJson(
			Result, 
			ResponseContentString
		);
		
		if (Result == EReztlyResult::Valid) {
			bool TokenFound;
			JsonObject->GetFieldValueAsString("token", G2Token, TokenFound);

			if (TokenFound) {
				RequestSnapshotRange();
				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Login Unsuccessful"));
}

void ANetBoxVisualizationController::RequestSnapshotRange()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnSnapshotRangeResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestSnapshotRange(
		G2APIURL, 
		G2Token, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnSnapshotRangeResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Snapshot Range Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FString TempJsonString = ResponseContentString.TrimStartAndEnd();
		if (TempJsonString.Len() > 4 &&
			TempJsonString[0] == '[' &&
			TempJsonString[1] == '[' &&
			TempJsonString[TempJsonString.Len() - 1] == ']' &&
			TempJsonString[TempJsonString.Len() - 2] == ']'
			) {
			// Remove starting and ending brackets
			TempJsonString = TempJsonString.RightChop(2);
			TempJsonString = TempJsonString.LeftChop(2);


			// String has "...],[...],[..." format
			TArray<FString> AvailableSnapshotsString;
			TempJsonString.ParseIntoArray(
				AvailableSnapshotsString,
				TEXT("],[")
			);

			for (FString AvailableSnapshotString : AvailableSnapshotsString) {
				// String has "...,...,..." format
				TArray<FString> AvailableSnapshotData;
				AvailableSnapshotString.ParseIntoArray(
					AvailableSnapshotData,
					TEXT(",")
				);

				if (AvailableSnapshotData.Num() == 2) {
					FTimeStampIDPair AvailableSnapshot;
					AvailableSnapshot.TimeStamp = 
						FCString::Atoi(*AvailableSnapshotData[0]);
					AvailableSnapshot.ID = 
						(int)FCString::Atof(*AvailableSnapshotData[1]);

					AvailableSnapshots.Add(AvailableSnapshot);
				}
			}
		}

		if (Snapshot->ID == -1) {
			RequestLatestSnapshot();
		}
		else if (SnapshotAvailable(Snapshot->ID)) {
			RequestSnapshot(Snapshot->ID, Snapshot->TimeStamp);
		}
		else {
			RequestLatestSnapshot();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Snapshot Range Request Unsuccessful"));
	}
}

void ANetBoxVisualizationController::RequestLatestSnapshot() {
		if (AvailableSnapshots.Num() == 0) {
			RequestUE4DataUtilsData();
		}
		else {
			int SnapshotID = AvailableSnapshots.Last(0).ID;
			int TimeStamp = AvailableSnapshots.Last(0).TimeStamp;

			RequestSnapshot(SnapshotID, TimeStamp);
		}
}

void ANetBoxVisualizationController::RequestSnapshot(
	int SnapshotID, 
	int TimeStamp
) {
	Snapshot->ID = SnapshotID;
	Snapshot->TimeStamp = TimeStamp;

	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnSnapshotResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestSnapshot(
		SnapshotID, 
		G2APIURL, 
		G2Token, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnSnapshotResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Snapshot Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FG2SnapshotResponse ResponseSnapshot;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString, 
				&ResponseSnapshot
			) && 
			ResponseSnapshot.Data.Num_snapshots != 0
		) {
			if (HasAuthority()) {
				AsyncTask(ENamedThreads::GameThread, [this]()
					{
						MakeClientsRequestSnapshot(
							G2Token, 
							Snapshot->ID, 
							Snapshot->TimeStamp
						);
					});
			}

			ParseG2Snapshot(ResponseSnapshot);
		}
		else
		{
			// Remove TimeStampIDPair from list of Available Snapshots
			for (int i = AvailableSnapshots.Num() - 1; i >= 0; i--) {
				FTimeStampIDPair TimeStampIDPair = AvailableSnapshots[i];
				if (Snapshot->ID == TimeStampIDPair.ID) {
					AvailableSnapshots.RemoveAt(i);
					break;
				}
			}
			
			RequestLatestSnapshot();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Snapshot Request Unsuccessful"));
		AvailableSnapshots.RemoveAt(AvailableSnapshots.Num() - 1);
		RequestLatestSnapshot();
	}
}

void ANetBoxVisualizationController::RequestUE4DataUtilsData() {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnUE4DataUtilsResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestUE4NautilusData(
		UE4NautilusDataUtilsURL, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnUE4DataUtilsResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Snapshot Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		EReztlyResult ExecResult;
		UReztlyJsonObject* JsonObject = UReztlyFunctionLibrary::StringToJson(ExecResult, ResponseContentString);
		if (ExecResult == EReztlyResult::Valid)
		{
			FUE4Response ResponseSnapshot;

			// Parse Nodes Field
			TArray<UReztlyJsonValue*> NodeJsonValues;
			bool NodesFieldFound;
			JsonObject->GetFieldValueAsArray("nodes", NodeJsonValues, NodesFieldFound);

			if (NodesFieldFound) {
				for (UReztlyJsonValue* NodeJsonValue : NodeJsonValues) {
					UReztlyJsonObject* NodeJsonObject;
					bool NodeJsonObjectSuccess;
					NodeJsonValue->TryAsJsonObject(NodeJsonObject, NodeJsonObjectSuccess);

					if (NodeJsonObjectSuccess) {
						FUE4Node NodeStruct;

						// Parse Paths Field
						TArray<UReztlyJsonValue*> PathJsonValues;
						bool PathsFieldFound;
						NodeJsonObject->GetFieldValueAsArray("paths", PathJsonValues, PathsFieldFound);

						if (PathsFieldFound) {
							for (UReztlyJsonValue* PathJsonValue : PathJsonValues) {
								TArray<UReztlyJsonValue*> ValueJsonValues;
								bool ValueJsonValuesSuccess;
								PathJsonValue->TryAsArray(ValueJsonValues, ValueJsonValuesSuccess);

								if (ValueJsonValuesSuccess) {
									FPath PathStruct;

									for (UReztlyJsonValue* ValueJsonValue : ValueJsonValues) {
										FString ValueString;
										bool ValueStringSuccess;
										ValueJsonValue->TryAsString(ValueString, ValueStringSuccess);

										if (ValueStringSuccess) {
											PathStruct.Values.Add(ValueString);
										}
									}

									NodeStruct.Paths.Add(PathStruct);
								}
							}
						}

						// Parse Hostname Field
						bool HostnameFieldFound;
						NodeJsonObject->GetFieldValueAsString("hostname", NodeStruct.Hostname, HostnameFieldFound);

						// Parse Ip Field
						bool IpFieldFound;
						NodeJsonObject->GetFieldValueAsString("ip", NodeStruct.Ip, IpFieldFound);

						// Parse Latitude Field
						bool LatitudeFieldFound;
						NodeJsonObject->GetFieldValueAsFloat("latitude", NodeStruct.Latitude, LatitudeFieldFound);

						// Parse Hostname Field
						bool LongitudeFieldFound;
						NodeJsonObject->GetFieldValueAsFloat("longitude", NodeStruct.Longitude, LongitudeFieldFound);

						// Parse Hostname Field
						bool PrimaryFieldFound;
						NodeJsonObject->GetFieldValueAsBoolean("primary", NodeStruct.Primary, PrimaryFieldFound);

						ResponseSnapshot.Nodes.Add(NodeStruct);
					}
				}
			}

			// Parse Edges Field
			TArray<UReztlyJsonValue*> EdgeJsonValues;
			bool EdgesFieldFound;
			JsonObject->GetFieldValueAsArray("edges", EdgeJsonValues, EdgesFieldFound);

			if (EdgesFieldFound) {
				for (UReztlyJsonValue* EdgeJsonValue : EdgeJsonValues) {
					UReztlyJsonObject* EdgeJsonObject;
					bool EdgeJsonObjectSuccess;
					EdgeJsonValue->TryAsJsonObject(EdgeJsonObject, EdgeJsonObjectSuccess);

					if (EdgeJsonObjectSuccess) {
						FUE4Edge EdgeStruct;

						// Parse Source Field
						bool SourceFieldFound;
						EdgeJsonObject->GetFieldValueAsInteger("source", EdgeStruct.Source, SourceFieldFound);

						// Parse Target Field
						bool TargetFieldFound;
						EdgeJsonObject->GetFieldValueAsInteger("target", EdgeStruct.Target, TargetFieldFound);

						// Parse Mtu Field
						bool MtuFieldFound;
						EdgeJsonObject->GetFieldValueAsInteger("mtu", EdgeStruct.Mtu, MtuFieldFound);

						// Parse Latency Field
						bool LatencyFieldFound;
						EdgeJsonObject->GetFieldValueAsFloat("latency", EdgeStruct.Latency, LatencyFieldFound);

						// Parse Paths Field
						TArray<UReztlyJsonValue*> PathJsonValues;
						bool PathsFieldFound;
						EdgeJsonObject->GetFieldValueAsArray("paths", PathJsonValues, PathsFieldFound);

						if (PathsFieldFound) {
							for (UReztlyJsonValue* PathJsonValue : PathJsonValues) {
								TArray<UReztlyJsonValue*> ValueJsonValues;
								bool ValueJsonValuesSuccess;
								PathJsonValue->TryAsArray(ValueJsonValues, ValueJsonValuesSuccess);

								if (ValueJsonValuesSuccess) {
									FPath PathStruct;

									for (UReztlyJsonValue* ValueJsonValue : ValueJsonValues) {
										FString ValueString;
										bool ValueStringSuccess;
										ValueJsonValue->TryAsString(ValueString, ValueStringSuccess);

										if (ValueStringSuccess) {
											PathStruct.Values.Add(ValueString);
										}
									}

									EdgeStruct.Paths.Add(PathStruct);
								}
							}
						}

						ResponseSnapshot.Edges.Add(EdgeStruct);
					}
				}
			}

			if (ResponseSnapshot.Nodes.Num() != 0)
			{
				ParseUE4Data(ResponseSnapshot);
				return;
			}
			else {
				UE_LOG(
					LogTemp,
					Warning,
					TEXT("No Data recieved from UE4 Data Utils")
				);
			}
		}
		else {
			UE_LOG(LogJson, Warning, TEXT("OnUE4DataUtilsResponse - Unable to parse. json=[%s]"), *ResponseContentString);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UE4 Data Utils Request Unsuccessful"));		
	}

	RequestNetboxRegionsGet();
}

void ANetBoxVisualizationController::ParseUE4Data(const FUE4Response& UE4Response) {
	// Create G2Node objects
	for (FUE4Node Node : UE4Response.Nodes) {
		UG2Node* G2Node = NewObject<UG2Node>();

		G2Node->ID = Node.Ip;
		G2Node->Name = Node.Hostname.Left(MAX_DEVICE_NAME_LEN);
		G2Node->IP = Node.Ip;

		if (IsValidLatLong(Node.Latitude, Node.Longitude))
		{
			G2Node->Latitude = Node.Latitude;
			G2Node->Longitude = Node.Longitude;
		}

		G2Node->Primary = Node.Primary;

		Snapshot->IDToNodeMap.Add(G2Node->ID, G2Node);
		Snapshot->IPToNodeMap.Add(G2Node->IP, G2Node);
	}
	UE_LOG(LogTemp, Log, TEXT("Finished Parsing UE4 Node Data."));

	// Create Links
	for (FUE4Node Node : UE4Response.Nodes) {
		for (FPath Path : Node.Paths) {
			FG2Link G2Link;

			FString SourceIP = Path.Values[0];
			FString TargetIP = Path.Values[1];

			bool SkipLink = false;
			for (FG2Link Link : Snapshot->Links) {
				if (!Snapshot->IDToNodeMap.Contains(SourceIP) || 
					!Snapshot->IDToNodeMap.Contains(TargetIP) ||
					(
						Link.Source->ID == SourceIP && 
						Link.Target->ID == TargetIP
					) ||
					(
						Link.Source->ID == TargetIP &&
						Link.Target->ID == SourceIP
					)
				) {
					SkipLink = true;
					break;
				}
			}
			if (SkipLink) {
				break;
			}

			/* edge case: skip when either src_ip or dest_ip are missing.
			   The G2 response snapshot topology nodes do not contain ip */
			if (!Snapshot->IPToNodeMap.Contains(SourceIP) ||
				!Snapshot->IPToNodeMap.Contains(TargetIP))
			{
				continue;
			}

			G2Link.Source = *Snapshot->IDToNodeMap.Find(SourceIP);
			G2Link.Target = *Snapshot->IDToNodeMap.Find(TargetIP);

			Snapshot->Links.Add(G2Link);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Finished Parsing UE4 Link Data."));

	RequestNetboxRegionsGet();
}

void ANetBoxVisualizationController::ParseG2Snapshot(
	const FG2SnapshotResponse& SnapshotIn
) {
	FSnapshot SnapshotResponse = SnapshotIn.Data.Snapshots[0];

	ParseNodeData(SnapshotResponse.Topo.Topology.Nodes);
	ParseLinkData(SnapshotResponse.Topo.Topology.Links);
	ParseFlowData(SnapshotResponse.Flows.Flowgroups);

	UE_LOG(LogTemp, Log, TEXT("Finished Parsing G2 Data."));

	RequestNetboxRegionsGet();
}

void ANetBoxVisualizationController::ParseRegionData(
	const TArray<FRegionStruct>& NetboxRegions
) {
	for (FRegionStruct NetboxRegion : NetboxRegions)
	{
		URegion* Region = NewObject<URegion>();

		Region->ID = NetboxRegion.Id;
		Region->Url = NetboxRegion.Url;
		Region->Display = NetboxRegion.Display;
		Region->Name = NetboxRegion.Name;
		Region->Slug = NetboxRegion.Slug;
		Region->ParentName = NetboxRegion.Parent.Name;
		Region->Description = NetboxRegion.Description;

		Region->LogoUrl = NetboxRegion.Custom_fields.Logo;
		Region->Latitude = FCString::Atof(*NetboxRegion.Custom_fields.Region_latitude);
		Region->Longitude = FCString::Atof(*NetboxRegion.Custom_fields.Region_longitude);

		NameToRegionMap.Add(Region->Name, Region);
	}
}

void ANetBoxVisualizationController::ParseSiteData(
	const TArray<FSiteStruct>& NetboxSites
) {
	for (FSiteStruct NetboxSite : NetboxSites)
	{
		USite* Site = NewObject<USite>();

		Site->ID = NetboxSite.Id;
		Site->Url = NetboxSite.Url;
		Site->Display = NetboxSite.Display;
		Site->Name = NetboxSite.Name;
		Site->Slug = NetboxSite.Slug;
		Site->RegionName = NetboxSite.Region.Name;

		Site->Latitude = NetboxSite.Latitude;
		Site->Longitude = NetboxSite.Longitude;

		NameToSiteMap.Add(Site->Name, Site);
	}
}

void ANetBoxVisualizationController::ParseLocationData(
	const TArray<FLocationStruct>& NetboxLocations
) {
	for (FLocationStruct NetboxLocation : NetboxLocations)
	{
		ULocation* Location = NewObject<ULocation>();

		Location->ID = NetboxLocation.Id;
		Location->Url = NetboxLocation.Url;
		Location->Display = NetboxLocation.Display;
		Location->Name = NetboxLocation.Name;
		Location->Slug = NetboxLocation.Slug;

		Location->LocationWorldLocationOffset.InitFromString(
			NetboxLocation.Custom_fields.Location_world_location_offset);
		Location->LocationWorldRotationOffset.InitFromString(
			NetboxLocation.Custom_fields.Location_world_rotation_offset);

		Location->Site = NameToSiteMap[NetboxLocation.Site.Name];

		NameToLocationMap.Add(Location->Name, Location);
	}

	for (FLocationStruct NetboxLocation : NetboxLocations)
	{
		ULocation* Location = NameToLocationMap[NetboxLocation.Name];

		if (!NetboxLocation.Parent.Name.IsEmpty()) {
			Location->Parent = NameToLocationMap[NetboxLocation.Parent.Name];
		}
	}
}

void ANetBoxVisualizationController::ParseRackData(
	const TArray<FRackStruct>& NetboxRacks
) {
	for (FRackStruct NetboxRack : NetboxRacks)
	{
		URack* Rack = NewObject<URack>();

		Rack->ID = NetboxRack.Id;
		Rack->Url = NetboxRack.Url;
		Rack->Display = NetboxRack.Display;
		Rack->Name = NetboxRack.Name;

		Rack->FacilityID = NetboxRack.Facility_id;
		Rack->Status = NetboxRack.Status.Value;
		Rack->Role = NetboxRack.Role;
		Rack->Serial = NetboxRack.Serial;
		Rack->AssetTag = NetboxRack.Asset_tag;
		Rack->Type = NetboxRack.Type.Value;
		Rack->Width = FCString::Atof(*NetboxRack.Width.Value);

		Rack->UHeight = NetboxRack.U_height;
		Rack->OuterWidth = NetboxRack.Outer_width;
		Rack->OuterDepth = NetboxRack.Outer_depth;
		Rack->OuterUnit = NetboxRack.Outer_unit;

		Rack->Comments = NetboxRack.Comments;

		Rack->RackLatitude = NetboxRack.Custom_fields.Rack_latitude;
		Rack->RackLongitude = NetboxRack.Custom_fields.Rack_longitude;
		Rack->WorldLocationOffset.InitFromString(
			NetboxRack.Custom_fields.Rack_world_location_offset);
		Rack->WorldRotationOffset.InitFromString(
			NetboxRack.Custom_fields.Rack_world_rotation_offset);

		Rack->Site = NameToSiteMap[NetboxRack.Site.Name];

		if (!NetboxRack.Location.Name.IsEmpty()) {
			Rack->Location = NameToLocationMap[NetboxRack.Location.Name];
		}

		NameToRackMap.Add(Rack->Name, Rack);
	}
}

void ANetBoxVisualizationController::ParseDeviceTypeData(
	const TArray<FNetboxDeviceType>& DeviceTypes
) {
	for (FNetboxDeviceType NetboxDeviceType : DeviceTypes) {
		UDeviceType* DeviceType = NewObject<UDeviceType>();

		DeviceType->Id = NetboxDeviceType.Id;
		DeviceType->Url = NetboxDeviceType.Url;
		DeviceType->Display = NetboxDeviceType.Display;
		DeviceType->Model = NetboxDeviceType.Model;
		DeviceType->Slug = NetboxDeviceType.Slug;
		DeviceType->Part_number = NetboxDeviceType.Part_number;
		DeviceType->U_height = NetboxDeviceType.U_height;
		DeviceType->Is_full_depth = NetboxDeviceType.Is_full_depth;
		DeviceType->Subdevice_role = NetboxDeviceType.Subdevice_role;
		DeviceType->Airflow = NetboxDeviceType.Airflow;
		DeviceType->Front_image = NetboxDeviceType.Front_image;
		DeviceType->Rear_image = NetboxDeviceType.Rear_image;
		DeviceType->Comments = NetboxDeviceType.Comments;
		DeviceType->Custom_fields = NetboxDeviceType.Custom_fields;
		DeviceType->Created = NetboxDeviceType.Created;
		DeviceType->Last_updated = NetboxDeviceType.Last_updated;

		ModelToDeviceTypeMap.Add(DeviceType->Model, DeviceType);
	}
}

void ANetBoxVisualizationController::ParseNodeData(
	const TArray<FG2NodeStruct>& SnapshotNodes
) {
	for (FG2NodeStruct Node : SnapshotNodes) {
		if (Snapshot->IDToNodeMap.Contains(Node.ID))
		{
			UE_LOG(LogTemp, Log, TEXT("Duplicate Node Found: %s"), *Node.ID);
			continue;
		}

		UG2Node* G2Node = NewObject<UG2Node>();
		G2Node->ID = Node.ID;
		G2Node->Info = Node.Info;
		G2Node->Name = Node.Name;

		float NodeLat = FCString::Atof(*Node.Lat);
		float NodeLng = FCString::Atof(*Node.Lng);
		if (IsValidLatLong(NodeLat, NodeLng))
		{
			G2Node->Latitude = NodeLat;
			G2Node->Longitude = NodeLng;
		}

		FString IPAddress;
		float MTU;
		ParseNodeInfo(G2Node->Info, IPAddress, MTU);

		G2Node->IP = IPAddress;

		Snapshot->IDToNodeMap.Add(G2Node->ID, G2Node);

		if (G2Node->IP.Len() != 0) {
			Snapshot->IPToNodeMap.Add(G2Node->IP, G2Node);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Finished Parsing Node Data."));
}

void ANetBoxVisualizationController::ParseLinkData(
	const TArray<FLink>& SnapshotLinks
) {
	for (FLink Link : SnapshotLinks) {
		FG2Link G2Link;
		G2Link.Bandwidth = FCString::Atof(*Link.Bandwidth);
		G2Link.Delay = FCString::Atof(*Link.Delay);
		G2Link.Group = Link.Group;
		G2Link.ID = Link.ID;
		G2Link.Info = Link.Info;
		G2Link.Loss = Link.Loss;
		G2Link.MaxQueueSize = Link.Max_queue_size;
		G2Link.UseHTB = Link.Use_htb;

		G2Link.Source = *Snapshot->IDToNodeMap.Find(Link.Source);
		G2Link.Target = *Snapshot->IDToNodeMap.Find(Link.Target);

		Snapshot->Links.Add(G2Link);
	}

	UE_LOG(LogTemp, Log, TEXT("Finished Parsing Link Data."));
}

void ANetBoxVisualizationController::ParseFlowData(
	const TArray<FFlow>& SnapshotFlows
) {
	for (FFlow Flow : SnapshotFlows) {
		FString EndName = Flow.End;
		FString StartName = Flow.Start;

		Flow.Info = Flow.Info.Replace(TEXT("'"), TEXT("\""));

		FFlowInfo FlowInfo;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				Flow.Info,
				&FlowInfo
			)
		) {
			/* edge case: skip when either src_ip or dest_ip are missing.
				The G2 response snapshot topology nodes do not contain ip */
			if (!Snapshot->IPToNodeMap.Contains(FlowInfo.Src_ip) ||
					!Snapshot->IPToNodeMap.Contains(FlowInfo.Dst_ip))
			{
				continue;
			}

			UG2Node* StartNode = *Snapshot->IPToNodeMap.Find(FlowInfo.Src_ip);
			UG2Node* EndNode = *Snapshot->IPToNodeMap.Find(FlowInfo.Dst_ip);

			ReplaceFlowLinkNodeIDs(Flow.Links, StartNode, EndNode);

			if (StartNode != nullptr) {
				StartName = StartNode->ID;
			}

			if (EndNode != nullptr) {
				EndName = EndNode->ID;
			}

			FFlow G2Flow;
			G2Flow.End = EndName;
			G2Flow.Exp_share = Flow.Exp_share;
			G2Flow.Id = Flow.Id;
			G2Flow.Info = Flow.Info;
			G2Flow.Links = Flow.Links;
			G2Flow.Num_bytes = Flow.Num_bytes;
			G2Flow.Num_flows = Flow.Num_flows;
			G2Flow.Start = StartName;
			G2Flow.Start_time = Flow.Start_time;

			Snapshot->Flows.Add(G2Flow);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Finished Parsing Flow Data."));
}

void ANetBoxVisualizationController::ParseNodeInfo(
	FString Info, 
	FString& IPAddress,
	float& MTU
) {
	// Find IP Address
	int IPAddressHeaderIndex = Info.Find("'ipaddress'");
	if (IPAddressHeaderIndex != -1) {
		int IPAddressHeaderLength = 13;

		int IPAddressStartIndex = IPAddressHeaderIndex + IPAddressHeaderLength;
		int IPAddressEndIndex = Info.Find("'", ESearchCase::IgnoreCase,
			ESearchDir::Type::FromStart,
			IPAddressStartIndex + 1);
		int IPAddressLength = (IPAddressEndIndex - IPAddressStartIndex) - 1;

		IPAddress = Info.Mid(IPAddressStartIndex + 1, IPAddressLength);


		// Find MTU
		int MTUHeaderIndex = Info.Find("'mtu'");
		if (MTUHeaderIndex != -1) {
			int MTUHeaderLength = 7;

			int MTUStartIndex = MTUHeaderIndex + MTUHeaderLength;
			int MTUEndIndex = Info.Find("'", ESearchCase::IgnoreCase,
				ESearchDir::Type::FromStart,
				MTUStartIndex + 1);
			int MTULength = (MTUEndIndex - MTUStartIndex) - 1;

			MTU = FCString::Atof(*Info.Mid(MTUStartIndex + 1, MTULength));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("MTU Header Missing"));
			MTU = 0;
		}

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("IP Address Header Missing"));
		IPAddress = "";
		MTU = 0;
	}
}

void ANetBoxVisualizationController::ReplaceFlowLinkNodeIDs(
	TArray<FFlowLink>& FlowLinks,
	UG2Node* StartNode,
	UG2Node* EndNode
) {
	if (StartNode != nullptr) {
		FlowLinks[0].Source = StartNode->ID;
	}

	if (EndNode != nullptr) {
		FlowLinks[FlowLinks.Num() - 1].Target = EndNode->ID;
	}
}

void ANetBoxVisualizationController::RequestNetboxRegionsGet()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxRegionsGetResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRegionsGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxRegionsGetResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful && 
		!ResponseContentString.Contains("\"error\": \"connection to server at")
	) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxRegionResponse NetboxRegionResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString, 
				&NetboxRegionResponse
			)
		) {
			AsyncTask(ENamedThreads::GameThread, [this, NetboxRegionResponse]()
			{
				ParseRegionData(NetboxRegionResponse.Results);

				RequestNetboxSitesGet();
			});
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	OnSnapshotUpdate();
}

void ANetBoxVisualizationController::RequestNetboxRegionPatch(
	FRegionStruct Region
) {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxRegionPatchResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRegionPatch(
		Region, 
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxRegionPatchResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	}
	UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
		*ResponseContentString);
}

void ANetBoxVisualizationController::RequestNetboxSitesGet()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxSitesGetResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxSitesGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxSitesGetResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful && 
		!ResponseContentString.Contains("\"error\": \"connection to server at")
	) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxSiteResponse NetboxSiteResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString,
				&NetboxSiteResponse
			)
		) {
			AsyncTask(ENamedThreads::GameThread, [this, NetboxSiteResponse]()
			{
				ParseSiteData(NetboxSiteResponse.Results);

				RequestNetboxLocationsGet();
			});
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
}

void ANetBoxVisualizationController::RequestNetboxSitePatch(FSiteStruct Site) {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxSitePatchResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxSitePatch(
		Site, 
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxSitePatchResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	}
	UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
		*ResponseContentString);
}

void ANetBoxVisualizationController::RequestNetboxLocationsGet()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxLocationsGetResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxLocationsGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxLocationsGetResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful && 
		!ResponseContentString.Contains("\"error\": \"connection to server at")
	) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxLocationResponse NetboxLocationResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString, 
				&NetboxLocationResponse
			)
		) {
			AsyncTask(
				ENamedThreads::GameThread, 
				[this, NetboxLocationResponse]()
			{
				ParseLocationData(NetboxLocationResponse.Results);

				RequestNetboxRacksGet();
			});
			return;
		}
	}
		
	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
}

void ANetBoxVisualizationController::RequestNetboxLocationPatch(
	FLocationStruct Location
) {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxSitePatchResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxLocationPatch(
		Location, 
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxLocationPatchResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	}
	UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
		*ResponseContentString);
}

void ANetBoxVisualizationController::RequestNetboxRacksGet()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxRacksGetResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRacksGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxRacksGetResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful && 
		!ResponseContentString.Contains("\"error\": \"connection to server at")
	) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxRackResponse NetboxRackResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString,
				&NetboxRackResponse
			)
		) {
			AsyncTask(ENamedThreads::GameThread, [this, NetboxRackResponse]()
			{
				ParseRackData(NetboxRackResponse.Results);

				RequestNetboxDeviceTypesGet();
			});
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
}

void ANetBoxVisualizationController::RequestNetboxRackPatch(FRackStruct Rack)
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxRackPatchResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxRackPatch(
		Rack, 
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxRackPatchResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	}
	UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
		*ResponseContentString);
}

void ANetBoxVisualizationController::RequestNetboxDeviceTypesGet() {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxDeviceTypesResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDeviceTypesGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxDeviceTypesResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxDeviceTypeResponse NetboxDeviceTypeResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString,
				&NetboxDeviceTypeResponse
			)
		) {
			AsyncTask(
				ENamedThreads::GameThread, 
				[this, NetboxDeviceTypeResponse]()
			{
				ParseDeviceTypeData(NetboxDeviceTypeResponse.Results);

				RequestNetboxDevicesGet();
			});
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
}

void ANetBoxVisualizationController::RequestNetboxDevicesGet()
{
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxDevicesResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesGet(
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxDevicesResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		FNetboxDeviceResponse NetboxDeviceResponse;
		if (FJsonObjectConverter::JsonObjectStringToUStruct(
				ResponseContentString,
				&NetboxDeviceResponse
			)
		) {
			AsyncTask(ENamedThreads::GameThread, [this, NetboxDeviceResponse]()
			{
				ParseNetboxDeviceData(NetboxDeviceResponse);

				if (NetboxDeviceResponse.Next == "") {
					AsyncTask(ENamedThreads::AnyBackgroundHiPriTask,
						[this, NetboxDeviceResponse]()
						{
							CrossReferenceNodeData();
						});
				}
				else {
					FResponseDelegate Delegate;
					Delegate.BindUFunction(
						this, 
						FName("OnNetboxDevicesResponse")
					);

					UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxGet(
						NetboxDeviceResponse.Next, 
						NetboxToken, 
						Delegate
					);
				}
			});
			return;
		}		
	}

	UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
}

void ANetBoxVisualizationController::ParseNetboxDeviceData(
	const FNetboxDeviceResponse& NetboxResponse
) {
	for (FNetboxDevice NetboxDevice : NetboxResponse.Results)
	{
		UDevice* Device = NewObject<UDevice>();
		Device->ID = NetboxDevice.Id;
		Device->Url = NetboxDevice.Url;
		Device->Display = NetboxDevice.Display;
		Device->Name = NetboxDevice.Name;
		Device->Info = NetboxDevice.Custom_fields.Info;
		Device->Position = NetboxDevice.Position;

		Device->WorldLocationOffset.InitFromString(
			NetboxDevice.Custom_fields.Device_world_location_offset
		);
		Device->WorldRotationOffset.InitFromString(
			NetboxDevice.Custom_fields.Device_world_rotation_offset
		);

		TArray<FString> IPAddressStringParts;
		NetboxDevice.Primary_ip.Address.ParseIntoArray(
			IPAddressStringParts, 
			TEXT("/"), 
			true
		);
		Device->IP = IPAddressStringParts.Num() > 0 ?
			IPAddressStringParts[0] : "";

		Device->MTU = NetboxDevice.Custom_fields.Mtu;

		Device->Site = NameToSiteMap[NetboxDevice.Site.Name];

		if (!NetboxDevice.Location.Name.IsEmpty()) {
			Device->Location = NameToLocationMap[NetboxDevice.Location.Name];
		}

		if (!NetboxDevice.Rack.Name.IsEmpty()) {
			Device->Rack = NameToRackMap[NetboxDevice.Rack.Name];
		}

		Device->DeviceType = 
			ModelToDeviceTypeMap[NetboxDevice.Device_Type.Model];

		NameToDeviceMap.Add(Device->Name, Device);
	}
}

void ANetBoxVisualizationController::CrossReferenceNodeData() {
	if (!NameToSiteMap.Contains("TBD")) {
		UE_LOG(LogTemp, Error, TEXT("Required Device TBD missing. Please "
									"ensure that NetBox is running and "
									"contains a Device with the name "
									"\"TBD\""));
		return;
	}

	DevicesToUpdate.Empty();
	NewDevices.Empty();
	for (TPair<FString, UG2Node*> IDToNodePair : Snapshot->IDToNodeMap) {
		UG2Node* Node = IDToNodePair.Value;
		if (NameToDeviceMap.Contains(Node->Name))
		{
			Node->Device = NameToDeviceMap[Node->Name];

			USite* Site = Node->Device->Site;

			if (!Site->Name.Equals("TBD"))
			{
				if (Node->MTU == 0)
				{
					Node->MTU = Node->Device->MTU;
				}

				if (!Node->Device->IP.Equals(""))
				{
					Node->IP = Node->Device->IP;
				}

				if (!IsValidLatLong(Node->Latitude, Node->Longitude))
				{
					Node->Latitude = Site->Latitude;
					Node->Longitude = Site->Longitude;
				}
				else if (Site->Latitude == 0 && Site->Longitude == 0 &&
					(Node->Latitude != 0 || Node->Longitude != 0))
				{
					Site->Latitude = Node->Latitude;
					Site->Longitude = Node->Longitude;

					if (HasAuthority()) {
						RequestNetboxSitePatch(Site->ToStruct());
					}
				}
			}
		}
		else if (!IsHop(Node->Name))
		{
			UDevice* NewDevice = NewObject<UDevice>();
			NewDevice->Name = Node->Name;
			NewDevice->Site = NameToSiteMap["TBD"];
			NewDevice->Info = Node->Info;
			NewDevice->MTU = Node->MTU;
			NewDevice->Primary = Node->Primary;

			NewDevice->DeviceType = ModelToDeviceTypeMap["TBD"];

			Node->Device = NewDevice;

			NewDevices.Add(NewDevice);
			NameToDeviceMap.Add(NewDevice->Name, NewDevice);
		}
		else {
			Node->Device = NameToDeviceMap["TBD"];
		}
	}

	if (HasAuthority()) {
		NumNewBatches = NewDevices.Num() / MaxEntriesPerRequest +
			(NewDevices.Num() % MaxEntriesPerRequest == 0 ? 0 : 1);
		NumUpdateBatches = DevicesToUpdate.Num() / MaxEntriesPerRequest +
			(DevicesToUpdate.Num() % MaxEntriesPerRequest == 0 ? 0 : 1);

		if (NumNewBatches > 0)
		{
			CurrentNewBatch = 1;
			UE_LOG(LogTemp, Log, TEXT("Creating %d Devices"), NewDevices.Num());
			RequestNetboxDevicesPost();
		}
		else if (NumUpdateBatches > 0)
		{
			CurrentUpdateDevice = 1;
			UE_LOG(LogTemp, Log, TEXT("Updating %d Devices"), DevicesToUpdate.Num());
			RequestNetboxDevicesPatch();
		}
		else {
			AsyncTask(ENamedThreads::GameThread, [this]() {
				OnSnapshotUpdate();
			});
		}
	}
	else {
		AsyncTask(ENamedThreads::GameThread, [this]() {
			OnSnapshotUpdate();
		});
	}
}

bool ANetBoxVisualizationController::CompareNodeToNetboxDeviceData(UG2Node* Node) {
	if (Node->MTU == 0)
	{
		Node->MTU = Node->Device->MTU;
	}

	if (!Node->Device->IP.Equals(""))
	{
		Node->IP = Node->Device->IP;
	}

	return Node->MTU == Node->MTU;
}

void ANetBoxVisualizationController::RequestNetboxDevicesPost()
{
	TArray<FNetboxDevice> DeviceBatch;
	for (int i = 0; i < FGenericPlatformMath::Min(MaxEntriesPerRequest, NewDevices.Num()); i++)
	{
		DeviceBatch.Add(NewDevices[i]->ToStruct());
	}

	UE_LOG(LogTemp, Log, TEXT("Device Post Request %d/%d"), CurrentNewBatch, NumNewBatches);

	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxPostDeviceResponse"));
	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesPost(DeviceBatch, NetboxURL, NetboxToken, Delegate);

	CurrentNewBatch++;
}

void ANetBoxVisualizationController::OnNetboxPostDeviceResponse(FString ResponseContentString,
	bool bWasSuccessful)
{
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Post Device Batch Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		TArray<FNetboxDevice> DeviceResults; 
		if (FJsonObjectConverter::JsonArrayStringToUStruct(
				ResponseContentString, 
				&DeviceResults
			)
		) {
			for (FNetboxDevice DeviceStruct : DeviceResults) {
				UDevice* Device = NameToDeviceMap[DeviceStruct.Name];
				Device->ID = DeviceStruct.Id;
				Device->Url = DeviceStruct.Url;
				Device->Display = DeviceStruct.Display;
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Unable to parse Device Results"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Post Device Batch Unsuccessful"));
	}

	int BatchSize = FGenericPlatformMath::Min(
		MaxEntriesPerRequest, 
		NewDevices.Num()
	);

	for (int i = 0; i < BatchSize; i++) {
		NewDevices.RemoveAt(0);
	}

	if (NewDevices.Num() == 0) {
		if (NumUpdateBatches > 0)
		{
			CurrentUpdateDevice = 1;

			UE_LOG(
				LogTemp,
				Log, 
				TEXT("Updating %d Devices"), 
				DevicesToUpdate.Num()
			);

			RequestNetboxDevicesPatch();
		}
		else {
			AsyncTask(ENamedThreads::GameThread, [this]() {
				OnSnapshotUpdate();
			});
		}
	}
	else {
		RequestNetboxDevicesPost();
	}
}

void ANetBoxVisualizationController::RequestNetboxDevicesPatch()
{
	TArray<FNetboxDevice> DeviceBatch;
	for (int i = 0; 
		i < FGenericPlatformMath::Min(
			MaxEntriesPerRequest, 
			DevicesToUpdate.Num()
		);
		i++
	) {
		DeviceBatch.Add(DevicesToUpdate[i]->ToStruct());
	}

	UE_LOG(
		LogTemp, 
		Log, 
		TEXT("Device Patch Request %d/%d"),
		CurrentUpdateDevice, 
		NumUpdateBatches
	);

	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxPatchDevicesResponse"));

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesPatch(
		DeviceBatch, 
		NetboxURL, 
		NetboxToken, 
		Delegate
	);
}

void ANetBoxVisualizationController::RequestNetboxDevicePatch(
	const FNetboxDevice& Device
) {
	FResponseDelegate Delegate;
	Delegate.BindUFunction(this, FName("OnNetboxPatchDeviceResponse"));

	TArray<FNetboxDevice> Devices;
	Devices.Add(Device);

	UCesiumNetBoxVisualizationRequestLibrary::RequestNetboxDevicesPatch(
		Devices, 
		NetboxURL, 
		NetboxToken,
		Delegate
	);
}

void ANetBoxVisualizationController::OnNetboxPatchDeviceResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Request Successful"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Netbox Request Unsuccessful"));
	}
	UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
		*ResponseContentString);
}

void ANetBoxVisualizationController::OnNetboxPatchDevicesResponse(
	FString ResponseContentString,
	bool bWasSuccessful
) {
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Log, TEXT("Netbox Patch Device Batch Successful"));
		UE_LOG(LogTemp, Log, TEXT("Response Body: %s"),
			*ResponseContentString);

		TArray<FNetboxDevice> DeviceResults;
		if (!FJsonObjectConverter::JsonArrayStringToUStruct(
				ResponseContentString, 
				&DeviceResults)
		) {
			UE_LOG(LogTemp, Warning, TEXT("Unable to parse Device Results"));
		}
	}
	else {
		UE_LOG(
			LogTemp, 
			Warning, 
			TEXT("Netbox Patch Device Batch Unsuccessful")
		);
	}

	int BatchSize = FGenericPlatformMath::Min(
		MaxEntriesPerRequest, 
		DevicesToUpdate.Num()
	);

	for (int i = 0; i < BatchSize; i++) {
		DevicesToUpdate.RemoveAt(0);
	}

	if (DevicesToUpdate.Num() == 0) {
		AsyncTask(ENamedThreads::GameThread, [this]() {
			OnSnapshotUpdate();
		});
	}
	else {
		RequestNetboxDevicesPatch();
	}
}

bool ANetBoxVisualizationController::SnapshotAvailable(int SnapshotID) {
	for (FTimeStampIDPair TimeStampIDPair : AvailableSnapshots) {
		if (SnapshotID == TimeStampIDPair.ID) {
			return true;
		}
	}

	return false;
}

#include "Misc/Char.h"
bool ANetBoxVisualizationController::IsValidLatLong(
	float Latitude,
	float Longitude
) {
	return FGenericPlatformMath::Abs(Latitude - KansasLatitude) > 
		KansasThreshold ||
		FGenericPlatformMath::Abs(Longitude - KansasLongitude) > 
		KansasThreshold;
}

bool ANetBoxVisualizationController::IsHop(const FString& Name) {
	std::string NameString = std::string(TCHAR_TO_UTF8(*Name));

	if (Name.Len() < 2 || NameString[0] != 's') {
		return false;
	}

	for (int i = 1; i < Name.Len(); i++) {
		if (!std::isdigit(NameString[i])) {
			return false;
		}
	}
	return true;
}
