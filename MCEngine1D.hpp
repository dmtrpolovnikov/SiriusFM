#include "MCEngine1D.h"
#include "Time.h"
#include <random>
#include <iostream>
#include <cassert>

using namespace std;

namespace SiriusFM 
{
	template <typename Diffusion1D,
		  typename AProvider, typename BProvider,
		  typename AssetClassA, typename AssetClassB>

	inline void MCEngine1D <Diffusion1D, 
		AProvider, BProvider,
		AssetClassA, AssetClassB>::Simulate 
			(time_t a_t0, time_t a_T,
			int a_tau_min, double a_S0,
			long a_P,
			Diffusion1D const* a_diff,
			AProvider const* a_rateA,
			BProvider const* a_rateB,
			AssetClassA a_A,
			AssetClassB a_B,
			bool a_isRN
		 )
	{	
		double y0 =YearFrac(a_t0);
		double yT = YearFrac(a_T);
		
		double tau = double (a_tau_min) / (365.25 * 1440.0);
		long L = (ceil((yT - y0) / tau)) + 1; // Path length
		long P = 2 * a_P; // Antithetic variables
		std:: normal_distribution <> N01(0.0,1.0);
		std:: mt19937_64 u;
		double stau = sqrt(tau);
                double tlast = sqrt(yT - y0 - double(L-1) * tau);
                double slast = sqrt(tlast);
                double mu0 = 0.0;
		double mu1 = 0.0;
                assert(slast <= stau);
                
                // Checks valid
		assert(a_diff != nullptr && 
			a_rateA != nullptr && 
			a_rateB != nullptr &&
			a_A != AssetClassA::UNDEFINED && 
			a_B != AssetClassB::UNDEFINED &&
			a_t0 <= a_T &&
		       	a_tau_min > 0 && a_P > 0);

		// Main Simulation Loop 
		if ( L * P > m_MaxL * m_MaxP)
			throw invalid_argument("Invalid length paths");

		for (long p = 0; p < a_P; p++) 
		{
			double* path0 = m_Paths + 2 * p * L;
			double* path1 = path0 + L;
			path0[0] = a_S0;
			path1[0] = a_S0;
			double y = y0;
			double Sp0 = a_S0;
			double Sp1 = a_S0;
			
			assert(slast <= stau && slast > 0);

			for (long l = 1; l < L; l++) 
			{
				if (a_A = a_isRN) 
				{
					double delta_r = (a_rateA -> r(a_A, y))
					       	- (a_rateB -> r(a_B, y));
					double mu0 = delta_r * Sp0;
					double mu1 = delta_r * Sp1;
				}
				else
				{
					double mu0 = (a_diff -> Mu(Sp0,y));
					double mu1 = (a_diff -> Mu(Sp1, y));
				};
				
				double sigma0 = a_diff -> Sigma(Sp0, y);
				double sigma1 = a_diff -> Sigma(Sp1, y);             	
                        
				// St = St-1 + mu*tau + sigma * sqrt(tau) * (dW==Z)
				double Z = N01(u);
				double Sn0 = 0., Sn1 = 0.;
				
				if (l == L - 1)
				{
					Sn0 = Sp0 + mu0 * tlast + sigma0 * Z * slast;
					Sn1 = Sp1 + mu0 * tlast - sigma1 * Z * slast;
					y += tau;
				}
				else
				{
					Sn0 = Sp0 + mu0 * tau + sigma0 * Z * stau;
					Sn1 = Sp1 + mu1 * tau - sigma1 * Z * stau;
				}

				path0 [l] = Sn0;
				path1 [l] = Sn1;
				Sp0 = Sn0;
				Sp1 = Sn1;
			}; // end of loop

			};
		}
};
