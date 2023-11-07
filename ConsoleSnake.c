#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define OUTPUT_SIZE 10
#define EMPTY_FIELD_IMAGE '.'
#define FOOD_IMAGE '*'
#define SNAKE_IMAGE '+'
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int reverse_direction(int direction)
{
    switch (direction)
    {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    default:
        return 0;
    }
}

void init_snake(char output[OUTPUT_SIZE][OUTPUT_SIZE])
{
    output[OUTPUT_SIZE / 2][OUTPUT_SIZE / 2] = SNAKE_IMAGE;
}

void init_output(char output[OUTPUT_SIZE][OUTPUT_SIZE])
{
    srand(time(NULL));
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        for (int j = 0; j < OUTPUT_SIZE; j++)
        {
            output[i][j] = EMPTY_FIELD_IMAGE;
        }
    }
}

void print_output(char output[OUTPUT_SIZE][OUTPUT_SIZE], int score)
{
    system("cls");
    printf("SNAKE - MSABOU\n");
    printf("SCORE : %d\n", score);

    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        for (int j = 0; j < OUTPUT_SIZE; j++)
        {
            printf("%c", output[i][j]);
        }
        printf("\n");
    }
    printf("\n\nTo start the game press the arrows.\n");
    printf("To quit press \"q\"\n");
    printf("The goal of this game is to get to level 50!\nWhen you get near level 50 the snake will reach a speed that affects the multiverse,\nyou will have halucinations\n");
    printf("Moise Daniel Sabou crafted this game on November 7th, 2023.");
}

void add_food(char output[OUTPUT_SIZE][OUTPUT_SIZE])
{
    int x = 0;
    int y = 0;
    do
    {
        x = rand() % OUTPUT_SIZE;
        y = rand() % OUTPUT_SIZE;

    } while (output[x][y] != EMPTY_FIELD_IMAGE);
    output[x][y] = FOOD_IMAGE;
}

void move_snake_coordinates(char output[OUTPUT_SIZE][OUTPUT_SIZE], int x, int y, int* score, int* time_for_move)
{
    if (x >= 0 && y >= 0 &&
        x < OUTPUT_SIZE && y < OUTPUT_SIZE)
    {

        if (output[x][y] == FOOD_IMAGE)
        {
            (*score)++;
            add_food(output);
        }
        output[x][y] = SNAKE_IMAGE;
        if (*score == 10)
        {
            *time_for_move = 250;
        }
        if (*score == 20)
        {
            *time_for_move = 125;
        }
        if (*score == 30)
        {
            *time_for_move = 62;
        }
        if (*score == 40)
        {
            *time_for_move = 31;
        }
        if (*score == 50)
        {
            *time_for_move = 15;
        }
        if (*score == 60)
        {
            *time_for_move = 7;
        }
        if (*score == 70)
        {
            *time_for_move = 3;
        }
        if (*score == 80)
        {
            *time_for_move = 1;
        }
    }
    else
    {
        if (x < 0)
        {
            move_snake_coordinates(output, OUTPUT_SIZE - 1, y, score, time_for_move);
        }
        else if (y < 0)
        {
            move_snake_coordinates(output, x, OUTPUT_SIZE - 1, score, time_for_move);
        }
        else if (x >= OUTPUT_SIZE)
        {
            move_snake_coordinates(output, 0, y, score, time_for_move);
        }
        else if (y >= OUTPUT_SIZE)
        {
            move_snake_coordinates(output, x, 0, score, time_for_move);
        }
    }
}

void move_snake(char output[OUTPUT_SIZE][OUTPUT_SIZE], int direction, int* score, int* time_for_move)
{
    if (direction != 0)
    {
        for (int i = 0; i < OUTPUT_SIZE; i++)
        {
            for (int j = 0; j < OUTPUT_SIZE; j++)
            {
                if (output[i][j] == SNAKE_IMAGE)
                {
                    output[i][j] = EMPTY_FIELD_IMAGE;
                    switch (direction)
                    {
                    case UP:
                        move_snake_coordinates(output, i - 1, j, score, time_for_move);
                        return;
                    case DOWN:
                        move_snake_coordinates(output, i + 1, j, score, time_for_move);
                        return;
                    case LEFT:
                        move_snake_coordinates(output, i, j - 1, score, time_for_move);
                        return;
                    case RIGHT:
                        move_snake_coordinates(output, i, j + 1, score, time_for_move);
                        return;
                    default:
                        return;
                    }
                }
            }
        }
    }
}

int main()
{
    char output[OUTPUT_SIZE][OUTPUT_SIZE] = { 0 };
    int direction = 0;
    int snake_size = 0;
    unsigned char user_input = 0;
    clock_t time, previous_time;
    int score = 0;
    int time_for_move = 500;

    init_output(output);
    init_snake(output);
    add_food(output);
    print_output(output, score);

    previous_time = clock();
    while (user_input != 'q')
    {
        time = clock();
        if (time - previous_time > time_for_move)
        {
            move_snake(output, direction, &score, &time_for_move);
            print_output(output, score);
            previous_time = clock();
        }
        if (_kbhit())
        {
            user_input = _getch();
            if (user_input == UP ||
                user_input == DOWN ||
                user_input == LEFT ||
                user_input == RIGHT)
            {
                if (user_input != 10000000)//reverse_direction(direction))
                {
                    direction = user_input;
                }
            }
        }
    }

    system("cls");
    printf("END_GAME\n");

    return 0;
}
