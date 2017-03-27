#include <iostream>
#include <string>
#include <libpmizer/to_sphere_map.h>


int main (int argc, char *argv[]) {
	std::cout << "Converting...";
	libpmizer::to_sphere_map(std::string("D:/matek/Downloads/input.jpg"), "D:/matek/Downloads/output.jpg");
	std::cout << "\tdone!" << std::endl;
}
