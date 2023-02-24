#include "Site.h"

USite::USite()
{
	
}

USite::USite(int IDIn, FString UrlIn, FString DisplayIn, FString NameIn,
	FString SlugIn, float LatitudeIn, float LongitudeIn) {
	ID = IDIn;
	Url = UrlIn;
	Display = DisplayIn;
	Name = NameIn;
	Slug = SlugIn;

	Latitude = LatitudeIn;
	Longitude = LongitudeIn;
}

USite::~USite()
{
	
}

FSiteStruct USite::ToStruct()
{
	FSiteStruct Site;
	Site.Id = ID;
	Site.Url = Url;
	Site.Display = Display;
	Site.Name = Name;
	Site.Slug = Slug;
	Site.Latitude = Latitude;
	Site.Longitude = Longitude;

	return Site;
}
