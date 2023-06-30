

///////////////////////////////////////////////////////////////////////////////
// store encoder pulsePerRev needed by encoder
int encA_ppr = 0;
int encB_ppr = 0;

// motorA pid control global params needed by pid
float kpA = 0, kiA = 0, kdA = 0;
float outMinA = -255.0, outMaxA = 255.0;
float targetA = 0.00;
float outputA;

// motorB pid control global params needed by pid
float kpB = 0, kiB = 0, kdB = 0;
float outMinB = -255.0, outMaxB = 255.0;
float targetB = 0.00;
float outputB;

// check if in PID or PWM mode
bool pidMode = true; // true-PID MODE, false-SETUP MODE

// initial i2cAddress
int i2cAddress = 0;
