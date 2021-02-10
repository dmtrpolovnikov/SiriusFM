#include "DiffusionGBM.h"
#include "IRProviderConst.h"
#include "MCEngine1D.hpp"
using namespace SiriusFM;
using namespace std;

int main (int argc, char* argv[]) 
{
	//gbm parameters, number and length of paths, tau: mu, sigma, S0, Tdays, tau_min, P 
	
	if (argc != 7)
	{
		cout << "Parameters: mu, sigma, S0, T(days), tau(min), Paths" << endl;
		return 1;
	};
	
	double mu = atof(argv[1]);
	double sigma = atof(argv[2]);
	double S0 = atof(argv[3]);
	long T_days = atof(argv[4]);
	int tau_min = atof(argv[5]);
	long P = atof(argv[6]);  // Check mu > 0, sigma > 0, Tdays > 0, taumin > 0, P > 0
	
	CcyE ccyA = CcyE:: USD;
	IRProvider<IRModeE::Const> IRProvider(nullptr);
	DiffusionGBM diff(mu, sigma);
	MCEngine1D<decltype(diff), decltype(IRProvider), decltype(IRProvider),
		decltype(ccyA), decltype(ccyA)> mce(20000, 20000);
	
	time_t t0 = time(nullptr);
	time_t T = t0 + T_days * 86400;
	time_t Ty = double(T_days/365.25);
	mce.Simulate<false> (t0, T, tau_min, S0, P, &diff, &IRProvider, &IRProvider, ccyA, ccyA);
	
	//Analyze the results
	tuple res = mce.GetPaths();
	long L1 = get<0>(res);
	long P1 = get<1>(res);
	double const* paths = get<2>(res);
	double NVP = 0.0; // valid path
	cout << "L1 = " << L1 << " P1 = " << P1 << " Paths = " << paths << endl;
	
	//Compute E and LogSt
	double EST = 0.0;
	double EST2 = 0.0;
	cout << "EST = " << EST << " EST2 = " << EST2 << endl;
	
	for (int p = 0; p < P1; p++)
	{
		double const* path = paths + p * L1;
		double ST = path[L1 - 1];
		// In practise may get ST<0
		if (ST <= 0.0)
			continue;
		++NVP;
		
		double RT = log(ST / S0);
		EST += RT;
		EST2 += RT * RT;
	} // end of loop
	
	assert(NVP > 0);
	cout << "NVP = " << NVP << endl;
	EST /= double(NVP); // (mu - sigma^2/2)dt = 
	cout << "EST = " << EST << " EST2 = " << EST2 << endl;
	
	//Now find variance of ST
	double VarST = (EST2 - double(NVP) * EST * EST) / double(NVP-1); // sigma^2T
	cout << "EST = " << EST << " EST2 = " << EST2 << endl;
	double sigma2E = VarST / Ty;
	cout << "EST = " << EST << " EST2 = " << EST2 << endl;
	double muE = (EST + VarST / 2.0) / Ty;
	cout << "EST = " << EST << " EST2 = " << EST2 << endl;
	
	cout << "Mu = " << mu << ", muE" << muE << endl; 
	cout << "Sigma = " << sigma * sigma << ", sigma2E" << sigma2E << endl; 
	
	// mu 0.1 sigma 0.25 s0 100 tdays 90 5 min p10000
	
	return 0;
}
