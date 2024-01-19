#define MAX_ROOMS 7
#define ROOM_SIZE 7

typedef struct room {
    int id;
    char name[32];
    char description[256];
    char map[7][7];
}room_t;

typedef struct player {
    char name[32];
    int room;
    int gold;
    int pos_x;
    int pos_y;
    int health;
    int attack;
}player_t;

/*
    Presentation of the game to the player
*/
void game_presentation();

/*
    Initialize the game and launch the game loop
*/
void game_start();

/*
    Create a new player and ask for his name
*/
player_t *create_player();

/*
    Initialize the rooms of the game
    input: rooms[MAX_ROOMS] - array of rooms
*/
void init_rooms(room_t *rooms[MAX_ROOMS]);

/*
    Create a new room
    input: id - id of the room
           name - name of the room
           map - map of the room
           description - description of the room
*/
room_t * create_room(int id, const char *name, const char map[ROOM_SIZE][ROOM_SIZE], const char *description);

/*
    Infinite loop of the game
    input: player - player of the game
           rooms[MAX_ROOMS] - array of rooms
*/
int game_loop(player_t *player, room_t *rooms[MAX_ROOMS]);

/*
    Display the map of the current room
    input: room - current room
           player - player of the game
*/
void print_room(room_t *room, player_t *player);

/*
    Handle the user input
    input: player - player of the game
           rooms[MAX_ROOMS] - array of rooms
*/
void user_input(player_t *player, room_t *rooms[MAX_ROOMS]);

/*
    Check if the player can move to the given position and do some actions
    input: player - player of the game
           room - current room
           x - x next position
           y - y next position
*/
bool can_move(player_t *player, room_t *room, int x, int y);

/*
    Move the player to another room
    input: player - player of the game
           room_number - number of the room
*/
void change_room(player_t *player, char room_number);

/*
    Change the color of the text
    input: color - color code
*/
void textcolor (int color);

/*
    Change the color of the room
    input: room_number - number of the room
*/
int room_color(int room_number);

/*
    Check if the player is dead
    input: player - player of the game
*/
bool is_dead(player_t *player);

/*
    Save the game
    input: player - player of the game
           rooms[MAX_ROOMS] - array of rooms
*/
int save_game(player_t *player, room_t *rooms[MAX_ROOMS]);

/*
    Load the game
    input: player - player of the game
           rooms[MAX_ROOMS] - array of rooms
*/
int load_game(player_t *player, room_t *rooms[MAX_ROOMS]);