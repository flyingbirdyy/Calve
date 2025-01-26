#ifndef _KALMAN_H
#define	_KALMAN_H



 

#define	Dt															((float)1.0/208)
#define DpsLSB														0.035f
#define DryDatalebgth												1024


#define	Q_angle														0.001f
#define Q_bias														0.003f
#define R_measure													0.03f


#define	CpSysMain													0.9755f
#define	CpSysMin													0.0245f
#define	TpPara														0.003f


typedef struct
{
	float q_angle; // Process noise variance for the accelerometer
	float q_bias; // Process noise variance for the gyro bias
	float r_measure; // Measurement noise variance - this is actually the variance of the measurement noise
	
	float angle; // The angle calculated by the Kalman filter - part of the 2x1 state vector
	float bias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
	float rate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
	
	float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
	float K[2]; // Kalman gain - This is a 2x1 vector
	float y; // Angle difference
	float S; // Estimate error

} KalmanFilter_t;
 
typedef struct
{
	KalmanFilter_t Kalman;
	float gyroangle; // Angle calculate using the gyro only
	float compAngle; // Calculated angle using a complementary filter
	float kalAngle;  // Calculated angle using a Kalman filter
} KalmanFilterSys_t;

 






extern KalmanFilterSys_t	DryX, DryY, DryZ;
















void DryXKalParaInit(void);
void DryYKalParaInit(void);
void DryZKalParaInit(void);
float getAngle(KalmanFilterSys_t *drydeta, float newAngle, float newRate, float dt);
void setAngle(KalmanFilterSys_t *drydeta, float newAngle);
float getRate(KalmanFilterSys_t *drydeta);
void setQangle(KalmanFilterSys_t *drydeta, float newQ_angle);
void setQbias(KalmanFilterSys_t *drydeta, float newQ_bias);
void setRmeasure(KalmanFilterSys_t *drydeta, float newR_measure);
float getQangle(KalmanFilterSys_t *drydeta);
float getQbias(KalmanFilterSys_t *drydeta);
float getRmeasure(KalmanFilterSys_t *drydeta);
void KalmanInit(void);





#endif



