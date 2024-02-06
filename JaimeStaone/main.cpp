#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Cst.hpp"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(Cst::WINDOW_WIDTH, Cst::WINDOW_HEIGHT), "JaimeStaone!");

    Entity player(Cst::PLAYER, Cst::WINDOW_WIDTH / 2, Cst::WINDOW_HEIGHT);
    player.setSprite("../art/player.png");

    Entity ufo(Cst::UFO, Cst::WINDOW_WIDTH / 2, 0);
    ufo.setSprite("../art/ufo.png");

    std::vector<Entity> bullets(0);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Entity bullet(Cst::BULLET, player.xx, player.yy);
            bullet.setSprite("../art/bullet.png");
            bullets.push_back(bullet);
        }

        window.clear();
        player.update();
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].update();
            window.draw(bullets[i].sprite);
        }
        window.draw(player.sprite);
        window.draw(ufo.sprite);

        window.display();
    }

    return 0;
}
