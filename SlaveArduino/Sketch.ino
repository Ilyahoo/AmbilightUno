			
uint8_t RGBs[6];
				//Red1, Green1, Blue1, Red2, Green2, Blue2;
uint8_t Pins[] = {9,10,11,6,5,4,3};
	
void setup()
{
	Serial.begin(115200); //Set Baudrate Hardware Serial!				
	for (uint8_t i = 0; i < 6; i++){
		RGBs[i] = 0;
	}
}
void loop()
{
	
  if (Serial.available()>=1) {
    if(Serial.read() == 0x4B){    //4B just marker to ensure proper synchronization.
      for(uint8_t i = 0; i < 6; i++){ 
		    RGBs[i] = Serial.read();		//followed by RGB bytes  
		}	
	}
	  //finally control led brightness through PWM
	for(uint8_t i = 0; i < 6; i++){
  
			analogWrite(Pins[i],RGBs[i]);

	}
}
