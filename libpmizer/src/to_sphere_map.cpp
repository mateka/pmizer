#include <pmize/to_sphere_map.h>
#include <boost/gil/gil_all.hpp>
#include <pmize/cube_map.h>
#include <pmize/mappings.h>


namespace pmize {

::std::tuple<image_coordinates, CubeFace>
spheremap_coords_to_cubemap(
	const image_coordinates on_sphere,
	const image_dimensions cube_size
) {
	const auto sp_tex_coord = normalized(
		on_sphere.x(), on_sphere.y(),
		on_sphere.size().width() - 1, on_sphere.size().height() - 1
	);
	const auto spherical_coords = to_sphere(sp_tex_coord);
	const auto cartesian_sphere = spherical_to_cartesian(spherical_coords);
	const auto cube = sphere_to_cube(cartesian_sphere);
	const auto qmap_info = to_cube_map(cube);
	const auto qmap_coords = unnormalized(
		::std::get<1>(qmap_info),
		cube_size.width() - 1, cube_size.height() - 1
	);
	return {
		{ ::std::get<0>(qmap_coords), ::std::get<1>(qmap_coords), cube_size },
		::std::get<0>(qmap_info)
	};
}

void to_sphere_map(image_view_t cubemap, image_view_t spheremap) {
	auto qmap = cube_map{ cubemap };
	for (int y = 0; y < spheremap.height(); ++y) {
		for (int x = 0; x < spheremap.width(); ++x) {
			const auto mapped = spheremap_coords_to_cubemap(
				{ x, y, image_dimensions(spheremap.width(), spheremap.height()) },
				image_dimensions(qmap.front().width(), qmap.front().height())
			);
			const auto coords = ::std::get<0>(mapped);
			spheremap(x, y) = qmap.face(::std::get<1>(mapped))(coords.x(), coords.y());
		}
	}
}

}
