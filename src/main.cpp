#include <Arduino.h>

#include "thermistor.h"
#include "virtualTimer.h"

VirtualTimerGroup timer_group;

const uint8_t kNumThermistors{8};

std::array<NXFT15XH103FA2B050ADCThermistor*, kNumThermistors> thermistors;
std::array<uint8_t, kNumThermistors> thermistor_pins{A0, A3, A6, A7, A4, A5, A18, A19};

void PrintValues()
{
    Serial.print(thermistors[0]->GetTemperature());
    for (int i = 1; i < kNumThermistors; i++)
    {
        Serial.print(", ");
        Serial.print(thermistors[i]->GetTemperature());
    }
    Serial.println();
}

void setup()
{
    for (int i = 0; i < kNumThermistors; i++)
    {
        thermistors[i] = new NXFT15XH103FA2B050ADCThermistor(thermistor_pins[i], 3.3f / 4095, 0.14, 3.3f, 10000);
    }
    Serial.begin(115200);
    Serial.println("Begin");
    timer_group.AddTimer(100, []() { PrintValues(); });
}

void loop()
{
    // put your main code here, to run repeatedly:
    timer_group.Tick(millis());
}