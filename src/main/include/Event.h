#include <vector>
std::vector<jEvent> eventlist;


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
