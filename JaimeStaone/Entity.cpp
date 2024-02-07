#include "Entity.hpp" 
#include "Cst.hpp"
#include <SFML/Graphics.hpp>

Entity::Entity() {
}

Entity::Entity(std::string path, float x, float y) {
    setCoordinates(x, y);
    dx = 0;
    dy = 0;
    setSprite(path);
}

void Entity::hascollision(int cx, int cy) {

}

void Entity::setCoordinates(float x, float y) {
    xx = x;
    yy = y;
    cx = xx / Cst::GAME_GRID;
    cy = yy / Cst::GAME_GRID;
    xr = (xx - cx * Cst::GAME_GRID) / Cst::GAME_GRID;
    yr = (yy - cy * Cst::GAME_GRID) / Cst::GAME_GRID;
}

void Entity::setSprite(std::string path) {
    if (!texture.loadFromFile(path))
    {
        printf("Error loading png file: %s", path);
    }
    sprite.setTexture(texture);
    textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x / 2, textureSize.y/2);
}

void Entity::update() {
    if (isEnemy) {
        sf::Vector2f direction = targetPosition - sf::Vector2f(xx, yy);
        float factor = sqrt((direction.x * direction.x) + (direction.y * direction.y));
        // Arrived at destination, going back;
        if (factor < Cst::THRESHOLD_FLOAT) {
            auto tmpVector = targetPosition;
            targetPosition = originPosition;
            originPosition = tmpVector;
        }
        direction /= factor;
        dx += direction.x * speed;
        dy += direction.y * speed;
    }
    xr += dx;
    while (xr > 1) { xr--; cx++;}
    while (xr < 0) { xr++; cx--;}
    yr += dy;
    while (yr > 1) { yr--; cy++; }
    while (yr < 0) { yr++; cy--; }
    
    xx = (cx + xr) * Cst::GAME_GRID;
    yy = (cy + yr) * Cst::GAME_GRID;
    // Enemy can exist offscreen.
    if (!isEnemy) {
        xx = clamp(xx, textureSize.x / 2, Cst::WINDOW_WIDTH - textureSize.x / 2);
        yy = clamp(yy, textureSize.y / 2, Cst::WINDOW_HEIGHT - textureSize.y / 2);
    }


        
    sprite.setPosition(xx, yy );
    if (isEnemy) {
        sprite.rotate(0.01);
    }
    dx = 0;
    dy = 0;
}

float Entity::clamp(float valeur, float min, float max) {
    return std::min(std::max(valeur, min), max);
}

sf::Vector2f Entity::getFirePositionLeft() {
    return sf::Vector2f(xx - textureSize.x / 2 , yy - textureSize.y/3);
}


sf::Vector2f Entity::getFirePositionRight() {
    return sf::Vector2f(xx + textureSize.x / 2, yy - textureSize.y/3);
}


bool Entity::isOffScreen() {
    if (xx > (Cst::WINDOW_WIDTH + textureSize.x)
        || xx < -static_cast<int>(textureSize.x)
        || yy < -static_cast<int>(textureSize.y)
        || yy > Cst::WINDOW_HEIGHT + textureSize.y) {
        return true;
    }
    return false;
}


EnemiesPool* EnemiesPool::INSTANCE = nullptr;

EnemiesPool::EnemiesPool(int size) {
    for (int i = 0; i < size; ++i) {
        enemies.push_back(new Entity());
    }
}

EnemiesPool::~EnemiesPool() {
    for (auto entity : enemies) {
        delete entity;
    }
}

Entity* EnemiesPool::get() {
    if (enemies.empty()) {
        enemies.push_back(new Entity());
    }

    Entity* enemy = enemies.back();
    enemies.pop_back();
    enemiesToRender.push_back(enemy);
    return enemy;
}

void EnemiesPool::recycle(Entity* enemie) {
    auto it = std::find(enemiesToRender.begin(), enemiesToRender.end(), enemie);
    if (it != enemiesToRender.end()) {
        enemiesToRender.erase(it);
    }
    enemies.push_back(enemie);
}

std::vector<Entity*> EnemiesPool::getEntitiesToRender() {
    return enemiesToRender;
}
