#pragma once
#include<stdexcept>
#include<iostream>
#include<cmath>
using namespace std;

namespace SiriusFM {
	class Call_Option {
		private:
			double const m_full_exp_time;
			double const m_exp_strike;
		
		public:
			Call_Option (double exp_strike, double full_exp_time):
				m_exp_strike(exp_strike), m_full_exp_time(full_exp_time) 
			{if (full_exp_time < 0 || exp_strike <= 0) {
						throw invalid_argument("Incorrect arguments");};
		};
		
		double PayOff(double curr_stock) {
                                if (curr_stock <= 0) {
                                throw invalid_argument("Incorrect arguments");
                                } else {
				return max(curr_stock - (this -> m_exp_strike), 0.);
				};
				};
		};
};
				
