#include <pmize/image.h>

#include <algorithm>

#define png_infopp_NULL nullptr
#define int_p_NULL nullptr
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
#include <boost/gil/extension/io/png_io.hpp>


namespace pmize {

namespace {

::std::string extension(const ::std::experimental::filesystem::path& path) {
	using namespace ::std;

	auto ext = path.extension().string();
	transform(begin(ext), end(ext), begin(ext), tolower);
	return ext;
}

}


image_t load_image(const ::std::experimental::filesystem::path& path) {
	namespace gil = ::boost::gil;

	image_t result;
	const auto ext = extension(path);
	if (ext == ".jpeg" || ext == ".jpg")
		gil::jpeg_read_and_convert_image(path.string(), result);
	else if (ext == ".tiff" || ext == ".tif")
		gil::tiff_read_and_convert_image(path.string(), result);
	else if (ext == ".png")
		gil::png_read_and_convert_image(path.string(), result);
	else
		throw unknown_extension_error(path, ext);

	return result;
}

void save_image(const ::std::experimental::filesystem::path& path, const image_t& image) {
	namespace gil = ::boost::gil;

	const auto ext = extension(path);
	const auto out_view = gil::const_view(image);
	if (ext == ".jpeg" || ext == ".jpg")
		gil::jpeg_write_view(path.string(), gil::color_converted_view<gil::rgb8_pixel_t>(out_view));
	else if (ext == ".tiff" || ext == ".tif")
		gil::tiff_write_view(path.string(), gil::color_converted_view<gil::rgb32f_pixel_t>(out_view));
	else if (ext == ".png")
		gil::png_write_view(path.string(), gil::color_converted_view<gil::rgba16_pixel_t>(out_view));
	else
		throw unknown_extension_error(path, ext);
}

}