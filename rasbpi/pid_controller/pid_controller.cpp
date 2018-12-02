#include <pid_controller.h>
#include <gps.h>
#include <math.h>

void Controller::control(double target_long, double target_lat) {

	if(PARAM_P >= PARAM_P_MAX) {
		// This should not happen
		// How should we handle this?
	}

	double curr_heading = SerialParse::getHeading();
	double target_heading = Controller::get_target_heading(target_long, target_lat);

	double new_rudder_angle = Controller::compute_rudder_angle(curr_heading, target_heading);

	// Either return or set the value in here automatically
	SerialParse::setRudderAngle(new_rudder_angle);
	// return new_rudder_angle;
}

double Controller::get_target_heading(double target_long, double target_lat) {
	double curr_lat = SerialParse::getLatitude();
	double curr_long = SerialParse::getLongitude();

	// double magnitude = sqrt((target_lat - curr_lat)*(target_lat - curr_lat) +
	// 				   (target_long - curr_long)*(target_long - curr_long)); 

	// // Use u.v = |u|*|v|*cos(a)
	// double target_heading = acos((target_long-curr_long) / magnitude) * 180 / PI ;

	double target_heading = atan((target_long - curr_long)/(target_lat - curr_lat));

	return curr_lat < target_lat? target_heading : 360 - target_heading; 
}

double Controller::compute_rudder_angle(double curr_heading, double target_heading) {
	if(target_heading - curr_heading > 90 || target_heading - curr_heading < -90) {
		// This is an error
	}

	return (PARAM_P * (target_heading - curr_heading))/90;
}

