#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "PhysicsEngine.hpp"
#include "Body.hpp"
#include "RenderEngine.hpp"

int main(){
    Body Sun(1000.0, Vector_2D(0, 0), Vector_2D(0, 0));
    Body Planet(1, Vector_2D(100,0), Vector_2D(0,3.16));
    Body Planet2(1, Vector_2D(200,0), Vector_2D(0,9.16));

    std::vector<Body> planets;
    planets.push_back(Planet);
    planets.push_back(Planet2);

    sf::RenderWindow window(sf::VideoMode(800,600), "Planets simulation");
    window.setFramerateLimit(60);

    Engine Calculations;
    RenderEngine render(window);

    double dt = 0.1;
    double SunMass = 1000;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto& p :planets){
            Calculations.rk4(p, dt, Sun, SunMass);
            p.update_history();
        }

        window.clear(sf::Color::Black);

        render.render(Sun, planets);
    }
    return 0;
}