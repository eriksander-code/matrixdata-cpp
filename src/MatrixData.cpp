#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>

//////////////////////////////////
// GLOBAL CONSTANTS AND VARIABLES

constexpr int MAP_SIZE_X = 20;
constexpr int MAP_SIZE_Y = 20;
constexpr int MAP_LAST_POSITION_X = MAP_SIZE_X-1;
constexpr int MAP_LAST_POSITION_Y = MAP_SIZE_Y-1;

//////////////////////////////////
// STRUCTS AND CLASSES

struct Cell {
    std::string description;
    char symbol;
    bool known;
};

struct GameData {
    std::stringstream left, right, front, here, back, pov;
};

class Player {
    private:
        int x;
        int y;
        char pov[3];
        GameData gd;
    
    public:
        char _key;
        Player(int _x, int _y, char __key);
        void AnalysisUpdate(Cell DataMap[MAP_SIZE_X][MAP_SIZE_Y]);
        void AnalysisDraw();
        void Clear();
        void Walk();
        int GetPlayerX();
        int GetPlayerY();
        void GetUserInput();
};

int Player::GetPlayerX() { return x; };
int Player::GetPlayerY() { return y; };
void Player::GetUserInput() { _key = toupper(_getch()); };

Player::Player(int _x, int _y, char __key) { 
    _key = __key;
    x = _x; 
    y = _y;
};

void Player::Clear() {
    gd.left.str("");
    gd.left.clear();

    gd.right.str("");
    gd.right.clear();

    gd.front.str("");
    gd.front.clear();

    gd.here.str("");
    gd.here.clear();

    gd.back.str("");
    gd.back.clear();

    gd.pov.str("");
    gd.pov.clear();
}

void Player::AnalysisUpdate(Cell DataMap[MAP_SIZE_X][MAP_SIZE_Y]) {
    pov[0] = '.';
    pov[1] = '.';
    pov[2] = '.';
        
    gd.here << "Aqui....: " << DataMap[y][x].description << std::endl;
    
    if (x > 0) {
        gd.left << "Esquerda: " << DataMap[y][x-1].description << std::endl;
        pov[0] = DataMap[y][x-1].symbol;
    }
    
    if (x < MAP_LAST_POSITION_X) {
        gd.right << "Direita.: " << DataMap[y][x+1].description << std::endl;
        pov[2] = DataMap[y][x+1].symbol;
    }
    
    if (y > 0) {
        gd.front << "Frente..: " << DataMap[y-1][x].description << std::endl;
        pov[1] = DataMap[y-1][x].symbol;
    }
    
    if (y < MAP_LAST_POSITION_Y)
    gd.back << "Atras...: " << DataMap[y+1][x].description << std::endl;
    
    gd.pov << pov[0] << pov[0] << pov[1] << pov[2] << pov[2] << std::endl;
}

void Player::AnalysisDraw() {
   std::cout << gd.left.str() << std::endl;
   std::cout << gd.right.str() << std::endl;
   std::cout << gd.front.str() << std::endl;
   std::cout << gd.here.str() << std::endl;
   std::cout << gd.back.str() << std::endl;
   std::cout << gd.pov.str() << std::endl;
   std::cout << gd.pov.str() << std::endl;
}

void Player::Walk() {
    if (_key == 'W') {
        if (y >= 2)
        y--;
    }
    if (_key == 'S') {
        if (y <= 17)
        y++;
    }
    if (_key == 'A') {
        if (x >= 2)
        x--;
    }
    if (_key == 'D') {
        if (x <= 17)
        x++;
    }
}

class Level {
    private:
        char map[20][20];
    
    public:
        Cell DataMap[20][20];
    
        Level();
        ~Level();
        void PrintMap();
        void FillMap(int player_x, int player_y);
        void FillDataMap();
};

Level::~Level() 
{
}

Level::Level() {
    
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++) {
            map[i][j] = '.';
            DataMap[i][j].description = "Just an empty block";
            DataMap[i][j].symbol = '.';
            
            if (i == 12) { 
                DataMap[i][j].description = "A BLOCK!";
                DataMap[i][j].symbol = '$';
            }
            if (j == 17) { 
                DataMap[i][j].description = "WHAT IS THAT?";
                DataMap[i][j].symbol = '?';
            }
            
            if (i == 0) { 
                DataMap[i][j].description = "A WALL!"; 
                DataMap[i][j].symbol = '|';
            }
            if (i == 19) { 
                DataMap[i][j].description = "A WALL!"; 
                DataMap[i][j].symbol = '|';
            }
            if (j == 0) { 
                DataMap[i][j].description = "A WALL!"; 
                DataMap[i][j].symbol = '|';
            }
            if (j == 19) { 
            DataMap[i][j].description = "A WALL!"; 
                DataMap[i][j].symbol = '|';
            }
        }
    }    
}

void Level::PrintMap() {
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++) {
            std::cout << map[i][j];;
            if ((j < 19) && ((i == 0) || (i == 19))) {
                std::cout << "-";
            }
            else {
                std::cout << " ";
            }
            
        }
        std::cout << "\n";
    }
}

void Level::FillMap(int player_x, int player_y) {
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++) {
            map[i][j] = '.';
            
            if (i == 0) { map[i][j] = '-';}
            if (i == 19) { map[i][j] = '-';}
            if (j == 0) { map[i][j] = '|';}
            if (j == 19) { map[i][j] = '|';}
            if ((j == player_x) && (i == player_y)) { map[i][j] = '@';}
        }
    }
}


int main() {
    Player player(7,5,' ');
    Level level;
    
    while (player._key != 27) {

        player.GetUserInput();
        player.Walk();

        player.AnalysisUpdate(level.DataMap);
        player.AnalysisDraw();
        
        level.FillMap(player.GetPlayerX(), player.GetPlayerY());
        level.PrintMap();
        
        player.Clear();

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif    
        
    }

    return 0;
}