#pragma once
#include<stdexcept>
#include<iostream>
#include<cmath>

namespace SiriusFM
{
	class DiffusionCEV {
		private:
			double const m_mu;
			double const m_sigma;
			double const m_beta;
		public:

			DiffusionCEV (double mu, double sigma, double beta): m_mu(mu), m_sigma(sigma),
									m_beta(beta)
			{ if (sigma <= 0 || beta < 0 || beta > 1)
				{throw std:: invalid_argument("Incorrect values");};
			};

			double mu (double st, double t) {
				return (st * (this -> m_mu) >= 0)?st*(this -> m_mu):0;};
			double sigma(double st, double t){
				double sig = this -> m_sigma * pow(st, this -> m_beta);
				return sig>0? sig : 0;};
	};
};
