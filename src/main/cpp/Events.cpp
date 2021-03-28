#include "Event.h"
std::vector<jEvent> eventlist;

class jEvent {
	jEvent(enum jEventType t, void* d) {
		switch (t) {
			case btn:
				btn_state = *((bool*)d);
				break;
			case axis:
				data = *((float*)d);
				break;
			case dpad:
				data = *((int*)d);
				break;
		}
	}
	enum jEventType {btn, dpad, axis} type;
	bool btn_state;
	int data = 0;
};

class eventHandler { //[TODO]
  eventHandler() {

  }
	processEvents() {
		
	}
}

class joystick_snapshot {
	public:
		joystick_snapshot(frc::Joystick* j) : m_j(j) {}
		~joystick_snapshot() {}
		void Update() {
			// Update Buttons
			for(int i = 1; i < ControlMap::NUM_BUTTONS) {
				bool btnTmp = m_j->GetRawButton(i);
				if(btnTmp != btns[i-1])
					eventlist.push_back(jEvent(jEvent::btn, btnTmp));
				btns[i-1] = btTmp;
			}
			// Update Axis
			for(int i = 0; i < ControlMap::NUM_AXIS) {
				float axisTmp = m_j->GetRawAxis(i);
				if (tmp != axis[i]) {
					change_axis[i] = true;
					eventlist.push_back(jEvent(jEvent::axis, axisTmp));
				}
				axis[i] = axisTmp;
			}
			// Update DPAD
			int dpadTmp = j->GetPOV(0);
			if (dpadTmp != dpad) {
				change_dpad = true;
				eventlist.push_back(jEvent(jEvent::dpad,dpadTmp))
			}
			dpad = dpadTmp;

		}

	bool btns[] = {};
	int dpad = -1;
	float axis[] = {};

	bool change_btns[] = {};
	bool change_dpad = false;
	bool axis[] = {};

	private:
		frc::Joystick* m_j;
};
