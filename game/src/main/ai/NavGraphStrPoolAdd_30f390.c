/* rgp:protos */
#define RGP_SELF_NavGraphStrPoolAdd_30f390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj0030f390 {
    u8 pad00[0xD0];
    s32 unkD0;
    u8 pad1[4];
    u16 unkD8;
    u16 unkDA;
} Obj0030f390;

extern s32 strlen(s32);
extern void strcpy(s32, s32);

s32 NavGraphStrPoolAdd_30f390(Obj0030f390 *arg0, s32 arg1) {
    u32 temp_16;
    s32 temp_17;
    u32 sum;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->unkD0 == 0) {
        return 0;
    }
    temp_16 = strlen(arg1) + 1;
    if (arg0->unkDA < temp_16 + arg0->unkD8) {
        return 0;
    }
    temp_17 = arg0->unkD0 + arg0->unkD8;
    strcpy(temp_17, arg1);
    sum = temp_16 + arg0->unkD8;
    if (arg0->unkD0 != 0) {
        if (sum <= arg0->unkDA) {
            arg0->unkD8 = (u16)sum;
        }
    }
    return temp_17;
}
