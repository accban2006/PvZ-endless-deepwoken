#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "GameObject.h"
class Peashooter : public GameObject {
public:
    float shootCooldown;
    float shootTimer;
    static sf::Texture peaTexture; 
    Peashooter(int row, int col, const sf::Texture& texture);
    void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) override;
};
#endif 