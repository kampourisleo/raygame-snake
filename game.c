#include <stdio.h>
#include "raylib.h" 
#include <time.h>
#include <stdlib.h>

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

int main()
{   //RESOLUTION: 
    float screenWidth = 500.0;
    float screenHeight = 500.0; 
    //SQUARE SIZE: 
    float RectangleWidth = screenWidth / 20.0; 
    float RectangleHeight = screenHeight / 20.0; 
    //TILE SIZE: 
    float tileHeight = RectangleHeight; 
    float tileWidth = RectangleWidth; 
    //pixels 
    //INITIAL POSITIONS IN WINDOW: 
    //STARTING TILE: UP AND LEFT TILE FROM MIDDLE OF GRID
    float x0 = screenWidth / 2 - (RectangleWidth); 
    float y0 = screenHeight / 2 - (RectangleHeight); 
    //COORDINATES REFER TO LOCATION OF UPPER LEFT CORNER OF SQUARE (HEAD).
    float x1 = x0; 
    float y1 = y0; 
    float radius;
    int scoreCounter = 0; 
    //For circle: 
    float rand_x; 
    float rand_y;
    int lower_x = 1; 
    int lower_y = 1; 
    int upper_x = 19; 
    int upper_y = 19; 
    int circleExists = 0; 
    int snakeSize = 0; //MAX VALUE == 60???? 
    float passed_x[60] = {-1}; 
    float passed_y[60] = {-1};
//-----------------------------
    InitWindow(screenWidth, screenHeight, "raygame");
//-----------------------------
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing(); 
        //WINDOW AND COLOR CHANGE
        Color clearColor = BLACK;
        if (IsKeyDown(KEY_SPACE)){ 
            clearColor = PINK;
        } 
        ClearBackground(clearColor);
        //Drawing lines to form tile grid on screen-space.
        for (int i=1; i <= (screenHeight/tileHeight - 1); i++){ 
            DrawLine(0, i*tileHeight, screenWidth, i*tileHeight, WHITE);
        }
        for (int i=1; i <= (screenWidth/tileWidth - 1); i++){ 
            DrawLine(i*tileWidth, 0, i*tileWidth, screenHeight, WHITE);
        }
        //--------------------------------- 
        DrawFPS(0.85*screenWidth, 0.01*screenHeight); 
        //---------------------------------
        //GENERATING RANDOM CIRCLES PART: 
        //TILE SIZE: RECTANGLE HEIGHT X RECTANGLE WIDTH. ==> 
        //CENTER: y2 = y + tileHeight/2, x2 = x + tileWidth/2. 
        //Circle RANDOM position: 
        if (circleExists==0)
        {
            rand_x = ((rand() % (upper_x - lower_x + 1)  + lower_x) * tileWidth) + tileWidth/2; 
            rand_y = ((rand() % (upper_y - lower_y + 1) + lower_y) * tileHeight) + tileHeight/2; 
            //Radius:
            if(tileHeight >= tileWidth) radius = tileWidth/2; 
            else radius = tileHeight/2;
            //Drawing circle: 
            DrawCircle(rand_x, rand_y, (radius), RED); 
            circleExists = 1;
        } 
        //Drawing circle: 
        DrawCircle(rand_x, rand_y, (radius), RED); 
        //----------------------------------------------
        //"Use 'WASD' to move player" 
        //DRAW SNAKE HEAD, MOVEMENT INCREMENTS AND BORDER CHECK PART:  
        DrawRectangle(x1, y1, RectangleWidth, RectangleHeight, BLUE); //DRAWING STARTS FROM UPPER LEFT CORNER. 
        //MOVEMENT: 
        if ((IsKeyPressed(KEY_W) || IsKeyPressedRepeat(KEY_W)) && (y1 - (RectangleHeight / 2) >= 0)){ 
            //previous: 

            //movement:
            y1 = y1 - (RectangleHeight); 
            x1 = x1; 
        } else  if ((IsKeyPressed(KEY_S) || IsKeyPressedRepeat(KEY_S)) && (y1 + RectangleHeight < screenHeight)){ 
            y1 = y1 + (RectangleHeight); 
            x1 = x1;
        } else if ((IsKeyPressed(KEY_A) || IsKeyPressedRepeat(KEY_A)) && (x1 - (RectangleWidth / 2) >= 0)){ 
            y1 = y1; 
            x1 = x1 - (RectangleWidth);
        } else if ((IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D)) && (x1 + RectangleWidth < screenWidth)){ 
            y1 = y1; 
            x1 = x1 + (RectangleWidth);
        }
        //---------------------------------- 
        //EATING CIRCLE (FRUIT) PART:
        if((x1 == (rand_x - tileWidth/2)) && (y1 == (rand_y - tileHeight/2))){ 
        circleExists=0; 
        scoreCounter++;
        snakeSize++;
        }
        //DRAWING SCORE: 
        DrawText(TextFormat("SCORE: %02i", scoreCounter), 0.02*screenWidth, 0.01*screenHeight, 20, SKYBLUE);
        //---------------------------------

        //DRAWING BODY OF SNAKE: 


        //--------------------------
        EndDrawing();
    }

    CloseWindow(); 

    return 0;
} 