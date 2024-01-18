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

void game_start();

player_t *create_player();

void init_rooms(room_t *rooms[MAX_ROOMS]);

room_t * create_room(int id, char *name, const char map[ROOM_SIZE][ROOM_SIZE]);

int game_loop(player_t *player, room_t *rooms[MAX_ROOMS]);

void print_room(room_t *room, player_t *player);

void user_input(player_t *player, room_t *rooms[MAX_ROOMS]);

bool can_move(player_t *player, room_t *room, int x, int y);

void change_room(player_t *player, char room_number);

void textcolor (int color);
