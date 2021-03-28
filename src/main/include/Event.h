#include <vector>
#include "Arm.h"
#include "Intake.h"
#include "Drivesystem.h"
std::vector<jEvent> eventlist;

//                 type,  ID, Event,            Mapped Function, Param
typedef std::tuple< int, int,  Subsystem*, int, , std::function<void(float)>, float* > JoystickMap_Record
std::vector<JoystickMap_Record> JoystickMap;

class jEvent {
	jEvent(enum jEventType t, void* d) {}
	enum jEventType {btn, dpad, axis} type;
	bool btn_state;
	float data = 0;
};

class EventHandler { //[TODO]
  EventHandler() {}
  ~EventHandler() {}
private:
  joystick_snapshot js;
}

class JoystickSnapshot {
	public:
		JoystickSnapshot(frc::Joystick* j) : m_j(j) {}
		~JoystickSnapshot() {}


	bool btns[] = {};
	int dpad = -1;
	float axis[] = {};

	bool change_btns[] = {};
	bool change_dpad = false;
	bool change_axis[] = {};

	private:
		frc::Joystick* m_j;
};
