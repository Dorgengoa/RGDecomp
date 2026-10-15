/* PARKED s17b: m2c fails outright ("jr instruction... jump table is not
   provided"). Not attempted by hand -- throughput budget spent on smaller
   units in this lane. Needs a manual jump-table read from
   asm/matchings/main/MenuOptionLoadValue_350240.s starting at line 21. */
/* s49m: MATCH jtbl rodata_check */
#include "types.h"

extern u8 *GetGameData_1fede0(void);

void MenuOptionLoadValue_350240(u8 *self)
{
    u8 *g;
    s32 x;

    g = GetGameData_1fede0();
    switch (*(s16 *)(self + 0x12)) {
    case 0:
        x = (*(s16 *)(*(u8 **)(g + 0xC) + 0x1A) & 1);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 1:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x22);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 2:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x12);
        if (x == 0) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 1) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 3:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x26);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 4:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x2A);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 5:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x28);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 6:
        x = (*(s16 *)(*(u8 **)(g + 0xC) + 0x1A) & 2);
        if (x == 0) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 2) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 7:
        x = (*(s16 *)(*(u8 **)(g + 0xC) + 0x1A) & 4);
        if (x == 0) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 4) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 8:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x2C);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    case 9:
        x = *(s16 *)(*(u8 **)(g + 0xC) + 0x20);
        if (x == 1) {
            *(s16 *)(self + 0x10) = 0;
        } else if (x == 0) {
            *(s16 *)(self + 0x10) = 1;
        }
        break;
    }
}
