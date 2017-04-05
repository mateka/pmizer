#include <pmize/cube_map.h>


namespace pmize {

cube_map::cube_map(image_view_t texture)
{
	namespace gil = ::boost::gil;

	const int size = static_cast<int>(texture.width() / 4);
	if (size * 3 != texture.height())
		throw not_a_cube_map_error{};

	m_left		= gil::subimage_view(texture,        0,	   size,	size,	size);
	m_right		= gil::subimage_view(texture, 2 * size,	   size,	size,	size);
	m_front		= gil::subimage_view(texture,     size,	   size,	size,	size);
	m_back		= gil::subimage_view(texture, 3 * size,	   size,	size,	size);
	m_top		= gil::subimage_view(texture,     size,  	  0,	size,	size);
	m_bottom	= gil::subimage_view(texture,     size, 2 * size,	size,	size);
}


cube_map::cube_map(
	image_view_t left, image_view_t right,
	image_view_t front, image_view_t back,
	image_view_t top, image_view_t bottom
)
	: m_left{ left }, m_right{ right }, m_front{ front },
	  m_back{ back }, m_top{ top }, m_bottom{ bottom }
{}


image_view_t cube_map::face(const CubeFace f) const {
	switch (f) {
	case CubeFace::Left:
		return left();
	case CubeFace::Front:
		return front();
	case CubeFace::Right:
		return right();
	case CubeFace::Back:
		return back();
	case CubeFace::Top:
		return top();
	case CubeFace::Bottom:
		return bottom();
	default:
		throw unknown_cube_face_error{};
	}
}

}
