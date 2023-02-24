#include "Region.h"

URegion::URegion() {

}

URegion::~URegion() {

}

FRegionStruct URegion::ToStruct() {
	FRegionStruct Region;
	Region.Id = ID;
	Region.Url = Url;
	Region.Name = Name;
	Region.Slug = Slug;
	Region.Description = Description;

	Region.Custom_fields.Logo = LogoUrl;
	Region.Custom_fields.Region_latitude = FString::SanitizeFloat(Latitude);
	Region.Custom_fields.Region_longitude = FString::SanitizeFloat(Longitude);

	Region.Parent.Name = ParentName;

	return Region;
}
