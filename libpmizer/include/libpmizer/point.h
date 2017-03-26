#pragma once

#include <cstddef>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>


namespace libpmizer {

template<typename Type = double, std::size_t Dim = 3>
using point = ::boost::geometry::model::point<Type, Dim, ::boost::geometry::cs::cartesian>;


template<typename Type = double>
using point2d = point<Type, 2>;


template<typename Type = double>
using point3d = point<Type, 3>;

}