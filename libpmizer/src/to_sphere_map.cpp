#include <libpmizer/to_sphere_map.h>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <libpmizer/cube.h>
#include <libpmizer/ray.h>


namespace libpmizer {

namespace {

using cubed = cube<double>;
using spherical_coords = ::boost::geometry::model::point<
	double,
	2,
	::boost::geometry::cs::spherical_equatorial<::boost::geometry::degree>
>;

spherical_coords spherical(double x, double y) {
	return { x * 360.0, y * 90.0 };
}


cubed::point cartesian(const spherical_coords p) {
	cubed::point result;
	::boost::geometry::transform(p, result);
	return result;
}

}

void to_sphere_map(texture_view cubemap, texture_view spheremap) {
	namespace bg = ::boost::geometry;
	using sphere_point = bg::model::point<double, 2, bg::cs::spherical_equatorial<bg::degree>>;

	const cubed qbe{ cubed::point{0, 0, 0}, 0.5, cubemap };
	for (int y = 0; y < cubemap.height(); ++y) {
		const auto y_norm = y / (cubemap.height() - 1.0) - 0.5;
		for (int x = 0; x < cubemap.width(); ++x) {
			const auto x_norm = x / (cubemap.width() - 1.0) - 0.5;
			const auto on_sphere = spherical(x_norm, y_norm);
			auto ray_end = cartesian(on_sphere);
			bg::multiply_value(ray_end, 2.0);	// to have all point of sphere outside cube
			const ray<double, 3> r{ cubed::point{ 0, 0, 0 }, ray_end };
			spheremap(x, y) = qbe.colour(r);
		}
	}
}


void to_sphere_map(const ::std::string& cubemap, const ::std::string& spheremap) {
	namespace gil = ::boost::gil;
	gil::rgb8_image_t input;
	gil::jpeg_read_and_convert_image(cubemap.c_str(), input);

	gil::rgb8_image_t output{ input.dimensions() };
	to_sphere_map(gil::view(input), gil::view(output));
	jpeg_write_view(spheremap.c_str(), gil::const_view(output));
}

}
