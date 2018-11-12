/*One stop_button control value stop,
and at the same time Ledpin blink
Used Pin No.
2: interrupt;
3,4:SR04;
10: LED;
A0:Potentiometer;
A2:control valve;
*/
int SR04_inputPin = 4; // echo
int SR04_outputPin = 3; // trig
// 
int ledpin = 10; // working status Shown LED
// 
int sensitive_input = A0; // Potentiometer input to control testing distance
int sensitive;
// 
int valve = A2; // water valve output
int stop_but = 2; // valve stop working
// 
boolean stop_flag = false;
// 
void blink() // interrupt
{
	stop_flag = !stop_flag;
}

void setup()
{
	pinMode(valve, OUTPUT);
	pinMode(ledpin, OUTPUT);
	// 
	pinMode(stop_but, INPUT_PULLUP);
	//
	pinMode(SR04_inputPin, INPUT);
	pinMode(SR04_outputPin, OUTPUT);
	// 
	attachInterrupt(0, blink, CHANGE);
	// 
	pinMode(sensitive_input, INPUT);
}

void loop()
{
	if (stop_flag == true)
	{
		digitalWrite(valve, LOW);
		digitalWrite(ledpin, HIGH);
		delay(200);
		digitalWrite(ledpin, LOW);
		delay(200);
	}
	while (stop_flag == false)
	{
		unsigned int x1, x2;
		digitalWrite(SR04_outputPin, LOW); //使发出发出超声波信号接口低电平2 μs
		delayMicroseconds(2);
		digitalWrite(SR04_outputPin, HIGH); //使发出发出超声波信号接口高电平10μs,这里是至少10μs
		delayMicroseconds(10);
		digitalWrite(SR04_outputPin, LOW); //保持发出超声波信号接口低电平
		float distance1 = pulseIn(SR04_inputPin, HIGH); //读出接收脉冲的时间
		distance1 = distance1 / 58; //将脉冲时间转化为距离（单位：厘米）
		x1 = distance1 * 100.0;
		distance1 = x1 / 100.0; //保留两位小数
		delay(150);
		//
		float temp1 = analogRead(sensitive_input) / 4;
		sensitive = temp1;
		if (distance1 <= sensitive)
		{
			digitalWrite(valve, HIGH);
			digitalWrite(ledpin, HIGH);
			delay(60000); // working delay
		}
	}
}
