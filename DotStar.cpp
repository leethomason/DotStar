#include "dotstar.h"
#include <Arduino.h>
#include <SPI.h>

// 8 MHz seems to work for the prop shield.
// With a level shifter, about 1 MHz is needed. (Possibly faster with testing.)
static const SPISettings dotstarSettings(8000000, MSBFIRST, SPI_MODE0);

DotStar::DotStar(uint8_t enable)
{
	m_enable = enable;
	pinMode(m_enable, OUTPUT);
	digitalWrite(m_enable, LOW);
}

void DotStar::begin()
{
	SPI.begin();
}

void DotStar::display()
{
	//Serial.print("display nLeds="); Serial.println(m_nLEDs);
	SPI.beginTransaction(dotstarSettings);
	digitalWrite(m_enable, HIGH);

	// Frame marker.
	for(int i=0; i<4; ++i) {
		SPI.transfer(0);
	}

	const RGB* led = m_leds;
	for(int i=0; i<m_nLEDs; ++i, ++led) {
		// Pixel start:
		SPI.transfer(0xff);

		// Value:
		SPI.transfer((uint16_t(led->b) * m_brightness) >> 8);
		SPI.transfer((uint16_t(led->g) * m_brightness) >> 8);
		SPI.transfer((uint16_t(led->r) * m_brightness) >> 8);
	}
	// End frame.
	for(int i=0; i<4; ++i) {
		SPI.transfer(0xff);
	}

	digitalWrite(m_enable, LOW);
    SPI.endTransaction();
}



