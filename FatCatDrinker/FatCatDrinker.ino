/*One stop_button control value stop,
and at the same time Ledpin blink
Used Pin No.
3,4:SR04;
A0:Potentiometer;
A2:control valve;
*/
// int SR04_inputPin = 4; // echo
// int SR04_outputPin = 3; // trig
int cat_check = 2;
// 
int ledpin = 3; // working status Shown LED
// 
// 
int valve = 1; // water valve output
int stop_but = 4; // valve stop working
// 
boolean stop_flag = false;
// 
int start_no = 1;
void blink() // interrupt
{
	stop_flag = !stop_flag;
}

void setup()
{
	pinMode(valve, OUTPUT);
	digitalWrite(valve, LOW);
	pinMode(ledpin, OUTPUT);
	digitalWrite(ledpin, LOW);
	// 
	pinMode(stop_but, INPUT_PULLUP);
	// pinMode(SR04_inputPin, INPUT);
	// pinMode(SR04_outputPin, OUTPUT);
	pinMode(cat_check, INPUT);
	// sensitive = map(analogRead(sensitive_input),1,1023,5,25);
}

void loop()
{
	if (digitalRead(stop_but) == LOW)
	{
		blink();
		delay(1000);
	}
	if (stop_flag == true)
	{
		digitalWrite(valve, LOW);
		digitalWrite(ledpin, HIGH);
		delay(100);
		digitalWrite(ledpin, LOW);
		delay(100);
		// float temp1 = analogRead(sensitive_input);
		// sensitive = map(temp1, 1, 1023, 5, 25);
	}
	// 
	if (stop_flag == false)
	{
		if (digitalRead(cat_check) == HIGH)
		{
			digitalWrite(valve, HIGH);
			digitalWrite(ledpin, HIGH);
			delay(20000); // working delay
		}
		else
		{
			digitalWrite(valve, LOW);
			digitalWrite(ledpin, LOW);
		}
	}
}