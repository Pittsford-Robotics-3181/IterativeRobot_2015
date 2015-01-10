#include "WPILib.h"
#include <Gyro.h>

class Robot: public IterativeRobot
{
	Compressor* c = new Compressor(1);
	Solenoid* sol = new Solenoid(1,0);
	RobotDrive robotDriveSystem;
	Accelerometer* acell = new BuiltInAccelerometer(Accelerometer::kRange_4G);
	Victor m_motor;
	Potentiometer* pot = new AnalogPotentiometer(2,360,0);
	Encoder* enc = new Encoder(1,2,false,Encoder::EncodingType::k4X);
	Joystick driveStick;
	DigitalInput* limitSwitch = new DigitalInput(0);
	DigitalOutput light;
	Gyro gyro;
	PWM pwm;
	float gyroAngle;
	double kUpdatePeriod = 0.005;

	double xVal = 0;
	double yVal = 0;
	double zVal = 0;


	//LiveWindow *lw;

public:
	Robot() :
		robotDriveSystem(0, 1),
		gyro(0),
		pwm(2),
		light(10),
		m_motor(0),
		driveStick(0)//,
		//lw(NULL)
	{
		robotDriveSystem.SetExpiration(0.01);
	}

private:

	void RobotInit()
	{
		enc->SetDistancePerPulse(5);
		SmartDashboard::init();
		gyro.Reset();
		enc->Reset();
		//lw = LiveWindow::GetInstance();
		robotDriveSystem.SetSafetyEnabled(false);

		c->SetClosedLoopControl(true);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		light.Set(1);
		//for(int i = 0; i < 65000; i++){
		pwm.SetRaw(1);
		//}

		xVal = acell->GetX();
		yVal = acell->GetY();
		zVal = acell->GetZ();

		//m_motor.Set(driveStick.GetY());
		robotDriveSystem.ArcadeDrive(driveStick);

		gyroAngle = gyro.GetAngle();

		int Count = enc->Get();
		double distance = enc->GetDistance();

		double potVal = pot->Get();

		sol->Set(driveStick.GetRawButton(1));

		SmartDashboard::PutBoolean("Limit Switch", limitSwitch->Get());
		SmartDashboard::PutNumber("Gyro Angle", gyroAngle);
		SmartDashboard::PutNumber("Acell X", xVal);
		SmartDashboard::PutNumber("Acell Y", yVal);
		SmartDashboard::PutNumber("Acell Z", zVal);
		SmartDashboard::PutNumber("Pot Val", potVal);
		SmartDashboard::PutNumber("Count Val", Count);
		SmartDashboard::PutNumber("Distance Val", distance);
		SmartDashboard::PutBoolean("Joy Button", driveStick.GetRawButton(1));


	}

	void TestPeriodic()
	{
		//lw->Run();
	}

//	void OperatorControl() {
//			while (IsOperatorControl() && IsEnabled()) {
//				// Set the motor controller's output.
//				// This takes a number from -1 (100% speed in reverse) to +1 (100% speed forwards).
//				m_motor.Set(driveStick.GetY());
//
//				Wait(kUpdatePeriod); // Wait 5ms for the next update.
//			}
//		}
};

START_ROBOT_CLASS(Robot);
