#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Cst.hpp"
#include <vector>
#include "LevelFileReader.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


void fire(sf::Vector2f startPosition) {
    Bullet* bullet = BulletPool::INSTANCE->get();
    bullet->setCoordinates(startPosition);
    bullet->setSprite("../art/bullet.png");
}

void manageInput(Entity& player, sf::Clock& fireCooldownClock) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.dx = -player.speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.dx = player.speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.dy = -player.speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.dy = player.speed;
    }
    sf::Time elapsedTime = fireCooldownClock.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && elapsedTime > Cst::FIRE_COOLDOWN)
    {
        fire(player.getFirePositionLeft());
        fire(player.getFirePositionRight());
        fireCooldownClock.restart();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Cst::WINDOW_WIDTH, Cst::WINDOW_HEIGHT), "JaimeStaone!");
    ImGui::SFML::Init(window);

    Entity player("../art/player.png", Cst::WINDOW_WIDTH / 2, Cst::WINDOW_HEIGHT);
    player.speed = 0.001;

    BulletPool bulletPool(10);
    BulletPool::INSTANCE = &bulletPool;
    EnemiesPool enemiesPool(10);
    EnemiesPool::INSTANCE = &enemiesPool;
   
    LevelFileReader levelInit;
    levelInit.readFile();

    sf::Clock fireCooldownClock;
    sf::Clock imguiClock;
    float backgroundColor[3] = {
        (float)31 / 255,
        (float)0 / 255,
        (float)44 / 255
    };
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }


        ImGui::SFML::Update(window, imguiClock.restart());
        
        ImGui::Begin("Inspector");
        ImGui::Text("Framerate: %.1d FPS", ImGui::GetIO().Framerate);
        if (ImGui::TreeNode("Enemies")) {
            ImGui::Text("Rendered: %d", EnemiesPool::INSTANCE->enemiesToRender.size());
            ImGui::Text("In pool: %d", EnemiesPool::INSTANCE->enemies.size());
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Bullets")) {
            ImGui::Text("Rendered: %d", BulletPool::INSTANCE->bulletsToRender.size());
            ImGui::Text("In pool: %d", BulletPool::INSTANCE->bullets.size());
            ImGui::TreePop();
        }
        ImGui::SeparatorText("Kill enemies");
        for (auto enemy : EnemiesPool::INSTANCE->enemiesToRender)
        {
            if (ImGui::Button(("Kill " + enemy->name).c_str()))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                EnemiesPool::INSTANCE->recycle(enemy);
        }
        ImGui::SeparatorText("Background color");
        ImGui::ColorEdit3("", backgroundColor);
        ImGui::End();


        manageInput(player, fireCooldownClock);
        window.clear(sf::Color((int)(backgroundColor[0]*255), (int)(backgroundColor[1]*255), (int)(backgroundColor[2]*255)));
        player.update();
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
        ImGui::SFML::Render(window);
        window.display();

        //check pool size
        //printf(" pool : available %d | rendered %d\n", BulletPool::INSTANCE->bullets.size(), BulletPool::INSTANCE->bulletsToRender.size());
    }

    ImGui::SFML::Shutdown();
    return 0;
}
