#include <pmize/cube_map.h>


namespace pmize {

cube_map::cube_map(texture_view texture)
{
	namespace gil = ::boost::gil;

	const auto size = texture.width() / 4;
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
	texture_view left, texture_view right,
	texture_view front, texture_view back,
	texture_view top, texture_view bottom
)
	: m_left(left), m_right(right), m_front(front),
	  m_back(back), m_top(top), m_bottom(bottom)
{}

}
