#include "raylib.h"
#include <ctype.h>
#include <ctype.h>

typedef enum {
    SCREEN_MAIN,
    SCREEN_INSERT,
    SCREEN_SEARCH,
    SCREEN_SORT,
    SCREEN_DELETE
} ScreenState;

bool IsArraySorted(int arr[], int n) {
    if (n == 1) return true;
    for (int i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) return false;
    }
    return true;
}

void InsertIntoSortedArray(int arr[], int *n, int value) {
    int i;
    for (i = *n - 1; (i >= 0 && arr[i] > value); i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = value;
    (*n)++;
}

void InsertAtEnd(int arr[], int *n, int value) {
    arr[*n] = value;
    (*n)++;
}

void ConvertCharArrayToIntArray(char charArray[100][20], int *intArray, int size) {
    for (int i = 0; i < size; i++) {
        intArray[i] = atoi(charArray[i]);
    }
}

void intArrayTo2DCharArray(int *arr, int size, char arrayValues[100][20]) {
    for (int i = 0; i < size; ++i) {
        sprintf(arrayValues[i], "%d", arr[i]);
    }
}

int main(void)
{
    const int screenWidth = 1024;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Welcome to our App");

    char inputText[20] = "\0";
    char inputText_insert[20] = "\0";

    int letterCount = 0;
    int letterCount_insert=0;

    int framesCounter = 0;
    int framesCounter2 =0;
    int framesCounter_insert=0;

    int arraySize = 0;
    char arrayValues[100][20] = {0}; // Assuming a maximum array size of 100
    int activeArrayInput = -1;

    Color inputTextColor = DARKGRAY;
    Color primaryColor = DARKBLUE;

    int textX = 100;
    int textY = 300;
    int spaceBetween = 20;
    int inputWidth = 120;
    int inputWidth_insert = 80;
    Rectangle inputField = { textX + 325, textY + spaceBetween, inputWidth, 20 };
    Rectangle inputField_insert = { textX + 380, textY + spaceBetween, inputWidth_insert, 20 };

    bool inputFieldActive = false;
    bool inputFieldActive_insert = false;

    int arrayBoxWidth = 50;
    int arrayBoxHeight = 30;
    int arrayBoxSpacing = 5;
    int maxElementsPerLine = (screenWidth - 50) / (arrayBoxWidth + arrayBoxSpacing); // Calculate maximum elements per line
    int intArray[50] = {0};

    // Button positions and dimensions
    Rectangle insertButton = { 250, 600, 120, 40 };
    Rectangle deleteButton = { 400, 600, 120, 40 };
    Rectangle searchButton = { 550, 600, 120, 40 };
    Rectangle sortButton = { 700, 600, 120, 40 };

    // Button colors
    Color insertButtonColor = BLUE;
    Color deleteButtonColor = GRAY;
    Color searchButtonColor = LIGHTGRAY;
    Color sortButtonColor = DARKGRAY;

    Color menuButtonColor = BLUE;

    // Button states (enabled/disabled)
    bool insertButtonEnabled = false;
    bool deleteButtonEnabled = false;
    bool searchButtonEnabled = false;
    bool sortButtonEnabled = false;
    bool display_flag = false;
    bool arrayInputActive = false;

    ScreenState currentScreen = SCREEN_MAIN;
    // Button for returning to the main menu from the delete screen
    Rectangle menuButton = { 250, 600, 120, 40 };

    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        Vector2 mousePoint = GetMousePosition();
        switch (currentScreen) {
            case SCREEN_MAIN:
                // Check if mouse is over buttons and change button colors
                if (CheckCollisionPointRec(mousePoint, insertButton) && insertButtonEnabled) {
                    insertButtonColor = BLUE;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = SCREEN_INSERT; // Change to delete confirmation screen
                        memset(inputText, 0, 20); // Clear the inputText
                        letterCount = 0;
                        inputFieldActive = false;
                    }
                } else {
                    insertButtonColor = DARKBLUE;
                }

                if (CheckCollisionPointRec(mousePoint, deleteButton) && deleteButtonEnabled) {
                    deleteButtonColor = GRAY;

                } else {
                    deleteButtonColor = DARKGRAY;
                }

                if (CheckCollisionPointRec(mousePoint, searchButton) && searchButtonEnabled) {
                    searchButtonColor = LIGHTGRAY;
                } else {
                    searchButtonColor = GRAY;
                }

                if (CheckCollisionPointRec(mousePoint, sortButton) && sortButtonEnabled) {
                    sortButtonColor = DARKGRAY;
                } else {
                    sortButtonColor = LIGHTGRAY;
                }

                if (CheckCollisionPointRec(mousePoint, (Rectangle){inputField.x, inputField.y - 20, inputField.width, 24})) {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        inputFieldActive = true;
                        arrayInputActive = false;
                    }
                } else {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        inputFieldActive = false;
                        arrayInputActive = true;
                    }
                }

                if (inputFieldActive) {
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 32) && (key <= 125) && (letterCount < 19)) {
                            if (isdigit(key)) { // Check if key is a digit
                                inputText[letterCount] = (char)key;
                                letterCount++;
                            }
                        }

                        key = GetCharPressed();
                    }

                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        if (letterCount > 0) {
                            letterCount--;
                            inputText[letterCount] = '\0';
                        }
                    }

                    framesCounter++;
                }


                if (inputFieldActive && IsKeyPressed(KEY_ENTER)) {
                    memset(arrayValues, 0, sizeof(arrayValues));
                    arraySize = atoi(inputText); // Convert inputText to integer for arraySize
                    //memset(inputText, 0, 20); // Clear the inputText
                    //letterCount = 0;
                    //inputFieldActive = false;
                    // Enable buttons when a valid array size is entered
                    insertButtonEnabled = true;
                    deleteButtonEnabled = true;
                    searchButtonEnabled = true;
                    sortButtonEnabled = true;
                }

                break;
            case SCREEN_INSERT:
                if (CheckCollisionPointRec(mousePoint, menuButton)) {

                    menuButtonColor = BLUE;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = SCREEN_MAIN; // Change to main screen
                        
                        memset(inputText_insert, 0, 20); // Clear the inputText
                        letterCount_insert = 0;
                        inputFieldActive_insert = false;

                        memset(arrayValues, 0, sizeof(arrayValues));
                        arraySize = 0;
                        display_flag = false;
                        memset(intArray, 0, sizeof(intArray));
                        arrayInputActive = false;
            

                    }
                    
                }else{menuButtonColor = DARKBLUE;}

                // Check if mouse is over buttons and change button colors

                if (CheckCollisionPointRec(mousePoint, deleteButton)) {
                    deleteButtonColor = GRAY;

                } else {
                    deleteButtonColor = DARKGRAY;
                }

                if (CheckCollisionPointRec(mousePoint, searchButton)) {
                    searchButtonColor = LIGHTGRAY;
                } else {
                    searchButtonColor = GRAY;
                }

                if (CheckCollisionPointRec(mousePoint, sortButton) ) {
                    sortButtonColor = DARKGRAY;
                } else {
                    sortButtonColor = LIGHTGRAY;
                }


                if (CheckCollisionPointRec(mousePoint, (Rectangle){inputField_insert.x, inputField_insert.y - 20, inputField_insert.width, 24})) {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        inputFieldActive_insert = true;
                    }
                } else {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        inputFieldActive_insert = false;
                    }
                }

                if (inputFieldActive_insert) {
                    int key = GetCharPressed();
                    while (key > 0) {
                        if ((key >= 32) && (key <= 125) && (letterCount_insert < 19)) {
                            if (isdigit(key)) { // Check if key is a digit
                                inputText_insert[letterCount_insert] = (char)key;
                                letterCount_insert++;
                            }
                        }

                        key = GetCharPressed();
                    }

                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        if (letterCount_insert > 0) {
                            letterCount_insert--;
                            inputText_insert[letterCount_insert] = '\0';
                        }
                    }

                    framesCounter_insert++;
                }

                

                

                // Handle new value insertion
                if (inputFieldActive_insert && IsKeyPressed(KEY_ENTER)) {
                    ConvertCharArrayToIntArray(arrayValues, intArray, arraySize);
                    int newValue = atoi(inputText_insert); // Convert input to integer

                    if (IsArraySorted(intArray, arraySize)) {
                        InsertIntoSortedArray(intArray, &arraySize, newValue);
                    } else {
                        InsertAtEnd(intArray, &arraySize, newValue);
                    }

                    display_flag = true;
                }
                break;
            case SCREEN_SEARCH:

                break;
            case SCREEN_DELETE:

                break;
            case SCREEN_SORT:

                break;
        }
        // Start Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (currentScreen) {
                case SCREEN_MAIN:
                    ClearBackground(RAYWHITE);
                    //// Drawing logic for main screen screen

                    DrawText("Welcome to our app", screenWidth / 2 - MeasureText("Welcome to our app", 40) / 2, 50, 40, primaryColor);
                    DrawText("Enter the size of your array:", textX, textY, 20, primaryColor);
                    
                    // Check if all values in the array have been entered
                    bool allValuesEntered = true;
                    for (int i = 0; i < arraySize; i++) {
                        if (strlen(arrayValues[i]) == 0) {
                            allValuesEntered = false;
                            break;
                        }
                    }

                    if( arraySize == 0){allValuesEntered = false;}

                    // Only display buttons when all values in the array are entered
                    if(allValuesEntered){
                    DrawRectangleRec(insertButton, insertButtonColor);
                    DrawText("Insert", insertButton.x + 10, insertButton.y + 10, 20, WHITE);

                    DrawRectangleRec(deleteButton, deleteButtonColor);
                    DrawText("Delete", deleteButton.x + 10, deleteButton.y + 10, 20, WHITE);

                    DrawRectangleRec(searchButton, searchButtonColor);
                    DrawText("Search", searchButton.x + 10, searchButton.y + 10, 20, WHITE);

                    DrawRectangleRec(sortButton, sortButtonColor);
                    DrawText("Sort", sortButton.x + 10, sortButton.y + 10, 20, WHITE);}


                    // Draw bottom line of input field
                    DrawLineEx((Vector2){inputField.x, inputField.y}, (Vector2){inputField.x + inputField.width, inputField.y}, 2, primaryColor);

                    // Draw the input text
                    if (letterCount < 20 ) {
                        DrawText(inputText, textX + 325, textY  - 5, 20, inputTextColor); // Adjusted for alignment
                    }

                    // Draw blinking cursor
                    if (inputFieldActive && ((framesCounter / 20) % 2 == 0) ) {
                        DrawRectangle(textX + 325 + MeasureText(inputText, 20), textY  - 5, 2, 20, inputTextColor);
                    }

                    // Draw array input boxes
                    if (arraySize > 0) {
                        DrawText("Enter array values:", textX, textY + 100, 20, DARKBLUE);
                        int line = 0;
                        for (int i = 0; i < arraySize; i++) {
                            // Calculate position with line breaks
                            int x = textX + (i % maxElementsPerLine) * (arrayBoxWidth + arrayBoxSpacing);
                            int y = textY + 140 + line * (arrayBoxHeight + arrayBoxSpacing);

                            Rectangle arrayBox = {x, y, arrayBoxWidth, arrayBoxHeight};
                            DrawRectangleRec(arrayBox, LIGHTGRAY);
                            DrawText(arrayValues[i], arrayBox.x + 5, arrayBox.y + 5, 20, DARKGRAY);

                            if (CheckCollisionPointRec(GetMousePosition(), arrayBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                activeArrayInput = i;
                            }

                            if ((i + 1) % maxElementsPerLine == 0) {
                                line++; // Move to next line after reaching max elements
                            }
                        }
                    }
                    // Draw cursor in the active array input cell (with blinking)
                    if (activeArrayInput != -1 && arrayInputActive && ((framesCounter2 / 20) % 2 == 0) ) {
                        int x = textX + (activeArrayInput % maxElementsPerLine) * (arrayBoxWidth + arrayBoxSpacing);
                        int y = textY + 140 + (activeArrayInput / maxElementsPerLine) * (arrayBoxHeight + arrayBoxSpacing);
                        DrawRectangle(x + 5 + strlen(arrayValues[activeArrayInput]) * 15, y + 5, 2, 20, DARKGRAY);
                    }


                    // Handle input for active array element
                    if (arrayInputActive) {
                        int key = GetCharPressed();
                        while (key > 0) {
                            if ((key >= 48 && key <= 57) && (strlen(arrayValues[activeArrayInput]) < 19)) {
                                int len = strlen(arrayValues[activeArrayInput]);
                                arrayValues[activeArrayInput][len] = (char)key;
                                arrayValues[activeArrayInput][len + 1] = '\0';
                            }
                            key = GetCharPressed();
                        }

                        // Handle Backspace key
                        if (IsKeyPressed(KEY_BACKSPACE)) {
                            int len = strlen(arrayValues[activeArrayInput]);
                            if (len > 0) {
                                arrayValues[activeArrayInput][len - 1] = '\0'; // Delete the last character
                            }
                        }
                        
                        // Handle Tab key to move to the next cell
                        if (IsKeyPressed(KEY_TAB)) {
                            activeArrayInput++; // Move to the next input cell
                            if (activeArrayInput >= arraySize) {
                                activeArrayInput = 0; // Wrap around to the first cell if at the end
                            }
                        }
                        framesCounter2++;
                    }
                    break;


            }


            

        EndDrawing();
        // End Drawing
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
