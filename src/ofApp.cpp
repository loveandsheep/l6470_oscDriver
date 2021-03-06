#include "ofApp.h"

void ofApp::setup()
{
	receiver.setup(12400);
	driver.setup(true, 1);
	
	setting_accel = 0x80;
	setting_decel = 0x80;
	setting_speed_max = 0x20;
	setting_speed_min = 0x00;
	setting_voltage = 0x80;
	
	init_motor();
	
	step_int = 1;
}

void ofApp::update()
{
	if (ofGetFrameNum() % step_int == 0) driver.step(0);
	
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if (m.getAddress() == "/interval")
			step_int = MAX(1, m.getArgAsInt32(0));
		
		if (m.getAddress() == "/call")
		{
			cout << "response" << endl;
		}
		
		if (m.getAddress() == "/motor/step")
		{
			driver.step(m.getArgAsInt32(0));
		}
		
		if (m.getAddress() == "/motor/setting/reset")
		{
			driver.resetDevice();
		}
		
		if (m.getAddress() == "/motor/setting/accel")
		{
			setting_accel = m.getArgAsInt32(0);
			driver.enableAllMotor();
			driver.sendSignal(RPI_L6470_SIG_ACCEL, setting_accel);
			driver.disableAllMotor();
		}
		
		if (m.getAddress() == "/motor/setting/decel")
		{
			setting_decel = m.getArgAsInt32(0);
			driver.enableAllMotor();
			driver.sendSignal(RPI_L6470_SIG_DECEL, setting_decel);
			driver.disableAllMotor();
		}
		
		if (m.getAddress() == "/motor/stepmode")
		{
			driver.sendSignal(RPI_L6470_SIG_STEPMODE, m.getArgAsInt32(0));
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
			init_motor();
		}
		
		driver.enableAllMotor();

		if (m.getAddress() == "/motor/drive/goto")
		{
			driver.sendSignal(RPI_L6470_SIG_GOTO,
							  m.getArgAsInt32(0));
			
		}
		
		if (m.getAddress() == "/motor/drive/run")
		{
			if (m.getArgAsInt32(0) < 0)
			{
				driver.sendSignal(RPI_L6470_SIG_RUN_INV,
								  m.getArgAsInt32(0) * -1);
			}else{
				driver.sendSignal(RPI_L6470_SIG_RUN,
								  m.getArgAsInt32(0));
			}
			
		}
		
		if (m.getAddress() == "/motor/drive/softHiz")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_SOFTHIZ, 0);
		}
		
		if (m.getAddress() == "/motor/drive/hardHiz")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_HARDHIZ, 0);
		}
		
		if (m.getAddress() == "/motor/setting/stepmode")
		{
			driver.sendSignal(RPI_L6470_SIG_STEPMODE, m.getArgAsInt32(0));
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
		
		if (m.getAddress() == "/system/shutdown")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_SOFT, 0);
			system("sudo shutdown -h now");
		}
		
		if (m.getAddress() == "/motor/raw")
		{
			int val = (m.getNumArgs() > 1 ? m.getArgAsInt32(1) : 0);
			driver.sendSignal(m.getArgAsInt32(0) & 0xFF, val);
		}
		
		if (m.getAddress() == "/test/step128")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_HARDHIZ, 0);
			driver.sendSignal(RPI_L6470_SIG_STEPMODE, m.getArgAsInt32(0));
			driver.sendSignal(RPI_L6470_SIG_STEP, 0);
			for (int i = 0;i < 128 * 200;i++) driver.step(0);
			driver.sendSignal(RPI_L6470_SIG_STEP_INV, 0);
			for (int i = 0;i < 128 * 200;i++) driver.step(0);
		}
		
		driver.disableAllMotor();
	}
}

void ofApp::draw()
{

}

void ofApp::init_motor()
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
