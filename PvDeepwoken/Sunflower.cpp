#include "Sunflower.h"
#include "Sun.h"
#include "Constants.h"
sf::Texture Sunflower::sunTexture;  
Sunflower::Sunflower(int row, int col, const sf::Texture& texture)
    : GameObject(row, col, 100, texture), sunProductionRate(8.0f), sunTimer(0.0f) {
}
void Sunflower::update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) {
    sunTimer += deltaTime;
    if (sunTimer >= sunProductionRate) {
        sunTimer = 0.0f;
        gameObjects.emplace_back(std::make_unique<Sun>(row, col, sunTexture));
    }
}