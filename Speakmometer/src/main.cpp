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
#include <LiquidCrystal.h>

#define RS 8
#define EN 7
#define D4 A0
#define D5 A1
#define D6 A2
#define D7 A3

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#define SD_ChipSelectPin 10

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer;

TMRpcm tmrpcm;

int i_temp = 0;
float f_temp = 0.0;
float temp = 0.0;
float point = 0;

String lang;
String m_str1;
String m_str2;

void setup()
{
    Serial.begin(57600);
    Serial.println("Serial done.");

    lcd.begin(8, 2);
    lcd.setCursor(0, 0);
    lcd.print("Thermo  ");
    lcd.setCursor(0, 1);
    lcd.print("    Talk");
    delay(3000);

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
    tmrpcm.setVolume(5);

    lcd.clear();
}

void loop()
{
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);

    lcd.setCursor(0, 0);
    lcd.print("Temp : ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.print(temp);
    lcd.print("C  ");

    i_temp = temp;
    f_temp = temp - i_temp;
    f_temp = f_temp * 10;

    tmrpcm.quality(1);

    m_str1 = "" + String(i_temp) + ".wav";
    char *m_play1 = &m_str1[0u];
    tmrpcm.play(m_play1);
    delay(2000);

    int mmm = f_temp;
    if (mmm != 0)
    {
        tmrpcm.play("point.wav");
        delay(2000);

        m_str2 = "" + String(mmm) + ".wav";
        char *m_play2 = &m_str2[0u];
        tmrpcm.play(m_play2);
        delay(2000);
    }

    tmrpcm.play("celsius.wav");
    delay(3000);

    if (temp >= 30.0 && temp <= 35.5)
    {
        tmrpcm.play("case1.wav");
        delay(6000);
    }
    else if (temp >= 36.0 && temp <= 38.5)
    {
        tmrpcm.play("case2.wav");
        delay(7000);
    }
    else if (temp >= 38.6 && temp <= 39.5)
    {
        tmrpcm.play("case3.wav");
        delay(8000);
    }
    else if (temp >= 39.6 && temp <= 40.5)
    {
        tmrpcm.play("case4.wav");
        delay(10000);
    }
    else if (temp >= 40.6)
    {
        tmrpcm.play("case5.wav");
        delay(10000);
    }

    tmrpcm.disable();
    delay(5000);
}