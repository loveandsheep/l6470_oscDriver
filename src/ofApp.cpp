#include "ofApp.h"

void ofApp::setup()
{
	receiver.setup(12400);
	
	driver.setup(true, 1);
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
		
		if (m.getAddress() == "/motor/setting/init")
		{
			driver.enableAllMotor();
			driver.sendSignal(RPI_L6470_SIG_ACCEL	, 0x30);
			driver.sendSignal(RPI_L6470_SIG_DECEL	, 0x30);
			driver.sendSignal(RPI_L6470_SIG_MAXSPEED, 0x20);
			driver.sendSignal(RPI_L6470_SIG_MINSPEED, 0x0);
			driver.sendSignal(RPI_L6470_SIG_VOLT_RUN, 0x5F);
			driver.sendSignal(RPI_L6470_SIG_VOLT_ACC, 0x5F);
			driver.sendSignal(RPI_L6470_SIG_VOLT_DEC, 0x5F);
			driver.sendSignal(RPI_L6470_SIG_VOLT_HOLD, 0x5F);
			driver.sendSignal(RPI_L6470_SIG_ABSPOS, 0);
			driver.sendSignal(RPI_L6470_SIG_GOTO, 0);
			driver.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
			driver.sendSignal(RPI_L6470_SIG_STEPMODE, 0);
			driver.disableAllMotor();
			
			cout << "initialize" << endl;
		}
		
		driver.enableAllMotor();

		if (m.getAddress() == "/motor/drive/goto")
		{
			driver.sendSignal(RPI_L6470_SIG_GOTO,
							  m.getArgAsInt32(0));
			
			cout << "goto " << m.getArgAsInt32(0) << endl;
		}
		
		if (m.getAddress() == "/motor/drive/run")
		{
			driver.sendSignal(RPI_L6470_SIG_RUN,
							  m.getArgAsInt32(0));

			cout << "move " << m.getArgAsInt32(0) << endl;
		}
		
		if (m.getAddress() == "/motor/drive/stopHard")
		{
			driver.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
		}
		
		if (m.getAddress() == "/motor/drive/sropSoft")
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