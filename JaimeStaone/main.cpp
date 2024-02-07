#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Cst.hpp"
#include <vector>
#include "LevelFileReader.hpp"



void fire(sf::Vector2f startPosition) {
    Bullet* bullet = BulletPool::INSTANCE->get();
    bullet->setCoordinates(startPosition);
    bullet->setSprite("../art/bullet.png");
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Cst::WINDOW_WIDTH, Cst::WINDOW_HEIGHT), "JaimeStaone!");

    Entity player("../art/player.png", Cst::WINDOW_WIDTH / 2, Cst::WINDOW_HEIGHT);

    BulletPool bulletPool(10);
    BulletPool::INSTANCE = &bulletPool;
    EnemiesPool enemiesPool(10);
    EnemiesPool::INSTANCE = &enemiesPool;
   
    LevelFileReader levelInit;
    levelInit.readFile();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.dx = -0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.dx = 0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.dy = -0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.dy = 0.001;
        }
        sf::Time elapsedTime = clock.getElapsedTime();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsedTime > Cst::FIRE_COOLDOWN)
        {
            fire(player.getFirePositionLeft());
            fire(player.getFirePositionRight());
            clock.restart();
        }

        window.clear();
        player.update();
        //if (EnemiesPool::INSTANCE->enemiesToRender.empty()) {
        //    initEnemies(5);
        //}
        window.draw(player.sprite);
        for (auto bullet : bulletPool.getBulletsToRender())
        {
            bullet->update();
            window.draw(bullet->sprite);
        }
        for (auto enemy : EnemiesPool::INSTANCE->enemiesToRender)
        {
            if (enemy != nullptr) {
                enemy->update();
                window.draw(enemy->sprite);           
            }
        }       
        window.display();

        //check pool size
        //printf(" pool : available %d | rendered %d\n", BulletPool::INSTANCE->bullets.size(), BulletPool::INSTANCE->bulletsToRender.size());
    }

    return 0;
}
