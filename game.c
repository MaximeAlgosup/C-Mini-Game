/* This file contains the implementation of the game functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include "game.h"

// Constants for player
#define BASE_HEALTH 20
#define BASE_ATTACK 10
#define BASE_ROOM 0
#define BASE_GOLD 0
#define BASE_POS_X 3
#define BASE_POS_Y 3

// Constants for game
#define KEYBOARD_DELAY 100
#define CHEST '$'
#define ESC '?'
#define FOOD 'F'
#define MOB '+'

// Constants for display
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define PURPLE 5
#define CYAN 6
#define WHITE 7


const char room_map_0[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '1', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'1', '.', '.', '.', '.', '.', '2'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '3', '#', '#', '#'}
};

const char room_map_1[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '4', '#', '#', '#'},
    {'#', FOOD, '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '.', '#'},
    {'0', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', MOB, CHEST, '#'},
    {'#', '#', '#', '0', '#', '#', '#'}
};

const char room_map_2[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '.', '#'},
    {'0', '.', '#', '.', '#', FOOD, '#'},
    {'#', MOB, '#', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_3[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '0', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '#', '.', '4'},
    {'#', '.', '.', MOB, '.', '.', '#'},
    {'#', MOB, '.', '.', '.', MOB, '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_4[ROOM_SIZE][ROOM_SIZE] = {
    {'X', 'v', 'v', '1', 'v', 'v', 'X'},
    {'>', '.', '>', '.', '<', CHEST, '<'},
    {'>', MOB, '>', '.', '<', '.', '<'},
    {'3', '.', '.', '.', '<', '.', '5'},
    {'>', '^', '.', '.', '.', '.', '<'},
    {'>', CHEST, '>', '.', '.', MOB, '<'},
    {'X', '^', '^', '^', '^', '^', 'X'}
};

const char room_map_5[ROOM_SIZE][ROOM_SIZE] = {
    {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'O', CHEST, '.', '.', 'o', '.', 'O'},
    {'O', 'o', MOB, 'O', '.', MOB, 'O'},
    {'4', '.', '.', '.', '.', '.', 'O'},
    {'O', '.', 'o', 'o', '.', MOB, 'O'},
    {'O', '.', 'O', '.', '.', '.', 'O'},
    {'O', 'O', 'O', '6', 'O', 'O', 'O'}
};

const char room_map_6[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '_', '_', '5', '_', '_', '#'},
    {'|', '.', '.', '.', '.', '.', '|'},
    {'|', CHEST, MOB, '.', MOB, CHEST, '|'},
    {'|', '.', '.', '.', '.', '.', '|'},
    {'|', '.', '.', MOB, '.', '.', '|'},
    {'|', '.', MOB, ESC, MOB, '.', '|'},
    {'#', '_', '_', '_', '_', '_', '#'}
};


int main(){
    system("cls");
    game_start();
    exit(EXIT_SUCCESS);
}

void game_presentation(){
    textcolor(RED);
    printf("  ____        _   _                                      \n");
    printf(" |  _ \\ _   _| |_| |__   __ _  __ _  ___  _ __ __ _ ___ \n");
    printf(" | |_) | | | | __| '_ \\ / _` |/ _` |/ _ \\| '__/ _` / __|\n");
    printf(" |  __/| |_| | |_| | | | (_| | (_| | (_) | | | (_| \\__ \\\n");
    printf(" |_|    \\__, |\\__|_| |_|\\__,_|\\__, |\\___/|_|  \\__,_|___/\n");
    printf("        |___/                 |___/                     \n");
    printf("\n");
    textcolor(WHITE);
    printf("You are in a dark room. You can't see anything.\n");
    printf("You have to find the exit of the dungeon.\n");
    printf("You can move with the keys 'w', 'a', 's', 'd'.\n");
    printf("Player is represented by '@'.\n");
    printf("You can save your game by pressing 'p'.\n");
    printf("Good luck!\n");
}

void game_start(){
    textcolor(WHITE);
    game_presentation();
    player_t *player = malloc(sizeof(player_t));
    room_t *rooms[MAX_ROOMS];
    init_rooms(rooms);

    // try to load existing game
    FILE *fp;
    fp = fopen("save.txt", "r");
    if(fp == NULL){
        player = create_player();
        printf("No save file found. Starting new game...\n");
        if (player == NULL){
            printf("Error creating player\n");
            exit(EXIT_FAILURE);
        };
    }
    else{
        printf("Save file found. Loading game...\n");
        load_game(player, rooms);
    }
    printf("Game loaded!\n");
    fclose(fp);
    game_loop(player, rooms);
}

player_t *create_player(){
    player_t *player = malloc(sizeof(player_t));
    if(player == NULL){
        printf("Error allocating memory for player\n");
        exit(EXIT_FAILURE);
    }

    do{
        printf("Enter your name: ");
        scanf("%s", player->name);
        if(strlen(player->name) > 32){
            printf("Name too long\n");
        }
    }while(strlen(player->name) > 32);      
    player->room = BASE_ROOM;
    player->pos_x = BASE_POS_X;
    player->pos_y = BASE_POS_Y;
    player->gold = BASE_GOLD;
    player->health = BASE_HEALTH;
    player->attack = BASE_ATTACK;

    return player;
}

void init_rooms(room_t *rooms[MAX_ROOMS]){
    printf("Initializing rooms...\n");
    if(rooms == NULL){
        printf("Error allocating memory for rooms\n");
        exit(EXIT_FAILURE);
    }

    rooms[0] = create_room(0, "Entrance", room_map_0, "You are in the entrance of the dungeon. There are doors in front of you. Choose one.");
    rooms[1] = create_room(1, "Kitchen", room_map_1, "You are in the kitchen. Only women are allowed in this room.");
    rooms[2] = create_room(2, "Cellar", room_map_2, "You are in the cellar. Try to find some food.");
    rooms[3] = create_room(3, "Mob Room", room_map_3, "You are in the mob room. There are some monsters here. Be careful!");
    rooms[4] = create_room(4, "Coral Cave", room_map_4, "You are in the coral cave. There are some chests here. Try to open them.");
    rooms[5] = create_room(5, "Bubble Area", room_map_5, "You are in the bubble area.");
    rooms[6] = create_room(6, "Final Room", room_map_6, "You are almost at the end courage.");
}

room_t *create_room(int id, const char *name,const char map[ROOM_SIZE][ROOM_SIZE], const char *description){
    room_t *room = malloc(sizeof(room_t));
    if(room == NULL){
        printf("Error allocating memory for room %d\n", id);
        exit(EXIT_FAILURE);
    }

    room->id = id;
    strcpy(room->name, name);
    memcpy(room->map, map, sizeof(room->map));\
    strcpy(room->description, description);
    return room;
}

int game_loop(player_t *player, room_t *rooms[MAX_ROOMS]){
    while (true)
    {
        print_room(rooms[player->room], player);
        user_input(player, rooms);
        sleep(0.8);
        if(is_dead(player)){
            system("cls");
            textcolor(RED);
            printf("You died!\n");
            textcolor(WHITE);
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}

void print_room(room_t *room, player_t *player){
    system("cls");
    printf("Player: %s \t Life: %d \t Golds: %d \n", player->name, player->health, player->gold);
    printf("Room: %d \t %s\n", room->id, room->name);
    for(int i = 0; i < ROOM_SIZE; i++){
        for(int j = 0; j < ROOM_SIZE; j++){
            textcolor(room_color(room->id));
            //check if player is in this position
            if(i == player->pos_x && j == player->pos_y){
                textcolor(CYAN);
                printf("@ ");
                continue;
            }
            else if(room->map[i][j] == '.' || (room->map[i][j] >= '0' && room->map[i][j] <= '7')){
                printf("  ");
                continue;
            }
            else if(room->map[i][j] == CHEST){
                textcolor(YELLOW);
                printf("%c ", room->map[i][j]);
                continue;
            }
            else if(room->map[i][j] == FOOD){
                textcolor(GREEN);
                printf("%c ", room->map[i][j]);
                continue;
            }
            else if(room->map[i][j] == MOB){
                textcolor(RED);
                printf("%c ", room->map[i][j]);
                continue;
            }
            else if(room->map[i][j] == ESC){
                textcolor(PURPLE);
                printf("%c ", room->map[i][j]);
                continue;
            }
            else{
                printf("%c ", room->map[i][j]);
                }
            
        }
        printf("\n");
    }
    textcolor(WHITE);
    printf("%s\n", room->description);
}

void user_input(player_t *player, room_t *rooms[MAX_ROOMS]){
    char input = ' ';
    clock_t start_time = clock();
    while ((clock() - start_time) < KEYBOARD_DELAY) {
        if (_kbhit()) {
            // Key pressed
            input = _getch();
            break;
        }
        sleep(0.1);
    }
    switch (input)
    {
    case 'w':
        if (can_move(player, rooms[player->room], player->pos_x - 1, player->pos_y)){
            player->pos_x--;
        }
        break;
    case 's':
        if (can_move(player, rooms[player->room], player->pos_x + 1, player->pos_y)){
            player->pos_x++;
        }
        break;
    case 'a':
        if (can_move(player, rooms[player->room], player->pos_x, player->pos_y - 1)){
            player->pos_y--;
        }
        break;
    case 'd':
        if (can_move(player, rooms[player->room], player->pos_x, player->pos_y + 1)){
            player->pos_y++;
        }
        break;
    case 'p':
        printf("Saving game...\n");
        int res = save_game(player, rooms);
        if(res == -1){
            printf("Error saving game\n");
        }
        else{
            printf("Game saved!\n");
        }
        break;
    default:
        break;
    }
}

bool can_move(player_t *player, room_t *room, int x, int y){
    if(room->map[x][y] >= '0' && room->map[x][y] <= '7'){
        change_room(player, room->map[x][y]);
        return false;
    }
    else if(room->map[x][y] == CHEST){
        player->gold += 10;
        room->map[x][y] = '.';
        return true;
    }
    else if(room->map[x][y] == FOOD){
        player->health += 10;
        room->map[x][y] = '.';
        return true;
    }
    else if(room->map[x][y] == MOB){
        player->health -= 10;
        room->map[x][y] = '.';
        return true;
    }
    else if(room->map[x][y] == ESC){
        system("cls");
        textcolor(GREEN);
        printf("Congratulations %s! You escaped from the dungeon!\n", player->name);
        textcolor(WHITE);
        exit(EXIT_SUCCESS);
    }
    else
    if(room->map[x][y] == '.'){
        return true;
    }
    else{
        return false;
    }
}

void change_room(player_t *player, char room_number){
    player->room = (int)(room_number - '0');
    player->pos_x = BASE_POS_X;
    player->pos_y = BASE_POS_Y;
}

void textcolor (int color){
    char *colorPrefix = "\033[0;30m"; // Black
    switch (color)
    {
    case 1:
        colorPrefix = "\033[0;31m"; // Red
        break;
    case 2:
        colorPrefix = "\033[0;32m"; // Green
        break;
    case 3:
        colorPrefix = "\033[0;33m"; // Yellow
        break;
    case 4:
        colorPrefix = "\033[0;34m"; // Blue
        break;
    case 5:
        colorPrefix = "\033[0;35m"; // Purple
        break;
    case 6:
        colorPrefix = "\033[0;36m"; // Cyan
        break;
    case 7:
        colorPrefix = "\033[0;37m"; // White
        break;
    default:
        break;
    }
    printf("%s", colorPrefix);
}

int room_color(int room_number){
    switch (room_number)
    {
    case 0:
        return BLUE;
        break;
    case 1:
        return BLUE;
        break;
    case 2:
        return BLUE;
        break;
    case 3:
        return RED;
        break;
    case 4:
        return PURPLE;
        break;
    case 5:
        return CYAN;
        break;
    case 6:
        return YELLOW;
        break;
    default:
        return BLACK;
    }
}

bool is_dead(player_t *player){
    if(player->health <= 0){
        return true;
    }
    else{
        return false;
    }
}

int save_game(player_t *player, room_t *rooms[MAX_ROOMS]){
    FILE *fp;
    fp = fopen("save.txt", "w");
    if(fp == NULL){
        return -1;
    }
    fprintf(fp, "%s\n", player->name);
    fprintf(fp, "%d\n", player->room);
    fprintf(fp, "%d\n", player->pos_x);
    fprintf(fp, "%d\n", player->pos_y);
    fprintf(fp, "%d\n", player->gold);
    fprintf(fp, "%d\n", player->health);
    fprintf(fp, "%d\n", player->attack);
    for(int i = 0; i < MAX_ROOMS; i++){
        for(int j = 0; j < ROOM_SIZE; j++){
            for(int k = 0; k < ROOM_SIZE; k++){
                fprintf(fp, "%c", rooms[i]->map[j][k]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    return 0;
}

int load_game(player_t *player, room_t *rooms[MAX_ROOMS]){
    FILE *fp;
    fp = fopen("save.txt", "r");
    if(fp == NULL){
        return -1;
    }
    fscanf(fp, "%s", player->name);
    fscanf(fp, "%d", &player->room);
    fscanf(fp, "%d", &player->pos_x);
    fscanf(fp, "%d", &player->pos_y);
    fscanf(fp, "%d", &player->gold);
    fscanf(fp, "%d", &player->health);
    fscanf(fp, "%d", &player->attack);
    printf("pass\n");
    for(int i = 0; i < MAX_ROOMS; i++){        
        for(int j = 0; j < ROOM_SIZE; j++){
            for(int k = 0; k < ROOM_SIZE; k++){
                char c = fgetc(fp);
                if (c == '\n'){
                    c = fgetc(fp);
                }
                rooms[i]->map[j][k] = c;
            
            }
        }
    }
    return 0;
}