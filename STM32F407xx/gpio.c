#include "gpio.h"

GPIO_TypeDef * GpioBase[] = GPIO_PORTS;

void GPIO_DRV_Init(const GpioInputUserConfig * inputPins, const GpioOutputUserConfig * outputPins)
{
	while(inputPins->PinInfo.Port != Undefined)
	{
		GPIO_DRV_InputInit(inputPins++);
	}
	
	while(outputPins->PinInfo.Port != Undefined)
	{
		GPIO_DRV_OutputInit(outputPins++);
	}
}
	
void GPIO_DRV_InputInit(const GpioInputUserConfig * inputPin)
{
	/* Enable clock for port */
	RCC->AHB1ENR |= (1 << inputPin->PinInfo.Port);
	
	/* Get structure base of gpio */
	GPIO_TypeDef * gpioBase = GpioBase[inputPin->PinInfo.Port];
	
	/* Set dirrection for input pin */
	GPIO_DRV_SetPinDir(inputPin->PinInfo, GpioInput);
	
	/* Enable interrupt for this pin */
	if(inputPin->Config.IsEnableInterrupt == true)
	{
		
	}
}
	
void GPIO_DRV_OutputInit(const GpioOutputUserConfig * outputPin)
{
	/* Enable clock for port */
	RCC->AHB1ENR |= (1 << outputPin->PinInfo.Port);
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	/* Get structure base of gpio */
	GPIO_TypeDef * gpioBase = GpioBase[outputPin->PinInfo.Port];
	
	GPIO_DRV_SetPinDir(outputPin->PinInfo, GpioOutput);
	
	/* Set speed */
	gpioBase->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (2 * outputPin->PinInfo.PinNumber));
	gpioBase->OSPEEDR |= outputPin->Config.Speed;
	
	/* Set type */
	gpioBase->OTYPER &= ~(GPIO_OTYPER_OT0 << outputPin->PinInfo.PinNumber);
	gpioBase->OTYPER |= (outputPin->Config.Type << outputPin->PinInfo.PinNumber);
	
	/* Set push-pull */
	gpioBase->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (2 * outputPin->PinInfo.PinNumber));
	gpioBase->PUPDR |= (outputPin->Config.PullSelect << (2 * outputPin->PinInfo.PinNumber));
	
	/* Enable interrupt */
	if(outputPin->Config.IsEnableInterrupt == true)
	{	
		int order = outputPin->PinInfo.PinNumber / 4;
		int subOrder = outputPin->PinInfo.PinNumber % 4;

		/* Enable clock for EXTI */
		SYSCFG->EXTICR[order] &= ~(0x0F << subOrder);
		SYSCFG->EXTICR[order] |= (outputPin->PinInfo.Port << subOrder);
		
		/* Enable raising edge */
		EXTI->RTSR |= (1 << outputPin->PinInfo.PinNumber);
		
		/* Enable mask for this interrupt */
		EXTI->IMR |= (1 << outputPin->PinInfo.PinNumber);
		
		/* Enable interrupt for line on NVIC */
		switch(outputPin->PinInfo.PinNumber)
		{
			case 0:
				NVIC_EnableIRQ(EXTI0_IRQn);
				break;
			case 1:
				NVIC_EnableIRQ(EXTI1_IRQn);
				break;
			case 2:
				NVIC_EnableIRQ(EXTI2_IRQn);
				break;
			case 3:
				NVIC_EnableIRQ(EXTI3_IRQn);
				break;
			case 4:
				NVIC_EnableIRQ(EXTI4_IRQn);
				break;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				NVIC_EnableIRQ(EXTI9_5_IRQn);
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				NVIC_EnableIRQ(EXTI15_10_IRQn);
				break;
			default:
				break;
		}
	}
}
	
GpioPinDirection GPIO_DRV_GetPinDir(unsigned int pinName)
{
	
}
	
void GPIO_DRV_SetPinDir(GpioPin pinInfo, GpioPinDirection dir)
{
	GPIO_TypeDef * gpioBase = GpioBase[pinInfo.Port];
	
	if(dir == GpioInput)
	{	
		/* Set pin is input */
		gpioBase->MODER &= ~GPIO_MODER_MODE0;
	}
	else if(dir == GpioOutput)
	{
		/* Set pin as output */
		gpioBase->MODER &= ~(GPIO_MODER_MODE0 << (2 * pinInfo.PinNumber));
		gpioBase->MODER |= (GPIO_MODER_MODE0_0 << (2 * pinInfo.PinNumber));
	}
}
	
void GPIO_DRV_WritePinOutput(unsigned int pinName, unsigned int output)
{}
	
void GPIO_DRV_SetPinOutput(GpioPin pinInfo)
{
	GPIO_TypeDef * gpioBase = GpioBase[pinInfo.Port];
	
	gpioBase->ODR |= (GPIO_ODR_OD0 << pinInfo.PinNumber);
}
	
void GPIO_DRV_ClearPinOnput(GpioPin pinInfo)
{
	GPIO_TypeDef * gpioBase = GpioBase[pinInfo.Port];
	
	gpioBase->ODR &= ~(GPIO_ODR_OD0 << pinInfo.PinNumber);
}
	
void GPIO_DRV_TogglePinOutput(GpioPin pinInfo)
{}
	
bool GPIO_DRV_ReadPinInput(GpioPin pinInfo)
{
	GPIO_TypeDef * gpioBase = GpioBase[pinInfo.Port];
	return ((gpioBase->IDR & (GPIO_IDR_ID0 << pinInfo.PinNumber)) >> pinInfo.PinNumber == 1);
}

