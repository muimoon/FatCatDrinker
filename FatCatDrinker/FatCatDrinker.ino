int cat_check = 2;
int valve = 0; // water valve output
void setup()
{
	pinMode(valve, OUTPUT);
	digitalWrite(valve, HIGH);
	pinMode(cat_check, INPUT);
}

void loop()
{
	if (digitalRead(cat_check) == HIGH)
	{
		digitalWrite(valve, LOW);
		delay(60000); // working delay
	}
	else
	{
		digitalWrite(valve, HIGH);
	}
}
