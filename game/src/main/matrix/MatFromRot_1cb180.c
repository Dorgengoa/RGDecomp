/* rgp:protos */
#define RGP_SELF_MatFromRot_1cb180 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- MatFromRotPos_1caf90 takes (buf, arg1, v) and the eight gp floats are TWO
   16-byte .sdata STRUCTS copied by assignment (C); element-wise reads schedule wrong. */
#include "types.h"

/*rgp*/
/*rgp*/
typedef struct { f32 x, y, z, w; } V1CB180;
extern V1CB180 D_0047E2C0 __attribute__((section(".sdata")));
extern V1CB180 D_0047E2D0 __attribute__((section(".sdata")));

void MatFromRot_1cb180(s32 arg0, s32 arg1) {
    f32 sp70[4] __attribute__((aligned(16)));
    f32 sp60[4] __attribute__((aligned(16)));
    u8 sp20[0x40] __attribute__((aligned(16)));

    *(V1CB180 *)sp70 = D_0047E2C0;
    *(V1CB180 *)sp60 = D_0047E2D0;
    MatFromRotPos_1caf90(sp20, arg1, sp60);
    MatScaleRows_1cbc20(arg0, sp20, sp70);
}
