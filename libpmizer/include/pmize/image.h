#pragma once

#include <string>
#include <filesystem>
#include <boost/gil/gil_all.hpp>
#include <pmize/error.h>


namespace pmize {

class unknown_extension_error : public error, public ::std::runtime_error {
public:
	unknown_extension_error(const ::std::experimental::filesystem::path& path, const ::std::string& extension)
		: ::std::runtime_error("Unknown extension: \"" + extension + "\" for file: " + path.string())
	{}
};

using image_t = ::boost::gil::rgba32_image_t;
using image_view_t = ::boost::gil::rgba32_view_t;


image_t load_image(const ::std::experimental::filesystem::path& path);
void save_image(const ::std::experimental::filesystem::path& path, const image_t& image);

}
