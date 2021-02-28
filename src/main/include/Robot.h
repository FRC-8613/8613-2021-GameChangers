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
	float joystick_lspeed;
	float joystick_rspeed;
	std::chrono::time_point<std::chrono::system_clock> curr_time;
	std::chrono::time_point<std::chrono::system_clock> prev_time;
	float lacceleration = 1; // acceleration in time it takes to get to max speed
	float racceleration = 1;
	float motor_lspeed = 0; // default starting motor speed
	float motor_rspeed = 0;
	int mode = 0; // 0=tankdrive, 1=arcade drive


};
