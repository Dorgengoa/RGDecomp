/* rgp:protos */
#define RGP_SELF_normal_FieldHudPreInit_4f79e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F79E0 -- the shorter sibling of normal_FieldHudShutdown_4f7180, all five stores
 * through the parameter in retail's emission order.
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A2 - 0x37A];
    s16 f3A2;
    u8  pad3A4[0x3C8 - 0x3A4];
    s32 f3C8;
    u8  pad3CC[0x3D4 - 0x3CC];
    s32 f3D4;
    u8  pad3D8[0x434 - 0x3D8];
    s32 f434;
} Obj;

void normal_FieldHudPreInit_4f79e0(Obj *p)
{
    p->f378 = 0;
    p->f3A2 = 0;
    p->f3D4 = -1;
    p->f434 = 0;
    p->f3C8 = 0;
}
