#pragma once

#include "ParameterSet.h"
#include "Vector3.h"

class Optimizer
{
    public:
        virtual void iterate() = 0;
        virtual const ParameterSet& getResult() = 0;
        const Vector3& getTarget() { return target; }

    protected:
        Optimizer(const Vector3& target, Solver& solver): target(target), solver(solver) {}

        Vector3 target;
        Solver& solver;
    private:
};
