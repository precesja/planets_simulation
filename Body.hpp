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
    double mass;
    State state;
    std::deque<sf::Vector2f> history; // orbit history
    int max_history = 500;

    Body(double m, Vector_2D p, Vector_2D v) : mass(m), state{p, v}
    {}

    Derivative Evaluation(const State& planet, const Vector_2D& SunPosition, const double& SunMass){
        Derivative output;

        output.d_position = planet.velocity;

        Vector_2D distance = SunPosition - planet.position;
        double r2 = distance.LengthSquared();
        double G = 1;
        double acceleration = G * SunMass / r2;
        output.d_velocity = distance.VectorNormalized() * acceleration;
        return output;
    }

    void update_history(){
        history.push_back({static_cast<float>(state.position.x) + 400.0f, 
                           static_cast<float>(state.position.y) + 300.0f});

        if(max_history < history.size()){
            history.pop_front();
        }
    }
};
#endif