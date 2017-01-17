//Program for EV3 Forklift control
#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <ev3dev.h>

	void forks(ev3::medium_motor mm, int time, int speed) {

		mm.set_time_sp(time).set_speed_sp(speed).run_timed();
		std::this_thread::sleep_for(std::chrono::milliseconds(time + 500));
	}

	void move(ev3::large_motor lm, ev3::large_motor rm, int time, int speed) {

		lm.set_time_sp(time).set_speed_sp(speed).run_timed();
		rm.set_time_sp(time).set_speed_sp(speed).run_timed();
		std::this_thread::sleep_for(std::chrono::milliseconds(time + 500));
	}

int main(int argc, char **argv) {

	ev3::medium_motor mediumMotor(ev3::OUTPUT_A);
	ev3::large_motor leftMotor(ev3::OUTPUT_B);
	ev3::large_motor rightMotor(ev3::OUTPUT_C);

	move(leftMotor, rightMotor, 1500, 400);
	forks(mediumMotor, 3500, 500);
	move(leftMotor, rightMotor, 1500, -400);
	forks(mediumMotor, 3500, -500);		
}