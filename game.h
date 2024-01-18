#define MAX_ROOMS 7
#define ROOM_SIZE 7

typedef struct room {
    int id;
    char name[32];
    char map[7][7];
    bool isVisited;
}room_t;

typedef struct player {
    char name[32];
    int room;
    int pos_x;
    int pos_y;
    int health;
    int attack;
}player_t;

void game_presentation();

player_t *create_player();

void init_rooms(room_t *rooms[MAX_ROOMS]);

room_t * create_room(int id, char *name, const char map[ROOM_SIZE][ROOM_SIZE]);

void print_room(room_t *room, player_t *player);