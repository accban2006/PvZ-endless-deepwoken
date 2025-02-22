#include "GameObject.h"
#include "Constants.h" 
GameObject::GameObject(int row, int col, int health, const sf::Texture& texture) : row(row), col(col), health(health) {
    sprite.setTexture(texture);
    sprite.setPosition(col * GRID_SIZE, row * GRID_SIZE);
    sprite.setScale((float)GRID_SIZE / texture.getSize().x, (float)GRID_SIZE / texture.getSize().y); 
}
GameObject::~GameObject() {}
void GameObject::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (health < 100) {
        sf::RectangleShape healthBar(sf::Vector2f(GRID_SIZE * (static_cast<float>(health) / 100.0f), 5));
        healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
        healthBar.setFillColor(sf::Color::Red);
        window.draw(healthBar);
    }
}
bool GameObject::isColliding(const GameObject& other) const {
    return (row == other.row && col == other.col);
}
bool GameObject::takeDamage(int damage) {
    health -= damage;
    return health <= 0;
}