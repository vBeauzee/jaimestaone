#pragma once 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <algorithm>

class Entity {
public:

	// Graphical object
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2u textureSize;

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

	// target destination
	float tx;
	float ty;

	// Check overlaps
	float radius;

	bool kill;

	Entity();

	Entity(std::string path, float x, float y);

	virtual void update();

	void hascollision(int cx, int cy);

	void setCoordinates(float x, float y);

	void setSprite(std::string path);

	float clamp(float valeur, float min, float max);

	sf::Vector2f getFirePositionLeft();
	sf::Vector2f getFirePositionRight();

	bool isOffScreen();

};

class EnemiesPool {
public:
	EnemiesPool(int size);
	~EnemiesPool();
	static EnemiesPool* INSTANCE;

	std::vector<Entity*> enemies;
	std::vector<Entity*> enemiesToRender; // Vecteur contenant tous les enemies actuellement utilisées


	Entity* get();
	void recycle(Entity* enemy);
	std::vector<Entity*> getEntitiesToRender();

};