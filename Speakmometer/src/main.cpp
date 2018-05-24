#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SD_ChipSelectPin 10

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer;

TMRpcm tmrpcm;

int t;
String lang;
String m_str;


void setup()
{
    Serial.begin(57600);

    if (!SD.begin(SD_ChipSelectPin))
    {
        Serial.println("SD fail");
        return;
    }

    sensors.begin();
    sensors.isParasitePowerMode();
    sensors.getAddress(Thermometer, 0);
    sensors.setResolution(Thermometer, 9);

    tmrpcm.speakerPin = 9;
    tmrpcm.setVolume(6);
    tmrpcm.play("temp.wav");
    delay(5000);
    tmrpcm.play("tellTemp1.mp3");
    delay(1000);
}

void loop()
{
    sensors.requestTemperatures();
    t = sensors.getTempCByIndex(0);
    Serial.print("Temp = ");
    Serial.println(t);

    tmrpcm.quality(1);
    m_str = "" + String(t) + ".wav";
    char *m_play = &m_str[0u];
    tmrpcm.play(m_play);

    Serial.print("m_play = ");
    Serial.println(m_play);
    delay(5000);
}