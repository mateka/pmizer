#include <pmize/to_sphere_map.h>
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

}
