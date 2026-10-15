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
extern void EffectArchiveLoadFromDesc_2e2560(Res *, s32, s32, s32, s32, s32);
extern s32 TableFindByNameHashed_429540(s32, s32);

void EffectArchiveLoadByName_2e28a0(Res *out, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
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
        EffectArchiveLoadFromDesc_2e2560(&tmp, arg1, arg2, h, arg4, arg5);
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
