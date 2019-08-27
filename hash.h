#pragma once

#include <iostream>
#include <string>
#include <functional>

template <class K> class Hash;

template<>
class Hash<std::string>
{
public:
	size_t operator()(const std::string theKey) const
	{
		unsigned long hashValue = 0;
		int length = (int)theKey.length();

		for (int i = 0; i < length; i++) {

			hashValue = 5*hashValue + (unsigned char)theKey[i];
		}

		return size_t(hashValue);
	}
};

template<>
class Hash<int>
{
public:
	size_t operator()(const int theKey) const
	{
		return size_t(theKey);
	}
};

template<>
class Hash<long>
{
public:
	size_t operator()(const long theKey) const
	{
		return size_t(theKey);
	}
};
