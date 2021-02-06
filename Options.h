#pragma once
#include<stdexcept>
#include<iostream>
#include<cmath>
using namespace std;

namespace SiriusFM {
	class Call_Option {
		private:
			double const mc_exp_time;
			double const mc_exp_cost;
		
		public:
			Call_Option (double exp_cost, double exp_time):
				mc_exp_cost(exp_cost), mc_exp_time(exp_time) 
			{if (exp_time < 0 || exp_cost <= 0) {
						throw invalid_argument("Incorrect arguments");};
		};
		
		double Curr_expiration(double curr_cost, double left_exp_time) {
                                if (curr_cost <= 0 || left_exp_time < 0) {
                                throw invalid_argument("Incorrect arguments");
                                } else {
				return max((this -> mc_exp_cost) - curr_cost * ((this -> mc_exp_time)-left_exp_time), 0.);
				};
				};
		};
};
				
