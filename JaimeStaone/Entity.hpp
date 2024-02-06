#pragma once 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <algorithm>

class Entity {
public:
	std::string id;

	// Graphical object
	sf::Texture texture;
	sf::Sprite sprite;

	// Base coordinates
	int cx;
	int cy;
	float xr;
	float yr;

	// Resulting coordinates
	float xx;
	float yy;

	// Movements
	float dx;
	float dy;

	float speed;

	Entity();

	Entity(std::string name, float x, float y);

	void update();

	void hascollision(int cx, int cy);

	void setCoordinates(float x, float y);

	void setSprite(std::string path);

	float clamp(float valeur, float min, float max);

};