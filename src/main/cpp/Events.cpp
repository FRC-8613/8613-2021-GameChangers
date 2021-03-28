#include "Event.h"
#include "Arm.h"
#include "Intake.h"
#include "Drivesystem.h"

void EventHandler::processEvents() {
	js->update();
	// Stuff
	for(auto& event : eventlist) {
		switch (event.type) {
			case btn:
				btnMap[event.btn].second();
			break;
			case axis:

			break;
			case dpad:

			break:
			default:
				std::cerr << "EventHander: Unrecognised event type.\n";
		}




	}
}

jEvent::jEvent(enum jEventType t, float d) {
	type = t;
	data = d;
}

void JoystickSnapshot::update() {
	// Update Buttons
	for(int i = 1; i < ControlMap::NUM_BUTTONS) {
		bool btnTmp = m_j->GetRawButton(i);
		if(btnTmp != btns[i-1])
			eventlist.push_back(jEvent(jEvent::btn, (float)btnTmp));
		btns[i-1] = btnTmp;
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
		eventlist.push_back(jEvent(jEvent::dpad, (float)dpadTmp))
	}
	dpad = dpadTmp;

}
