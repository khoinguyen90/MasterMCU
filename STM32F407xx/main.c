#include "gpio.h"

int main(void)
{

	GpioInputUserConfig PinA0Config;
	PinA0Config.Config.IsEnableInterrupt = false;
	PinA0Config.PinInfo.PinNumber = 0;
	PinA0Config.PinInfo.Port = PORT_A;
	
	GpioOutputUserConfig PinD12Config;
	PinD12Config.Config.PullSelect = NoPullUpOrPullDown;
	PinD12Config.Config.Type = OutputPushPull;
	PinD12Config.Config.Speed = MediumSpeed;
	PinD12Config.Config.IsEnableInterrupt = true;
	PinD12Config.PinInfo.PinNumber = 12;
	PinD12Config.PinInfo.Port = PORT_D;
	
	GPIO_DRV_InputInit(&PinA0Config);
	GPIO_DRV_OutputInit(&PinD12Config);
	
	while(true)
	{
		if(GPIO_DRV_ReadPinInput(PinA0Config.PinInfo))
		{
			GPIO_DRV_SetPinOutput(PinD12Config.PinInfo);
		}
		else	
		{
			GPIO_DRV_ClearPinOnput(PinD12Config.PinInfo);
		}
	}
	
	return 0;
}

void EXTI15_10_IRQHandler(void)
{

}
