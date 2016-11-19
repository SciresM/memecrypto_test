#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>

#include "memecrypto.h"

int main(int argc, char **argv)
{
    // Initialize services
    aptInit();
    gfxInitDefault();
    hidInit();
    gspLcdInit();
    
    consoleInit(GFX_TOP, NULL);
    
    printf("Press A to test memecrypto!\n");
    
    while(aptMainLoop()) //Always have the main code loop in here
    {
        hidScanInput(); //Checks which keys are pressed

        u32 button = hidKeysDown(); // Checks which keys are up and which ones are down
        if (button & KEY_A)
        {
            break;
        }
    }
    
    printf("Doing Memecrypto!\n");
    
    unsigned char input[0x80];
    unsigned char output[0x80];
    for (int i = 0; i < 0x80; i++)
    {
        input[i] = 0;
        output[i] = 0;
    }
    
    memecrypto_sign(input, output, 0x80);
    
    for (int i = 0; i < 0x8; i++)
    {
        for (int j = 0; j < 0x10; j++)
            printf("%02X", output[i*0x10+j]);
        printf("\n");
    }
    
    if (memecrypto_verify(output, input, 0x80))
    {
        printf("memesig verified!\nDecrypted memebuffer:\n");
        for (int i = 0; i < 0x8; i++)
        {
            for (int j = 0; j < 0x10; j++)
                printf("%02X", input[i*0x10+j]);
            printf("\n");
        }
    }
    else 
    {
        printf("Failed to verify memesig! :( \n");
    }
    
    
    printf("Did Memecrypto!\n");
    printf("Press START to exit.\n");
    
    while(aptMainLoop()) //Always have the main code loop in here
    {
        hidScanInput(); //Checks which keys are pressed

        u32 button = hidKeysDown(); // Checks which keys are up and which ones are down
        if (button & KEY_START)
        {
            break;
        }
    } 

    // Exit services
    aptExit();
    gfxExit();
    hidExit();
    gspLcdExit();
    return 0;
}
