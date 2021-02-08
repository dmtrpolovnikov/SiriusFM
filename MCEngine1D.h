#pragma once
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

namespace SiriusFM 
{
	
	template <typename Diffusion1D, typename AProvider, typename BProvider, 
		 typename AssetClassA, typename AssetClassB>
	class MCEngine1D {
		private:
			long int m_MaxL; // path length
			long int m_MaxP; // max N paths
			double* m_Paths; // 
			long m_L; // m_l < Max_L
			long m_P; // m_P M max_P
			double m_tau; // TimeStep as YearFraction
			double m_tau0; // start point =2021
			double m_S0; // Start price point

			Diffusion1D const* m_;
			AProvider const* m_rateA;
			BProvider const* m_rateB;
			AssetClassA m_a; // Asset A
			AssetClassB m_b; // Asset B
			bool m_RN; // Risk-Neutral Trend
		public:
			MCEngine1D (long a_MaxL, long a_MaxP)
			: m_MaxL(a_MaxL), m_MaxP(a_MaxP), 
			m_Paths (new double [m_MaxL * m_MaxP])
			/*m_L (0), m_P (0), m_tau (nan),m_diff (nullptr), 
		        m_rateA (nullptr), m_rateB (nullptr),
			m_a (AssetClassA:: UNDEFINED), 
			m_b (AssetClassB:: INDEFINED)*/
			
			{
				if (m_MaxL <= 0 || m_MaxP <= 0) 
					throw invalid_argument ("Invalid values!");
			};
			
			void Simulate ( time_t a_t0, // Curr pricing Time
				time_t a_T, // Expiration Time
				int a_tau_min, // Step in minutes
				double a_S0, long a_P, // start point and paths
				Diffusion1D const* a_diff,
				AProvider const* a_rateA,
				BProvider const* a_rateB,
				AssetClassA a_A,
				AssetClassB a_B,
				bool a_isRN);
	};
}
			
