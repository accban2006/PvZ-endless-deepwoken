#ifndef SUN_H
#define SUN_H
#include "GameObject.h"
class Sun : public GameObject {
public:
    int value;
    float fallSpeed;
    float lifespan;
    Sun(int row, int col, const sf::Texture& texture);
    void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) override;
};

#endif 
