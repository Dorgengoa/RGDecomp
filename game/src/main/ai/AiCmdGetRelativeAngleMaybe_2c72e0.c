/* rgp:protos */
#define RGP_SELF_AiCmdGetRelativeAngleMaybe_2c72e0 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: m2c draft references unresolved pseudo-variables (`unkspA4`,
 * `sp54`) plus s128 locals and an "s128, f32" mixed-type extern
 * (Sinf_128fd0) that does not parse as ordinary C; 0 round trips spent.
 * Needs asm/matchings/main/AiCmdGetRelativeAngleMaybe_2c72e0.s read by hand to find what
 * unkspA4/sp54 actually are (likely a 4th quaternion word and a Y component
 * of an already-named local). Not attempted. */
/* s49m: 45 */
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} Vec4 __attribute__((aligned(16)));

extern u8 *D_004DB920[];
extern f32 D_0047D358;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdGetRelativeAngleMaybe_2c72e0(u8 *arg0)
{ RG_VU0_FRAME;
    s32 *o;
    u128 rot;
    u128 pos;
    u128 tpos;
    Vec4 dir __attribute__((aligned(16)));
    Vec4 to __attribute__((aligned(16)));
    Vec4 cr __attribute__((aligned(16)));
    u8 *ctx;
    u8 *a;
    u8 *b;
    f32 ang;
    s32 ia;
    s32 ib;

    ctx = D_004DB920[0];
    { s64 *r = (s64 *)arg0; o = (s32 *)r; r++; ia = ScriptSlotGetInt_2cc9c0((u8 *)r++); ib = ScriptSlotGetInt_2cc9c0((u8 *)r); }
    a = ((u8 *)ObjRecGetLiveObject_1c4a90(ctx, ia));
    b = ((u8 *)ObjRecGetLiveObject_1c4a90(ctx, ib));
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    rot = *(u128 *)(a + 0x190);
    pos = *(u128 *)(a + 0x180);
    tpos = *(u128 *)(b + 0x180);
    dir.x = Sinf_128fd0(((f32 *)&rot)[1]);
    dir.y = 0.0f;
    dir.z = Cosf_128d30(((f32 *)&rot)[1]);
    VecNormalize_13bd90(&dir, &dir);
    VecSub_13be40(&to, (Vec4 *)&tpos, (Vec4 *)&pos);
    to.y = 0.0f;
    VecNormalize_13bd90(&to, &to);
    ang = Vu0InnerProduct_13bd60(&dir, &to);
    sceVu0OuterProduct(&cr, &dir, &to);
    if (cr.y < 0.0f) {
        ang *= -1.0f;
    }
    switch (*o) {
    case 0:
        ScriptSlotStoreIntRef_2cc900(o, (s32)((ang + D_0047D358) / 8.0f) & 7);
        break;
    case 1:
        ScriptSlotStoreFloatRef_2cc8e0(o, ang);
        break;
    }
    return 1;
}
