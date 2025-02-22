#include "Peashooter.h"
#include "Pea.h"
#include "Zombie.h"
#include "Constants.h"
sf::Texture Peashooter::peaTexture; 
Peashooter::Peashooter(int row, int col, const sf::Texture& texture)
    : GameObject(row, col, 100, texture), shootCooldown(2.0f), shootTimer(0.0f) {
}
void Peashooter::update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) {
    shootTimer += deltaTime;
    if (shootTimer >= shootCooldown) {
        for (const auto& obj : gameObjects) {
            if (dynamic_cast<Zombie*>(obj.get()) && obj->row == row) {
                shootTimer = 0;
                gameObjects.emplace_back(std::make_unique<Pea>(row, col, peaTexture));
                break;
            }
        }
    }
}