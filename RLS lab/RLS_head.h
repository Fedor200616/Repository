#include <iostream>
#ifndef PI
#define PI	3.1415
#endif
const double delta_t = 0.1;

enum class etype {
    Aircraft,
    Missile
};

class TTarget { // Öåëü (ðîäèòåëüñêèé êëàññ)
public:
	double x0, y0; // Íà÷àëüíûå êîîðäèíàòû öåëè
	double v; // Ñêîðîñòü öåëè
    double k; // Êóðñ
	etype type; // Òèï öåëè
	double x, y; // Òåêóùèå êîîðäèíàòû öåëè
    TTarget(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: x0(ax0), y0(ay0), v(av), k(ak), type(atype), x(ax), y(ay){};
    TTarget(){};
    ~TTarget(){};
    virtual void move(double dt) = 0;
};

class TAircraft : public TTarget { // Ñàìîëåò
public:
    TAircraft(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay){};
    void move(double dt);
};

class TMissile : public TTarget { // Ðàêåòà
public:
	double a; // Óñêîðåíèå ðàêåòû
    TMissile(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay, double aa)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay), a(aa){};
	void move(double dt); 
};

class TRls { // ÐËÑ
public:
	double x, y; // Êîîðäèíàòû ÐËÑ
    double d; // Äàëüíîñòü îáíàðóæåíèÿ öåëè
	TTarget** target; // Ìàññèâ óêàçàòåëåé íà öåëè
	int target_n; // Êîëè÷åñòâî öåëåé
	TRls(double ax, double ay, double ad) : x(ax), y(ay), d(ad) {}; // Êîíñòðóêòîð êëàññà RLS
	~TRls() {};
	virtual void peleng(double t0, double tk, double dt); // Ìåòîä äëÿ âû÷èñëåíèÿ ïåëåíãà íà öåëè
};
