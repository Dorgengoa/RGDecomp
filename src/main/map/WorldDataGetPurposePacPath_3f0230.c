#include "types.h"

extern s32 D_00480140;
extern s32 D_00480144;
extern s32 D_00480148;
extern s32 D_0048014C;
extern s32 D_00480150;
extern s32 D_00480154;
extern s32 D_00480158;
extern s32 D_0048015C;
extern s32 D_00480160;

s32 WorldDataGetPurposePacPath_3f0230(void *a0, s32 idx) {
    s32 result = 0;
    switch (idx) {
    case 0: result = D_00480140; break;
    case 1: result = D_00480144; break;
    case 2: result = D_00480148; break;
    case 3: result = D_0048014C; break;
    case 4: result = D_00480150; break;
    case 5: result = D_00480154; break;
    case 6: result = D_00480158; break;
    case 7: result = D_0048015C; break;
    case 8: result = D_00480160; break;
    }
    return result;
}
