#include <xmp/meta_engine.h>
#include <xmp/xmp_toolkit.h>


namespace xmp {

meta_engine::meta_engine()
	: m_engine(
		[]() {
			if (!SXMPMeta::Initialize())
				throw init_xmp_engine_error("SXMPMeta");
		},
		[]() { SXMPMeta::Terminate(); }),
	m_files(
		[]() {
			if (!SXMPFiles::Initialize())
				throw init_xmp_engine_error("SXMPMeta");
		},
		[]() { SXMPFiles::Terminate(); })
{}

}
