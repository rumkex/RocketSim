#pragma once
#include <vector>
#include <stdlib.h>
#include "ParameterSet.h"
#include "Optimizer.h"

enum SelectionStrategy
{
    Tournament,
    Elite,
    Roulette
};

class PopulationManager: public Optimizer
{
    public:
        PopulationManager(const Vector3& target, Solver& solver,
                          std::vector<ParameterSet> initialPopulation):
        Optimizer(target, solver),
        population(initialPopulation)
        {
            for(unsigned int i = 0; i < population.size(); i++)
            {
                evaluate(population[i]);
            }
        }

        virtual void iterate()
        {
            breed();
            eliteSelection();
        }

        const ParameterSet& getResult()
        {
            int best = 0;
            for (int i = 0; i < population.size(); i++)
            {
                double score = getScore(population[i]);
                if (score < getScore(population[best])) best = i;
            }
            return population[best];
        }

    protected:
    private:
        std::vector<ParameterSet> population;

        double getScore(const ParameterSet& p)
        {
            return (p.endPoint - target).length();
        }

        void evaluate(ParameterSet& p)
        {
            solver.solve(p);
        }

        void rouletteSelection()
        {
            double total = 0.0;
            for (int i = 0; i < population.size(); i++)
            {
                total += getScore(population[i]);
            }
            while (population.size() > SELECT_THRESHOLD * MAXPOPULATION)
            {
                int i = rand() % population.size();
                int r = double(rand()) / RAND_MAX;
                if (r < getScore(population[i]) / total)
                {
                    std::swap(population[i], population.back());
                    population.pop_back();
                }
            }
        }

        void tournamentSelection()
        {
            while (population.size() > SELECT_THRESHOLD * MAXPOPULATION)
            {
                int i1 = rand() % population.size();
                int i2 = rand() % population.size();
                int bad = getScore(population[i1]) > getScore(population[i2]) ? i1: i2;
                std::swap(population[bad], population.back());
                population.pop_back();
            }
        }

        void eliteSelection()
        {
            int ptr = 0;
            while(ptr < SELECT_THRESHOLD * MAXPOPULATION)
            {
                for (int i = 0; i < population.size(); i++)
                {
                    if (getScore(population[i]) < getScore(population[ptr]))
                        std::swap(population[i], population[ptr]);
                }
                ptr++;
            }
            population.erase(population.begin() + ptr, population.end());
        }

        void breed()
        {
            int srcsize = population.size();
            while(population.size() < MAXPOPULATION)
            {
                int first = rand() % srcsize;
                int second = rand() % srcsize;
                ParameterSet p = population[first].crossbreed(population[second]).mutate();
                evaluate(p);
                population.push_back(p);
            }
        }
};
