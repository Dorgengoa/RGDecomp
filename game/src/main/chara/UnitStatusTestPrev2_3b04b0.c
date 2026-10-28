/* rgp:protos */
#define RGP_SELF_UnitStatusTestPrev2_3b04b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx { u8 pad00[0xC]; void *f0C; } Ctx;
typedef struct Ref { s64 *p; u32 i; } Ref;

extern Ctx *D_00449858[];
extern char D_0045CB40[];
extern void Fprintf_12f9a0(void *ctx, const char *fmt);
/*rgp*/

s32 UnitStatusTestPrev2_3b04b0(u8 *a0, u32 bit)
{
    Ref r __attribute__((aligned(16)));
    Ref *rp = &r;
    u32 bc;

    r.p = (s64 *)(a0 + 0x1B8);
    r.i = bit;
    bc = r.i;
    if (bc >= 0x30) {
        Fprintf_12f9a0(D_00449858[0]->f0C, D_0045CB40);
        Abort_12de80();
    }
    return (*rp->p & (1LL << bc)) != 0;
}
