#pragma once

#include <string>
#include "frc/Joystick.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <rev/CANSparkMax.h>


class Robot : public frc::TimedRobot {
public:
	// Public stuff
	void RobotInit() override;
	void RobotPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;

	void TestInit() override;
	void TestPeriodic() override;

private:
	// private stuff
	rev::CANSparkMax *leftF;
	rev::CANSparkMax *leftB;
	rev::CANSparkMax *rightF;
	rev::CANSparkMax *rightB;
	frc::Joystick *j;

	std::chrono::time_point<std::chrono::system_clock> t_now;
	std::chrono::time_point<std::chrono::system_clock> t_last_dpad_press;
	float lacceleration = 1; // acceleration in time it takes to get to max speed
	float racceleration = 1;
	float motor_lspeed = 0; // default starting motor speed
	float motor_rspeed = 0;
	int mode; // mode value for driving type
	int tank_drive_mode = 0;
	int arcade_drive_mode = 1;
	float gear_increment = 0.125; // increments of gear multiplier
	float gear = 0.5; // default gear setting
	int dpad_up = 0;
	int dpad_right = 90;
	int dpad_down = 180;
	int dpad_left = 270; 
	float deadband_threshold = 0.1; // Threshold where motors are set to 0 e.g. 0.1 -> between -0.1 and 0.1 motors set to 0.

	int left_stick_x = 0;
	int left_stick_y = 1;
	int right_stick_x = 4;
	int right_stick_y = 5;
	int left_trigger = 2;
	int right_trigger = 3;
	
	int button_a = 1;
	int button_b = 2;
	int button_x = 3;
	int button_y = 4;
	int left_bumper = 5;
	int right_bumper = 6;
	int back = 7; // also left arrow
	int start = 8; // also right arrow
	int left_stick = 9;
	int right_stick = 10;

	bool shifted = false;


};
