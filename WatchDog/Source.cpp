#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <future>
#include <thread>

#include "StopWatch_II.h"


bool KillProcess() {
	//do something....
	return false;
}

std::string GetCommand() {
	std::string R;

	std::getline(std::cin, R);

	return R;
}



int main() {

	StopWatch SW;
	std::int64_t L = 4900;
	std::future<std::string> F = std::async(std::launch::async,GetCommand);
	
	{
		std::ifstream ifs("WatchDog.cfg");
		if (ifs.is_open()) {
			ifs >> L;
		}
	}

	std::cout << "Start WatchDog." << std::endl;
	std::int64_t C = 0;

	while (SW.Ellipse<std::chrono::milliseconds>().count() <= L) {
		std::string R;
		
		if (F.wait_for(std::chrono::milliseconds(500)) == std::future_status::ready) {
			R = F.get();
			F = std::async(std::launch::async,GetCommand);
		}

		if (R == "" && SW.Ellipse<std::chrono::seconds>().count() > C) {
			C = SW.Ellipse<std::chrono::seconds>().count()+5;
			std::cout << "�N�D���@�N�D���E�E�E" << std::endl;
		}

		if (R == "Cry") {
			std::cout << "���I" << std::endl;
		}
		if (R == "Right") {
			std::cout << "���I" << std::endl;
		}
		if (R == "Left") {
			std::cout << "���I" << std::endl;
		}
		if (R == "Reset") {
			SW.Reset();
			std::cout << "�����I" << std::endl;
		}
		if (R == "Drop"|| R=="Exit"||R=="Quit") {
			std::cout << "���߂����Ă��炤��I�I" << std::endl;
			break;
		}

		if (R == "Now") {
			std::cout << "�΂�" << std::endl;
			KillProcess();
			std::cout << "�����I�I" << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	std::cout << "Dog go to Sleep..."<<std::endl;

	return 0;

}