/* rgp:protos */
#define RGP_SELF_InvCategoryGetMinId_3d5210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 v; s32 pad[3]; } Padded_003D5210;
extern Padded_003D5210 D_00465A08;
extern Padded_003D5210 D_00465A38;
extern Padded_003D5210 D_00465A60;
extern Padded_003D5210 D_00465A78;
extern Padded_003D5210 D_00465AD0;
extern Padded_003D5210 D_00465AE8;
extern Padded_003D5210 D_00465B00;
extern Padded_003D5210 D_00465B30;

s32 InvCategoryGetMinId_3d5210(s32 idx) {
    s32 result;
    switch (idx) {
    case 0: result = D_00465A08.v; break;
    case 1: result = D_00465A38.v; break;
    case 2: result = D_00465A60.v; break;
    case 3: result = D_00465A78.v; break;
    case 6: result = D_00465AD0.v; break;
    case 7: result = D_00465AE8.v; break;
    case 8: result = D_00465B00.v; break;
    case 9: result = D_00465B30.v; break;
    default: result = -1; break;
    }
    return result;
}
