#include <iostream>
#include <fstream>
#include "RLS_head.h"


void TAircraft::move(double dt){
    x = x0 + v * std::cos(k) * dt;
    y = y0 + v * std::sin(k) * dt;
}

void TMissile::move(double dt){
    x = x0 + (v + a * (dt)) * std::cos(k) * dt;
    y = y0 + (v + a * (dt)) * std::sin(k) * dt; 
}

void TRls::peleng(double t0, double tk, double dt) {
	std::ofstream fout("Targets.txt");
    for (double ti = t0; t0 <= tk; ti += delta_t){
		for (int i = 0; i < target_n; i++) {
			target[i]->move(dt);

			double distance_target = std::sqrt(std::pow(target[i]->x - x, 2) 
                + std::pow(target[i]->y - y, 2));
            if (distance_target < d) {
                double bearing = std::atan2(target[i]->x - x, target[i]->y - y) * 180.0 / PI;
                if (bearing < 0) bearing += 360.0;

                // Вывод в файл для обнаруженных целей D, В
                fout << "Время: " << ti << '\t'
					<< " Цель: " << i << '\t'
					<< "Дистанция: " << distance_target << '\t'
					<< " Пеленг: " << bearing << std::endl;
            }
		}
    }
}
