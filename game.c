#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "game.h"

#define BASE_HEALTH 100
#define BASE_ATTACK 10
#define BASE_ROOM 0
#define BASE_POS_X 3
#define BASE_POS_Y 3

const char room_map_0[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_1[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_2[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_3[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_4[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_5[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

const char room_map_6[ROOM_SIZE][ROOM_SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};


int main(){


    game_presentation();

    player_t *player = create_player();

    if (player == NULL){
        printf("Error creating player\n");
        exit(EXIT_FAILURE);
    }
    // Create rooms array
    room_t *rooms[MAX_ROOMS];
    init_rooms(rooms);

    // Print initial room
    while (true)
    {
        print_room(rooms[player->room], player);
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

void game_presentation(){
    printf("Welcome to PYTHAGORE!\n");
    printf("You are in a dark room. You can't see anything.\n");
    printf("Good luck!\n");
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

    rooms[0] = create_room(0, "Entrance", room_map_0);
    rooms[1] = create_room(1, "Room 1", room_map_1);
    rooms[2] = create_room(2, "Room 2", room_map_2);
    rooms[3] = create_room(3, "Room 3", room_map_3);
    rooms[4] = create_room(4, "Room 4", room_map_4);
    rooms[5] = create_room(5, "Room 5", room_map_5);
    rooms[6] = create_room(6, "Room 6", room_map_6);
}

room_t *create_room(int id, char *name,const char map[ROOM_SIZE][ROOM_SIZE]){
    room_t *room = malloc(sizeof(room_t));
    if(room == NULL){
        printf("Error allocating memory for room %d\n", id);
        exit(EXIT_FAILURE);
    }

    room->id = id;
    strcpy(room->name, name);
    memcpy(room->map, map, sizeof(room->map));
    room->isVisited = false;

    return room;
}

void print_room(room_t *room, player_t *player){
    system("cls");
    printf("Player: %s \t Life: %d\n", player->name, player->health);
    printf("Room: %d \t %s\n", room->id, room->name);
    for(int i = 0; i < ROOM_SIZE; i++){
        for(int j = 0; j < ROOM_SIZE; j++){
            //check if player is in this position
            if(i == player->pos_x && j == player->pos_y){
                printf("P ");
                continue;
            }
            else if(room->map[i][j] == '.'){
                printf("  ");
            }
            else{
                printf("%c ", room->map[i][j]);
                }
            
        }
        printf("\n");
    }
}