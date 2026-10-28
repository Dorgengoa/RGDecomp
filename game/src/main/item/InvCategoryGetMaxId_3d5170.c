/* rgp:protos */
#define RGP_SELF_InvCategoryGetMaxId_3d5170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 v; s32 pad[3]; } Padded_003D5170;
extern Padded_003D5170 D_00465A10;
extern Padded_003D5170 D_00465A40;
extern Padded_003D5170 D_00465A68;
extern Padded_003D5170 D_00465A80;
extern Padded_003D5170 D_00465AD8;
extern Padded_003D5170 D_00465AF0;
extern Padded_003D5170 D_00465B08;
extern Padded_003D5170 D_00465B38;

s32 InvCategoryGetMaxId_3d5170(s32 idx) {
    s32 result;
    switch (idx) {
    case 0: result = D_00465A10.v; break;
    case 1: result = D_00465A40.v; break;
    case 2: result = D_00465A68.v; break;
    case 3: result = D_00465A80.v; break;
    case 6: result = D_00465AD8.v; break;
    case 7: result = D_00465AF0.v; break;
    case 8: result = D_00465B08.v; break;
    case 9: result = D_00465B38.v; break;
    default: result = -1; break;
    }
    return result;
}
