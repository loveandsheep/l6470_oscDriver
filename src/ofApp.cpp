#include "ofApp.h"

void ofApp::setup()
{
	receiver.setup(12400);
	driver.setup(true, 1);
	
	setting_accel = 0x30;
	setting_decel = 0x30;
	setting_speed_max = 0x20;
	setting_speed_min = 0x00;
	setting_voltage = 0x1F;
}

void ofApp::update()
{
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if (m.getAddress() == "/motor/setting/reset")
		{
			driver.resetDevice();
		}
		
		if (m.getAddress() == "/motor/setting/accel")
		{
			setting_accel = m.getArgAsInt32(0);
			driver.sendSignal(RPI_L6470_SIG_ACCEL, setting_accel);
		}
		
		if (m.getAddress() == "/motor/setting/decel")
		{
			setting_decel = m.getArgAsInt32(0);
			driver.sendSignal(RPI_L6470_SIG_DECEL, setting_decel);
		}
		
		if (m.getAddress() == "/motor/setting/speedMax")
		{
			setting_speed_max = m.getArgAsInt32(0);
			driver.sendSignal(RPI_L6470_SIG_MAXSPEED, setting_speed_max);
		}
	
		if (m.getAddress() == "/motor/setting/speedMin")
		{
			setting_speed_min = m.getArgAsInt32(0);
			driver.sendSignal(RPI_L6470_SIG_MINSPEED, setting_speed_min);
		}
		
		if (m.getAddress() == "/motor/setting/voltage")
		{
			setting_voltage = m.getArgAsInt32(0);
			driver.sendSignal(RPI_L6470_SIG_VOLT_ACC, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_DEC, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_RUN, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_HOLD, setting_voltage);
		}
		
		if (m.getAddress() == "/motor/setting/init")
		{
			driver.resetDevice();
			driver.enableAllMotor();
			driver.sendSignal(RPI_L6470_SIG_ACCEL	, setting_accel);
			driver.sendSignal(RPI_L6470_SIG_DECEL	, setting_decel);
			driver.sendSignal(RPI_L6470_SIG_MAXSPEED, setting_speed_max);
			driver.sendSignal(RPI_L6470_SIG_MINSPEED, setting_speed_min);
			driver.sendSignal(RPI_L6470_SIG_VOLT_RUN, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_ACC, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_DEC, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_VOLT_HOLD, setting_voltage);
			driver.sendSignal(RPI_L6470_SIG_ABSPOS, 0);
			driver.sendSignal(RPI_L6470_SIG_GOTO, 0);
			driver.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
			driver.sendSignal(RPI_L6470_SIG_STEPMODE, 0);
			driver.disableAllMotor();
		}
		
		driver.enableAllMotor();

		if (m.getAddress() == "/motor/drive/goto")
		{
			driver.sendSignal(RPI_L6470_SIG_GOTO,
							  m.getArgAsInt32(0));
			
		}
		
		if (m.getAddress() == "/motor/drive/run")
		{
			driver.sendSignal(RPI_L6470_SIG_RUN,
							  m.getArgAsInt32(0));
		}
		
		if (m.getAddress() == "/motor/drive/stopHard")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
		}
		
		if (m.getAddress() == "/motor/drive/stopSoft")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_SOFT, 0);
		}
		
		if (m.getAddress() == "/motor/rawSignal")
		{
			driver.sendSignal(m.getArgAsInt32(0),
							  m.getArgAsInt32(1));
		}
		
		driver.disableAllMotor();
	}
}

void ofApp::draw()
{

}