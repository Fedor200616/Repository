#include <iostream>

enum class etype {
    Aircraft,
    Missile
};

class TTarget{
public:
    double x0, y0;
    double v;
    double k;
    etype type;
    double x, y;
    TTarget(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: x0(ax0), y0(ay0), v(av), k(ak), type(atype), x(ax), y(ay){};
    TTarget(){};
    ~TTarget(){};
    virtual void move(double dt) = 0;
};

class TAircraft : public TTarget{
public:
    TAircraft(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay){};
    void move(double dt);
};

class TMissile : public TTarget{
public:
    double a;
    TMissile(double ax0, double ay0, double av, double ak, etype atype, double ax, double ay, double aa)
	: TTarget(ax0, ay0, av, ak, atype, ax, ay), a(aa){};
    void move(double dt);
};

class TRls {
    double x, y, z;
    double d;
    TTarget **target;
    int target_n;
    TRls (double ax, double ay, double az, double ad) : x(ax), y(ay), z(az), d(ad){};
    virtual void peleng(int t0, int tk);
};
