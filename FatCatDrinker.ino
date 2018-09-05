int SR04_inputPin = 4; //echo
int SR04_outputPin = 3; //trig
int SR04_VCC = 2;
int SR04_GND = 5;

int ledpin = 10;
//int sensitive_output = 8;
int sensitive_input = A0;
int sensitive;
int button = A1;
int valve = A2;    // water valve output

int stop_but = A3;
boolean stop_flag = false;
boolean flag = false;
void setup()
{ //初始化串口及引脚的输入、输出模式
  //Serial.begin(9600);
  pinMode(valve, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(SR04_inputPin, INPUT);
  pinMode(SR04_outputPin, OUTPUT);

  pinMode(SR04_VCC, OUTPUT);
  digitalWrite(SR04_VCC, HIGH);

  pinMode(SR04_GND, OUTPUT);
  digitalWrite(SR04_GND, LOW);

  pinMode(sensitive_input, INPUT);
  //pinMode(sensitive_output, OUTPUT);
  //digitalWrite(sensitive_output, HIGH);
  pinMode( LED_BUILTIN_TX, INPUT);
  pinMode( LED_BUILTIN_RX, INPUT);
}
void loop()
{
  // Serial.print("STOP_but=");
  // Serial.println(analogRead(stop_but));
  if (analogRead(stop_but) < 100)
  {
    stop_flag = !stop_flag;
    delay(200);
  }

  while (stop_flag == false) {
    if (analogRead(stop_but) < 100)
    {
      digitalWrite(valve, LOW);
      digitalWrite(ledpin, LOW);
      digitalWrite(9, HIGH);
      break;
    }
    digitalWrite(9, LOW);
    unsigned int x1, x2;
    digitalWrite(SR04_outputPin, LOW); //使发出发出超声波信号接口低电平2 μs
    delayMicroseconds(2);
    digitalWrite(SR04_outputPin, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs
    delayMicroseconds(10);
    digitalWrite(SR04_outputPin, LOW);  // 保持发出超声波信号接口低电平
    float distance1 = pulseIn(SR04_inputPin, HIGH);  //  读出接收脉冲的时间
    distance1 = distance1 / 58;     // 将脉冲时间转化为距离（单位：厘米）
    //Serial.print("distance1 = ");
    //Serial.println(distance1);
    x1 = distance1 * 100.0;
    distance1 = x1 / 100.0; //保留两位小数
    //   Serial.print("x1 = ");
    //  Serial.println(distance1);   // 输出距离值
    delay(150);
    float temp1 = analogRead(sensitive_input) / 4;
    sensitive = temp1 ;
    //   Serial.print("sensitive= ");
    //  Serial.println(sensitive);
    //   Serial.println(analogRead(button));
    if (analogRead(button) < 10)
    {
      digitalWrite(valve, HIGH);
      digitalWrite(ledpin, HIGH);
      flag = !flag;
      delay(100);
    }

    if (distance1 >= sensitive)
    {
      if (flag == false) {
        digitalWrite(valve, LOW);
        digitalWrite(ledpin, LOW);
      }
    }
    else
    {
      digitalWrite(valve, HIGH);
      digitalWrite(ledpin, HIGH);
    }
    //   delay(1000);
  }
}
