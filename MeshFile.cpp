#include "MeshFile.h"

// 参考： https://blog.csdn.net/qq_28057541/article/details/51362945

void CMeshFile::LoadFromFile(const std::string &filename)
{
	mesh.request_vertex_normals();
	//如果不存在顶点法线，则报错
	if (!mesh.has_vertex_normals())
	{
		throw std::runtime_error("错误：标准定点属性 “法线”不存在");
	}

	// 读取文件，错误就throw
	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mesh, filename, opt))
	{
		throw std::runtime_error("error loading from file");
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		// 通过面法线计算顶点法线
		mesh.request_face_normals();
		// mesh计算出顶点法线
		mesh.update_normals();
		// 释放面法线
		mesh.release_face_normals();
	}
}

void CMeshFile::SaveToFile(const std::string &filename) const
{
	if(!OpenMesh::IO::write_mesh(mesh, filename))
		throw std::runtime_error("error saving to file");
}