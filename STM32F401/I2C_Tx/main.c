#include "RccConfig.h"
#include "Delay.h"

void I2C_Config (void);

void I2C_Config (void) {
	// Steps to be followed
	// 1. Enable the I2C CLOCK and GPIO CLOCK
	// 2. Configure the I2C PINs for Alternate Functions
	//		a) Select Alternate Function in MODER Register
	//		b) Select Open Drain Output
	// 		c) Select High SPEED for the PINs
	//		d) Select Pull-up for both the Pins
	// 		e) Configure the Alternate Function in AFR Register
	//	3. Reset the I2C
	//	4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	//	5. Configure the clock control register
	//	6. Configure the rise time register
	//	7. Program the I2C_CR1 register to enable the peripheral

	
	// Enable the I2C CLOCK and GPIO CLOCK
	RCC->APB1ENR |= (1<<21); // enable I2C CLOCK
	RCC->AHB1ENR |= (1<<1); // enable GPIOB CLOCK
	
	// Configure the I2C PINs for Alternate Functions
	GPIOB->MODER |= (2<<16) | (2<<18); // Bits (17:16) = 1:0 --> Alternate Function for pin PB8; Bits (19:18) = 1:0 --> Alternate Function for pin PB9
	GPIOB->OTYPER |= (1<<8) | (1<<9); // Bit8=1, Bit9=1 output open drain
	GPIOB->OSPEEDR |= (3<<16) | (3<<18); // Bits (17:16) = 1:1 --> High Speed for pin PB8; Bits (19:18) = 1:1 --> High Speed for pin PB9
	GPIOB->PUPDR |= (1<<16) | (1<<18); // Bits (17:16) = 0:1 --> Pull up for pin PB8; Bits (19:18) = 0:1 --> Pull up for pin PB9
	GPIOB->AFR[1] |= (4<<0) | (4<<4); // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8; Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9
	
	// Reset the I2C
	I2C1->CR1 |= (1<<15);
	I2C1->CR1 &= ~(1<<15);
	
	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2C1->CR2 |= (42<<0); // PCLK1 Frequency in MHz
	
	// Configure the clock control register
	I2C1->CCR = (210<<0); // calculated value for 42 MHz and 1000 ns, 4 us
												// CCR = (Tr(scl) + Tw(sclh)) / Tpclk1
												// Tpclk1 = 1 / Frequency
		
	// Configure the rise time register
	I2C1->TRISE = 43; // calculated value for 42 MHz and 1000 ns
										// Trise = Tr(scl) / Tpclk1 + 1
										// Tpclk1 = 1 / Frequency
	
	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1<<0); // Enable I2C
	
}



int main (void) {

	while (1) {
	
	
	}
	
}

