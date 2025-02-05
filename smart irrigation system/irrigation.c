#include <ESP8266WiFi.h> 
#include <ThingSpeak.h>
const char *ssid = "Mythili";
const char *password = "mythili1208";
unsigned long channelID = 2735583;
const char *writeAPIKey = "4LKHTG4ME96F2644"; 
const int motorPin = D1;
const int moistureThreshold = 70; 
void setup() 
{
	Serial.begin(115200);
    Serial.print("Connecting to WiFi");
	WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
        Serial.print(".");
		} 
		Serial.println("Connected to Wi-Fi!");
		ThingSpeak.begin(client); 
		pinMode(motorPin, OUTPUT); 
		digitalWrite(motorPin, LOW);
}
void loop() 
{
int moistureValue = analogRead(A0);
Serial.print("Soil Moisture Sensor Value: ");
 Serial.println(moistureValue);
int moisturePercent = map(moistureValue, 0, 1023, 0, 100); 
Serial.print("Soil Moisture (Percentage): "); 
Serial.println(moisturePercent);
if (moisturePercent < moistureThreshold) 
{
	Serial.println("Soil is WET! Turning motor OFF."); 
	digitalWrite(motorPin, HIGH);
}
 
else {
 Serial.println("Soil is DRY! Turning motor ON.");
 digitalWrite(motorPin, LOW);
}
int httpCode = ThingSpeak.writeField(channelID, 1, moisturePercent, writeAPIKey); 
field1 int motorStatus = (digitalRead(motorPin) == HIGH) ? 1 : 0;
ThingSpeak.writeField(channelID, 2, motorStatus, writeAPIKey);
if (httpCode == 200) { Serial.println("Channel update successful.");
} 
else {
	
Serial.print("Error updating channel. HTTP error code: "); Serial.println(httpCode);
}
delay(2000);
}

