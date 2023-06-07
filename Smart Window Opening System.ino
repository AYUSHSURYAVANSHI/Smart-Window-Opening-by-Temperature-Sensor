#include <DHT.h>
#include <Servo.h>

#define DHTPIN   2
#define SERVOPIN1 5
#define SERVOPIN2 6

DHT dht(DHTPIN, DHT11);
Servo servo1;
Servo servo2;
uint32_t ms, msD;
float h = 0;
float t = 0;
float et = 0;

int angle;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  servo1.attach(SERVOPIN1);
  servo2.attach(SERVOPIN2);
}

void loop()
{
  ms = millis();
  if (ms - msD > 1000)
  {
    h = dht.readHumidity();
    t = dht.readTemperature();
    et = t - 0.4*(t - 10)*(1.0 - (h/100));

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Теmperature: ");
    Serial.print(t);
    Serial.print(" *C\t");
    Serial.print("Effective temperature: ");
    Serial.print(et);
    Serial.println(" *C");

    msD = ms;
  }

  if (isnan(h) || isnan(t))
  {
    Serial.println("Reading error");
    return;
  }

  if (et < 26)
  {
    servo1.write(95);
    delay(300);
    servo2.write(120);

  }
  if (et >= 26 && et <= 28)
  {
    servo2.write(70);
    delay(100);

    servo1.write(80);

    
  }
  if (et > 28)
  {
    servo1.write(0);
    delay(200);

    servo2.write(118);

 
  }
}