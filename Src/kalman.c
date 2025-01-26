
#include "kalman.h"
#include <math.h>
#include "globalval.h"



KalmanFilterSys_t	DryX, DryY, DryZ;



void DryXKalParaInit(void)
{
	DryX.Kalman.q_angle = Q_angle;
	DryX.Kalman.q_bias = Q_bias;
	DryX.Kalman.r_measure = R_measure;

	DryX.Kalman.angle = 0;
	DryX.Kalman.bias = 0;

	DryX.Kalman.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
	DryX.Kalman.P[0][1] = 0;
	DryX.Kalman.P[1][0] = 0;
	DryX.Kalman.P[1][1] = 0;

	XYZGyRaw.accxangle = 0;
	XYZGyRaw.xangle = 0;
}



void DryYKalParaInit(void)
{
	DryY.Kalman.q_angle = Q_angle;
	DryY.Kalman.q_bias = Q_bias;
	DryY.Kalman.r_measure = R_measure;

	DryY.Kalman.angle = 0;
	DryY.Kalman.bias = 0;

	DryY.Kalman.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
	DryY.Kalman.P[0][1] = 0;
	DryY.Kalman.P[1][0] = 0;
	DryY.Kalman.P[1][1] = 0;

	XYZGyRaw.accyangle = 0;
	XYZGyRaw.yangle = 0;
}



void DryZKalParaInit(void)
{
	DryZ.Kalman.q_angle = Q_angle;
	DryZ.Kalman.q_bias = Q_bias;
	DryZ.Kalman.r_measure = R_measure;

	DryZ.Kalman.angle = 0;
	DryZ.Kalman.bias = 0;

	DryZ.Kalman.P[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
	DryZ.Kalman.P[0][1] = 0;
	DryZ.Kalman.P[1][0] = 0;
	DryZ.Kalman.P[1][1] = 0;

	XYZGyRaw.acczangle = 0;
	XYZGyRaw.zangle = 0;
}



void KalmanInit(void)
{
	DryXKalParaInit();
	DryYKalParaInit();
	DryZKalParaInit();
}



float getAngle(KalmanFilterSys_t *drydeta, float newAngle, float newRate, float dt) 
{
	// KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
	// Modified by Kristian Lauszus
	// See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it

	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	/* Step 1 */
	drydeta->Kalman.rate = newRate - drydeta->Kalman.bias;
	drydeta->Kalman.angle += dt * drydeta->Kalman.rate;

	// Update estimation error covariance - Project the error covariance ahead
	/* Step 2 */
	drydeta->Kalman.P[0][0] += dt * (dt*drydeta->Kalman.P[1][1] - drydeta->Kalman.P[0][1] - drydeta->Kalman.P[1][0] + drydeta->Kalman.q_angle);
	drydeta->Kalman.P[0][1] -= dt * drydeta->Kalman.P[1][1];
	drydeta->Kalman.P[1][0] -= dt * drydeta->Kalman.P[1][1];
	drydeta->Kalman.P[1][1] += drydeta->Kalman.q_bias * dt;

	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	/* Step 4 */
	drydeta->Kalman.S = drydeta->Kalman.P[0][0] + drydeta->Kalman.r_measure;
	/* Step 5 */
	drydeta->Kalman.K[0] = drydeta->Kalman.P[0][0] / drydeta->Kalman.S;
	drydeta->Kalman.K[1] = drydeta->Kalman.P[1][0] / drydeta->Kalman.S;

	// Calculate angle and bias - Update estimate with measurement zk (newAngle)
	/* Step 3 */
	drydeta->Kalman.y = newAngle - drydeta->Kalman.angle;
	/* Step 6 */
	drydeta->Kalman.angle += drydeta->Kalman.K[0] * drydeta->Kalman.y;
	drydeta->Kalman.bias += drydeta->Kalman.K[1] * drydeta->Kalman.y;

	// Calculate estimation error covariance - Update the error covariance
	/* Step 7 */
	drydeta->Kalman.P[0][0] -= drydeta->Kalman.K[0] * drydeta->Kalman.P[0][0];
	drydeta->Kalman.P[0][1] -= drydeta->Kalman.K[0] * drydeta->Kalman.P[0][1];
	drydeta->Kalman.P[1][0] -= drydeta->Kalman.K[1] * drydeta->Kalman.P[0][0];
	drydeta->Kalman.P[1][1] -= drydeta->Kalman.K[1] * drydeta->Kalman.P[0][1];

	return drydeta->Kalman.angle;
};



void setAngle(KalmanFilterSys_t *drydeta, float newAngle) 
{ 
	drydeta->Kalman.angle = newAngle; 
} // Used to set angle, this should be set as the starting angle



float getRate(KalmanFilterSys_t *drydeta) 
{ 
	return drydeta->Kalman.rate; 
} // Return the unbiased rate


void setQangle(KalmanFilterSys_t *drydeta, float newQ_angle) 
{ 
	drydeta->Kalman.q_angle = newQ_angle; 
}


void setQbias(KalmanFilterSys_t *drydeta, float newQ_bias) 
{ 
	drydeta->Kalman.q_bias = newQ_bias;
}


void setRmeasure(KalmanFilterSys_t *drydeta, float newR_measure) 
{ 
	drydeta->Kalman.r_measure = newR_measure; 
}


float getQangle(KalmanFilterSys_t *drydeta) 
{ 
	return drydeta->Kalman.q_angle; 
}

float getQbias(KalmanFilterSys_t *drydeta) 
{ 
	return drydeta->Kalman.q_bias;
}


float getRmeasure(KalmanFilterSys_t *drydeta) 
{
	return drydeta->Kalman.r_measure; 
}





