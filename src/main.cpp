#include <Arduino.h>

#include "thermistor.h"
#include "virtualTimer.h"

VirtualTimerGroup timer_group;

const uint8_t kNumThermistors{8};

std::array<NXFT15XH103FA2B050ADCThermistor*, kNumThermistors> thermistors;
std::array<uint8_t, kNumThermistors> thermistor_pins{36, 39, 34, 35, 32, 33, 25, 26};

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
        thermistors[i] = new NXFT15XH103FA2B050ADCThermistor(thermistor_pins[i], 3.3f / 4095, 3.3f, 10000);
    }
    Serial.begin(9600);
    timer_group.AddTimer(100, []() { PrintValues(); });
    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
    timer_group.Tick(millis());
}