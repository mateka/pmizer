#pragma once

#include <cstddef>
#include <tuple>
#include <boost/qvm/all.hpp>
#include <pmize/cube_face.h>


namespace pmize {

template<::std::size_t Dim>
using vec = ::boost::qvm::vec<double, Dim>;


double normalized(const int value, const ::std::ptrdiff_t factor);
vec<2> normalized(
	const int x, const int y,
	const ::std::ptrdiff_t width,
	const ::std::ptrdiff_t height
);

int unnormalized(const double value, const ::std::ptrdiff_t factor);
::std::tuple<int, int> unnormalized(
	const vec<2> v, const ::std::ptrdiff_t width, const ::std::ptrdiff_t height);

vec<3> to_sphere(const vec<2> v, const double radius = 1.0);

vec<3> spherical_to_cartesian(const vec<3> v);
vec<3> cartesian_to_spherical(const vec<3> v);

double norm_infinity(const vec<3> v);

vec<3> sphere_to_cube(const vec<3> v);
vec<3> cube_to_sphere(const vec<3> v);

::std::tuple<CubeFace, vec<2>> to_cube_map(const vec<3> v);
}