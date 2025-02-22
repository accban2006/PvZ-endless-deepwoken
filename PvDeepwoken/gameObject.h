#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class GameObject {
public:
    int row;
    int col;
    sf::Sprite sprite;
    int health;

    GameObject(int row, int col, int health, const sf::Texture& texture);
    virtual ~GameObject();

    virtual void update(std::list<std::unique_ptr<GameObject>>& gameObjects, float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    bool isColliding(const GameObject& other) const;
    bool takeDamage(int damage);
};

#endif 