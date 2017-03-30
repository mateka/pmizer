#pragma once

#include <xmp/meta.h>
#include <xmp/error.h>
#include <functional>
#include <stdexcept>
#include <filesystem>


namespace xmp {

// Helper for calling init and deinit functions
class unique_init
{
public:
	using Shutdown = ::std::function<void()>;

	template<typename Init>
	unique_init(Init init, Shutdown shutdown)
		: m_shutdown(shutdown)
	{
		init();
	}

	~unique_init() {
		m_shutdown();
	}
private:
	Shutdown	m_shutdown;
};


// Initializing engine error
class init_xmp_engine_error : public error, public std::runtime_error
{
public:
	init_xmp_engine_error(const std::string& msg) : std::runtime_error(msg) {}
};


// Factory class of meta engine
class meta_engine final
{
public:
	meta_engine();
	meta_engine(const meta_engine&) = delete;
	meta_engine& operator=(const meta_engine&) = delete;

	meta file_meta(
		const ::std::experimental::filesystem::path& path,
		const ::std::size_t width, const ::std::size_t height);
private:
	unique_init		m_engine;
	unique_init		m_files;
};

}
