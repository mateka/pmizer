#pragma once

#include <stdexcept>
#include <pmize/error.h>
#include <pmize/image.h>
#include <pmize/cube_face.h>


namespace pmize {

// class for wrong cube map
class not_a_cube_map_error : public error, public ::std::logic_error {
public:
	not_a_cube_map_error() : ::std::logic_error("")
	{}
};


// class for unknown cube face
class unknown_cube_face_error : public error, public ::std::logic_error {
public:
	unknown_cube_face_error() : ::std::logic_error("")
	{}
};


// Class for cube texture (6 sub-textures)
class cube_map final
{
public:
	cube_map(image_view_t texture);
	cube_map(
		image_view_t left, image_view_t right,
		image_view_t front, image_view_t back,
		image_view_t top, image_view_t bottom
	);

	image_view_t face(const CubeFace f) const;
	image_view_t left() const { return m_left; }
	image_view_t right() const { return m_right; }
	image_view_t front() const { return m_front; }
	image_view_t back() const { return m_back; }
	image_view_t top() const { return m_top; }
	image_view_t bottom() const { return m_bottom; }
private:
	image_view_t		m_left;
	image_view_t		m_right;
	image_view_t		m_front;
	image_view_t		m_back;
	image_view_t		m_top;
	image_view_t		m_bottom;
};

}
