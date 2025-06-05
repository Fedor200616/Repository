#include <iostream>
#include <locale>
#include <codecvt>
#ifndef PI
#define PI	3.1415
#endif
const double delta_t = 0.01;


enum class etype {
    Aircraft = 0,
    Missile = 1
};

class TTarget { // Класс-цель (Target) - базовый класс для всех целей
public:
    double x0, y0; // Начальные координаты
    double v; // Скорость 
    double k; // Курс
    etype type; // Тип цели
    double x, y; // Координаты в текущий момент времени
    TTarget(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: x0(ax0), y0(ay0), v(av), k(ak), type(atype), x(ax), y(ay){};
    TTarget(){};
    virtual ~TTarget() = default;
    virtual void move(double dt) = 0;
};

class TAircraft : public TTarget { // Класс-цель самолет
public:
    TAircraft(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: TTarget(ax0, ay0, av, ak, etype::Aircraft, ax, ay){};
    void move(double dt);
};

class TMissile : public TTarget { // Класс-цель ракета
public:
	double a; // Ускорение
    TMissile(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay, double aa)
	: TTarget(ax0, ay0, av, ak, etype::Missile, ax, ay), a(aa){};
	void move(double dt); 
};

class TRls { //	Класс РЛС 
public:
	double x, y; // Координаты РЛС
	double d; // Дальность обнаружения
	TTarget** target; // Массив указателей на цели
	int target_n; // Количество целей
	TRls(double ax, double ay, double ad) : x(ax), y(ay), d(ad), target(nullptr), target_n(0) {};
	~TRls() {
		for (int i = 0; i < target_n; i++)
			delete target[i];
		delete[] target;
	}
	
	void TInit(int n, const double* x0, const double* y0, const double* v, const double* k, 
		const etype* types, const double* a = nullptr);	// Метод для инициализации целей
	virtual void peleng(double t0, double tk); // Метод для вычисления пеленга на цели
};

void my_init_plane(); // Функция для инициализации целей вручную

void random_init_plane(); // Функция для случайной инициализации целей
