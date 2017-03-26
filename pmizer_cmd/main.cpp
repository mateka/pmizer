//#include <iostream>
//#include <string>
//#include <libpmizer/to_sphere_map.h>
//
//
//int main (int argc, char *argv[]) {
//	std::cout << "Converting...";
//	libpmizer::to_sphere_map(std::string("D:/matek/Downloads/input.jpg"), "D:/matek/Downloads/output.jpg");
//	std::cout << "\tdone!" << std::endl;
//}

#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/point.hpp>

int main()
{
	// Calculate the intersects of a cartesian polygon
	typedef boost::geometry::model::point<double, 3> P;
	boost::geometry::model::ring<P> line1, line2;

	//boost::geometry::read_wkt("linestring(1 1 7,2 2 7,3 3 7)", line1);
	//boost::geometry::read_wkt("linestring(2 1 7,1 2 7,4 0 7)", line2);

	bool b = boost::geometry::intersects(line1, line2);

	std::cout << "Intersects: " << (b ? "YES" : "NO") << std::endl;

	return 0;
}