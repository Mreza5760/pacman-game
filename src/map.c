#include "map.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

const char map[3][Row][Col] = {
   {
        "#########################",
        "#                       #",
        "#  #######   #######    #",
        "#  #     #   #     #    #",
        "#  # ### ## ## ### #    #",
        "#  # #           # #    #",
        "#  # #########   # #    #",
        "#  #             # #    #",
        "#  ####### ##    # #    #",
        "#           #    #      #",
        "#   ####### #  ######   #",
        "#   #                 # #",
        "#   #   ## ########   # #",
        "#   #   #         #   # #",
        "#   #####   P     ##### #",
        "#                       #",
        "######  ####    #########",
        "#                       #",
        "#########################"
    },
    { 
        "#########################",
        "#   ####           #### #",
        "#   #                 # #",
        "#   #  # # ###     # ## #",
        "#   #        #          #",
        "#   ######## #     #    #",
        "#            #     #    #",
        "#   ##########     ######",
        "#       P               #",
        "### ######  #####     ###",
        "#   ###                 #",
        "#   #     ####   ####   #",
        "#   ##   #       #      #",
        "#         #####  #      #",
        "#                ########",
        "# #####   ####          #",
        "#       #        ########",
        "#  ###   #####   #      #",
        "#########################"
    },
    {
        "#########################",
        "#   ####           #### #",
        "#      #              # #",
        "#   #  #######     # ## #",
        "#   #        #     #    #",
        "#   ###  ### #          #",
        "#            #     #    #",
        "#   ##########     ## ###",
        "#                       #",
        "#####   #########     ###",
        "#   ###                 #",
        "#   #     ####   ####   #",
        "#   ##               # ##",
        "#       P  #####        #",
        "#                ########",
        "# #####  #####          #",
        "#       #        ########",
        "#  ###      ##   #      #",
        "#########################",
    }
};

int randomMap() {
    srand(time(0));
    return rand()%3;
}

void DrawMap(int x) {
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            if (map[x][i][j] == '#') 
                DrawRectangle(j*32, i*32, 32, 32, DARKGRAY);
            else if (map[x][i][j] == 'P')
                DrawRectangle(j*32, i*32, 32, 32, YELLOW);
        }
    }
}