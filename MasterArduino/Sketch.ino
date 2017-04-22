#include <SoftwareSerial.h>
SoftwareSerial SlaveArd(10, 11); //Rx Tx


		//Red1, Green1, Blue1, Red2, Green2, Blue2;
uint8_t Pins[] = {9,10,11,6,5,4,3};

uint8_t ColorData[12]; // Store Data from serial.
uint8_t SlaveFlag;
#define Send 0
#define Sent 1

void setup(){

	Serial.begin(115200); //Set Baudrate Hardware Serial!				
	SlaveArd.begin(115200); // Set Baudrate Software Serial!

}

void loop(){

  if (Serial.available()>=4) {
    if(Serial.read() == 0x4A){              //4A just a marker to ensure proper synchronization
      for(uint8_t i = 0; i < 12; i++){ 
	ColorData[i] = Serial.read();		  //followed by RGB bytes  
		}	
	}
  
	SlaveFlag = Send;
	for(uint8_t i = 0; i < 12; i++){	
		if(i < 6){
			analogWrite(Pins[i],ColorData[i]);
		}
		else {
			if (SlaveFlag == Send){
				SlaveArd.write(0x4B); //4B just marker for Slave Arduino
				SlaveFlag = Sent;
			}
			SlaveArd.write(ColorData[i]);
		}
	}
  }
}
