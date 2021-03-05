#include "Robot.h"

float clamp(float x, float l = -1.0f, float u = 1.0f) {
	return (x<u) ? ((x>l) ? (x) : (l)) : (u);
}

// Robot Logic (runs when robot is on regardless of below functions)
void Robot::RobotInit() {
	// init controllers and motors in here
	leftF = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushed); // cannot set ID of motors to 0 else motor will not function
	leftB = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushed);
	rightF = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushed);
	rightB = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushed);
	
	t_gear_last_press = std::chrono::system_clock::now();
	t_mode_last_press = std::chrono::system_clock::now();
	

	// Initialise Joystick
	j = new frc::Joystick(0);
	// Setup default drive mode
	mode = arcade_drive_mode;
	pref = left_pref;


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
		// Joystick switching preference
		// Mode switching
		t_pref_now = std::chrono::system_clock::now();
		bool is_pref_switch_l = j->GetRawButton(left_stick);
		bool is_pref_switch_r = j->GetRawButton(right_stick);
		
		if (!is_pref_switch_l && !is_pref_switch_r) {
			t_pref_last_press = t_pref_now;
			pref_shifted = false;
		}
		std::chrono::duration<double> duration_elapsed_pref = t_pref_now - t_pref_last_press;
		double time_dif2 = duration_elapsed_pref.count();
		if (time_dif2 > press_delay && !pref_shifted) { 
			if (pref == left_pref && is_pref_switch_r) {
				pref = right_pref;
				std::cout << "PREF: Right" << std::endl;
			}
			else if (pref == right_pref && is_pref_switch_l) {
				pref = left_pref;
				std::cout << "PREF: LEFT" << std::endl;
			}
			
			pref_shifted = true;
		}


		// Calculate motor speeds
		float lx = j->GetRawAxis(left_stick_x);
		float ly = j->GetRawAxis(left_stick_y);
		float rx = j->GetRawAxis(right_stick_x);
		float ry = j->GetRawAxis(right_stick_y); 

		float x = 0;
		float y = 0;
		if (lx == 0 && ly == 0 && pref == left_pref) {
			x = rx;
			y = ry;
			float theta = atan2(y,-x);
			float radius = pow(x*x+y*y,0.5);
			motor_lspeed = radius*cos(theta-M_PI/4);
			motor_rspeed = -radius*sin(theta-M_PI/4);
		}
		else if (rx == 0 && ry == 0 && pref == right_pref) {
			x = lx;
			y = ly;
			float theta = atan2(y,-x);
			float radius = pow(x*x+y*y,0.5);
			motor_lspeed = radius*cos(theta-M_PI/4);
			motor_rspeed = -radius*sin(theta-M_PI/4);
		}
		else if (pref == left_pref) {
			x = lx;
			y = ly;
			float theta = atan2(y,-x);
			float radius = pow(x*x+y*y,0.5);
			motor_lspeed = radius*cos(theta-M_PI/4);
			motor_rspeed = -radius*sin(theta-M_PI/4);
		}
		else if (pref == right_pref) {
			x = rx;
			y = ry;
			float theta = atan2(y,-x);
			float radius = pow(x*x+y*y,0.5);
			motor_lspeed = radius*cos(theta-M_PI/4);
			motor_rspeed = -radius*sin(theta-M_PI/4);
		}

		
	}
	else {
		mode = tank_drive_mode; // First drive mode
	}

	// Mode switching
	t_mode_now = std::chrono::system_clock::now();
	bool is_mode_switch = j->GetRawButton(7);
	
	if (!is_mode_switch) {
		t_mode_last_press = t_mode_now;
		mode_shifted = false;
	}
	std::chrono::duration<double> duration_elapsed_mode = t_mode_now - t_mode_last_press;
	double time_dif2 = duration_elapsed_mode.count();
	if (time_dif2 > press_delay && !mode_shifted) { 
		if (mode == tank_drive_mode) {
			mode = arcade_drive_mode;
			std::cout << "MODE: Arcade" << std::endl;
		}
		else if (mode == arcade_drive_mode) {
			mode = tank_drive_mode;
			std::cout << "MODE: Tank" << std::endl;
		}
		
		mode_shifted = true;
	}
	// D Pad controls for virtual gearbox
	t_gear_now = std::chrono::system_clock::now();
	int dpad_direction = j->GetPOV(0);

	if (dpad_direction != dpad_right && dpad_direction != dpad_left) {
		t_gear_last_press = t_gear_now;
		gear_shifted = false;
	}
	std::chrono::duration<double> duration_elapsed_gear = t_gear_now - t_gear_last_press;
	double time_dif1 = duration_elapsed_gear.count();
	if (time_dif1 > press_delay && !gear_shifted) { // value may have to be fine tuned as to ensure it only changes gear once per dpad press.
		if (dpad_direction == dpad_right) {
			gear += gear_increment;
		}
		if (dpad_direction == dpad_left) {
			gear -= gear_increment;
		}
		// Restrict gear values
		gear = clamp(gear, 0, 1);
		std::cout << "GEAR: " << gear << std::endl;
		gear_shifted = true;
	}

	// cap motor speed
	motor_lspeed = clamp(motor_lspeed)*gear;
	motor_rspeed = clamp(motor_rspeed)*gear;

	// Set motors to be correct speeds
	leftF->Set(motor_lspeed);
	leftB->Set(motor_lspeed);
	rightF->Set(motor_rspeed);
	rightB->Set(motor_rspeed);


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

