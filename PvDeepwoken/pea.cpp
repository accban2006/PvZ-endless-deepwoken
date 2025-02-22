#include "Pea.h"
#include "Zombie.h"
#include "Constants.h" 
Pea::Pea(int row, int col, const sf::Texture& texture)
    : GameObject(row, col, 1, texture), speed(200.0f), damage(20) {
}
void Pea::update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) {
    sprite.move(speed * deltaTime, 0);
    for (auto& obj : gameObjects) {
        if (Zombie* zombie = dynamic_cast<Zombie*>(obj.get())) {
            if (sprite.getGlobalBounds().intersects(zombie->sprite.getGlobalBounds())) {
                zombie->takeDamage(damage);
                health = 0;
                return;
            }
        }
    }
    if (sprite.getPosition().x > SCREEN_WIDTH) {
        health = 0;
    }
}