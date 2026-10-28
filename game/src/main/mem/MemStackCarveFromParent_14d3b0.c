/* rgp:protos */
#define RGP_SELF_MemStackCarveFromParent_14d3b0 1
#define RGP_SELF_canTake 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub40 {
    u8 pad0[0x20];
    s32 unk20;
    f32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
} Sub40;

typedef struct Obj {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u8 pad38[4];
    s32 unk3C;
    Sub40 *unk40;
} Obj;

/*rgp*/
/*rgp*/

static __inline s32 canTake(Obj *o, s32 n)
{
    Sub40 *s = o->unk40;
    if (s->unk30 < 0) {
        return 0;
    }
    if (s->unk30 + n > s->unk34) {
        return 0;
    }
    return 1;
}

s32 MemStackCarveFromParent_14d3b0(Obj *arg0, s32 arg1, s32 arg2)
{
    void * arg_h0;

    s32 mode;
    s32 base;
    s32 off;
    s32 end;
    s32 ok;
    Sub40 *s;
    s32 *p;

    mode = arg2;
    if (arg0->unk3C != -2 && arg2 == -3) {
        return 0;
    }
    if (arg2 != -3 && arg0->unk28 != 0) {
        return 0;
    }
    if (arg2 != -3) {
        MemStackSetParent_14d770(arg0, (void *)arg1);
    }
    s = arg0->unk40;
    if (s == NULL) {
        return 0;
    }
    p = &s->unk30;
    if (*p < 0) {
        *p = s->unk2C;
    }
    if (arg2 < 0) {
        if ((u32)(arg2 + 2) < 2U) {
            arg2 = arg0->unk40->unk34 - arg0->unk40->unk30;
        }
        if (mode == -3) {
            end = arg0->unk34;
            ok = end - arg0->unk2C;
            if (arg0->unk30 >= 0) {
                arg0->unk40->unk30 -= end - arg0->unk30;
                arg0->unk34 = arg0->unk30;
            } else {
                arg0->unk40->unk30 -= ok;
                arg0->unk34 = arg0->unk2C;
            }
            arg0->unk3C = 0;
            return 1;
        }
    } else {
        mode = 0;
    }
    arg_h0 = arg0;
    ok = canTake(arg_h0, arg2);
    if (ok == 0) {
        return 0;
    }
    s = arg0->unk40;
    base = s->unk28;
    off = s->unk30 * 0x10;
    s->unk30 = s->unk30 + arg2;
    arg0->unk40->unk20 = 1;
    end = base + off;
    MemStackReset_14d830(arg0);
    arg0->unk28 = end;
    arg0->unk2C = 0;
    arg0->unk34 = arg2;
    arg0->unk30 = -1;
    arg0->unk3C = 0;
    arg0->unk24 = 0;
    arg0->unk3C = mode;
    return 1;
}
