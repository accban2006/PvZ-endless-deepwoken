#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "GameObject.h"
class Sunflower : public GameObject {
public:
    float sunProductionRate;
    float sunTimer;
    static sf::Texture sunTexture;
    Sunflower(int row, int col, const sf::Texture& texture);
    void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) override;
};

#endif
