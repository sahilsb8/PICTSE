const int PIEZO_PIN = A0; // Piezo output
int count = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // Read Piezo ADC value in, and convert it to a voltage
  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC / 1023.0 * 5.0;
  if(piezoV >= 5.0)
  {
    count++;
    delay(1000);
  }
  Serial.print(piezoV);
  Serial.print("  Steps: ");
  Serial.println(count);
}
