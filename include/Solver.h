#pragma once

#include <iostream>
#include <vector>
#include "Vector3.h"
#include "ParameterSet.h"

class Solver
{
    public:
        Solver(): w(.0, .0, 1.0/86400.0) {}
        virtual ~Solver() {}

        std::vector<Vector3> solve(ParameterSet& p)
        {
            std::vector<Vector3> trajectory;
            Vector3 r = p.getStart();
            Vector3 v = p.getVelocity();
            double t = 0.0;
            double pathLength = 0.0;
            while(r.length() > RADIUS - EPSILON && t < TIMELIMIT)
            {
                trajectory.push_back(r);
                v = v + F(r, v, t) * STEP;
                r = r + v * STEP;
                t = t + STEP;

                pathLength += v.length() * STEP;
            }
            p.travelTime = t;
            p.pathLength = pathLength;
            p.endPoint = trajectory.back();
            return trajectory;
        }

    protected:
    private:
        Vector3 w;

        Vector3 F(Vector3 r, Vector3 v, double t)
        {
            double R = r.length();
            return - r * (G * RADIUS * RADIUS / R / R / R) - w.cross(v)*2.0 - w.cross(w.cross(r));
        }
};
