#ifndef GRINLIZ_DOTSTAR_INCLUDED
#define GRINLIZ_DOTSTAR_INCLUDED

#include <stdint.h>

struct RGB {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

	void set(uint8_t _r, uint8_t _g, uint8_t _b) {
		r = _r; g = _g; b = _b;
	}
	void set(uint32_t c) {
		r = (c & 0xff0000) >> 16;
		g = (c & 0xff00) >> 8;
		b = c & 0xff;
	}
    void scale(uint8_t s) {
        r = (uint16_t(r) * uint16_t(s)) >> 8;
        g = (uint16_t(g) * uint16_t(s)) >> 8;
        b = (uint16_t(b) * uint16_t(s)) >> 8;
    }
	uint8_t operator[](const int index) const {
		return *(&r + index);
	}
    uint8_t& operator[](const int index) {
        return *(&r + index);
    }
};


class DotStar
{
public:
	DotStar(uint8_t enablePin);
	void begin();

	void attachLEDs(const RGB* leds, int nLEDs) {
		m_leds = leds;
		m_nLEDs = nLEDs;
	}

	void setBrightness(uint16_t value256)	{ m_brightness = value256; }
	uint16_t brightness() const				{ return m_brightness; }

	void display();

private:
	uint8_t 	m_enable = 0;
	const RGB* 	m_leds = 0;
	int 		m_nLEDs = 0;
	uint16_t 	m_brightness = 256;
};

#endif // GRINLIZ_DOTSTAR_INCLUDED
