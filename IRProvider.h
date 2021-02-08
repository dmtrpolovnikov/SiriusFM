#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdio>

using namespace std;

namespace SiriusFM 
{
	enum class CcyE 
	{
		UNDEFINED = -1,
		USD = 0, 
		EUR = 1, 
		GBP = 2, 
		CHF = 3, 
		JPY = 4, 
		CNY = 5, 
		RUB = 6,
		N = 7
	};
	
	inline char const* CcyE2Str (CcyE a_ccy)
	{
		switch(a_ccy)
		{
			case CcyE:: USD : return "USD";
			case CcyE:: EUR : return "EUR"; 
			case CcyE:: GBP : return "GBP";
			case CcyE:: CHF : return "CHF"; 
			case CcyE:: JPY : return "JPY";
			case CcyE:: CNY : return "CNY"; 
			case CcyE:: RUB : return "RUB";
			default : throw invalid_argument("Invalid currency!"); 
		};
	};
	
	inline CcyE Str2CcyE(char const* a_Str)
	{
		if (strcmp(a_Str, "USD") == 0)
			return CcyE:: USD;
		else if (strcmp(a_Str, "EUR") == 0)
			return CcyE:: EUR;
		else if (strcmp(a_Str, "GBP") == 0)
			return CcyE:: GBP;
		else if (strcmp(a_Str, "CHF") == 0)
			return CcyE:: CHF;
		else if (strcmp(a_Str, "JPY") == 0)
			return CcyE:: JPY;
		else if (strcmp(a_Str, "CNY") == 0)
			return CcyE:: CNY;
		else if (strcmp(a_Str, "RUB") == 0)
			return CcyE:: RUB;
		else
			throw invalid_argument("Invalid currency!");
	};
	
	enum class IRModeE 
	{
		Const = 0, 
		FwdCurve = 1, 
		Stoch = 2
	};
	
	template <IRModeE IRM>
	class IRProvider;
};
			


