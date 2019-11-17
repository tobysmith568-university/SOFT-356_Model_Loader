#pragma once
#include <string>
class Input
{
public:
	const std::string& GetSemantic();
	void SetSemantic(std::string _semantic);

	const std::string& GetSource();
	void SetSource(std::string _source);

	const std::string& GetOffset();
	void SetOffset(std::string _offset);

	const std::string& GetSet();
	void SetSet(std::string _set);

private:
	std::string semantic;
	std::string source;
	std::string offset;
	std::string set;
};