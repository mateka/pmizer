#include <pmize/image_coordinates.h>


namespace pmize {

image_dimensions::image_dimensions(
	const ::std::ptrdiff_t width, const ::std::ptrdiff_t height)
	: m_width{ width }, m_height{ height }
{
	if (m_width < 0 || m_height < 0)
		throw wrong_image_dimensions_error{};
}


image_coordinates::image_coordinates(
	const int x, const int y, const image_dimensions size)
	: m_x{ x }, m_y{ y }, m_size{ size }
{
	if (m_x < 0 || m_x >= m_size.width() || m_y < 0 || m_y >= m_size.height())
		throw wrong_image_coordinates_error{};
}

}
