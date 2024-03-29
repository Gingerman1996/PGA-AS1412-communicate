#include <Arduino.h>

#include <SPI.h>

const int clkPin = 13;
const int diPin = 12;

const uint8_t spiMode = SPI_MODE0;
const uint32_t spiFrequency = 1000000; // ความถี่ SPI 1 MHz

void setup()
{
    SPI.begin(clkPin, MISO, MOSI, SS);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(spiMode);
    SPI.setFrequency(spiFrequency);

    pinMode(diPin, INPUT);
    pinMode(clkPin, OUTPUT);

    Serial.begin(115200);
}

void loop()
{
    while (digitalRead(diPin))
        ;

    uint8_t data[3] = {0};
    for (int i = 0; i < 24; i++)
    {
        digitalWrite(clkPin, HIGH);

        // อ่านข้อมูล
        data[i / 8] |= (digitalRead(diPin) << (7 - (i % 8)));

        digitalWrite(clkPin, LOW);
    }

    uint32_t dataValue = (data[0] << 16) | (data[1] << 8) | data[2];

    String hexString = String(dataValue, HEX);

    String decString = String(dataValue);

    // Serial.print("HEX: ");
    // Serial.println(hexString);
    // Serial.print("DEC: ");
    Serial.println(decString);
}