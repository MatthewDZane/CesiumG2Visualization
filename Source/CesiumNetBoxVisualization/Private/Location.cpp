#include "Location.h"

ULocation::ULocation() {

}

ULocation::~ULocation() {

}

FLocationStruct ULocation::ToStruct() {
	FLocationStruct Location;
	Location.Id = ID;
	Location.Url = Url;
	Location.Display = Display;
	Location.Name = Name;
	Location.Slug = Slug;

	if (Site != nullptr) {
		Location.Site.Id = Site->ID;
		Location.Site.Url = Site->Url;
		Location.Site.Display = Site->Display;
		Location.Site.Name = Site->Name;
		Location.Site.Slug = Site->Slug;
	}

	if (Parent != nullptr) {
		Location.Parent.Id = Site->ID;
		Location.Parent.Url = Site->Url;
		Location.Parent.Display = Site->Display;
		Location.Parent.Name = Site->Name;
		Location.Parent.Slug = Site->Slug;
	}

	return Location;
}
