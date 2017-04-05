#pragma once

#include <tuple>
#include <pmize/image.h>
#include <pmize/cube_face.h>
#include <pmize/image_coordinates.h>


namespace pmize {

::std::tuple<image_coordinates, CubeFace>
spheremap_coords_to_cubemap(
	const image_coordinates on_sphere, const image_dimensions cube_size);

void to_sphere_map(image_view_t cubemap, image_view_t spheremap);

}