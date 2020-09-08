#include <grrlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "bumpitup_ttf.h"

#include "snake.h"
#include "fruit.h"
#include "global.h"
#include <string>


int main(void) {    

    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(bumpitup_ttf, bumpitup_ttf_size);

    Snake snake;
    Fruit fruit;
    Vector2 input;
    input.x = 1;
    input.y = 0;

    int updateDelay = 0;
    int targetDelay = 6;

    char score[32];
    // Main Menu
    while(1)
    {
        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) 
        {
            GRRLIB_FreeTTF(font);
            GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

            exit(0);  // Use exit() to exit a program, do not use 'return' from main()
        }
        // Go to the actual game.
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS) break;



        WPAD_ScanPads();  // Scan the Wiimotes

        // --------------------------------------------------------------------- Drawing START
        GRRLIB_FillScreen(GRRLIB_BLACK);
        GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, "Snek", 72) / 2 + PalCorrectionX, (screenHeight / 2) - 150 + PalCorrectionY, font, "Snek", 72, GRRLIB_WHITE);
        GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, "Press + to start", 18) / 2 + PalCorrectionX, (screenHeight / 2) + 50 + PalCorrectionY, font, "Press + to start", 18, LIGHT_GRAY);
        GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, "Press HOME to exit at any moment.", 12) / 2 + PalCorrectionX, (screenHeight / 2) + 100 + PalCorrectionY, font, "Press HOME to exit at any moment.", 12, GRAY);
        GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, "Made by Michele", 12) / 2 + PalCorrectionX, (screenHeight / 2) + 150 + PalCorrectionY, font, "Made by Michele", 12, GRAY);

        // --------------------------------------------------------------------- Drawing END

        GRRLIB_Render();  // Render the frame buffer to the TV
    }
    // Main Game
    while(1) {

        // Update the delay so that the speed will increase when the snake gets more long.
        if (targetDelay > 1)
            targetDelay = 6 - (snake.getLength() % 10);

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

        // The wiimote will be placed horizontally, so rotate the dpad as well
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT && !(input.y == 1))
        {
            input.x = 0;
            input.y = -1;
        }
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT && !(input.y == -1))
        {
            input.x = 0;
            input.y = 1;
        }
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP && !(input.x == 1))
        {
            input.x = -1;
            input.y = 0;
        }
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN && !(input.x == -1))
        {
            input.x = 1;
            input.y = 0;
        }

        // When dead, press [PLUS] on the wiimote to begin a new game
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS && !snake.checkAlive())
        {
            snake.revive();
        }        

        sprintf(score, "%d", snake.getLength() - 1);
        WPAD_ScanPads();  // Scan the Wiimotes
        if (snake.checkAlive())
        {
            if (updateDelay > targetDelay)
            {
                snake.updatePos(input);
                updateDelay = 0;
                fruit.checkForSnake(snake);
            }
            else
                updateDelay++;
        }

        

        // --------------------------------------------------------------------- Drawing START
        GRRLIB_FillScreen(GRRLIB_BLACK);
        GRRLIB_Rectangle(PalCorrectionX, PalCorrectionY, screenWidth, screenHeight, GRRLIB_WHITE, false);
        GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, score, 72) / 2 + PalCorrectionX, (screenHeight / 2) - 50 + PalCorrectionY, font, score, 72, DARK_GRAY);

        snake.draw();
        fruit.draw();

        if (!snake.checkAlive())
        {
            GRRLIB_PrintfTTF((screenWidth / 2) - GRRLIB_WidthTTF(font, "You lost, press + to retry", 18) / 2 + PalCorrectionX, (screenHeight / 2) + 100 + PalCorrectionY, font, "You lost, press + to retry", 18, DARK_GRAY);
            input.x = 1;
            input.y = 0;
        }

        // --------------------------------------------------------------------- Drawing END

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    GRRLIB_FreeTTF(font);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
