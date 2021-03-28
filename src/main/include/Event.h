#include <vector>
std::vector<jEvent> eventlist;


class jEvent {
	jEvent(enum jEventType t, void* d) {}
	enum jEventType {btn, dpad, axis} type;
	bool btn_state;
	int data = 0;
};

class eventHandler { //[TODO]
  eventHandler() {}
  ~eventHandler() {}

}

class joystick_snapshot {
	public:
		joystick_snapshot(frc::Joystick* j) : m_j(j) {}
		~joystick_snapshot() {}


	bool btns[] = {};
	int dpad = -1;
	float axis[] = {};

	bool change_btns[] = {};
	bool change_dpad = false;
	bool axis[] = {};

	private:
		frc::Joystick* m_j;
};
