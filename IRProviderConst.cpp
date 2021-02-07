#include "IRProviderConst.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define BUF_SIZE 128
#define CCY_SIZE 3

using namespace std;

namespace SiriusFM 
{

	IRProvider<IRModeE:: Const>:: IRProvider(const char* a_file) 
	{
		char buf [BUF_SIZE];
		char ccy [CCY_SIZE + 1];
		FILE* file = fopen(a_file, "r");
		
		for (int i = 0; i < int(CcyE::N); i++) 
		{
			m_IRs[i] = 0;
		};
	
		if (file == NULL) 
		{ 
			throw invalid_argument("Error opening file");
		} else 
		{
			while (fgets (ccy, CCY_SIZE + 1, file)) 
			{
				fgets (buf, BUF_SIZE, file);
				m_IRs[int(Str2CcyE(ccy))] = strtod(buf + 2, NULL);
			};
		};
	};
};





			
