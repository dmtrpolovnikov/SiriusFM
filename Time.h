#pragma once
#include <iostream>

namespace SiriusFM
{
	inline double YearFrac (time_t a_t) 
	{
		// Average year in seconds
		constexpr double SecInYear = 365.25 * 86400;
		return 1970.0 + double(a_t)/SecInYear;
	};
	
		inline double YearFracInterval (time_t a_t) 
	{
		// Average year in seconds
		constexpr double SecInYear = 365.25 * 86400;
		return double(a_t)/SecInYear;
	};
}
