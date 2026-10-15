#include "types.h"

typedef struct Ctx001873e0 {
    f32 t;
    s32 x;
} Ctx001873e0;

extern void MtxIdentity_13d2e0(void *);
extern f32 TimeOfDayGetHour_18d920(void);
extern s32 FuncDataTableCollectSounds_18e4c0(void *, void *, Ctx001873e0 *, s32 *, s32 *, s32 *, s32);
extern void NodeCalcWorldMatrixThunk_186130(void *, void *);

s32 MapAreaModelCollectSoundEmitters_1873e0(u8 *o, s32 *a, s32 *b, s32 *c, s32 rem)
{
    Ctx001873e0 ctx;
    u8 buf[0x40];
    s32 total;
    s32 s;
    s32 n;
    s32 cnt;
    s32 i;
    u8 **arr;
    u8 *e;

    ctx.t = 0.0f;
    ctx.t = TimeOfDayGetHour_18d920();
    ctx.x = *(s32 *)(o + 0x1678);
    total = 0;
    MtxIdentity_13d2e0(buf);
    n = FuncDataTableCollectSounds_18e4c0(buf, o + 0x1664, &ctx, a, b, c, rem);
    cnt = *(s32 *)(o + 0x51C);
    arr = *(u8 ***)(o + 0x520);
    s = n * 4;
    total += n;
    rem -= n;
    a = (s32 *)((u8 *)a + s);
    b = (s32 *)((u8 *)b + s);
    c = (s32 *)((u8 *)c + s);
    for (i = 0; i < cnt; i++) {
        e = arr[i];
        if (e != 0 && *(s16 *)(e + 0x32) != 0 && (*(s32 *)(e + 0x114) & 0x80)) {
            NodeCalcWorldMatrixThunk_186130(e, buf);
            if (rem <= 0) {
                return total;
            }
            n = FuncDataTableCollectSounds_18e4c0(buf, e + 0x114, &ctx, a, b, c, rem);
            s = n * 4;
            total += n;
            rem -= n;
            a = (s32 *)((u8 *)a + s);
            b = (s32 *)((u8 *)b + s);
            c = (s32 *)((u8 *)c + s);
        }
    }
    return total;
}
