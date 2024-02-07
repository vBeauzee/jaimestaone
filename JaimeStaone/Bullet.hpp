#pragma once
#include "Entity.hpp"

class Bullet : public Entity {
public:
	std::vector<Bullet> bullets;

	Bullet();

	void update() override;
	void setCoordinates(sf::Vector2f position);
	void checkCollisions();
};

class BulletPool {
public:
	BulletPool(int size);
	~BulletPool();
	static BulletPool* INSTANCE;

	std::vector<Bullet*> bullets;
	std::vector<Bullet*> bulletsToRender; // Vecteur contenant toutes les balles actuellement utilisées


	Bullet* get();
	void recycle(Bullet* bullet);
	std::vector<Bullet*> getBulletsToRender();

};