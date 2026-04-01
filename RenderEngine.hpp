#ifndef RenderEngine_hpp
#define RenderEngine_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.hpp"

class RenderEngine{
    private:
        sf::RenderWindow& window;
    public:
    RenderEngine(sf::RenderWindow& win) : window(win) {}

    void draw(float radius, sf::Color color, const Body& b){
        sf::CircleShape shape(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
        shape.setPosition(b.state.position.x + 400.0, b.state.position.y + 300.0);
        window.draw(shape);
    }

    void render(const Body& sun, const std::vector<Body>& planets){
        window.clear(sf::Color::Black);

        for(const auto& p : planets){
            drawTrail(p, sf::Color::White);
        }

        draw(15.0, sf::Color::Yellow, sun);

        for(const auto& p : planets){
            draw(5.0, sf::Color::Green, p);
        }
        window.display();
    }
    void drawTrail(const Body& b, sf::Color color){
        if (b.history.size() < 2) return;
        
        sf::VertexArray trail(sf::PrimitiveType::LineStrip, b.history.size());

        for (size_t i = 0; i < b.history.size(); ++i) {
        trail[i].position = b.history[i];
        
        sf::Color fadedColor = color;
        fadedColor.a = static_cast<sf::Uint8>((i * 255) / b.history.size()); 
        trail[i].color = fadedColor;
        }

        window.draw(trail);
    }   
};
#endif