#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include "config.h"
#include "include/Vector3.h"
#include "include/Solver.h"
#include "include/ParameterSet.h"
#include "include/PopulationManager.h"

const double PI = 3.14159265;

int main()
{
    double phi1, theta1, phi2, theta2;

    std::cout << "Start latitude(deg): ";
    std::cin >> theta1;
    std::cout << "Start longitude(deg): ";
    std::cin >> phi1;
    std::cout << "End latitude(deg): ";
    std::cin >> theta2;
    std::cout << "End longitude(deg): ";
    std::cin >> phi2;

    double r = RADIUS;

    Vector3 startPoint(r*cos(theta1*PI/180)*cos(phi1*PI/180),
                       r*cos(theta1*PI/180)*sin(phi1*PI/180),
                       r*sin(theta1*PI/180));
    Vector3 target(r*cos(theta2*PI/180)*cos(phi2*PI/180),
                   r*cos(theta2*PI/180)*sin(phi2*PI/180),
                   r*sin(theta2*PI/180));
    Solver solver;

    srand (time(NULL));
    std::vector<ParameterSet> init;
    for (int i = 0; i < MAXPOPULATION; i++)
    {
        double x = (double(rand())/RAND_MAX * 2.0 - 1.0) * sqrt(2.0 * G * RADIUS);
        double y = (double(rand())/RAND_MAX * 2.0 - 1.0) * sqrt(2.0 * G * RADIUS);
        double z = (double(rand())/RAND_MAX * 2.0 - 1.0) * sqrt(2.0 * G * RADIUS);
        Vector3 v(x, y, z);
        init.push_back(ParameterSet(startPoint, v));
    }
    PopulationManager population(target, solver, init);
    int iter = 0;
    double score = 0;
    double oldscore = 0;
    const int ITER_LIMIT = 200;
    while(iter < ITER_LIMIT)
    {
        population.iterate();

        const ParameterSet &p = population.getResult();
        oldscore = score;
        score = (p.endPoint - target).length();
        if (score != oldscore)
        {
            Vector3 r = p.endPoint;
            double lat = atan2(r.Z, sqrt(r.X*r.X + r.Y*r.Y));
            double lng = atan2(r.Y, r.X);
            std::cout << "Iteration " << iter << ": " <<
            "distance=" << score <<
            " time=" << p.travelTime <<
            " length=" << p.pathLength <<
            " velocity=" << p.getVelocity().length() <<
            " lat=" << lat*180/PI <<
            " long=" << lng*180/PI <<
            std::endl;
        }
        if (score < STEP * p.getVelocity().length())
            break;
        iter++;
    }
    std::cout << "Finished at iteration " << iter << std::endl;
    if (iter < ITER_LIMIT)
    {
        std::cout << "Convergence reached." << std::endl;
    }
    else
    {
        std::cout << "Iteration limit reached." << std::endl;
    }

    return 0;
}
