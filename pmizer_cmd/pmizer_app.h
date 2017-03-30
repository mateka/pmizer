#pragma once

#include <string>
#include <filesystem>
#include <boost/program_options.hpp>


namespace pmizer {

class pmizer_app {
public:
	pmizer_app();

	void run(int argc, char *argv[]);
private:
	bool parse_cmd(int argc, char *argv[]);
	void to_sphere_map();
	void add_meta();

	::boost::program_options::options_description	m_options;
	::std::experimental::filesystem::path			m_input;
	::std::experimental::filesystem::path			m_output;
	::std::string									m_author;
	::std::string									m_title;
	::std::string									m_description;
	::std::string									m_url;
	::std::string									m_camera;
	::std::size_t									m_width;
	::std::size_t									m_height;
	double											m_fov;
};

}
