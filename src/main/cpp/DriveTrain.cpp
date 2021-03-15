#include "DriveTrain.h"

float clamp(float x, float l = -1.0f, float u = 1.0f) {
	return (x<u) ? ((x>l) ? (x) : (l)) : (u);
}

DriveTrain::DriveTrain() {
    t_gear_last_press = std::chrono::system_clock::now();
	t_mode_last_press = std::chrono::system_clock::now();
    mode = arcade_drive_mode;
	pref = left_pref;
}

DriveTrain::AddMotor(int CANaddr, enum MotorType, int DriveTrainSide) {
    motors.push_back(std::make_pair<rev::CANSparkMax*,int>(new rev::CANSparkMax(CANaddr, MotorType),DriveTrainSide));
}

DriveTrain::TankDrive(float left, float right) {
	// cap motor speed
	motor_lspeed = clamp(motor_lspeed)*gear;
	motor_rspeed = clamp(motor_rspeed)*gear;

	// Set motors to be correct speeds
    for (auto& m : motors) {
        if (m.second == 1) {
            m.first->Set(motor_lspeed);
        }
        else {
            m.first->Set(motor_rspeed);
        }
    }
}

//=======================================================================================
//=======================================================================================

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
		if (fabs(lx) < deadband_threshold && fabs(ly) < deadband_threshold && pref == left_pref) {
			x = rx;
			y = ry;
			float theta = atan2(y,-x);
			float radius = pow(x*x+y*y,0.5);
			motor_lspeed = radius*cos(theta-M_PI/4);
			motor_rspeed = -radius*sin(theta-M_PI/4);
		}
		else if (fabs(rx) < deadband_threshold && fabs(ry) < deadband_threshold && pref == right_pref) {
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
	else 
		mode = tank_drive_mode; // First drive mode
	

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

