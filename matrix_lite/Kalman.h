#pragma once

#include"Matrix.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

class kalman : public matrix {

public:
	kalman();
	~kalman();
	void filter(
		double* data,
		const double& dx, const double& dy,
		const double& dvx, const double& dvy
	);
	void SetAllMatrix();
	void New_predict_state();
	void Predicted_Process_Covariance_matrix();
	void Calculate_Kalman_Gain();
	void New_Observation();
	void Calculate_Current_State();
	void Updating_Process_Covariance_Matrix_and_Data();
	void WriteToFile(double output_massive[100], const string& name_dot_type);
private:
	void countTime();
	size_t J = 0;
	double fx[100], fy[100], fvx[100], fvy[100], kg[100];
	const double _dPx=20, _dPy=20, _dPvx=5, _dPvy=5;
	double _ax=0, _ay=0, _dT=1 ,_dx,_dy,_dVx,_dVy;
	matrix _X_k0, _X_k1, _X_kp, _P_kp, _P_k0, _P_k1, _KG, _Obs,
		   A, B, C, H, U, I, R, Z, Y, Q;
	bool _first;

	clock_t interval;
};