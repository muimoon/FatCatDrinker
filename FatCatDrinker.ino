int inputPin = 4;   //  接超声波的 output 引脚到数字D4脚
int outputPin = 5;  //  接超声波的 input 引脚到数字D5脚
int valve = 12;    // water valve output
int ledpin = 11;
int sensitive_output = 8;
int sensitive_input = 0;
int sensitive;
int button = 1;
boolean flag = false;
void setup()
{ //初始化串口及引脚的输入、输出模式
  Serial.begin(9600);
  pinMode(valve, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(sensitive_input, INPUT);
  pinMode(sensitive_output, OUTPUT);
  digitalWrite(sensitive_output, HIGH);

}
void loop()
{
  unsigned int x1, x2;
  digitalWrite(outputPin, LOW); //使发出发出超声波信号接口低电平2 μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);  // 保持发出超声波信号接口低电平
  float distance1 = pulseIn(inputPin, HIGH);  //  读出接收脉冲的时间
  distance1 = distance1 / 58;     // 将脉冲时间转化为距离（单位：厘米）
  Serial.print("distance1 = ");
  Serial.println(distance1);
  x1 = distance1 * 100.0;
  distance1 = x1 / 100.0; //保留两位小数
  Serial.print("x1 = ");
  Serial.println(distance1);   // 输出距离值
  delay(150);
  float temp1 = analogRead(sensitive_input) / 4;
  sensitive = temp1 ;
  Serial.println(sensitive);
  Serial.println(analogRead(button));
  if (analogRead(button) < 10)
  {
    digitalWrite(valve, HIGH);
    digitalWrite(ledpin, HIGH);
    flag = !flag;
    delay(100);
  }
  if (distance1 >= sensitive)
  {
    if (flag != true) {
      digitalWrite(valve, LOW);
      digitalWrite(ledpin, LOW); //如果距离大于50厘米小灯亮起
    }
  }
  else
  {
    digitalWrite(valve, HIGH); //如果距离小于50厘米小灯熄灭
    digitalWrite(ledpin, HIGH);
  }
}
