#ifndef _HARDSPI_H
#define _HARDSPI_H

#include "Arduino.h"

// Внимание! Эта версия не совместима с SPI ванильного Ардуино... Но это пока.
// Чип селектом управляете сами, в ручном режиме, через digitalWrite

#ifndef LSBFIRST
#  define LSBFIRST 0
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03


class SPISettings
{
public:
    SPISettings(uint32_t clock, uint16_t bitOrder, uint8_t dataMode)
    {
        init_AlwaysInline(clock, bitOrder, dataMode);
    }
    SPISettings(uint32_t clock)
    {
        init_AlwaysInline(clock, LSBFIRST, SPI_MODE0);
    }
    SPISettings()
    {
        init_AlwaysInline(4000000, LSBFIRST, SPI_MODE0);
    }
private:

    void init_AlwaysInline(uint32_t clock, uint16_t bitOrder, uint8_t dataMode) __attribute__((__always_inline__))
    {
        this->clock = clock;
        this->bitOrder = bitOrder;
        this->dataMode = dataMode;
    }
    uint32_t clock;
    uint16_t bitOrder;
    uint8_t dataMode;

    friend class HardSPI;
};
// Максимальная частота шины SPI clock - 20 Мhz

class HardSPI {
    private:
	// func
    private:
	// var
    uint8_t   _miso = PB25;
    uint8_t   _mosi = PB26;
    uint8_t   _sck  = PB24;
	uint32_t  _clock = 4000000;
    uint16_t  _bitOrder = SPI_LITTLEENDIAN;
    uint8_t   _dataMode = SPI_MODE0;
	uint8_t   _prescaler = SPI_BAUDRATEPRESCALER_10;
    uint8_t clock_polarity ;
    uint8_t clock_phase ;
	uint16_t timeOut = 1000;
	SPI_HandleTypeDef hspi;
	
	public:
	// methods
		HardSPI() {HardSPI(PB26, PB25, PB24); /* Pins by default */ };
        HardSPI(uint8_t mosi, uint8_t miso, uint8_t sck); // alternatives see datasheet
		void SPI_Settings(uint32_t clock, uint16_t bitOrder, uint8_t dataMode);
 		void beginTransaction(SPISettings settings);
		void beginTransaction() {begin();};		
		void endTransaction() {end();};		
        void begin();
        void end();
        uint8_t transfer(uint8_t);
		uint16_t transfer16(uint16_t data);
		void transfer(void *buf, size_t count);
		
		// Deprecated, NOT IMPLEMENTED YET!
        void setBitOrder(uint8_t);
        void setDataMode(uint8_t);
        void setClockDivider(uint8_t);
		
};
extern HardSPI SPI;
#endif