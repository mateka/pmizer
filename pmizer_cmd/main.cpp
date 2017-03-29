#include <iostream>
#include <string>
#include <pmize/to_sphere_map.h>
#include <xmp/meta_engine.h>


int main (int argc, char *argv[]) {
	std::cout << "Converting...";
	pmize::to_sphere_map(std::string("D:/matek/Downloads/input.jpg"), "D:/matek/Downloads/output.jpg");
	std::cout << "\tdone!" << std::endl;
	std::cout << "Adding metadata...";
	xmp::meta_engine engine;
	std::cout << "\tdone!" << std::endl;
}
