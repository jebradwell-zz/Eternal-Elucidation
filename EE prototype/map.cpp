///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file map.cpp
///
/// @brief
/// Defines the map class functions.
///
/// @remarks
/// Basicly this file has functions which initualize a map object from a given
/// XML file, or initualizes to all default values if there is no XML file passed.
////////////////////////////////////////////////////////////////////////////////

#include "map.h"

#include <string>
#include <sstream>

#include "tinyxml.h"

#define _CRT_SECURE_NO_WARNINGS

//using namespace std;

/// Map Constructor.
///
/// constructs an empty Map object. All member variables are
/// set to defaults
/// @see Map Defaults Document
Map::Map()
{
}

/// Map Constructor.
///
/// takes a map xml file name{string} and initualizes a map object from the XML file.
Map::Map( const char *mapFile )
{
	load(mapFile);
}

Map::~Map()
{
}

void Map::load(const char *mapFile)
{
	TiXmlDocument XMLdoc(mapFile);
	if (XMLdoc.LoadFile())
	{
		TiXmlElement *e_mapName, *e_width, *e_height, *e_levelTotal, *e_tileDes, *e_tile;

		e_mapName = XMLdoc.FirstChildElement( "mapName" );
		if( e_mapName )
		{
			this->mapName = e_mapName->GetText();
		}
		e_width = XMLdoc.FirstChildElement( "width" );
		if( e_width )
		{
			this->width = atoi( e_width->GetText() );
		}
		e_height = XMLdoc.FirstChildElement( "height" );
		if( e_height )
		{
			this->height = atoi( e_height->GetText() );
		}
		e_levelTotal = XMLdoc.FirstChildElement( "levelTotal" );
		if( e_levelTotal )
		{
			this->levelTotal = atoi( e_levelTotal->GetText() );
		}
		e_tile = XMLdoc.FirstChildElement( "tile" );
		while(  e_tile )
		{
			Tile tmptile;
			tmptile.chipSetName = e_tile->Attribute("chipSetName");
			tmptile.tileID = atoi(e_tile->Attribute("tileID"));
			tmptile.srcX = (float)atof(e_tile->Attribute("srcX"));
			tmptile.srcY = (float)atof(e_tile->Attribute("srcY"));
			tmptile.width = atoi(e_tile->Attribute("width"));
			tmptile.height = atoi(e_tile->Attribute("height"));
			tmptile.rotation = atoi(e_tile->Attribute("rotation"));
			tmptile.level = atoi(e_tile->Attribute("level"));
			tmptile.terrainType = atoi(e_tile->Attribute("terrainType"));
			this->tiles.push_back(tmptile);
			e_tile = e_tile->NextSiblingElement("tile");
		}
		e_tileDes = XMLdoc.FirstChildElement( "tileDes" );
		while(e_tileDes)
		{
			std::pair<unsigned int, std::pair<float, float> > tmptile;
			tmptile.first = atoi( e_tileDes->Attribute("tileID") );
			tmptile.second.first = (float)atof( e_tileDes->Attribute("desX") );
			tmptile.second.second = (float)atof( e_tileDes->Attribute("desY") );
			this->tileDestionations.push_back( tmptile );
			e_tileDes = e_tileDes->NextSiblingElement("tileDes");
		}
	}
}

void Map::save(const char *mapFile)
{
	TiXmlDocument doc;  
	TiXmlElement *e_mapName, *e_width, *e_height, *e_levelTotal, *e_tile, *e_tileDes;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  

	e_mapName = new TiXmlElement( "mapName" );  
	doc.LinkEndChild( e_mapName );
	e_mapName->LinkEndChild( new TiXmlText( this->mapName.c_str() ) );

	e_width = new TiXmlElement( "width" );  
	doc.LinkEndChild( e_width );
	//convertedInt.seekp(0);
	//convertedInt << this->width;
	e_width->LinkEndChild( new TiXmlText( to_string(this->width) ) );

	e_height = new TiXmlElement( "height" );  
	doc.LinkEndChild( e_height );
	e_height->LinkEndChild( new TiXmlText( to_string(this->height) ) );

	e_levelTotal = new TiXmlElement( "levelTotal" );  
	doc.LinkEndChild( e_levelTotal );
	e_levelTotal->LinkEndChild( new TiXmlText( to_string(this->levelTotal) ) );

	for( unsigned int i = 0; i < this->tiles.size(); i++ )
	{
		//commented out because gcc says it's not used... -Ron
		//		char *tmpstr = (char*)"";
		e_tile = new TiXmlElement( "tile" );
		doc.LinkEndChild( e_tile );
		e_tile->SetAttribute("chipSetName", this->tiles.at(i).chipSetName);
		e_tile->SetAttribute("tileID", to_string(this->tiles.at(i).tileID) );
		e_tile->SetAttribute("srcX", to_string(this->tiles.at(i).srcX));
		e_tile->SetAttribute("srcY", to_string(this->tiles.at(i).srcY));
		e_tile->SetAttribute("width", to_string(this->tiles.at(i).width) );
		e_tile->SetAttribute("height", to_string(this->tiles.at(i).height) );
		e_tile->SetAttribute("rotation", to_string(this->tiles.at(i).rotation) );
		e_tile->SetAttribute("level", to_string(this->tiles.at(i).level) );
		e_tile->SetAttribute("terrainType", to_string(this->tiles.at(i).terrainType) );
	}

	for( unsigned int i = 0; i < this->tileDestionations.size(); i++ )
	{
		//commented out to keep gcc quiet... -Ron
		//		char *tmpstr = "";
		e_tileDes = new TiXmlElement( "tileDes" );
		doc.LinkEndChild( e_tileDes );
		e_tileDes->SetAttribute("tileID", this->tileDestionations.at(i).first);
		e_tileDes->SetAttribute("desX", to_string(this->tileDestionations.at(i).second.first) );
		e_tileDes->SetAttribute("desY", to_string(this->tileDestionations.at(i).second.second) );
	}

	doc.SaveFile(mapFile);
}