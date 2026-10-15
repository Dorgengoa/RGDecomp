#include "types.h"
#pragma optimization_level 3

typedef struct {
    u8 a : 1;
    u8 b : 1;
    u8 c : 1;
    u8 rest : 5;
} Bits004821D4;

extern void ClearInBattle_288400();
extern s16 D_004821C0;
extern s16 D_004821C2;
extern s32 D_004821C4;
extern s32 D_004821C8;
extern s16 D_004821D0;
extern s16 D_004821D2;
extern Bits004821D4 D_004821D4;
extern s32 D_004821D8;
extern u8 D_004D7E00[];
extern s16 D_004D7E02[];
extern s16 D_004D7E04[];
extern s16 D_004D7E06[];
extern s16 D_004D7E08[];
extern s16 D_004D7E0A[];
extern s32 D_004D7E0C[];
extern s32 D_004D7E10[];
extern s32 D_004D7E14[];
extern s32 D_004D7E18[];
typedef struct { u8 pad[0x1C]; s32 x1C[2]; s32 x24[2]; s32 x2C[3]; s32 x38[3]; } Blk004D7E00;
#define BLK ((Blk004D7E00 *)D_004D7E00)

void GameFlowReset_285c70(void) {
    s32 i;
    s32 z;

    D_004D7E00[0] = 0;
    D_004D7E04[0] = -1;
    D_004D7E02[0] = -1;
    D_004D7E08[0] = -1;
    D_004D7E06[0] = -1;
    D_004D7E0C[0] = 0;
    D_004D7E0A[0] = -1;
    D_004D7E10[0] = 0;
    D_004D7E14[0] = 0;
    D_004D7E18[0] = 0;
    i = 0;
    do {
        BLK->x1C[i] = 0;
        BLK->x24[i] = 0;
        i++;
    } while (i < 2);
    i = 0;
    do {
        BLK->x2C[i] = 0;
        BLK->x38[i] = 0;
        i++;
    } while (i < 3);
    z = 0;
    D_004821C0 = -1;
    D_004821C2 = -1;
    D_004821D4.a = z;
    D_004821D0 = -1;
    D_004821D2 = -1;
    D_004821D8 = -1;
    D_004821D4.b = z;
    D_004821C4 = 0;
    D_004821C8 = 0;
    D_004821D4.c = 1;
    ClearInBattle_288400();
}
