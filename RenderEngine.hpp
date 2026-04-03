#ifndef RenderEngine_hpp
#define RenderEngine_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.hpp"

class RenderEngine{
    private:
        sf::RenderWindow& window; // Reference to the SFML window for drawing
    public:
    RenderEngine(sf::RenderWindow& win) : window(win) {}

    void draw(float radius, sf::Color color, const Body& b){
        sf::CircleShape shape(radius);
        shape.setFillColor(color);

        //Set origin to center
        shape.setOrigin(radius, radius);
        shape.setPosition(b.state.position.x + 400.0, b.state.position.y + 300.0);
        window.draw(shape);
    }

    void render(const Body& sun, const std::vector<Body>& planets){
        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw the trails
        drawTrail(sun, sf::Color::Blue);
        for(const auto& p : planets){
            drawTrail(p, sf::Color::White);
        }

        // Draw the sun and planets
        draw(15.0, sf::Color::Yellow, sun);
        for(const auto& p : planets){
            draw(5.0, sf::Color::Green, p);
        }
        window.display();
    }
    void drawTrail(const Body& b, sf::Color color){
        // 2 points needed to draw a trail
        if (b.history.size() < 2) return;
        
        // lIneStrip connects points
        sf::VertexArray trail(sf::PrimitiveType::LineStrip, b.history.size());

        for (size_t i = 0; i < b.history.size(); ++i) {
        trail[i].position = b.history[i];
        
        // Fade the trail based on its history index
        sf::Color fadedColor = color;
        fadedColor.a = static_cast<sf::Uint8>((i * 255) / b.history.size()); 
        trail[i].color = fadedColor;
        }

        window.draw(trail);
    }   
};
#endif