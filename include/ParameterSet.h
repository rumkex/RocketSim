#pragma once

#include <stdlib.h>
#include <cmath>
#include "Vector3.h"

class ParameterSet
{
    public:

        double pathLength, travelTime;
        Vector3 endPoint;

        ParameterSet(Vector3 startPoint, Vector3 velocity): startPoint(startPoint), velocity(velocity), generation(0)
        {}

        virtual ~ParameterSet() {}

        ParameterSet crossbreed(const ParameterSet& other) const
        {
            double a = double(rand())/RAND_MAX;
            Vector3 v = velocity * a + other.velocity * (1-a);
            return ParameterSet(startPoint, v, generation+1);
        }

        ParameterSet& mutate()
        {
            double ax = 1.0 + MUTATE_FACTOR * (double(rand())/RAND_MAX - .5);
            double ay = 1.0 + MUTATE_FACTOR * (double(rand())/RAND_MAX - .5);
            double az = 1.0 + MUTATE_FACTOR * (double(rand())/RAND_MAX - .5);
            velocity.X *= ax;
            velocity.Y *= ay;
            velocity.Z *= az;
            return (*this);
        }

        const Vector3& getStart() const
        {
            return startPoint;
        }

        const Vector3& getVelocity() const
        {
            return velocity;
        }

        int getGeneration() const
        {
            return generation;
        }

    protected:
    private:
        ParameterSet(Vector3 startPoint, Vector3 velocity, int gen): startPoint(startPoint), velocity(velocity), generation(gen)
        {}

        int generation;
        Vector3 startPoint, velocity;
};
