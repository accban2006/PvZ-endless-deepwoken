#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <memory>
#include <fstream>
#include <map>

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Zombie.h"
#include "Pea.h"
#include "Sun.h"
#include "Constants.h"
#include "AssetManager.h"  // Make sure to include this

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Plants vs. Zombies");
    window.setFramerateLimit(FPS);

   
    AssetManager& assetManager = AssetManager::getInstance();
    assetManager.loadTexture("sunflower", "resources/sunflower.png");
    assetManager.loadTexture("peashooter", "resources/peashooter.png");
    assetManager.loadTexture("zombie", "resources/zombie.png");
    assetManager.loadTexture("pea", "resources/pea.png");
    assetManager.loadTexture("sun", "resources/sun.png");

    
    std::list<std::unique_ptr<GameObject>> gameObjects;
    int sunScore = 50;
    float zombieSpawnTimer = 5.0f;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, ROWS - 1);

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int clickedRow = mousePos.y / GRID_SIZE;
                int clickedCol = mousePos.x / GRID_SIZE;

                for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
                    if (Sun* sun = dynamic_cast<Sun*>(it->get())) {
                        if (sun->sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            sunScore += sun->value;
                            it->get()->health = 0;
                            break;
                        }
                    }
                }

                // Plant placement (now just checks for clicks, doesn't create objects directly)
                if (event.mouseButton.button == sf::Mouse::Left) {
                     bool canPlace = true;
                    //Check no plant in that cell
                    for (const auto& obj : gameObjects) {
                        if ((dynamic_cast<Sunflower*>(obj.get()) || dynamic_cast<Peashooter*>(obj.get())) && obj->row == clickedRow && obj->col == clickedCol)
                        {
                            canPlace = false;
                            break;

                        }
                    }
                    if(canPlace)
                    {
                        if (sunScore >= 50) { // Enough sun to plant
                            gameObjects.emplace_back(std::make_unique<Sunflower>(clickedRow, clickedCol)); //make sunflower
                            sunScore -= 50;
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    bool canPlace = true;
                    //Check no plant in that cell
                    for (const auto& obj : gameObjects) {
                        if ((dynamic_cast<Sunflower*>(obj.get()) || dynamic_cast<Peashooter*>(obj.get())) && obj->row == clickedRow && obj->col == clickedCol)
                        {
                            canPlace = false;
                            break;

                        }
                    }
                    if(canPlace)
                    {
                        if (sunScore >= 100) { // Enough sun to plant
                            gameObjects.emplace_back(std::make_unique<Peashooter>(clickedRow, clickedCol));//make peashooter
                            sunScore -= 100;
                        }
                    }
                }
            }
        }

     
        zombieSpawnTimer -= deltaTime;
        if (zombieSpawnTimer <= 0.0f) {
            gameObjects.emplace_back(std::make_unique<Zombie>(rowDist(gen), COLS - 1));  //create Zombie
            zombieSpawnTimer = 5.0f;
        }

        for (auto& obj : gameObjects) {
            obj->update(gameObjects, deltaTime);
        }

        gameObjects.remove_if([](const std::unique_ptr<GameObject>& obj) {
            return obj->health <= 0;
        });

    
        window.clear(sf::Color(100, 200, 100));

     
        for (int i = 0; i <= ROWS; i++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, i * GRID_SIZE)),
                sf::Vertex(sf::Vector2f(SCREEN_WIDTH, i * GRID_SIZE))
            };
            window.draw(line, 2, sf::Lines);
        }
        for (int i = 0; i <= COLS; i++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(i * GRID_SIZE, 0)),
                sf::Vertex(sf::Vector2f(i * GRID_SIZE, SCREEN_HEIGHT))
            };
            window.draw(line, 2, sf::Lines);
        }


      
        for (const auto& obj : gameObjects) {
            obj->draw(window);
        }

      
        sf::Font font;
        if(!font.loadFromFile("arial.ttf")){//check font file exists.
          std::cerr<<"Error: Font file 'arial.ttf' not found."<<std::endl;
          return 1;
        }
        sf::Text sunText("Sun: " + std::to_string(sunScore), font, 24);
        sunText.setPosition(10,10);
        sunText.setFillColor(sf::Color::Black);
        window.draw(sunText);

        window.display();
    }

    return 0;
}
