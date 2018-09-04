#pragma once
#include <sstream>
#include <string>

template<class...Args>
inline std::string MakeString(Args &&...args)
{
	std::ostringstream oss;
	// (oss << ... << args);
	int p[] = { ((oss << std::forward<Args>(args)), 0)... };
	return oss.str();
}