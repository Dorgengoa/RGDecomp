/* rgp:protos */
#define RGP_SELF_MesSlotInit_277e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00277e10 {
    s16 f00;
    s16 f02;
    s32 f04;
    u8 f08;
    u8 pad009[0x3F];
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
} Obj_FUN_00277e10;

typedef struct T_FUN_00277e10 T_FUN_00277e10;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesSlotInit_277e10(Obj_FUN_00277e10 *o)
{
    T_FUN_00277e10 *t;

    t = ((T_FUN_00277e10 *)GetDrawCtx_15de80());
    o->f00 = DrawEnvGetWidth_1451e0(t);
    o->f02 = DrawEnvGetHeight_1451d0(t);
    o->f04 = 0;
    TextStyleInit_26c610(&o->f08);
    TextStyleSetFontType_26edf0(&o->f08, 1);
    o->f48 = 0x338;
    o->f50 = 0;
    o->f4C = 0;
    o->f54 = -1;
}
