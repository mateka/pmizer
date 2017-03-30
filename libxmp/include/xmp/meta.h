#pragma once

#include <string>
#include <filesystem>
#include <xmp/xmp_toolkit.h>
#include <xmp/error.h>


namespace xmp {

// Opening file error
class open_xmp_file_error : public error, public std::runtime_error
{
public:
	open_xmp_file_error(const ::std::experimental::filesystem::path& path)
		: std::runtime_error(path.string())
	{}
};


// Writing meta data to file error
class write_xmp_data_error : public error, public std::runtime_error
{
public:
	write_xmp_data_error(
		const ::std::experimental::filesystem::path& path,
		const ::std::string& message)
		: std::runtime_error("Error: \"" + message + "\" file: " + path.string())
	{}
};


// Metadata of single file
class meta final
{
public:
	::std::string author() const;
	void set_author(::std::string value);
	::std::string title() const;
	void set_title(::std::string value);
	::std::string description() const;
	void set_description(::std::string value);
	::std::string url() const;
	void set_url(::std::string value);
	::std::string camera() const;
	void set_camera(::std::string value);
	double yaw() const;
	void set_yaw(double value);
	double pitch() const;
	void set_pitch(double value);
	double roll() const;
	void set_roll(double value);
	double heading() const;
	void set_heading(double value);
	double fov() const;
	void set_fov(double value);

	void write() const;
private:
	friend class meta_engine;

	meta(
		const ::std::experimental::filesystem::path& path,
		const ::std::size_t width, const ::std::size_t height);
	SXMPMeta createPanoMeta() const;

	::std::experimental::filesystem::path	m_path;
	::std::string							m_author;
	::std::string							m_title;
	::std::string							m_description;
	::std::string							m_baseURL;
	::std::string							m_camera;
	::std::string							m_tool;
	::std::size_t							m_width;
	::std::size_t							m_height;
	double									m_yaw;
	double									m_pitch;
	double									m_roll;
	double									m_heading;
	double									m_fov;
};

}
