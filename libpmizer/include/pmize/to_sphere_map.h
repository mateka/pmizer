#pragma once

#include <pmize/texture_view.h>
#include <string>


namespace pmize {

void to_sphere_map(texture_view cubemap, texture_view spheremap);
void to_sphere_map(const ::std::string& cubemap, const ::std::string& spheremap);

}