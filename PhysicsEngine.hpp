#ifndef PhysicsEngine
#define PhysicsEngine

#include "Body.hpp"

class Engine{
    public:
    void rk4(Body& planet, double dt, const Body& Sun, double SunMass){
        State current = planet.state;

        Derivative k1 = planet.Evaluation(current, Sun.state.position, SunMass);

        State s2 = {
            s2.position = current.position + k1.d_position * (0.5*dt),
            s2.velocity = current.velocity + k1.d_velocity * (0.5*dt)
        };

        Derivative k2 = planet.Evaluation(s2, Sun.state.position, SunMass);

        State s3 = {
            s3.position = current.position + k2.d_position * (0.5*dt),
            s3.velocity = current.velocity + k2.d_velocity * (0.5*dt)
        };

        Derivative k3 = planet.Evaluation(s3, Sun.state.position, SunMass);
        
        State s4 = {
            s4.position = current.position + k3.d_position * dt,
            s4.velocity = current.velocity + k3.d_velocity * dt
        };

        Derivative k4 = planet.Evaluation(s4, Sun.state.position, SunMass);

         planet.state.position = current.position +
         (k1.d_position + k2.d_position * 2.0 + k3.d_position * 2.0 + k4.d_position) * (1.0 / 6.0) * dt;

         planet.state.velocity = current.velocity +
         (k1.d_velocity + k2.d_velocity * 2.0 + k3.d_velocity * 2.0 + k4.d_velocity) * (1.0 / 6.0) * dt;
    }
};
#endif