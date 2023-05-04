/* Reaction time game */
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include “myTimer.h”
#include “myUart.h”

// UART 0
#define PC_UART_PORT    (0)
#define PC_UART_RX_PIN  (3)
#define PC_UART_TX_PIN  (1)

const struct note ImperialMarch[] =
{
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used TEMPO ms for a quart note
    {a, TEMPO},
    {a, TEMPO},
    {a, TEMPO},
    {f, TEMPO*3/4},
    {cH, TEMPO*1/4},

    {a, TEMPO},
    {f, TEMPO*3/4},
    {cH, TEMPO*1/4},
    {a, TEMPO*2},
    //first bit

    {eH, TEMPO},
    {eH, TEMPO},
    {eH, TEMPO},
    {fH, TEMPO*3/4},
    {cH, TEMPO*1/4},

    {gS, TEMPO},
    {f, TEMPO*3/4},
    {cH, TEMPO*1/4},
    {a, TEMPO*2},
    //second bit...

    {aH, TEMPO},
    {a, TEMPO*3/4},
    {a, TEMPO*1/4},
    {aH, TEMPO},
    {gSH, TEMPO/2},
    {gH, TEMPO/2},

    {fSH, TEMPO*1/4},
    {fH, TEMPO*1/4},
    {fSH, TEMPO/2},
    {0,TEMPO/2},
    {aS, TEMPO/2},
    {dSH, TEMPO},
    {dH, TEMPO/2},
    {cSH, TEMPO/2},
    //start of the interesting bit

    {cH, TEMPO*1/4},
    {b, TEMPO*1/4},
    {cH, TEMPO/2},
    {0,TEMPO/2},
    {f, TEMPO*1/4},
    {gS, TEMPO},
    {f, TEMPO*3/4},
    {a, TEMPO*1/4},

    {cH, TEMPO},
    {a, TEMPO*3/4},
    {cH, TEMPO*1/4},
    {eH, TEMPO*2},
    //more interesting stuff (this doesn't quite get it right somehow)

    {aH, TEMPO},
    {a, TEMPO*3/4},
    {a, TEMPO*1/4},
    {aH, TEMPO},
    {gSH, TEMPO/2},
    {gH, TEMPO/2},

    {fSH, TEMPO*1/4},
    {fH, TEMPO*1/4},
    {fSH, TEMPO/2},
    {0,TEMPO/2},
    {aS, TEMPO/2},
    {dSH, TEMPO},
    {dH, TEMPO/2},
    {cSH, TEMPO/2},
    //repeat... repeat

    {cH, TEMPO*1/4},
    {b, TEMPO*1/4},
    {cH, TEMPO/2},
    {0,TEMPO/2},
    {f, TEMPO/2},
    {gS, TEMPO},
    {f, TEMPO*3/4},
    {cH, TEMPO*1/4},

    {a, TEMPO},
    {f, TEMPO*3/4},
    {c, TEMPO*1/4},
    {a, TEMPO*2}
    //and we're done
};

int app_main()
{
    
    uartInit(PC_UART_PORT, 57600, 8, 1, 2, PC_UART_TX_PIN,PC_UART_RX_PIN);
    delayMs(500);
    uartClrScr(PC_UART_PORT);

    // TODO: GPIO Init
    timer0Init();
    
    while(1)
    {
        if (uartKbhit(0))
        {
            switch (uartGetchar(0))
            {
            case 'p':
            case 'P': // Play Song
                    timer1Play(ImperialMarch, sizeof(ImperialMarch)/sizeof(struct note));
                    break;
            /*
            case 'n':
            case 'N': //Next song
                            break;
            case 'b'
            case 'B'://Previous song
                            break;
            */
            default:
                    break;
            }
        }
        // Prevent watchdog fault
        delayMs(10);
    }

    return 0; 
}