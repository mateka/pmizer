#pragma once

#include <cstddef>
#include <tuple>
#include <boost/qvm/all.hpp>


namespace libpmizer {

template<::std::size_t Dim>
using vec = ::boost::qvm::vec<double, Dim>;


enum class CubeFace {
	Left,
	Front,
	Right,
	Back,
	Top,
	Bottom
};


double normalized(const int value, const int factor);
vec<2> normalized(const int x, const int y, const int width, const int height);

int unnormalized(const double value, const int factor);
::std::tuple<int, int> unnormalized(const vec<2> v, const int width, const int height);

vec<3> to_sphere(const vec<2> v, const double radius = 1.0);

vec<3> spherical_to_cartesian(const vec<3> v);
vec<3> cartesian_to_spherical(const vec<3> v);

double norm_infinity(const vec<3> v);

vec<3> sphere_to_cube(const vec<3> v);
vec<3> cube_to_sphere(const vec<3> v);

::std::tuple<CubeFace, vec<2>> to_cube_map(const vec<3> v);
}