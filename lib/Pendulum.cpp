#include "Pendulum.h"

const double TWO_M_PI = 2 * M_PI;


namespace PendulumPhysics
{
    // Pendulum class

    Pendulum::Pendulum()
    {
        this->mass = 1;
        this->length = 1;
        this->theta = 0;
        this->omega = 0;
    }

    Pendulum::Pendulum(double mass, double length, double theta, double omega)
    {
        this->mass = mass;
        this->length = length;
        this->theta = theta;
        this->omega = omega;
    }

    std::tuple<double, double> Pendulum::getCoordinates()
    {
        double x = length * sin(theta);
        double y = length * cos(theta);
        return std::make_tuple(x, y);
    }

    // Double pendulum class

    DoublePendulum::DoublePendulum()
    {
        p1 = Pendulum();
        p2 = Pendulum();
        g = 9.81;
        gamma= 0.1;
    }

    DoublePendulum::DoublePendulum(Pendulum pendulum1, Pendulum pendulum2, double gravity, double friction)
    {
        p1 = pendulum1;
        p2 = pendulum2;
        g = gravity;
        gamma = friction;
    }

    void DoublePendulum::update(double dt)
    {
        // Calculate derivatives using fourth-order Runge-Kutta method
        double k1_1 = p1.omega;
        double k1_2 = (-g * (2 * p1.mass + p2.mass) * sin(p1.theta) - p2.mass * g * sin(p1.theta - 2 * p2.theta) - 
            2 * sin(p1.theta - p2.theta) * p2.mass * (p2.omega * p2.omega * p2.length + p1.omega * p1.omega * p1.length * cos(p1.theta - p2.theta))) / 
            (p1.length * (2 * p1.mass + p2.mass - p2.mass * cos(2 * p1.theta - 2 * p2.theta))) - gamma * p1.omega;
        
        double k2_1 = p2.omega;
        double k2_2 = (2 * sin(p1.theta - p2.theta) * (p1.omega * p1.omega * p1.length * (p1.mass + p2.mass) + g * 
            (p1.mass + p2.mass) * cos(p1.theta) + p2.omega * p2.omega * p2.length * p2.mass * cos(p1.theta - p2.theta))) / 
            (p2.length * (2 * p1.mass + p2.mass - p2.mass * cos(2 * p1.theta - 2 * p2.theta))) - gamma * p2.omega;

        double l1_1 = p1.omega + 0.5 * k1_2 * dt;
        double l1_2 = k1_2 + 0.5 * k2_2 * dt;
        double l2_1 = p2.omega + 0.5 * k2_2 * dt;
        double l2_2 = k2_2;

        double m1_1 = p1.omega + 0.5 * l1_2 * dt;
        double m1_2 = l1_2 + 0.5 * l2_2 * dt;
        double m2_1 = p2.omega + 0.5 * l2_2 * dt;
        double m2_2 = l2_2;

        double n1_1 = p1.omega + m1_2 * dt;
        double n1_2 = m1_2 + m2_2 * dt;
        double n2_1 = p2.omega + m2_2 * dt;
        double n2_2 = m2_2;

        // Update angles and angular velocities
        p1.theta += dt * (k1_1 + 2 * l1_1 + 2 * m1_1 + n1_1) / 6.0;
        p1.omega += dt * (k1_2 + 2 * l1_2 + 2 * m1_2 + n1_2) / 6.0;
        p2.theta += dt * (k2_1 + 2 * l2_1 + 2 * m2_1 + n2_1) / 6.0;
        p2.omega += dt * (k2_2 + 2 * l2_2 + 2 * m2_2 + n2_2) / 6.0;

        // Constrain angles to [-pi, pi]
        p1.theta = fmod(p1.theta + M_PI, TWO_M_PI);
        if (p1.theta < 0.0)
        {
            p1.theta += TWO_M_PI;
        }
        p1.theta -= M_PI;

        p2.theta = fmod(p2.theta + M_PI, TWO_M_PI);
        if (p2.theta < 0.0)
        {
            p2.theta += TWO_M_PI;
        }
        p2.theta -= M_PI;
    }

    std::tuple<double, double> DoublePendulum::getP1Coordinates()
    {
        return p1.getCoordinates();
    }

    std::tuple<double, double> DoublePendulum::getP2Coordinates()
    {
        auto [p1x, p1y] = p1.getCoordinates();
        auto [p2x, p2y] = p2.getCoordinates();

        return std::make_tuple(p1x + p2x, p1y + p2y);
    }
}