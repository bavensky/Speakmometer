/*


Download mp3 file form youtube --> https://ycapi.org/iframe/
Convert mp3 to wav --> https://audio.online-convert.com/convert-to-wav
    Resolution 8 bit
    sampling rate 16000 Hz (16 khz)
    audio channels mono

*/
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
    Serial.println("Serial done.");

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
    tmrpcm.quality(1);
    // tmrpcm.play("temp.wav", 2);
    // delay(5000);
    // tmrpcm.play("tell1.wav", 3);
    // delay(5000);
    // tmrpcm.play("tell2.wav", 3);
    // delay(5000);
    // tmrpcm.play("tell3.wav", 3);
    // delay(5000);
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

    tmrpcm.play("tell1.wav");
    delay(3000);
    tmrpcm.play(m_play);
    delay(2000);
    tmrpcm.play("celsius.wav");
    delay(3000);

    Serial.print("m_play = ");
    Serial.println(m_play);
    delay(5000);
}