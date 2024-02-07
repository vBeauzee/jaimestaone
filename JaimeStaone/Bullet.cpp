#include "Bullet.hpp"
#include <string>
#include "Cst.hpp"
#include <vector>

Bullet::Bullet() {
    Entity::setSprite("../art/bullet.png");
}

void Bullet::update() {
    checkCollisions();
	dy = -0.005;

    xr += dx;
    while (xr > 1) { xr--; cx++; }
    while (xr < 0) { xr++; cx--; }
    yr += dy;
    while (yr > 1) { yr--; cy++; }
    while (yr < 0) { yr++; cy--; }

    xx = (cx + xr) * Cst::GAME_GRID;
    yy = (cy + yr) * Cst::GAME_GRID;

    if (isOffScreen()) {
        BulletPool::INSTANCE->recycle(this);
    }
    else {
        sprite.setPosition(xx - textureSize.x / 2, yy - textureSize.y / 2);
    }
    dx = 0;
    dy = 0;
}

void Bullet::setCoordinates(sf::Vector2f position) {
    Entity::setCoordinates(position.x, position.y);
}

BulletPool* BulletPool::INSTANCE = nullptr;

BulletPool::BulletPool(int size) {
        for (int i = 0; i < size; ++i) {
            bullets.push_back(new Bullet());
        }
    }

BulletPool::~BulletPool() {
        for (auto bullet : bullets) {
            delete bullet;
        }
    }

Bullet* BulletPool::get() {
    if (bullets.empty()) {
        bullets.push_back(new Bullet());
    }

    Bullet* bullet = bullets.back();
    bullets.pop_back();
    bulletsToRender.push_back(bullet);
    return bullet;
}

void BulletPool::recycle(Bullet* bullet) {
    auto it = std::find(bulletsToRender.begin(), bulletsToRender.end(), bullet);
    if (it != bulletsToRender.end()) {
        bulletsToRender.erase(it);
    }
    bullets.push_back(bullet);
}

std::vector<Bullet*> BulletPool::getBulletsToRender() {
    return bulletsToRender;
}

void Bullet::checkCollisions() {
    for (auto enemy : EnemiesPool::INSTANCE->enemiesToRender) {
        if (enemy != nullptr) {
            if (abs(cx - enemy->cx) <= 2 && abs(cy - enemy->cy) <= 2) {
                auto dist = sqrt((enemy->xx - xx) * (enemy->xx - xx) + (enemy->yy - yy) * (enemy->yy - yy));
                if (dist <= radius + enemy->radius) {
                    printf("Enemy kill!\n");
                    enemy->kill = true;
                    EnemiesPool::INSTANCE->recycle(enemy);
                }
            }
        }
    }
}

