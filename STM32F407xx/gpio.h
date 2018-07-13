#ifndef GPIO_H
#define GPIO_H

#include "stm32f407xx.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define GPIO_OUT_OF_RANGE = 0xFFFFFFFF;
#define GPIO_PORTS	{GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

typedef enum
{
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	Undefined,
} PortType;

typedef struct
{
	int PinNumber;
	PortType Port;
} GpioPin;

typedef enum
{
	GpioInput = 0x00,
	GpioOutput = 0x01,
} GpioPinDirection;

typedef enum
{
	OutputPushPull = 0x00,
	OutputOpenDrain = 0x01,
} OutputType;

typedef enum
{
	LowSpeed = 0x00,
	MediumSpeed = 0x01,
	HighSpeed = 0x02,
	VeryHighSpeed = 0x03,
} SpeedType;

typedef enum
{
	NoPullUpOrPullDown = 0x00,
	PullUp = 0x01,
	PullDown = 0x02,
	Reserved = 0x03,
} PullUpDownType;

typedef struct
{
	SpeedType Speed;
	bool IsEnableInterrupt;
} GpioInputPin;

typedef struct
{
	OutputType Type;
	SpeedType Speed;
	PullUpDownType PullSelect;
	bool IsEnableInterrupt;
} GpioOuputPin;

typedef struct
{
	GpioPin PinInfo;
	GpioInputPin Config;
} GpioInputUserConfig;

typedef struct
{
	GpioPin PinInfo;
	GpioOuputPin Config;
} GpioOutputUserConfig;

void GPIO_DRV_Init(const GpioInputUserConfig * inputPins, const GpioOutputUserConfig * outputPins);
void GPIO_DRV_InputInit(const GpioInputUserConfig * inputPins);
void GPIO_DRV_OutputInit(const GpioOutputUserConfig * outputPins);
GpioPinDirection GPIO_DRV_GetPinDir(unsigned int pinName);
void GPIO_DRV_SetPinDir(GpioPin pinInfo, GpioPinDirection dir);
void GPIO_DRV_WritePinOutput(unsigned int pinName, unsigned int output);
void GPIO_DRV_SetPinOutput(GpioPin pinInfo);
void GPIO_DRV_ClearPinOnput(GpioPin pinInfo);
void GPIO_DRV_TogglePinOutput(GpioPin pinInfo);
bool GPIO_DRV_ReadPinInput(GpioPin pinInfo);
#endif