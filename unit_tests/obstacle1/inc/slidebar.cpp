#include "slidebar.h"

SlideBar::SlideBar(int x, int y, int width, int height, int minValue, int maxValue, int initialValue)
    : minValue(minValue), maxValue(maxValue), value(initialValue), isDragging(false)
{
    barShape.setPosition(x, y);
    barShape.setSize(sf::Vector2f(width, height));
    barShape.setFillColor(sf::Color(200, 200, 200)); // Couleur grise pour la barre

    // Curseur initial
    int sliderWidth = 10; // Largeur du curseur
    sliderShape.setSize(sf::Vector2f(sliderWidth, height + 4)); // Hauteur légèrement plus grande que la barre
    sliderShape.setFillColor(sf::Color::Blue);
    float sliderX = x + ((float)(initialValue - minValue) / (maxValue - minValue)) * (width - sliderWidth);
    sliderShape.setPosition(sliderX, y - 2); // Positionner le curseur au bon endroit
}

int SlideBar::getValue() const {
    return value;
}

void SlideBar::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (sliderShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            isDragging = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        isDragging = false;
    } else if (event.type == sf::Event::MouseMoved) {
        if (isDragging) {
            float mouseX = sf::Mouse::getPosition(window).x;
            float barX = barShape.getPosition().x;
            float barWidth = barShape.getSize().x;
            float sliderWidth = sliderShape.getSize().x;

            // Limiter la position du curseur à la barre
            float newSliderX = std::max(barX, std::min(mouseX - sliderWidth / 2, barX + barWidth - sliderWidth));
            sliderShape.setPosition(newSliderX, sliderShape.getPosition().y);

            // Mettre à jour la valeur en fonction de la position du curseur
            float positionRatio = (newSliderX - barX) / (barWidth - sliderWidth);
            value = minValue + static_cast<int>(positionRatio * (maxValue - minValue));
        }
    }
}

void SlideBar::render(sf::RenderWindow& window) {
    window.draw(barShape);
    window.draw(sliderShape);
}