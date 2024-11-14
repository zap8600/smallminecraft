#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define CNFG_IMPLEMENTATION
#include "rawdraw_sf.h"

bool ininventory;
int movement;

void HandleKey( int keycode, int bDown ) {
    if(keycode == 0x65 && bDown) {
        ininventory = !ininventory;
    } else if(bDown) {
        switch(keycode) {
            case 0x77: movement = 1; break;
            case 0x61: movement = 2; break;
            case 0x73: movement = 3; break;
            case 0x64: movement = 4; break;
            default: break;
        }
    }
}

void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
int HandleDestroy() { return 0; }

uint32_t inventory[15];
uint32_t inventorySlot;

uint32_t craftingGrid[9];
uint32_t craftingOutput;

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

    drawGUIRow(168, 240, 5, &inventory[10], inventorySlot - 10);
}

uint32_t addItemToInventory(uint32_t item) {
    uint32_t ind = 0; 
    uint32_t newItemId = item & 0xF0;
    if(newItemId != 0xF0) {
        while(ind < 15) {
            uint32_t itemId = inventory[ind] & 0xF0;
            if(itemId == newItemId) {
                uint32_t sumItemCount = (item & 0x0F) + (inventory[ind] & 0x0F);
                if(sumItemCount > 16) {
                    inventory[ind] = itemId + sumItemCount;
                    return 0;
                } else {
                    inventory[ind] |= 15;
                    newItemId += sumItemCount;
                }
            }
            ind++;
        }
    }
    ind = 0;
    while(ind < 15) {
        uint32_t itemId = inventory[ind]; 
        if(!itemId) {
            inventory[ind] = item;
            return 0;
        }
        if((item > 0xF0) && (newItemId == (itemId &= 0xF0))) {
            uint32_t sumItemCount = (item & 0x0F) + (item & 0x0F);
            if(sumItemCount > 16) {
                inventory[ind] = itemId + sumItemCount;
                return 0;
            } else {
                inventory[ind] |= 15;
                return 0;
            }
        }
        ind++;
    }
    return 1;
}

void drawItemInGrid(uint32_t x, uint32_t y, uint32_t item) {
    x += 8;
    y += 8;
    uint32_t x1 = x;
    uint32_t y1 = y;
    uint32_t x2 = x + 56;
    uint32_t y2 = y + 56;

    CNFGColor(0x00000000);
    CNFGTackRectangle(x1, y1, x2, y2);

    if(!item) {
        // Draw empty texture
        return;
    }

    if(item > 0xF0) {
        // Draw stackable item

        item &= 0x0F;
        // Add number texture
        x += 8;
        y += 8;
        // Draw textures
        return;
    }

    // Draw item texture
}

void drawGUIRowInGrid(uint32_t x, uint32_t y, uint32_t length, uint32_t* items) {
    uint32_t ind = 0;
    while(length != 0) {
        drawItemInGrid(x, y, items[ind]);
        x += 72;
        ind++;
        length--;
    }
}

void reset2x2CraftingGrid() {
    uint32_t ind = 0;
    while(ind < 9) {
        addItemToInventory(craftingGrid[ind]);
        craftingGrid[ind] = 0;
        ind++;
    }

    CNFGColor(0x00000000);
    CNFGTackRectangle(208, 72, 352, 216);

    drawGUIRowInGrid(208, 72, 2, craftingGrid);

    drawGUIRowInGrid(208, 144, 2, craftingGrid);

    drawItem(480, 112, 0, 1);
    drawItemInGrid(480, 112, 0);
}

void loadInventoryGUI() {
    drawInventory();

    reset2x2CraftingGrid();

    // Draw "INVENTORY"

    // Draw arrow

    //
}

int main() {
    CNFGSetup("smallminecraft", 768, 512); // 96 * 8, 64 * 8
    while(CNFGHandleInput()) {
        CNFGBGColor = 0x00000000;

        short w;
        short h;
        CNFGClearFrame();
        CNFGGetDimensions(&w, &h);

        if(ininventory) {
            loadInventoryGUI();
            if(movement) {
                switch(movement) {
                    case 1: inventorySlot += 5; break;
                    case 2: inventorySlot -= 1; break;
                    case 3: inventorySlot -= 5; break;
                    case 4: inventorySlot += 1; break;
                }
                movement = 0;
            }
        }

        CNFGSwapBuffers();
    }
}
