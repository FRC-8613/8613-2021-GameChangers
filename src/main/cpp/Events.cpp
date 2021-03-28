#include "Event.h"

void eventHandler::processEvents() {

}

jEvent::jEvent(enum jEventType t, void* d) {
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

void joystick_snapshot::Update() {
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
