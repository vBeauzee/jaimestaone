#include "Entity.hpp" 
#include "Cst.hpp"

Entity::Entity() {
}

Entity::Entity(std::string name, float x, float y) {
    id = name;
    setCoordinates(x, y);
    dx = 0;
    dy = 0;
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
        printf("Error loading png file.");
    }
    sprite.setTexture(texture);
}

void Entity::update() {
    if (Cst::BULLET.compare(id) == 0) {
        dy = -0.001;
    }

    xr += dx;
    while (xr > 1) { xr--; cx++;}
    while (xr < 0) { xr++; cx--;}
    yr += dy;
    while (yr > 1) { yr--; cy++; }
    while (yr < 0) { yr++; cy--; }
    
    auto textureSize = texture.getSize();
    xx = clamp( (cx + xr) * Cst::GAME_GRID, textureSize.x / 2, Cst::WINDOW_WIDTH - textureSize.x/2);
    yy = clamp( (cy + yr) * Cst::GAME_GRID, textureSize.y / 2, Cst::WINDOW_HEIGHT - textureSize.y/2);
        
    sprite.setPosition(xx - textureSize.x/2, yy - textureSize.y / 2);
    //printf("Sprite %d has position %d:%d\n", id, xx, yy);
    dx = 0;
    dy = 0;
}

float Entity::clamp(float valeur, float min, float max) {
    return std::min(std::max(valeur, min), max);
}
