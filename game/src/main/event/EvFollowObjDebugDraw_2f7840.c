/* rgp:protos */
#define RGP_SELF_EvFollowObjDebugDraw_2f7840 1
#define RGP_SELF_isF 1
#define RGP_SELF_isNF 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct O { u8 pad[0x10]; u8 x10[0xC0]; s32 xD0; u8 padD4[0x40]; s32 x114; } O;
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F060;
extern f32 D_0047F064;
extern f32 D_0047F068;
extern f32 D_0047F06C;
static inline s32 isNF(O *o) { return !((o->xD0 & 0x40000000) != 0); }
static inline s32 isF(O *o) { return (o->xD0 & 0x40000000) != 0; }
void EvFollowObjDebugDraw_2f7840(O *arg0, s32 arg1)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(u8[0x30])]; char m1[0x30 + sizeof(u8[0x10])]; char m2[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(u8[0x30]) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    f32 v[4] __attribute__((aligned(16)));
    s32 t;
    s32 b;
    f32 *p;

    if (arg1 == 0) {
        return;
    }
    if (!isNF(arg0)) {
        return;
    }
    XformGetMatrix_2e7750(arg0->x10, (*(u8 (*)[0x30])(rgp_blk1 + 0x0)));
    p = v;
    p[0] = D_0047F060;
    p[1] = D_0047F064;
    p[2] = D_0047F068;
    p[3] = D_0047F06C;
    DbgDrawSphere_1cc7e0(arg1, (*(u8 (*)[0x10])(rgp_blk1 + 0x30)), p, 40.0f);
    t = arg0->x114;
    if (t != 0) {
        EventVolumeRecDebugDraw_2e49b0(t, arg1, (*(u8 (*)[0x30])(rgp_blk1 + 0x0)), v);
    }
}
