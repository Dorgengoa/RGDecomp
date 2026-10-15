#include "types.h"

/* A script-command handler.  The argument cursor steps 8 bytes per read and
   every advance sits in the reader call's DELAY SLOT, which is only reachable
   from a post-increment INSIDE the argument (`VariantGetInt_15f780(p++)`); the first
   advance is hoisted into the arity guard's `beql` slot.
   Both float clamps are ternaries -- `bc1fl` with the pass-through `mov.s` in
   the delay slot, one word each. */

typedef struct Arg { s32 lo; s32 hi; } Arg;

typedef struct Ent {
    f32 f00;
    f32 f04;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    s32 f10;
} Ent;

extern s32  SlotGetInt_15f720(Arg *p);
extern s32  VariantGetInt_15f780(Arg *p);
extern f32  VariantGetFloat_15f740(Arg *p);
extern void *MotionListFindSubEntry_172430(void *ctx, s32 a, s32 b);
extern s32  NamedRecFindIndex_173a00(void *o, s32 h);
extern f32  NamedRecLerpMaybe_173980(void *o, s32 h, f32 v);

extern u8  *D_0049D4E0[];
extern s32  D_0049D4E4[];
extern s32  D_0049D4E8[];
extern s32  D_0049D4F8[];
extern Ent *D_0049D4FC[];
extern s32  D_0049D500[];

s32 ParamScriptSeLoopCmd_1af490(Arg *p, s32 argc)
{
    s32 h;
    u8 *g;
    Ent *e;
    void *o;
    s32 a;
    s32 b;
    s32 c;
    s32 n;
    f32 v0;
    f32 v1;

    g = D_0049D4E0[0];
    if (g == 0) {
        return 0;
    }
    if (argc < 6) {
        return 0;
    }
    h  = SlotGetInt_15f720(p++);
    a  = VariantGetInt_15f780(p++);
    b  = VariantGetInt_15f780(p++);
    v0 = VariantGetFloat_15f740(p++);
    v1 = VariantGetFloat_15f740(p++);
    c  = VariantGetInt_15f780(p);

    n = D_0049D500[0];
    if (n >= D_0049D4F8[0]) {
        return 0;
    }
    e = D_0049D4FC[0] + n;
    o = MotionListFindSubEntry_172430(g + 0x1F0, D_0049D4E8[0], D_0049D4E4[0]);
    if (o == 0) {
        return 0;
    }
    h = NamedRecFindIndex_173a00(o, h);
    if (h < 0) {
        return 0;
    }
    v0 = (v0 <= 1.0f) ? NamedRecLerpMaybe_173980(o, h, v0) : v0;
    v1 = (v1 <= 1.0f) ? NamedRecLerpMaybe_173980(o, h, v1) : v1;
    /* Two float tests branching in OPPOSITE directions (`bc1tl` into the
       return, `bc1fl` past it) is one `||`, not two `if`s. */
    if (v0 <= 0.0f || v1 <= 0.0f) {
        return 0;
    }
    e->f00 = v0;
    e->f04 = v1;
    e->f0A = (s16)a;
    e->f0C = (s16)b;
    e->f08 = (s16)c;
    e->f0E = 0;
    e->f10 = 0;
    D_0049D500[0] = D_0049D500[0] + 1;
    return 1;
}
