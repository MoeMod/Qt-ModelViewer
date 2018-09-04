#include "PointManager.h"

#include "tinyply.h"


static CPointManager gPointManager;

CPointManager &PointManager()
{
	return gPointManager;
}

CPointManager::CPointManager()
{

}


CPointManager::~CPointManager()
{

}

void CPointManager::clear() noexcept
{
	m_vecPoints.clear();
}

size_t CPointManager::size() noexcept
{
	return m_vecPoints.size();
}

void CPointManager::LoadFromFile(std::ifstream &ss)
{
	using namespace tinyply;
	PlyFile file;
	file.parse_header(ss);

	std::shared_ptr<PlyData> points;

	points = file.request_properties_from_element("vertex", { "x", "y", "z", "nx", "ny", "nz", "red", "green", "blue", "alpha" });

	file.read(ss);

	{
		const size_t numPointsBytes = points->buffer.size_bytes();
		m_vecPoints.resize(points->count);

		static_assert(std::is_standard_layout<Point>::value && sizeof(Point) == sizeof(float) * 6 + sizeof(unsigned char) * 4, "struct Point format incorrect.");
		std::memcpy(m_vecPoints.data(), points->buffer.get(), numPointsBytes);
	}
}

void CPointManager::SaveToFile(std::ofstream &filename)
{
	using namespace tinyply;

	std::vector<Vector> vecVerticles( verticles().begin(), verticles().end() );
	std::vector<Vector> vecNormals(normals().begin(), normals().end());
	std::vector<Color> vecRgbas(rgbas().begin(), rgbas().end());

	PlyFile file;
	file.add_properties_to_element("vertex", { "x", "y", "z" },
		Type::FLOAT32, vecVerticles.size(), reinterpret_cast<uint8_t*>(vecVerticles.data()), Type::INVALID, 0);

	file.add_properties_to_element("vertex", { "nx", "ny", "nz" },
		Type::FLOAT32, vecNormals.size(), reinterpret_cast<uint8_t*>(vecNormals.data()), Type::INVALID, 0);

	file.add_properties_to_element("vertex", { "red", "green", "blue", "alpha" },
		Type::UINT8, vecRgbas.size(), reinterpret_cast<uint8_t*>(vecRgbas.data()), Type::INVALID, 0);

	file.write(filename, false); // write ascii
}