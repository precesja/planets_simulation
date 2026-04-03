#ifndef Body_hpp
#define Body_hpp

#include <deque>
#include "Vector2D.hpp"

struct State{
    Vector_2D position;
    Vector_2D velocity;
};

struct Derivative{
    Vector_2D d_position;
    Vector_2D d_velocity;
};

class Body{
    public:
    double mass;                            // Mass of the body
    State state;                            // Current state (position and velocity)
    std::deque<sf::Vector2f> history;       // Orbit history
    int max_history = 1000;                 // Maximum tail length

    Body(double m, Vector_2D p, Vector_2D v) : mass(m), state{p, v}
    {}

    Derivative Evaluation(const State& current, const std::vector<Body>& all_planets, int current_index){
        Derivative output;
        output.d_position = current.velocity;

        Vector_2D total_acceleration(0.0, 0.0);
        const double G = 1.0; // Gravitational constant

        for(int i = 0; i < all_planets.size(); i++){
            if(i == current_index) continue; // Skip self

            // Distance vector from current body to the other body
             Vector_2D distance = all_planets[i].state.position - current.position;
             double r2 = distance.LengthSquared();

             if(r2 < 1.0) r2 = 1.0; // Prevent singularity
             
             double acceleration = G * all_planets[i].mass / r2;                                        // a = G * M / r^2
             total_acceleration = total_acceleration + distance.VectorNormalized() * acceleration;
        }
        output.d_velocity = total_acceleration;
        return output;
    }

    // Update the history of positions for rendering trails
    void update_history(){
        // Offset to center the simulation in the window
        history.push_back({static_cast<float>(state.position.x) + 400.0f, 
                           static_cast<float>(state.position.y) + 300.0f});

        // Tail management: remove oldest position if history exceeds max length
        if(max_history < history.size()){
            history.pop_front();
        }
    }
};
#endif