#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define CNFG_IMPLEMENTATION
#include "rawdraw_sf.h"

void HandleKey( int keycode, int bDown ) { }
void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
int HandleDestroy() { return 0; }

uint32_t inventory[15];
uint32_t inventorySlot;

void drawItem(uint32_t x, uint32_t y, uint32_t item, uint32_t isselected) {
    uint32_t x1 = x;
    uint32_t y1 = y;
    uint32_t x2 = x + 72;
    uint32_t y2 = y + 72;
    x += 8;
    y += 8;

    if(!isselected) {
        CNFGColor(0xffffffff);
        CNFGTackRectangle(x1, y1, x2, y2);

        x1 = x;
        y1 = y;
        x2 = x + 56;
        y2 = y + 56;
    }

    CNFGColor(0x00000000);
    CNFGTackRectangle(x1, y1, x2, y2);

    if(!item) {
        return;
    }

    if(item > 0xF0) { // Stackable item
        uint32_t textureid = item >> 4;
        textureid += 0x40;
        // Get some kind of texture based on this ID and draw it

        item &= 0x0F;
        item += 0x20;
        x1 = x + 16;
        y1 = y + 16;

        // Draw another texture using `item` as the ID
        item += 0x10;
        // Same thing but an inverted texture.
    } else { // Nonstackable item
        uint32_t textureid = item >> 4;
        textureid += 0x50;
    }

    return;
}

void drawGUIRow(uint32_t x, uint32_t y, uint32_t length, uint32_t* items, uint32_t selecteditem) {
    uint32_t isselected = 0;
    selecteditem = length - selecteditem;
    uint32_t ind = 0;
    while(length != 0) {
        isselected = length - selecteditem;
        drawItem(x, y, items[ind], isselected);
        x += 88;
        ind++;
        length--;
    }
    return;
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

    drawGUIRow(168, 424, 5, inventory, inventorySlot);

    drawGUIRow(168, 328, 5, &inventory[5], inventorySlot - 5);

    drawGUIRow(168, 328, 5, &inventory[5], inventorySlot - 10);
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
