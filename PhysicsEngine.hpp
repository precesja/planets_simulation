#ifndef PhysicsEngine
#define PhysicsEngine

#include <vector>
#include "Body.hpp"

class Engine{
    public:
    void rk4(std::vector<Body>& planets, double dt){
        int n = planets.size();

        // Initial state of the planets
        std::vector<State> initial_states(n);
        for(int i = 0; i < n; i++){
            initial_states[i] = planets[i].state;
        }

        // k1, k2, k3, k4 for each planet
        std::vector<Derivative> k1(n), k2(n), k3(n), k4(n);

        for(int i = 0; i < n; i++){
            k1[i] = planets[i].Evaluation(initial_states[i], planets, i);
        }

        for(int i = 0; i < n; i++){
            State s2 = {
                initial_states[i].position + k1[i].d_position * (0.5*dt),
                initial_states[i].velocity + k1[i].d_velocity * (0.5*dt)
            };
            k2[i] = planets[i].Evaluation(s2, planets, i);
        }

        for(int i = 0; i < n; i++){
            State s3 = {
                initial_states[i].position + k2[i].d_position * (0.5*dt),
                initial_states[i].velocity + k2[i].d_velocity * (0.5*dt)
            };
            k3[i] = planets[i].Evaluation(s3, planets, i);
        }

        for(int i = 0; i < n; i++){
            State s4 = {
                initial_states[i].position + k3[i].d_position * dt,
                initial_states[i].velocity + k3[i].d_velocity * dt
            };
            k4[i] = planets[i].Evaluation(s4, planets, i);
        }

        for(int i = 0; i < n; i++){
            planets[i].state.position = initial_states[i].position +
             (k1[i].d_position + k2[i].d_position * 2.0 + k3[i].d_position * 2.0 + k4[i].d_position) * (1.0 / 6.0) * dt;

             planets[i].state.velocity = initial_states[i].velocity +
             (k1[i].d_velocity + k2[i].d_velocity * 2.0 + k3[i].d_velocity * 2.0 + k4[i].d_velocity) * (1.0 / 6.0) * dt;
        }
    }
};
#endif