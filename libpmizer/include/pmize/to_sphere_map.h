#pragma once

#include <tuple>
#include <boost/gil/gil_all.hpp>
#include <pmize/cube_face.h>
#include <pmize/cube_map.h>
#include <pmize/image_coordinates.h>


namespace pmize {

::std::tuple<image_coordinates, CubeFace>
spheremap_coords_to_cubemap(
	const image_coordinates on_sphere, const image_dimensions cube_size);

template<typename CubeImageView, typename SphereImageView>
void to_sphere_map(CubeImageView cubemap, SphereImageView spheremap) {
	namespace gil = ::boost::gil;

	gil::gil_function_requires<gil::ImageViewConcept<CubeImageView>>();
	gil::gil_function_requires<gil::MutableImageViewConcept<SphereImageView>>();
	gil::gil_function_requires<gil::ColorSpacesCompatibleConcept<
		typename gil::color_space_type<CubeImageView>::type,
		typename gil::color_space_type<SphereImageView>::type
	>>();

	auto qmap = cube_map{ cubemap };
	for (int y = 0; y < spheremap.height(); ++y) {
		for (int x = 0; x < spheremap.width(); ++x) {
			const auto mapped = spheremap_coords_to_cubemap(
				{ x, y, {spheremap.width(), spheremap.height()} },
				{ qmap.front().width(), qmap.front().height() }
			);
			const auto coords = ::std::get<0>(mapped);
			spheremap(x, y) = qmap.face(::std::get<1>(mapped))(coords.x(), coords.y());
		}
	}
}

}