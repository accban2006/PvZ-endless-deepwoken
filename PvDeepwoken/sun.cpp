#include "Sun.h"
#include "Constants.h" 
Sun::Sun(int row, int col, const sf::Texture& texture)
    : GameObject(row, col, 1, texture), value(25), fallSpeed(50.0f), lifespan(10.0f) {
}

void Sun::update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) {
    lifespan -= deltaTime;
    if (lifespan <= 0) {
        health = 0;
        return;
    }

    if (sprite.getPosition().y < (row + 1) * GRID_SIZE) {
        sprite.move(0, fallSpeed * deltaTime);
    }
}