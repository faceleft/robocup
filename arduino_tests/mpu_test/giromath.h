double AcYsum = 0;
double AcXsum = 0;
double AcZsum = 0;
uint32_t dt;
uint32_t  t0;
uint32_t micros_;
 
//==================================
double GyroZ, GyroY, GyroX, Acsel;
float imu[3];
const int max_j=2;
float quat[4];
float e[3];
//==================================
double CompensatorZ=0, CompensatorX=0, CompensatorY=0;
