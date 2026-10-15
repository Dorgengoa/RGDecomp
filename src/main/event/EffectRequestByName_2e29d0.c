#include "types.h"

typedef struct { u16 x : 16; } H;
typedef union { u32 w; struct { H lo; H hi; } f; } Bits;

typedef struct {
    s16 id;
    s32 v;
    Bits b;
    s32 x;
} Res;

extern void *GetGameData_1fede0(void);
extern void EffectRequestFromDesc_2e2710(Res *, s32, s32, s32, s32);
extern s32 TableFindByNameHashed_429540(s32, s32);

void EffectRequestByName_2e29d0(Res *out, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    Res r;
    Res tmp;
    s32 h;
    void *p;

    r.id = 0;
    r.v = -1;
    r.b.w = 0;
    p = GetGameData_1fede0();
    if (p == NULL) {
        out->id = r.id;
        out->v = r.v;
        out->b.w = r.b.w;
        out->x = r.x;
        return;
    }
    h = TableFindByNameHashed_429540(*(s32 *)(*(u8 **)(*(u8 **)((u8 *)p + 0x8) + 0x5C) + 0x8), arg3);
    if (h != 0) {
        EffectRequestFromDesc_2e2710(&tmp, arg1, arg2, h, arg4);
        r.id = tmp.id;
        r.v = tmp.v;
        r.b.f.lo = tmp.b.f.lo;
        r.b.f.hi = tmp.b.f.hi;
        r.x = tmp.x;
    }
    out->id = r.id;
    out->v = r.v;
    out->b.w = r.b.w;
    out->x = r.x;
}
