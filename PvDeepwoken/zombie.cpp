#include "Zombie.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Constants.h" 
Zombie::Zombie(int row, int col, const sf::Texture& texture)
    : GameObject(row, col, 200, texture), speed(20.0f), damage(10) {
}
void Zombie::update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) {
    sprite.move(-speed * deltaTime, 0);
    col = static_cast<int>(sprite.getPosition().x) / GRID_SIZE;
    for (auto& obj : gameObjects) {
        if (dynamic_cast<Sunflower*>(obj.get()) || dynamic_cast<Peashooter*>(obj.get())) {
            if (isColliding(*obj)) {
                obj->takeDamage(damage);
            }
        }
    }
}