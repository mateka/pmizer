#pragma once

#include <libpmizer/point.h>


namespace libpmizer {

template<typename Type = double, std::size_t Dim = 3>
using ray = ::boost::geometry::model::linestring<point<Type, Dim>>;

}