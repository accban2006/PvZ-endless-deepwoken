#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <memory>
#include <fstream> 

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Zombie.h"
#include "Pea.h"
#include "Sun.h"
#include "Constants.h"

bool loadTexture(sf::Texture& texture, const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }
    return true;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Plants vs. Zombies");
    window.setFramerateLimit(FPS);

    sf::Texture sunflowerTexture, peashooterTexture, zombieTexture;
    if (!loadTexture(sunflowerTexture, "resources/sunflower.png") ||
        !loadTexture(peashooterTexture, "resources/peashooter.png") ||
        !loadTexture(zombieTexture, "resources/zombie.png") ||
        !loadTexture(Sunflower::sunTexture, "resources/sun.png") ||
        !loadTexture(Peashooter::peaTexture, "resources/pea.png")) {
        return 1;
    }

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
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int clickedRow = mousePos.y / GRID_SIZE;
                int clickedCol = mousePos.x / GRID_SIZE;

                for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
                    if (Sun* sun = dynamic_cast<Sun*>(it->get())) {
                        if (sun->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            sunScore += sun->value;
                            it->get()->health = 0; 
                            break;
                        }
                    }
                }

                if (sunScore >= 50) {
                    bool canPlace = true;
                    for (const auto& obj : gameObjects) {
                        if ((dynamic_cast<Sunflower*>(obj.get()) || dynamic_cast<Peashooter*>(obj.get())) && obj->row == clickedRow && obj->col == clickedCol) {
                            canPlace = false;
                            break;
                        }
                    }
                    if (canPlace && event.mouseButton.button == sf::Mouse::Left) {
                        gameObjects.emplace_back(std::make_unique<Sunflower>(clickedRow, clickedCol, sunflowerTexture));
                        sunScore -= 50;
                    }
                }
                if (sunScore >= 100) {
                    bool canPlace = true;
                    for (const auto& obj : gameObjects) {
                        if ((dynamic_cast<Sunflower*>(obj.get()) || dynamic_cast<Peashooter*>(obj.get())) && obj->row == clickedRow && obj->col == clickedCol) {
                            canPlace = false;
                            break;
                        }
                    }
                    if (canPlace && event.mouseButton.button == sf::Mouse::Right) {
                        gameObjects.emplace_back(std::make_unique<Peashooter>(clickedRow, clickedCol, peashooterTexture));
                        sunScore -= 100;
                    }
                }
            }
        }

        zombieSpawnTimer -= deltaTime;
        if (zombieSpawnTimer <= 0.0f) {
            gameObjects.emplace_back(std::make_unique<Zombie>(rowDist(gen), COLS - 1, zombieTexture));
            zombieSpawnTimer = 5.0f;
        }

        for (auto& obj : gameObjects) {
            obj->update(gameObjects, deltaTime);
        }

        gameObjects.remove_if([](const std::unique_ptr<GameObject>& obj) {
            return obj->health <= 0;
            });

        window.clear(sf::Color(100, 200, 100));

        // Draw grid
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
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error: Font file 'arial.ttf' not found." << std::endl;
            return 1;
        }
        sf::Text sunText("Sun: " + std::to_string(sunScore), font, 24);
        sunText.setPosition(10, 10);
        sunText.setFillColor(sf::Color::Black);
        window.draw(sunText);

        window.display();
    }

    return 0;
}