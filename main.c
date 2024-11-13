#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define CNFG_IMPLEMENTATION
#include "rawdraw_sf.h"

void HandleKey( int keycode, int bDown ) { }
void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
int HandleDestroy() { return 0; }

int inventory[15];

void drawGUIRow(int x, int y, int length, int* firstitem, int selecteditem) {
    int isselected;
    selecteditem = length - selecteditem;
    while(length != 0) {
        //
    }
}

void drawInventory() {
    CNFGColor(0x00000000);
    CNFGTackRectangle(152, 0, 608, 504);

    CNFGColor(0xffffffff);
    CNFGTackRectangle(160, 0, 600, 504);

//drawInventoryOnlyInventoryPart
    CNFGColor(0x00000000);
    CNFGTackRectangle(152, 232, 608, 504);

    CNFGColor(0xffffffff);
    CNFGTackRectangle(160, 232, 600, 504);
}

int main() {
    CNFGSetup("smallminecraft", 768, 512); // 96 * 8, 64 * 8
    while(CNFGHandleInput()) {
        CNFGBGColor = 0x00000000;

        short w;
        short h;
        CNFGClearFrame();
        CNFGGetDimensions(&w, &h);
    }
}
