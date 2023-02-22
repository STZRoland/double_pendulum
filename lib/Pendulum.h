#include <tuple>
#include <math.h>
#include <iostream>

#ifndef PENDULUM_H
#define PENDULUM_H

namespace PendulumPhysics {

    class Pendulum {
    public:
        double mass;
        double length;
        double theta;
        double omega;

        Pendulum();
        Pendulum(double mass, double length, double theta, double omega);

        std::tuple<double, double> getCoordinates();
    };

    class DoublePendulum {
    public:
        Pendulum p1;
        Pendulum p2;
        double g;
        double gamma;

        DoublePendulum();
        DoublePendulum(Pendulum pendulum1, Pendulum pendulum2, double gravity, double friction);

        void update(double dt);
        std::tuple<double, double> getP1Coordinates();
        std::tuple<double, double> getP2Coordinates();
    };

}

#endif
