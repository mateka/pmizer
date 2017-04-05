#pragma once

#include <cstddef>
#include <stdexcept>
#include <pmize/error.h>


namespace pmize {

// Class for error of wrong image dimensions
class wrong_image_dimensions_error : public error, public ::std::logic_error {
public:
	wrong_image_dimensions_error() : ::std::logic_error("")
	{}
};


// Class for error of wrong image coordinates
class wrong_image_coordinates_error : public error, public ::std::logic_error {
public:
	wrong_image_coordinates_error() : ::std::logic_error("")
	{}
};


// Helper class for image dimensions
class image_dimensions {
public:
	image_dimensions(const ::std::ptrdiff_t width, const ::std::ptrdiff_t height);

	::std::ptrdiff_t	width() const { return m_width; }
	::std::ptrdiff_t	height() const { return m_height; }
private:
	::std::ptrdiff_t	m_width;
	::std::ptrdiff_t	m_height;
};


// Helper class for image coordinates
class image_coordinates {
public:
	image_coordinates(const int x, const int y, const image_dimensions size);

	int					x() const { return m_x; }
	int					y() const { return m_y; }
	image_dimensions	size() const { return m_size; }
private:
	int					m_x;
	int					m_y;
	image_dimensions	m_size;
};

}