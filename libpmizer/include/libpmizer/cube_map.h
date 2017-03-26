#pragma once

#include <stdexcept>
#include <libpmizer/error.h>
#include <libpmizer/texture_view.h>


namespace libpmizer {

// class for accessing intersection, when object do not intersect with face
class not_a_cube_map_error : public error, public ::std::logic_error {
public:
	not_a_cube_map_error() : ::std::logic_error("")
	{}
};


// Class for cube texture (6 sub-textures)
class cube_map
{
public:
	cube_map(texture_view texture);
	cube_map(
		texture_view left, texture_view right,
		texture_view front, texture_view back,
		texture_view top, texture_view bottom
	);

	texture_view left() const { return m_left; }
	texture_view right() const { return m_right; }
	texture_view front() const { return m_front; }
	texture_view back() const { return m_back; }
	texture_view top() const { return m_top; }
	texture_view bottom() const { return m_bottom; }
private:
	texture_view		m_left;
	texture_view		m_right;
	texture_view		m_front;
	texture_view		m_back;
	texture_view		m_top;
	texture_view		m_bottom;
};

}
