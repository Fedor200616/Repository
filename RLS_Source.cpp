#include <iostream>
#include "RLS_head.h"


void TAircraft::move(double dt){
    x = x0 + v * std::cos(k) * dt;
    y = y0 + v * std::sin(k) * dt;
}

void TMissile::move(double dt){
    x = x0 + (v + a * (dt)) * std::cos(k) * dt;
    y = y0 + (v + a * (dt)) * std::sin(k) * dt; 
}

void TRls::peleng(int t0, int tk, int deltat){
    for (; t0 <= tk; t0 += deltat)
}
