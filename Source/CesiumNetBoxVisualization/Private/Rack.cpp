#include "Rack.h"

URack::URack() {

}

URack::~URack() {

}

FRackStruct URack::ToStruct() {
	FRackStruct Rack;
	Rack.Id = ID;
	Rack.Url = Url;
	Rack.Display = Display;
	Rack.Name = Name;

	Rack.Facility_id = FacilityID;
	Rack.Status.Value = Status;
	Rack.Role = Role;
	Rack.Serial = Serial;
	Rack.Asset_tag = AssetTag;
	Rack.Type.Value = Type;
	Rack.Width.Value = FString::SanitizeFloat(Width);
	Rack.Width.Label = Rack.Width.Value + " inches";

	Rack.Outer_width = OuterWidth;
	Rack.Outer_depth = OuterDepth;
	Rack.Outer_unit = OuterUnit;

	Rack.Comments = Comments;

	Rack.Custom_fields.Rack_latitude = RackLatitude;
	Rack.Custom_fields.Rack_longitude = RackLongitude;
	Rack.Custom_fields.Rack_world_location_offset = WorldLocationOffset.ToString();
	Rack.Custom_fields.Rack_world_rotation_offset = WorldRotationOffset.ToString();

	if (Site != nullptr) {
		Rack.Site.Id = Site->ID;
		Rack.Site.Url = Site->Url;
		Rack.Site.Display = Site->Display;
		Rack.Site.Name = Site->Name;
		Rack.Site.Slug = Site->Slug;
	}

	if (Location != nullptr) {
		Rack.Location.Id = Location->ID;
		Rack.Location.Url = Location->Url;
		Rack.Location.Display = Location->Display;
		Rack.Location.Name = Location->Name;
		Rack.Location.Slug = Location->Slug;
	}

	return Rack;
}
