#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "PhysicsEngine.hpp"
#include "Body.hpp"
#include "RenderEngine.hpp"

int main(){

    // Create planets with mass, initial position and velocity
    Body Sun(5000, Vector_2D(0, 0), Vector_2D(0, 0));
    Body Planet(0.1, Vector_2D(120, 0), Vector_2D(0, 6.45));
    Body Planet2(0.1, Vector_2D(220, 0), Vector_2D(0, 4.77));

    std::vector<Body> planets;
    planets.push_back(Sun);
    planets.push_back(Planet);
    planets.push_back(Planet2);

    // Time step
    double dt = 0.1;

    sf::RenderWindow window(sf::VideoMode(800,600), "Planets simulation");
    window.setFramerateLimit(60);

    // Create physics and rendering engines
    Engine Calculations;
    RenderEngine render(window);

    // -- MAIN LOOP --
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update physics
        Calculations.rk4(planets, dt);

        // Update history for trails
        for(auto& p : planets){
            p.update_history();
        }

        window.clear(sf::Color::Black);

        render.render(planets[0], {planets.begin() + 1, planets.end()});
    }
    return 0;
}