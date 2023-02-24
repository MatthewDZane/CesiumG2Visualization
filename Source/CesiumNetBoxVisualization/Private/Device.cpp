#include "Device.h"

UDevice::UDevice() {

}

UDevice::~UDevice() {

}

FNetboxDevice UDevice::ToStruct() {
	FNetboxDevice Device;
	Device.Id = ID;
	Device.Url = Url;
	Device.Name = Name;
	Device.Primary_ip.Address = IP;

	Device.Custom_fields.Device_world_location_offset = WorldLocationOffset.ToString();
	Device.Custom_fields.Device_world_rotation_offset = WorldRotationOffset.ToString();
	Device.Custom_fields.Info = Info;
	Device.Custom_fields.Mtu = MTU;
	Device.Custom_fields.Primary = Primary;

	if (Site != nullptr) {
		Device.Site.Id = Site->ID;
		Device.Site.Url = Site->Url;
		Device.Site.Display = Site->Display;
		Device.Site.Name = Site->Name;
		Device.Site.Slug = Site->Slug;
	}

	if (Location != nullptr) {
		Device.Location.Id = Location->ID;
		Device.Location.Url = Location->Url;
		Device.Location.Display = Location->Display;
		Device.Location.Name = Location->Name;
		Device.Location.Slug = Location->Slug;
	}

	if (Rack != nullptr) {
		Device.Rack.Id = Rack->ID;
		Device.Rack.Url = Rack->Url;
		Device.Rack.Display = Rack->Display;
		Device.Rack.Name = Rack->Name;
	}

	return Device;
}
