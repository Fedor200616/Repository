#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "RLS_head.h"


void TAircraft::move(double dt){
	double angle = -k * PI / 180.0;
    x = x0 + v * std::cos(angle) * dt;
    y = y0 + v * std::sin(angle) * dt;
}

void TMissile::move(double dt){
	double angle = -k * PI / 180.0;
    x = x0 + (v + a * (dt)) * std::cos(angle) * dt;
    y = y0 + (v + a * (dt)) * std::sin(angle) * dt; 
}

void TRls::TInit(int n, const double* x0, const double* y0, const double* v, const double* k,
	const etype* types, const double* a) {
	target_n = n;
	target = new TTarget * [target_n];
	for (int i = 0; i < target_n; ++i) {
		if (types[i] == etype::Aircraft) {
			target[i] = new TAircraft(x0[i], y0[i], v[i], k[i], types[i], x0[i], y0[i]);
		}
		else if (types[i] == etype::Missile) {
			target[i] = new TMissile(x0[i], y0[i], v[i], k[i], types[i], x0[i], y0[i], a[i]);
		}
		else {
			std::cerr << "Unknown target type!" << std::endl;
			return;
		}
	}
}

void TRls::peleng(double t0, double tk) {
	std::ofstream fout("Targets.txt");
	if (!fout.is_open()) {
		std::cerr << "Error opening file Targets.txt" << std::endl;
		return;
	}
	double dt; // Изменение времени
	fout << "Time" << '\t' << "Target" << '\t'
			<< "Distance" << '\t' << "Bearing" << std::endl;
    for (double ti = t0; ti <= tk; ti += delta_t){
		dt = (ti - t0); // Изменение времени относительно начального моментаы
		fout << "===========================================" << std::endl;
		for (int i = 0; i < target_n; i++) {
			target[i]->move(dt);

			double distance_target = std::sqrt(std::pow(target[i]->x - x, 2) 
                + std::pow(target[i]->y - y, 2));
            if (distance_target < d) {
                double abearing = std::atan2(target[i]->y - y, target[i]->x - x) * 180.0 / PI;
				double bearing = 360.0 - abearing; // по часовой

				if (bearing >= 360.0) bearing -= 360.0;
				if (bearing < 0.0) bearing += 360.0;

				// Запись данных в файл
				fout << ti << '\t'
					<< i << '\t'
					<< distance_target << '\t' << '\t'
					<< bearing << std::endl;
            }
		}
    }
	fout.close();
	std::cout << "Data written to Targets.txt" << std::endl;
}

void my_init_plane() {
	int n;
	//std::cout << "Введите количество целей: ";
	//std::cin >> n;
	n = 4; // Пример количества целей

	double* x0 = new double[n];
	double* y0 = new double[n];
	double* v = new double[n];
	double* k = new double[n];
	etype* types = new etype[n];
	double* a = new double[n];

	TRls rls(0, 0, 10); // Создание объекта РЛС

	x0[0] = 4; y0[0] = 7; v[0] = 1; k[0] = 120; types[0] = etype::Aircraft;
	x0[1] = -4; y0[1] = 7; v[1] = 1; k[1] = 60; types[1] = etype::Aircraft;
	x0[2] = -4; y0[2] = -7; v[2] = 1; k[2] = 300; types[2] = etype::Aircraft;
	x0[3] = 4; y0[3] = -7; v[3] = 1; k[3] = 240; types[3] = etype::Aircraft;
	
	rls.TInit(n, x0, y0, v, k, types, a); // Инициализация целей
	rls.peleng(0, 10); // Вычисление пеленга на цели

	// Освобождение памяти
	delete[] x0;
	delete[] y0;
	delete[] v;
	delete[] k;
	delete[] types;
}

void random_init_plane() {
	srand(time(0));
	int n = 10 + rand() % 998; // Случайное число целей от 3 до 150
	double* x0 = new double[n];
	double* y0 = new double[n];
	double* v = new double[n];
	double* k = new double[n];
	etype* types = new etype[n];
	double* a = new double[n];
	std::cout << "Количество целей: " << n << std::endl;
	for (int i = 0; i < n; ++i) {
		x0[i] = rand() % 1000 - 500; // Случайные координаты X от -500 до 500
		y0[i] = rand() % 1000 - 500; // Случайные координаты Y от -500 до 500
		v[i] = 1 + rand() % 10 * 0.1; // Случайная скорость от 1 до 10 м/с
		k[i] = rand() % 360; // Курс от 0 до 360 градусов
		types[i] = static_cast<etype>(rand() % 2); // Случайный тип цели
		if (types[i] == etype::Missile) (a[i] = -10 + rand() % 21); // Ускорение для ракет 
		else a[i] = 0;
		std::cout << i + 1 << "\tX: " << x0[i] << " Y: " << y0[i] << " V: " << v[i] << " Курс: " << k[i] << " Type: "
			<< (types[i] == etype::Aircraft ? "Aircraft" : "Missile")
			<< " Ускорение: " << a[i] << std::endl;
	}

	TRls rls(0, 0, 500); // Создание объекта РЛС
	rls.TInit(n, x0, y0, v, k, types, a); // Инициализация целей
	rls.peleng(0, 100); // Вычисление пеленга на цели

	// Освобождение памяти
	delete[] x0;
	delete[] y0;
	delete[] v;
	delete[] k;
	delete[] types;
}