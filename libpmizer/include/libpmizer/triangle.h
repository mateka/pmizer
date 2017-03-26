#pragma once

#include <vector>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <libpmizer/point.h>


namespace libpmizer {

namespace details {

// Helper typedef for boost::geometry ring (polygon without holes)
template<typename Type = double, std::size_t Dim = 3>
using ring = ::boost::geometry::model::polygon<point<Type, Dim>>;

}


template<typename Type = double, std::size_t Dim = 3>
class triangle
{
public:
	using point = point<Type, Dim>;


	triangle(const point a, const point b, const point c)
		: m_ring{ {{ a, b, c, a }} }
	{}


	point barycentric(point v2) const {
		using namespace ::boost::geometry;

		point v0 = m_ring.outer()[1];
		subtract_point(v0, m_ring.outer()[0]);
		point v1 = m_ring.outer()[2];
		subtract_point(v1, m_ring.outer()[0]);
		subtract_point(v2, m_ring.outer()[0]);

		const auto d00 = dot_product(v0, v0);
		const auto d01 = dot_product(v0, v1);
		const auto d11 = dot_product(v1, v1);
		const auto d20 = dot_product(v2, v0);
		const auto d21 = dot_product(v2, v1);

		const auto det = d00 * d11 - d01 * d01;
		const auto v = (d11 * d20 - d01 * d21) / det;
		const auto w = (d00 * d21 - d01 * d20) / det;
		static constexpr Type one = 1.0;
		return { v, w, one - v - w };
	}


	bool intersects(const point p) const {
		return ::boost::geometry::within(p, m_ring);
	}


	bool intersects(const ray<Type, Dim> r) const {
		//details::ring<Type, Dim> rr{ {r[0], r[1]} };
		return false;// ::boost::geometry::intersects(m_ring, rr);
	}


	point intersection(const ray<Type, Dim> r) const {
		/*std::vector<point> result;
		::boost::geometry::intersection(m_ring, r, result);*/
		return point{};
	}
private:
	details::ring<Type, Dim>		m_ring;
};

}