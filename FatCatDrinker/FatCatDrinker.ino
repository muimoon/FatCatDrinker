
int cat_check = 2;

int valve = 1; // water valve output

void setup()
{
	pinMode(valve, OUTPUT);

	digitalWrite(valve, LOW);

	pinMode(cat_check, INPUT);

}

void loop()
{
	if (stop_flag == false)
	{
		if (digitalRead(cat_check) == HIGH)
		{
			digitalWrite(valve, HIGH);
			delay(20000); // working delay
		}
		else
		{
			digitalWrite(valve, LOW);
		}
	}
}