#include "pmizer_app.h"
#include <iostream>

#include <pmize/image.h>
#include <pmize/to_sphere_map.h>
#include <xmp/meta_engine.h>


namespace pmizer {

pmizer_app::pmizer_app()
	: m_options{ "Pmizer\t-App for converting cubemaps to panoramic photos" }
{
	namespace po = ::boost::program_options;

	m_options.add_options()
		("help", "shows help message")
		("input,i", po::value<::std::experimental::filesystem::path>(&m_input)->required(), "path to cubemap image")
		("output,o", po::value<::std::experimental::filesystem::path>(&m_output)->required(), "path to output image")
		("width,w", po::value<::std::size_t>(&m_width)->required(), "output image width")
		("height,h", po::value<::std::size_t>(&m_height)->required(), "output image height")
		("author,a", po::value<::std::string>(&m_author), "output image author")
		("title,t", po::value<::std::string>(&m_title), "output image title")
		("description,d", po::value<::std::string>(&m_description), "output image description")
		("camera", po::value<::std::string>(&m_camera), "output image camera model")
		("url", po::value<::std::string>(&m_url), "output image base URL")
		("fov", po::value<double>(&m_fov)->default_value(75.0), "output image initial Field Of View")
		;
}


void pmizer_app::run(int argc, char *argv[]) {
	try {
		if (!(parse_cmd(argc, argv)))
			return;

		::std::cout << "Converting to panorama..." << ::std::flush;
		to_sphere_map();
		::std::cout << "done." << std::endl;

		::std::cout << "Adding XMP meta..." << ::std::flush;
		add_meta();
		::std::cout << "done." << std::endl;
	}
	catch (const std::exception& ex) {
		::std::cerr << ex.what() << ::std::endl;
	}
}


bool pmizer_app::parse_cmd(int argc, char *argv[]) {
	try {
		namespace po = ::boost::program_options;

		po::variables_map cmd_variables;
		po::store(po::parse_command_line(argc, argv, m_options), cmd_variables);
		if (cmd_variables.count("help")) {
			::std::cout << m_options << std::endl;
			return false;
		}
		po::notify(cmd_variables);
		return true;
	}
	catch (const std::exception& ex) {
		::std::cout << m_options << std::endl;
		::std::cerr << ex.what() << ::std::endl;
	}
	return false;
}


void pmizer_app::to_sphere_map() {
	namespace gil = ::boost::gil;

	auto cubemap = ::pmize::load_image(m_input);
	::pmize::image_t output(m_width, m_height);
	::pmize::to_sphere_map(gil::view(cubemap), gil::view(output));
	::pmize::save_image(m_output, output);
}


void pmizer_app::add_meta() {
	using namespace ::xmp;
	
	meta_engine engine;
	auto xmp_meta = engine.file_meta(m_output, m_width, m_height);
	xmp_meta.set_author(m_author);
	xmp_meta.set_title(m_title);
	xmp_meta.set_description(m_description);
	xmp_meta.set_url(m_url);
	xmp_meta.set_fov(m_fov);
	xmp_meta.set_camera(m_camera);

	xmp_meta.write();
}

}
