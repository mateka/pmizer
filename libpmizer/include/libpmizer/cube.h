#pragma once

#include <array>
#include <algorithm>
#include <libpmizer/ray.h>
#include <libpmizer/face.h>
#include <libpmizer/cube_map.h>


namespace libpmizer {

template<typename Type = double>
class cube
{
public:
	using scalar = Type;
	using face = face<Type, 3>;
	using faces_type = ::std::array<face, 6>;
	using point = typename face::point;
	using pixel = texture_view::reference;

	cube(const point center, const scalar size, const cube_map texture)
		: m_texture(texture), m_faces{ [=]() -> faces_type {
			const auto extent = size * 0.5;
			// top 4 points
			const point p11{ center.get<0>() - extent, center.get<1>() - extent, center.get<2>() - extent };
			const point p12{ center.get<0>() + extent, center.get<1>() - extent, center.get<2>() - extent };
			const point p13{ center.get<0>() - extent, center.get<1>() - extent, center.get<2>() + extent };
			const point p14{ center.get<0>() + extent, center.get<1>() - extent, center.get<2>() + extent };
			// bottom 4 points
			const point p21{ center.get<0>() - extent, center.get<1>() + extent, center.get<2>() - extent };
			const point p22{ center.get<0>() + extent, center.get<1>() + extent, center.get<2>() - extent };
			const point p23{ center.get<0>() - extent, center.get<1>() + extent, center.get<2>() + extent };
			const point p24{ center.get<0>() + extent, center.get<1>() + extent, center.get<2>() + extent };
			return {{
				{ p11, p21, p23, p13, m_texture.left() },		// left
				{ p12, p14, p24, p22, m_texture.right() },		// right
				{ p11, p12, p22, p21, m_texture.front() },		// front
				{ p14, p13, p23, p24, m_texture.back() },		// back
				{ p12, p11, p13, p14, m_texture.top() },		// top
				{ p21, p22, p24, p23, m_texture.bottom() }		// bottom
			}};
		}()}
	{}


	pixel colour(const ray<Type, 3> r) const {
		using namespace ::std;

		const auto it = find_if(
			cbegin(m_faces), cend(m_faces),
			[r](auto f) { return f.intersects(r); }
		);

		if (it != cend(m_faces))
			return it->colour(r);
		else
			throw no_intersection_error{};
	}
private:
	cube_map			m_texture;
	faces_type			m_faces;
};

}
