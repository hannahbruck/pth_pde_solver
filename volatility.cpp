#include "volatility.hpp"
#include "normal_law.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

volatility::volatility(std::string name)
:v_name(name)
{
}

bs_vol::bs_vol(double vol, double T)
:volatility("Black-Scholes")
{
    vol_vector.resize(T);
    for(int i=0; i<T-1; i++)
    {
        vol_vector[i] = vol;
    }
}

heston_vol::heston_vol(double vol, double T, double dt, double kappa, double theta)
:volatility("Heston")
{
    vol_vector.resize(T);
    vol_vector[0] = vol;
    for(int i=1; i<T-1; i++)
    {
        vol_vector[i] = vol_vector[i-1] + kappa*(theta-fmax(vol_vector[i-1],0))*dt + vol*sqrt(fmax(vol_vector[i-1],0))*sqrt(dt)*normal_law(3);
    }
}

std::vector<double> volatility::get_vector()
{
    return vol_vector;
}


