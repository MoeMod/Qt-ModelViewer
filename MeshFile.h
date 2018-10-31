#pragma once

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

class CMeshFile
{
	/*
		throw std::runtime_error for error opening file
		throw std::exception for common error
	*/
public:
	CMeshFile() {}
	CMeshFile(const std::string &filename) { LoadFromFile(filename); }

public:
	/*
	throw std::runtime_error for error opening file
	throw std::exception for common error
	*/
	void LoadFromFile(const std::string &filename);
	void SaveToFile(const std::string &filename) const;

public:
	~CMeshFile() {};

public:
	typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

	// accessor
	MyMesh &Data() noexcept { return mesh; }
	const MyMesh &Data() const noexcept { return mesh; }
	
private:
	MyMesh mesh;
};