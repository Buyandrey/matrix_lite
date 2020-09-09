#include "Kalman.h"

kalman :: kalman() {
	_first = true;
}
kalman :: ~kalman() {
	WriteToFile(fx, "fx.txt");
	WriteToFile(fy, "fy.txt");
	WriteToFile(fvx, "fvx.txt");
	WriteToFile(fvy, "fvy.txt");
	WriteToFile(kg, "kg.txt");
	//cout << "_____";
}

void kalman :: SetAllMatrix() {
	_X_k0.SetMatr({ { 0 },{ 0 },{ 0 },{ 0 } });
	_X_k1.SetMatr({
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 }
		});
	_P_kp.SetMatr({
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
		});
	_P_k0.SetMatr({
		{ pow(_dPx, 2), 0, 0, 0 },
		{ 0, pow(_dPy, 2), 0, 0 },
		{ 0, 0, pow(_dPvx, 2), 0 },
		{ 0, 0, 0, pow(_dPvy, 2) }
	});
	A.SetMatr({
		{ 1, 0, _dT, 0 },
		{ 0, 1, 0, _dT },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	});
	B.SetMatr({
		{ 0.5 * pow(_dT,2), 0 },
		{ 0, 0.5 * pow(_dT,2) },
		{ _dT, 0 },
		{ 0, _dT }
	});
	//U.SetMatr({
	//	{ _ax },
	//	{ _ay }
	//	});
	I.SetMatr({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
		});
	H.SetMatr({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
		});
	Y.SetMatr({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
		});
	C.SetMatr({
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
		});
	Z.SetMatr({
		{ 0 },
		{ 0 },
		{ 0 },
		{ 0 }
		});
	R.SetMatr({/*ошибка gps*/
		{ pow(_dx / 3,2), 0, 0, 0 },
		{ 0, pow(_dy / 3,2), 0, 0 },
		{ 0, 0, pow(_dVx / 3,2), 0 },
		{ 0, 0, 0, pow(_dVy / 3,2) }
		});
	Q.SetMatr({
			{ _dx +  _dVx, 0, 0, 0 },
			{ 0, _dy + _dVy , 0, 0 },
			{ 0, 0, _dVx , 0 },
			{ 0, 0, 0, _dVy }
	});
	/*
		Q.SetMatr({
			{ _dx + 3 * _dVx, 0, 0, 0 },
			{ 0, _dy + 3 * _dVy , 0, 0 },
			{ 0, 0, 3 * _dVx , 0 },
			{ 0, 0, 0, 3 * _dVy }
	});
	*/
}
void kalman::New_predict_state() {
	//Xkp=A*Xk0 + B*Uk+Wk(=0)
	U.SetMatr({
		{ _ax },
		{ _ay }
	});
	_X_kp = A * _X_k0 + B * U /* +0 */;
}
void kalman::Predicted_Process_Covariance_matrix() {
	_P_kp = A * _P_k0 * Transponierte(A)+Q;
}
void kalman::Calculate_Kalman_Gain() {
	
	R.SetMatr({/*ошибка gps*/
		{ pow(_dx/3,2), 0, 0, 0 },
		{ 0, pow(_dy / 3,2), 0, 0 },
		{ 0, 0, pow(_dVx / 3,2), 0 },
		{ 0, 0, 0, pow(_dVy / 3,2) }
	});
	_KG =
		(_P_kp*Transponierte(H))
		/ 
		(H* _P_kp*Transponierte(H) + R);
}
void kalman::New_Observation() {
	Y = (C * _Obs) + Z;
}
void kalman::Calculate_Current_State() {
	_X_k1 = _X_kp + _KG * (Y - H * _X_kp);
}
void kalman::Updating_Process_Covariance_Matrix_and_Data() {
	_P_k1 = (I-(_KG*H))*_P_kp;
	_P_k0 = _P_k1;
	_X_k0 = _X_k1;
}
void kalman ::WriteToFile(double output_massive[100], const string& name_dot_type) {
	const string path = name_dot_type;
	ofstream rx(path);
	for (size_t i = 0; i < 100; i++)
		rx << output_massive[i] << endl;
}
void kalman :: filter(
	double* data,
	const double& dx, const double& dy,
	const double& dVx, const double& dVy
) {
	if (_first || _dx!=dx || _dy != dy || _dVx != dVx || _dVy != dVy) {
		//cout << endl<< _first <<' '<< _dx <<" != "<< dx << _dy << " != " << dy << _dVx << " != " << dVx << _dVy << " != " << dVy <<endl;
		
		_dx = dx;
		_dy = dy;
		_dVx = dVx;
		_dVy = dVy;
		_Obs.SetMatr({
			{data[0]},
			{data[1]},
			{data[2]},
			{data[3]}
			});
		
		SetAllMatrix();
		_X_k0 = _Obs;

		New_predict_state();
		Predicted_Process_Covariance_matrix();
		Calculate_Kalman_Gain();
		New_Observation();
		Calculate_Current_State();
		//Updating_Process_Covariance_Matrix_and_Data();

		
		_X_k1 = _Obs;

		data[0] = _X_k1.getElement(0, 0);
		data[1] = _X_k1.getElement(1, 0);
		data[2] = _X_k1.getElement(2, 0);
		data[3] = _X_k1.getElement(3, 0);

		_first = false;
		interval = clock();
	}
	else {
		//countTime();

		_dx = dx;
		_dy = dy;
		_dVx = dVx;
		_dVy = dVy;
		_Obs.SetMatr({
			{data[0]},
			{data[1]},
			{data[2]},
			{data[3]}
			});

		_ax = ( _Obs.getElement(2, 0)- _X_k1.getElement(2, 0)) / _dT;
		_ay = ( _Obs.getElement(3, 0)- _X_k1.getElement(3, 0)) / _dT;
		New_predict_state();
		Predicted_Process_Covariance_matrix();
		Calculate_Kalman_Gain();
		New_Observation();
		Calculate_Current_State();
		Updating_Process_Covariance_Matrix_and_Data();

		data[0] = _X_k1.getElement(0, 0);
		data[1] = _X_k1.getElement(1, 0);
		data[2] = _X_k1.getElement(2, 0);
		data[3] = _X_k1.getElement(3, 0);
	}
	fx[J] = data[0];
	fy[J] = data[1];
	fvx[J] = data[2];
	fvy[J] = data[3];
	kg[J] = _KG.getElement(0,0);
	J++;
}
void kalman::countTime() {
	if (_first) {
		interval = clock()-interval;
	}
	else {
		interval = (clock() - interval);
		_dT = interval * (1.0 / CLOCKS_PER_SEC);
		//cout << endl << _dT << endl;
		interval = clock();
	}
}