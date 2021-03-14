#ifndef Arm_8613
#define Arm_8613

extern class Motor;
extern class LimitSwitch;


class Arm
{
public:
    Arm(Motor *mot, LimitSwitch *LStop, LimitSwitch *LSbottom);
    ~Arm();
protected:
private:
    LimitSwitch *top, *bottom;
    Motor *motor;
};

#endif