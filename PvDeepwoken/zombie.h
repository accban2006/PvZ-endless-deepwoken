#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"
class Zombie : public GameObject {
public:
    float speed;
    int damage;
    Zombie(int row, int col, const sf::Texture& texture);
    void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) override;
};
#endif 