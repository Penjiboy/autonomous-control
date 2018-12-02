#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

#include <utlity>

/* 
 * Controller. 
 * Follows the PID Control ALgorithm to redirect the boat.
 */

// Parameters for PID algoritghm
#define PARAM_P 3
#define PARAM_P_MAX 1.0/360
// #define PARAM_I 3
// #define PARAM_D 3

using namespace std;


class Controller {
public:

	/*
	 * Orientates the rudder to reach the target coordinates TODO
	 */
	void control(double target_long, double target_lat);


private: 

	/*
	 * Retuns the angle in degrees.
	 */
	double get_target_heading(double target_long, double target_lat);

	/*
	 * Returns the new value of the rudder angle.
	 */
	double compute_rudder_angle(double curr_heading, double target_heading);
}

#endif // PID_CONTROLLER_H_