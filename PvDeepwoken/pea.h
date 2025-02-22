#ifndef PEA_H
#define PEA_H
#include "GameObject.h"
class Pea : public GameObject {
public:
    float speed;
    int damage;

    Pea(int row, int col, const sf::Texture& texture);
    void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) override;
};
#endif 
