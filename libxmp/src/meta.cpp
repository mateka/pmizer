#include <xmp/meta.h>
#include <sstream>


namespace xmp {

namespace {

// RAII helper for SXMPFiles
class xmp_file final {
public:
	explicit xmp_file(const ::std::experimental::filesystem::path& path) {
		if (!m_file.OpenFile(path.string(), kXMP_UnknownFile, kXMPFiles_OpenForUpdate | kXMPFiles_OpenOnlyXMP))
			throw open_xmp_file_error(path);
	}

	~xmp_file() {
		m_file.CloseFile();
	}

	SXMPFiles* operator->() {
		return &m_file;
	}
private:
	SXMPFiles	m_file;
};

}

meta::meta(
	const ::std::experimental::filesystem::path& path,
	const ::std::size_t width, const ::std::size_t height)
	: m_path{ path },
	m_tool{ "Pmizer (https://www.facebook.com/Pmizer-210285489456932/)" },
	m_width{ width }, m_height{ height },
	m_yaw{ 90.0 }, m_pitch{ 0.0 }, m_roll{ 0.0 },
	m_heading{ 180.0 }, m_fov{ 75.0 }
{}


::std::string meta::author() const {
	return m_author;
}

void meta::set_author(::std::string value) {
	m_author = ::std::move(value);
}

::std::string meta::title() const {
	return m_title;
}

void meta::set_title(::std::string value) {
	m_title = ::std::move(value);
}

::std::string meta::description() const {
	return m_description;
}

void meta::set_description(::std::string value) {
	m_description = ::std::move(value);
}

::std::string meta::url() const {
	return m_baseURL;
}

void meta::set_url(::std::string value) {
	m_baseURL = ::std::move(value);
}

::std::string meta::camera() const {
	return m_camera;
}

void meta::set_camera(::std::string value) {
	m_camera = ::std::move(value);
}

double meta::yaw() const {
	return m_yaw;
}

void meta::set_yaw(double value) {
	m_yaw = value;
}

double meta::pitch() const {
	return m_pitch;
}

void meta::set_pitch(double value) {
	m_pitch = value;
}

double meta::roll() const {
	return m_roll;
}

void meta::set_roll(double value) {
	m_roll = value;
}

double meta::heading() const {
	return m_heading;
}

void meta::set_heading(double value) {
	m_heading = value;
}

double meta::fov() const {
	return m_fov;
}

void meta::set_fov(double value) {
	m_fov = value;
}


void meta::write() const {
	try {
		xmp_file image{ m_path };

		SXMPMeta meta;
		image->GetXMP(&meta);
		meta.SetProperty(kXMP_NS_XMP, "CreatorTool", m_tool, NULL);
		if(!m_author.empty())
			meta.AppendArrayItem(kXMP_NS_DC, "creator", kXMP_PropArrayIsOrdered, m_author, 0);
		if(!m_title.empty())
			meta.SetLocalizedText(kXMP_NS_DC, "title", "en", "en-US", m_title);
		if (!m_description.empty())
			meta.SetLocalizedText(kXMP_NS_DC, "description", "en", "en-US", m_description);
		if (!m_baseURL.empty())
			meta.SetProperty(kXMP_NS_XMP, "BaseURL", m_baseURL, NULL);
		if (!m_camera.empty())
			meta.SetProperty(kXMP_NS_DM, "CameraModel", m_camera, NULL);
		
		XMP_DateTime updatedTime;
		SXMPUtils::CurrentDateTime(&updatedTime);
		meta.SetProperty_Date(kXMP_NS_XMP, "MetadataDate", updatedTime, 0);

		auto pano_meta = createPanoMeta();
		SXMPUtils::ApplyTemplate(
			&meta, pano_meta,
			kXMPTemplate_AddNewProperties |
			kXMPTemplate_ReplaceExistingProperties |
			kXMPTemplate_IncludeInternalProperties
		);

		if (image->CanPutXMP(meta))
			image->PutXMP(meta);
		else
			throw write_xmp_data_error(m_path, "Unable to add XMP data to file");
	}
	catch (XMP_Error &e) {
		throw write_xmp_data_error(m_path, e.GetErrMsg());
	}
}


SXMPMeta meta::createPanoMeta() const {
	std::ostringstream rdf;
	rdf << "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
		<< "	<rdf:Description rdf:about=\"\" xmlns:GPano=\"http://ns.google.com/photos/1.0/panorama/\">"
		<< "		<GPano:UsePanoramaViewer>True</GPano:UsePanoramaViewer>"
		<< "		<GPano:StitchingSoftware>" << m_tool << "</GPano:StitchingSoftware>"
		<< "		<GPano:ProjectionType>equirectangular</GPano:ProjectionType>"
		<< "		<GPano:InitialViewHeadingDegrees>" << m_yaw << "</GPano:InitialViewHeadingDegrees>"
		<< "		<GPano:InitialViewPitchDegrees>" << m_pitch << "</GPano:InitialViewPitchDegrees>"
		<< "		<GPano:InitialViewRollDegrees>" << m_roll << "</GPano:InitialViewRollDegrees>"
		<< "		<GPano:PoseHeadingDegrees>" << m_heading << "</GPano:PoseHeadingDegrees>"
		<< "		<GPano:InitialHorizontalFOVDegrees>" << m_fov << "</GPano:InitialHorizontalFOVDegrees>"
		<< "		<GPano:CroppedAreaLeftPixels>" << 0 << "</GPano:CroppedAreaLeftPixels>"
		<< "		<GPano:CroppedAreaTopPixels>" << 0 << "</GPano:CroppedAreaTopPixels>"
		<< "		<GPano:CroppedAreaImageWidthPixels>" << m_width << "</GPano:CroppedAreaImageWidthPixels>"
		<< "		<GPano:CroppedAreaImageHeightPixels>" << m_height << "</GPano:CroppedAreaImageHeightPixels>"
		<< "		<GPano:FullPanoWidthPixels>" << m_width << "</GPano:FullPanoWidthPixels>"
		<< "		<GPano:FullPanoHeightPixels>" << m_height << "</GPano:FullPanoHeightPixels>"
		<< "		<GPano:LargestValidInteriorRectLeft>" << 0 << "</GPano:LargestValidInteriorRectLeft>"
		<< "		<GPano:LargestValidInteriorRectTop>" << 0 << "</GPano:LargestValidInteriorRectTop>"
		<< "		<GPano:LargestValidInteriorRectWidth>" << m_width << "</GPano:LargestValidInteriorRectWidth>"
		<< "		<GPano:LargestValidInteriorRectHeight>" << m_height << "</GPano:LargestValidInteriorRectHeight>"
		<< "	</rdf:Description>"
		<< "</rdf:RDF>";

	SXMPMeta pano_meta;
	pano_meta.ParseFromBuffer(rdf.str().c_str(), static_cast<XMP_StringLen>(rdf.str().length()));
	return pano_meta;
}

}
