#include <stdio.h>
#include "raylib.h" 
#include <time.h>
#include <stdlib.h>
#define PHYSAC_IMPLEMENTATION
#include "physac.h"

int main()
{   
    //RESOLUTION: 
    const float screenWidth = 500.0;
    const float screenHeight = 500.0; 
    const int FPS_LIMIT = 60;
    //SQUARE SIZE: 
    const float RectangleWidth = screenWidth / 20.0; 
    const float RectangleHeight = screenHeight / 20.0; 
    //TILE SIZE: 
    const float tileHeight = RectangleHeight; 
    const float tileWidth = RectangleWidth; 
    
    //pixels 
    //INITIAL POSITIONS IN WINDOW: 
    //STARTING TILE: UP AND LEFT TILE FROM MIDDLE OF GRID 
    //COORDINATES REFER TO LOCATION OF UPPER LEFT CORNER OF SQUARE (HEAD).
    float x1 = screenWidth / 2 - (RectangleWidth); 
    float y1 = screenHeight / 2 - (RectangleHeight); 
    float radius;
    int scoreCounter = 0; 
    float velocity_x = 0.06; 
    float velocity_y = 0; 
    //For circle: 
    float rand_x; 
    float rand_y;
    int lower_x = 1; 
    int lower_y = 1; 
    int upper_x = 19; 
    int upper_y = 19; 
    int circleExists = 0;
    const int arraySize = (int)(screenHeight/tileHeight*screenWidth/tileWidth); 
    int snakeSize = 1; //MAX VALUE = length == 60.
    float passed_x[arraySize]; 
    float passed_y[arraySize];
    int length = sizeof(passed_x) / sizeof(passed_x[0]); 
//-----------------------------
    InitWindow(screenWidth, screenHeight, "Snake-game");
//-----------------------------
    SetTargetFPS(FPS_LIMIT);
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
        //-----------------------------------
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
        //-----------------------------------------------. 
        //DRAWING BODY OF SNAKE:
        //---------------------------------
        for(int i=snakeSize; i > 0; i--){ 
            if((passed_x[i] != 2*screenHeight) && (passed_y[i] != 2*screenHeight) && (snakeSize != 0)){ 
                DrawRectangle(passed_x[i], passed_y[i], RectangleWidth, RectangleHeight, SKYBLUE);
            }
        } 
         //DRAW SNAKE HEAD, MOVEMENT INCREMENTS AND BORDER CHECK PART:  
        DrawRectangle(x1, y1, RectangleWidth, RectangleHeight, BLUE); //DRAWING STARTS FROM UPPER LEFT CORNER.
        //------------------------------------
        //MOVEMENT: 
        if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (y1  >= RectangleHeight/2)){ 
            velocity_y = -0.06;
            velocity_x = 0;
            //y1 = y1 - (RectangleHeight); 
        } else  if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (y1 + RectangleHeight < screenHeight)){ 
            velocity_y = 0.06; 
            velocity_x = 0;
            //y1 = y1 + (RectangleHeight); 
        } else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (x1 - (RectangleWidth / 2) >= 0)){ 
            velocity_x = -0.06; 
            velocity_y = 0;
            //x1 = x1 - (RectangleWidth);
        } else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (x1 + RectangleWidth < screenWidth)){ 
            velocity_x = 0.06; 
            velocity_y = 0;
            //x1 = x1 + (RectangleWidth);
        }
        //---------------------------------- 
        y1 = y1 + velocity_y * RectangleHeight; //* RectangleHeight; 
        x1 = x1 + velocity_x * RectangleWidth; //* RectangleWidth;
        //----------------------------------
        //EATING CIRCLE (FRUIT) PART:
        if((x1 <= (rand_x - tileWidth/2 + radius)) && (x1 > rand_x - tileWidth/2 - radius) && (y1 <= (rand_y - tileHeight/2 + radius)) && (y1 > (rand_y - tileHeight/2 - radius))){ 
        circleExists=0; 
        scoreCounter++;
        snakeSize++;
        }
        //DRAWING SCORE: 
        DrawText(TextFormat("SCORE: %02i", scoreCounter), 0.02*screenWidth, 0.01*screenHeight, 20, SKYBLUE);
        // 
        if(x1 != passed_x[0] || y1 != passed_y[0]){ 
            passed_x[0]=x1; 
            passed_y[0]=y1;
            for(int i=length-1; i > 0; i--){ 
                passed_x[i] = passed_x[i-1]; 
                passed_y[i] = passed_y[i-1];
            } 
        }
        
        //COLLISION CHECKS:
        for(int i=1; i <= snakeSize; i++){ 
           if((passed_x[i+1] == x1) && (passed_y[i+1] == y1)){ 
                exit(1);
            }
        } 
        //--------------------------
        EndDrawing();
    }

    CloseWindow(); 

    return 0;
} 