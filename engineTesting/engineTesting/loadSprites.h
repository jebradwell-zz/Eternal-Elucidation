#ifndef LOAD_SPRITES_H
#define LOAD_SPRITES_H

#include "tinyxml.h"

void LoadSprites( const std::string file, const std::map<std::string, sf::Image> &images, std::map<std::string, sf::Sprite> *sprites)
{
	TiXmlDocument XMLdoc(file.c_str());
	if (XMLdoc.LoadFile())
	{
		TiXmlElement *e_sprite;
		e_sprite = XMLdoc.FirstChildElement( "Level" );
		e_sprite = e_sprite->FirstChildElement("Sprites");
		e_sprite = e_sprite->FirstChildElement("Sprite");
		sf::Sprite tmp;
		while( e_sprite )
		{
			std::string spriteName = e_sprite->Attribute("name");
			std::string str("true");
			if( str.compare( e_sprite->Attribute("FlipX") ) == 0 )
				tmp.FlipX(true);
			else
				tmp.FlipX(false);

			if( str.compare( e_sprite->Attribute("FlipY") ) == 0 )
				tmp.FlipY(true);
			else
				tmp.FlipY(false);
			std::string alpha("Alpha");
			std::string add("Add");
			std::string multiply("Multiply");
			if( alpha.compare( e_sprite->Attribute("SetBlendMode") ) == 0 )
				tmp.SetBlendMode(sf::Blend::Alpha);

			else if( add.compare( e_sprite->Attribute("SetBlendMode") ) == 0 )
				tmp.SetBlendMode(sf::Blend::Add);
			else if( multiply.compare( e_sprite->Attribute("SetBlendMode") ) == 0 )
				tmp.SetBlendMode(sf::Blend::Multiply);
			else
				tmp.SetBlendMode(sf::Blend::None);

			TiXmlAttribute *Atr = e_sprite->FirstAttribute(); //name
			Atr = Atr->Next(); //get pass name
			Atr = Atr->Next(); //get pass FlipX
			Atr = Atr->Next(); //get pass FlipY
			Atr = Atr->Next(); //get pass SetBlendMode
			double CenterX, CenterY;
			Atr->QueryDoubleValue(&CenterX);
			Atr = Atr->Next(); //get pass SetCenterX
			Atr->QueryDoubleValue(&CenterY);
			tmp.SetCenter((float)CenterX, (float)CenterY);

			Atr = Atr->Next(); //get pass SetCenterY
			Atr = Atr->Next(); //get pass SetColor
			std::string tag("tag"), value("value");
			if( tag.compare(e_sprite->Attribute("SetColor")) == 0 )
			{
				std::string Black("Black"), Blue("Blue"), Cyan("Cyan"), Green("Green"),
					Magenta("Magenta"), Red("Red"), White("White"), Yellow("Yellow");
				if( Black.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Black);
				}
				else if( Blue.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Blue);
				}
				else if( Cyan.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Cyan);
				}
				else if( Green.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Green);
				}
				else if( Magenta.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Magenta);
				}
				else if( Red.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Red);
				}
				else if( White.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::White);
				}
				else if( Yellow.compare(e_sprite->Attribute("Color")) == 0 )
				{
					tmp.SetColor(sf::Color::Yellow);
				}
				else
				{
					std::cout << "Error: Color attribute {" << e_sprite->Attribute("Color") << "was not found" << std::endl;
				}
				Atr = Atr->Next(); //get pass Color
				Atr = Atr->Next(); //get pass R
				Atr = Atr->Next(); //get pass G
				Atr = Atr->Next(); //get pass B
				Atr = Atr->Next(); //get pass A
			}
			else if( value.compare(e_sprite->Attribute("SetColor")) == 0 )
			{
				int r, g, b, a;
				Atr = Atr->Next(); //get pass Color
				Atr->QueryIntValue(&r);
				Atr = Atr->Next(); //get pass R
				Atr->QueryIntValue(&g);
				Atr = Atr->Next(); //get pass G
				Atr->QueryIntValue(&b);
				Atr = Atr->Next(); //get pass B
				Atr->QueryIntValue(&a);
				Atr = Atr->Next(); //get pass A
				tmp.SetColor(sf::Color::Color((sf::Uint8)r,(sf::Uint8)g,(sf::Uint8)b,(sf::Uint8)a));
			}
			else
			{
				Atr = Atr->Next(); //get pass Color
				Atr = Atr->Next(); //get pass R
				Atr = Atr->Next(); //get pass G
				Atr = Atr->Next(); //get pass B
				Atr = Atr->Next(); //get pass A
			}
			Atr = Atr->Next(); //get pass SetImage
			tmp.SetImage( images.find(e_sprite->Attribute("SetImage"))->second );
			double rot, scaleX, scaleY, L, T, R, B;
			Atr->QueryDoubleValue(&rot);
			tmp.SetRotation((float)rot);
			Atr = Atr->Next(); //get pass SetRotation
			Atr->QueryDoubleValue(&scaleX);
			tmp.SetScaleX((float)scaleX);
			Atr = Atr->Next(); //get pass SetScaleX
			Atr->QueryDoubleValue(&scaleY);
			tmp.SetScaleY((float)scaleY);
			Atr = Atr->Next(); //get pass SetScaleY
			Atr->QueryDoubleValue(&L);
			Atr = Atr->Next(); //get pass SetSubRectL
			Atr->QueryDoubleValue(&T);
			Atr = Atr->Next(); //get pass SetSubRectT
			Atr->QueryDoubleValue(&R);
			Atr = Atr->Next(); //get pass SetSubRectR
			Atr->QueryDoubleValue(&B);
			tmp.SetSubRect(sf::Rect<int>((int)L,(int)T,(int)R,(int)B));	
			double X, Y;
			Atr = Atr->Next(); //get pass SetSubRectB
			Atr->QueryDoubleValue(&X);
			Atr = Atr->Next(); //get pass SetX
			Atr->QueryDoubleValue(&Y);
			tmp.SetX((float)X);
			tmp.SetY((float)Y);

			//add the sprite to the dictionary/map
			sprites->insert(std::pair<std::string, sf::Sprite>( spriteName, tmp ) );
			e_sprite = e_sprite->NextSiblingElement("Sprite");
		}
	}
}


#endif