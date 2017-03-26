#pragma once

#include <array>
#include <numeric>
#include <stdexcept>
#include <libpmizer/error.h>
#include <libpmizer/triangle.h>
#include <libpmizer/ray.h>
#include <libpmizer/point.h>
#include <libpmizer/texture_view.h>


namespace libpmizer {

// class for accessing intersection, when object do not intersect with face
class no_intersection_error : public error, public ::std::logic_error {
public:
	no_intersection_error() : ::std::logic_error("")
	{}
};


// Class for textured quad
template<typename Type = double, std::size_t Dim = 3>
class face
{
public:
	using point = typename triangle<Type, Dim>::point;
	using texture_point = libpmizer::point<double, 2>;
	using pixel = texture_view::reference;


	face(
		const point a, const point b, const point c,
		const point d, const texture_view tex
	)
		: m_triangle_1{a, b, c}, m_triangle_2{a, c, d}, m_texture{ tex }
	{}


	bool intersects(const ray<Type, Dim> r) const {
		return m_triangle_1.intersects(r) || m_triangle_2.intersects(r);
	}


	point intersection(const ray<Type, Dim> r) const {
		point result;
		if (m_triangle_1.intersects(r))
			result = m_triangle_1.intersection(r);
		else if (m_triangle_2.intersects(r))
			result = m_triangle_2.intersection(r);
		else
			throw no_intersection_error{};
		return result;
	}


	texture_point tex_coord(const point p) const {
		using namespace ::std;

		static const std::array<texture_point, 4> coords = { {
			{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}
		} };

		std::array<double, 4> weights;
		if (m_triangle_1.intersects(p)) {
			const auto p_bar = m_triangle_1.barycentric(p);
			weights[0] = p_bar.get<0>();
			weights[1] = p_bar.get<1>();
			weights[2] = p_bar.get<2>();
			weights[3] = 0.0;
		}
		else if (m_triangle_2.intersects(p)) {
			const auto p_bar = m_triangle_1.barycentric(p);
			weights[0] = p_bar.get<0>();
			weights[1] = 0.0;
			weights[2] = p_bar.get<1>();
			weights[3] = p_bar.get<2>();
		}
		else
			throw no_intersection_error{};
		
		return/* inner_product(
			cbegin(coords), cend(coords),
			cbegin(weights), texture_point{}
		);*/texture_point{};
	}


	texture_point tex_coord(const ray<Type, Dim> r) const {
		const auto p = intersection(r);
		return tex_coord(p);
	}


	pixel colour(const point p) const {
		const auto coords = tex_coord(p);
		const texture_view::point_t tex_pos = {
			coord(m_texture.width() * coords.get<0>()),
			coord(m_texture.height() * coords.get<1>())
		};
		return *m_texture.xy_at(tex_pos);
	}


	pixel colour(const ray<Type, Dim> r) const {
		const auto p = intersection(r);
		return colour(p);
	}
private:
	texture_view::coord_t coord(Type val) const {
		return static_cast<texture_view::coord_t>(val);
	}


	triangle<Type, Dim>			m_triangle_1;
	triangle<Type, Dim>			m_triangle_2;
	texture_view				m_texture;
};

}
