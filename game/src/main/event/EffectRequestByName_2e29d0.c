/* rgp:protos */
#define RGP_SELF_EffectRequestByName_2e29d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { __extension__ unsigned short x : 16; } __attribute__((aligned(2))) H;
typedef union { u32 w; struct { H lo; H hi; } f; } Bits;

typedef struct {
    s16 id;
    s32 v;
    Bits b;
    s32 x;
} Res;

/*rgp*/
/*rgp*/
/*rgp*/

void EffectRequestByName_2e29d0(Res *out, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    Res r __attribute__((aligned(16)));
    Res tmp __attribute__((aligned(16)));
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
    h = ((s32)TableFindByNameHashed_429540(*(s32 *)(*(u8 **)(*(u8 **)((u8 *)p + 0x8) + 0x5C) + 0x8), arg3));
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
