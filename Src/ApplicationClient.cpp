#include "ApplicationClient.hpp"
#include "DGPIO.hpp"

extern DGPIO ledGreen;
extern DGPIO ledOrange;
extern DGPIO ledRed;
extern DGPIO ledBlue;

void ApplicationClient::deviceEventReceive(unsigned char state)
{
    if (state)
    {
        ledGreen.digitalWrite(1); // Acender LED Verde
        delay(1000000);
        ledGreen.digitalWrite(0); // Apagar LED Verde

        ledOrange.digitalWrite(1); // Acender LED Laranja
        delay(1000000);
        ledOrange.digitalWrite(0); // Apagar LED Laranja

        ledRed.digitalWrite(1); // Acender LED Vermelho
        delay(1000000);
        ledRed.digitalWrite(0); // Apagar LED Vermelho

        ledBlue.digitalWrite(1); // Acender LED Azul
        delay(1000000);
        ledBlue.digitalWrite(0); // Apagar LED Azul
    }
    else
    {
        ledGreen.digitalWrite(0);
        ledOrange.digitalWrite(0);
        ledRed.digitalWrite(0);
        ledBlue.digitalWrite(0);
    }
}
