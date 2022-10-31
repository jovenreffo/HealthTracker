#ifndef _ENTRYPAIR_H_
#define _ENTRYPAIR_H_

/*
* EntryPair is a class designed with the purpose of storing
* a string-string pair. One string will be the name of the entry, the other will be its contents.
* However, to avoid storing what may be a large string in a single std::string or wxString object,
* we will store its contents in an external text file and store the destination of the file in the second value of the pair.
*/

#include <string>

template<int size>
class EntryPair
{
private:
	std::string m_s1;
	std::string m_s2;

	int m_size{ size };

public:
	EntryPair() = default;
	EntryPair(const std::string& s1, const std::string& s2)
		: m_s1{ s1 }, m_s2{ s2 }
	{
	}

	//TODO : OVERLOAD OPERATOR[]

	// Getters
	const int GetSize() const { return m_size; }
	const std::string& GetString1() const { return m_s1; }
	const std::string& GetString2() const { return m_s2; }

	// Setters
	void SetString1(const std::string& s1) { m_s1 = s1; }
	void SetString2(const std::string& s2) { m_s2 = s2; }
};

#endif