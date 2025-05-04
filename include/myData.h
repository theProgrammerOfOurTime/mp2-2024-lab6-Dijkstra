#pragma once
#include <algorithm>

//data for heah
struct myPair
{
	int32_t v;
	int32_t w;
	myPair(int32_t _v, int32_t _w) : v(_v), w(_w) { }
	myPair(const myPair& mp)
	{
		w = mp.w;
		v = mp.v;
	}
	myPair(myPair&& mp)
	{
		std::swap(w, mp.w);
		std::swap(v, mp.v);
	}
	myPair& operator=(const myPair& mp)
	{
		w = mp.w;
		v = mp.v;
		return *this;
	}
	myPair& operator=(myPair&& mp)
	{
		std::swap(w, mp.w);
		std::swap(v, mp.v);
		return *this;
	}
	myPair() : v(-1), w(-1) { }
	bool operator>(const myPair& p2) const
	{ 
		return w > p2.w;
	}
	bool operator<(const myPair& p2) const 
	{ 
		return w < p2.w; 
	}
};