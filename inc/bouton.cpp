#include "bouton.h"

bool IsInside(sf::Vector2f wp, sf::Vector2f ws, sf::Vector2i sop) {
    if (wp.x < sop.x &&
        wp.x + ws.x > sop.x &&
        wp.y < sop.y &&
        wp.y + ws.y > sop.y) {
        return true;
    }
    return false;
}

Button::Button(int x, int y, int width, int height, const std::string& text_str) : pause(false) {
    buttonShape.setPosition(x, y);
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setFillColor(sf::Color::Green);

    // Charger la police une seule fois
    static sf::Font font;
    static bool isFontLoaded = false;
    if (!isFontLoaded) {
        if (!font.loadFromFile("fonts/DancingScript-Regular.ttf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }
        text.setFillColor(sf::Color::Black);
        isFontLoaded = true;
    }

    text.setFont(font);
    text.setString(text_str);
    text.setCharacterSize(height / 2);
    // Centrer le texte dans le bouton
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(x + width / 2, y + height / 2);
}

void Button::setPause(bool pause) {
    this->pause = pause;
    if (pause) {
        buttonShape.setFillColor(sf::Color::Red);
    } else {
        buttonShape.setFillColor(sf::Color::Green);
    }
}

bool Button::isClicked(sf::Vector2i mousePos) {
    return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::isMouseOver(sf::Vector2i mousePos) {
    return IsInside(buttonShape.getPosition(), buttonShape.getSize(), mousePos);
}

void Button::render(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(text);
}

bool Button::getPause()
{
    return pause;
}

sf::RectangleShape Button::getButtonShape()
{
    return buttonShape;
}

sf::Text Button::getText()
{
    return text;
}