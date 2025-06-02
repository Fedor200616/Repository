#include <iostream>
#ifndef PI
#define PI	3.1415
#endif
const double delta_t = 0.1;

enum class etype {
    Aircraft,
    Missile
};

class TTarget { // Цель (родительский класс)
public:
	double x0, y0; // Начальные координаты цели
	double v; // Скорость цели
    double k; // Курс
	etype type; // Тип цели
	double x, y; // Текущие координаты цели
    TTarget(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: x0(ax0), y0(ay0), v(av), k(ak), type(atype), x(ax), y(ay){};
    TTarget(){};
    ~TTarget(){};
    virtual void move(double dt) = 0;
};

class TAircraft : public TTarget { // Самолет
public:
    TAircraft(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay){};
    void move(double dt);
};

class TMissile : public TTarget { // Ракета
public:
	double a; // Ускорение ракеты
    TMissile(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay, double aa)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay), a(aa){};
	void move(double dt); 
};

class TRls { // РЛС
public:
	double x, y; // Координаты РЛС
    double d; // Дальность обнаружения цели
	TTarget** target; // Массив указателей на цели
	int target_n; // Количество целей
	TRls(double ax, double ay, double ad) : x(ax), y(ay), d(ad) {}; // Конструктор класса RLS
	~TRls() {};
	virtual void peleng(double t0, double tk, double dt); // Метод для вычисления пеленга на цели
};
