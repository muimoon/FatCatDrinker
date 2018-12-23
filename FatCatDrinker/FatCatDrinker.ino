/*One stop_button control value stop,
and at the same time Ledpin blink
Used Pin No.
3,4:SR04;
A0:Potentiometer;
A2:control valve;
*/
int SR04_inputPin = 4; // echo
int SR04_outputPin = 3; // trig
// 
int ledpin = 10; // working status Shown LED
// 
int sensitive_input = A0; // Potentiometer input to control testing distance
int sensitive = 15;
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
	digitalWrite(valve, LOW);
	pinMode(ledpin, OUTPUT);
	digitalWrite(ledpin, LOW);
	// 
	pinMode(stop_but, INPUT_PULLUP);
	// 
	pinMode(SR04_inputPin, INPUT);
	pinMode(SR04_outputPin, OUTPUT);
	// 
	// 
	pinMode(sensitive_input, INPUT);

	sensitive = map(analogRead(sensitive_input),1,1023,5,25);//added for last setting record
}

void loop()

{
	if (digitalRead(stop_but) == LOW) 
	{
		blink();
		delay(200);
	}
	if (stop_flag == true)
	{
		digitalWrite(valve, LOW);
		digitalWrite(ledpin, HIGH);
		delay(100);
		digitalWrite(ledpin, LOW);
		delay(100);
		float temp1 = analogRead(sensitive_input);
		sensitive = map(temp1, 1, 1023, 5, 25);
	}
	unsigned int x1, x2;
	digitalWrite(SR04_outputPin, LOW); // 使发出发出超声波信号接口低电平2 μs
	delayMicroseconds(2);
	digitalWrite(SR04_outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs,这里是至少10μs
	delayMicroseconds(10);
	digitalWrite(SR04_outputPin, LOW); // 保持发出超声波信号接口低电平
	float distance1 = pulseIn(SR04_inputPin, HIGH); // 读出接收脉冲的时间
	distance1 = distance1 / 58; // 将脉冲时间转化为距离（单位：厘米）
	x1 = distance1 * 100.0;
	distance1 = x1 / 100.0; // 保留两位小数
	delay(150);
	// 
	if (distance1 <= sensitive)
	{
		digitalWrite(valve, HIGH);
		digitalWrite(ledpin, HIGH);
		delay(20000); // working delay
		digitalWrite(valve, LOW);
		digitalWrite(ledpin, LOW);
	}
}
