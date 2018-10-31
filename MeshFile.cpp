#include "MeshFile.h"

// �ο��� https://blog.csdn.net/qq_28057541/article/details/51362945

void CMeshFile::LoadFromFile(const std::string &filename)
{
	// ��ȡ�ļ��������throw
	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mesh, filename, opt))
	{
		throw std::runtime_error("error loading from file");
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		// ͨ���淨�߼��㶥�㷨��
		mesh.request_face_normals();
		// mesh��������㷨��
		mesh.update_normals();
		// �ͷ��淨��
		mesh.release_face_normals();
	}
}

void CMeshFile::SaveToFile(const std::string &filename) const
{
	if(!OpenMesh::IO::write_mesh(mesh, filename))
		throw std::runtime_error("error saving to file");
}