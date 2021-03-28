/*
 * Subsystem. Accessed by Robot.cpp
 */

#include "Drivesystem.h"

float clamp(float x, float l = -1.0f, float u = 1.0f) {
	return (x<u) ? ((x>l) ? (x) : (l)) : (u);
}

Drivesystem::Drivesystem(Drivetrain &drivetrain) : _drivetrain(drivetrain) {
	/**
	 * Do logic when you create your drivesystem
	 */
	_leftPower = 0;
	_rightPower = 0;

}

void Drivesystem::updatePeriodic(double dt) {
	float lx = ControlMap::j->GetRawAxis(ControlMap::left_stick_x);
	float ly = ControlMap::j->GetRawAxis(ControlMap::left_stick_y);
	float rx = ControlMap::j->GetRawAxis(ControlMap::right_stick_x);
	float ry = ControlMap::j->GetRawAxis(ControlMap::right_stick_y);
	_leftPower = clamp(ly);//*gear;
	_rightPower = clamp(ry);//*gear;

	_drivetrain.set(_leftPower, _rightPower); // Sets power to the drivetrain, but is only updated in robot periodic
}
