#pragma once
#include<stdexcept>
#include<iostream>

namespace SiriusGM
{
	class DiffusionLipton
	{
		private:
			double const m_mu;
			double const m_sigma_1;
			double const m_sigma_2;
			double const m_sigma_3;
		public:
			DiffusionLipton(double mu, double sigma_1, double sigma_2, double sigma_3):
				m_mu(mu), m_sigma_1(sigma_1), m_sigma_2(sigma_2), m_sigma_3(sigma_3)
		{if (sigma_1 <= 0 || sigma_3 <= 0 || sigma_2*sigma_2 - 4*sigma_1*sigma_3 >= 0)
			{
				throw std:: invalid_argument("Incorrect values");
			};
		};
			double mu (double st, double t) {
				return (st*(this -> m_mu) >= 0) ? st*(this -> m_mu):0;};
			double sigma (double st, double t) {
				double sig = m_sigma_1 + st*(this -> m_sigma_2) + st*st*(this-> m_sigma_3);
				return sig>0 ? sig: 0;};
	};
};
