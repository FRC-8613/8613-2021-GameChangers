#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <unistd.h>
#include <chrono>

// Robot Logic (runs when robot is on regardless of below functions)
void Robot::RobotInit() {
	// init controllers and motors in here
	leftF = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushed); // cannot set ID of motors to 0 else motor will not function
	leftB = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushed);
	rightF = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushed);
	rightB = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushed);
	
	prev_time = std::chrono::system_clock::now();
	

	// Initialise Joystick
	j = new frc::Joystick(0);
	// Setup default drive mode
	mode = tank_drive_mode;


}

void Robot::RobotPeriodic() {
	// Constantly looping code after robot has turned on. (Cannot control motors in here as they are locked until teleop/auto/test is started)
}

// Dissabled Robot Logic
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {
	// Might want to zero encoders or something when you start teleop
}
void Robot::TeleopPeriodic() {
	// TODO: IMPLEMENT MODE CHANGNG CONTROLS (Pressing start and back simultaneously)
	if (mode == tank_drive_mode) {
		// Get new speeds
		float ly = j->GetRawAxis(left_stick_y);//*j->GetRawAxis(1)*j->GetRawAxis(1);
		float ry = -j->GetRawAxis(right_stick_y);//*j->GetRawAxis(5)*j->GetRawAxis(5);

		// Calculate motor speeds with gears
		motor_lspeed = ly;
		motor_rspeed = ry;

	}
	else if (mode == arcade_drive_mode) {
		float lx = j->GetRawAxis(left_stick_x);
		float ly = j->GetRawAxis(left_stick_y);
		float rx = j->GetRawAxis(right_stick_x);
		float ry = j->GetRawAxis(right_stick_y);
		// TODO: IMPLEMENT ARCADE DRIVE 
		motor_lspeed = ly/2+lx/2;
		motor_rspeed = ly/2-lx/2;
		// TODO: IMPLEMENT JOYSTICK PREFERENCE BASED ON START/BACK BUTTONS
	}
	else {
		mode = tank_drive_mode; // First drive mode
	}
	//D Pad controls for virtual gearbox
	curr_time = std::chrono::system_clock::now();
	std::chrono::duration<double> duration_elapsed = curr_time - prev_time;
	double time_dif = fmin(duration_elapsed.count(),deadband_threshold);
	int dpad_direction = j->GetPOV(0);
	if (dpad_direction == dpad_right || dpad_direction == dpad_left) {
		prev_time = curr_time;
	}
	if (time_dif < 0.01) { // value may have to be fine tuned as to ensure it only changes gear once per dpad press.
		if (dpad_direction == dpad_right) {
			gear += gear_increment;
		}
		else if (dpad_direction == dpad_left) {
			gear -= gear_increment;
		}
	}
	// Restrict gear values
	if (gear < 0) {
		gear = 0;
	}
	if (gear > 1) {
		gear = 1;
	}

	// cap motor speed
	if (motor_lspeed > 1) {
		motor_lspeed = 1;
	}
	if (motor_lspeed < 0) {
		motor_lspeed = 0;
	}
	if (motor_rspeed > 1) {
		motor_rspeed = 1;
	}
	if (motor_rspeed < 0) {
		motor_rspeed = 0;
	}
	

	// Set motors to be correct speeds
	leftF->Set(motor_lspeed*gear);
	leftB->Set(motor_lspeed*gear);
	rightF->Set(motor_rspeed*gear);
	rightB->Set(motor_rspeed*gear);


}

// Test Logic 
void Robot::TestInit() {}
void Robot::TestPeriodic() {}




/**
 * Don't touch these lines
 */
#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif


/* Acceleration Capping code
void Robot::TeleopPeriodic() {
	// Get new speeds
	joystick_lspeed = j->GetRawAxis(1);//*j->GetRawAxis(1)*j->GetRawAxis(1);
	joystick_rspeed = -j->GetRawAxis(5);//*j->GetRawAxis(5)*j->GetRawAxis(5);

	lacceleration = fabs(joystick_lspeed - motor_lspeed);
	racceleration = fabs(joystick_rspeed - motor_rspeed);

	curr_time = std::chrono::system_clock::now();
	std::chrono::duration<double> duration_elapsed = curr_time - prev_time;
	double time_dif = fmin(duration_elapsed.count(),0.1);
	prev_time = curr_time;
	// LEFT MOTOR
	
	if (fabs(joystick_lspeed) < 0.1 ) {
		motor_lspeed = 0;
	} 
	else {
		if (joystick_lspeed > motor_lspeed) {
			motor_lspeed += lacceleration * time_dif;
		}
		else {
			motor_lspeed -= lacceleration * time_dif;
		}
	}
	// RIGHT MOTOR
	
	if (fabs(joystick_rspeed) < 0.1 ) {
		motor_rspeed = 0;
	} 
	else {
		if (joystick_rspeed > motor_rspeed) {
			motor_rspeed += racceleration * time_dif;
		}
		else {
			motor_rspeed -= racceleration * time_dif;
		}
	}


	leftF->Set(motor_lspeed);
	leftB->Set(motor_lspeed);
	rightF->Set(motor_rspeed);
	rightB->Set(motor_rspeed);

	//std::cout << "Left Speed: " << motor_lspeed << std::endl;
	//std::cout << "Right Speed: " << motor_rspeed << std::endl;
	//std::cout << "Time Diff: " << time_dif << std::endl;
	//std::cout << std::endl;
}
*/