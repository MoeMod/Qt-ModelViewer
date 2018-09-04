#pragma once

#include <array>
#include <string>
#include <fstream>

#include "Vector.h"
#include "Color.h"

#pragma pack(push)
#pragma pack(1) // disable memory gaps.
struct Point
{
	Vector verticle;
	Vector normal;
	Color rgba;
};
#pragma pack(pop)

#include "tinyply.h"

class CPointManager
{
public:
	CPointManager();
	~CPointManager();

public:
	void clear() noexcept;
	size_t size() noexcept;

public:
	/*
		throw std::runtime_error for error opening file
		throw std::exception for common error 
	*/
	void LoadFromFile(std::ifstream &filename);

	template<class T, class = decltype(std::ifstream(std::declval<T>()))>
	void LoadFromFile(T &&filename) // adapter
	{
		std::ifstream ss(std::forward<T>(filename), std::ios::binary);
		if (ss.fail()) throw std::runtime_error("file not found");
		return LoadFromFile(ss);
	}

	template<class T>
	bool LoadFromFile(T &&file, std::nothrow_t)
	{
		try { LoadFromFile(std::forward<T>(file)); return true; }
		catch (...) { return false; }
	}

public:
	/*
	throw std::runtime_error for error opening file
	throw std::exception for common error
	*/
	void SaveToFile(std::ofstream &filename);

	template<class T, class = decltype(std::ifstream(std::declval<T>()))>
	void SaveToFile(T &&filename) // adapter
	{
		std::ofstream ss(std::forward<T>(filename), std::ios::binary);
		if (ss.fail()) throw std::runtime_error("cannot save");
		return SaveToFile(ss);
	}

	template<class T>
	bool SaveToFile(T &&file, std::nothrow_t)
	{
		try { LoadFromFile(std::forward<T>(file)); return true; }
		catch (...) { return false; }
	}

private:
	using ContainerType = std::vector<Point>;
	ContainerType m_vecPoints;

public:
	template<class MyClass, class MyType, MyType MyClass::*P>
	struct ProxyContainer // how to reduce the 1st and 2nd template argument?
	{
		ContainerType &vec;
		
		struct iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using value_type = MyType;
			using difference_type = ptrdiff_t;
			using pointer = value_type * ;
			using reference = value_type & ;

			ContainerType::iterator iter;
			value_type &operator*(){ return (*iter).*P; }
			const value_type &operator*() const { return (*iter).*P; }
			iterator &operator++() { ++iter; return *this; }
			bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
			bool operator==(const iterator &rhs) { return iter == rhs.iter; }
		};

		iterator begin() { return { vec.begin() }; };
		iterator end() { return { vec.end() }; };
	};
	

	ProxyContainer<Point, Vector, &Point::verticle> verticles() { return { m_vecPoints }; }
	ProxyContainer<Point, Vector, &Point::normal> normals() { return { m_vecPoints }; }
	ProxyContainer<Point, Color, &Point::rgba> rgbas() { return { m_vecPoints }; }
	ContainerType::iterator begin() { return m_vecPoints.begin(); }
	ContainerType::iterator end() { return m_vecPoints.end(); }
};

CPointManager &PointManager();