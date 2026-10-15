#include "types.h"

typedef struct Ctx { u8 pad00[0xC]; void *f0C; } Ctx;
typedef struct Ref { s64 *p; u32 i; } Ref;

extern Ctx *D_00449858[];
extern const char D_0045CB40[];
extern void Fprintf_12f9a0(void *ctx, const char *fmt);
extern void Abort_12de80(void);

s32 CharaStatusTest_2121c0(u8 *a0, u32 bit)
{
    Ref r;
    Ref *rp = &r;
    u32 bc;

    r.p = (s64 *)(a0 + 0xC8);
    r.i = bit;
    bc = r.i;
    if (bc >= 0x30) {
        Fprintf_12f9a0(D_00449858[0]->f0C, D_0045CB40);
        Abort_12de80();
    }
    return (*rp->p & (1LL << bc)) != 0;
}
