#include <libpmizer/to_sphere_map.h>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>

#include <libpmizer/cube_map.h>
#include <libpmizer/mappings.h>


namespace libpmizer {

void to_sphere_map(texture_view cubemap, texture_view spheremap) {
	auto qmap = cube_map{ cubemap };
	for (int y = 0; y < spheremap.height(); ++y) {
		for (int x = 0; x < spheremap.width(); ++x) {
			const auto sp_tex_coord = normalized(x, y, spheremap.width() - 1, spheremap.height() - 1);
			const auto spherical_coords = to_sphere(sp_tex_coord);
			const auto cartesian_sphere = spherical_to_cartesian(spherical_coords);
			const auto cube = sphere_to_cube(cartesian_sphere);
			const auto qmap_info = to_cube_map(cube);

			auto face = qmap.front();
			switch (::std::get<0>(qmap_info))
			{
			case CubeFace::Left:
				face = qmap.left();
				break;
			case CubeFace::Front:
				face = qmap.front();
				break;
			case CubeFace::Right:
				face = qmap.right();
				break;
			case CubeFace::Back:
				face = qmap.back();
				break;
			case CubeFace::Top:
				face = qmap.top();
				break;
			case CubeFace::Bottom:
				face = qmap.bottom();
				break;
			}
			const auto qmap_coords = unnormalized(::std::get<1>(qmap_info), face.width() - 1, face.height() - 1);
			spheremap(x, y) = face(::std::get<0>(qmap_coords), ::std::get<1>(qmap_coords));
		}
	}
}


void to_sphere_map(const ::std::string& cubemap, const ::std::string& spheremap) {
	namespace gil = ::boost::gil;
	gil::rgb8_image_t input;
	gil::jpeg_read_and_convert_image(cubemap.c_str(), input);

	gil::rgb8_image_t output{ input.width(), input.height() };
	to_sphere_map(gil::view(input), gil::view(output));
	jpeg_write_view(spheremap.c_str(), gil::const_view(output));
}

}
