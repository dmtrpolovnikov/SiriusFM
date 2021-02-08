#pragma once
#include <iostream>

using namespace std;

namespace SiriusFM
{
	inline double YearFrac (time_t a_t) 
	{
		// Average year in seconds
		constexpr double SecY = 365.25 * 86400;
		return 1970.0 + double(a_t)/SecY;
	};
}
