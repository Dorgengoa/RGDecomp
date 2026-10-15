#include "types.h"

/* the first call writes only $5 (= p2); $4 is still p0.  Param `q` and the
   loop counter share $17 - mwcc coalesced them after q's last use. */

typedef struct {
    void *p;
    s32 a, b, c, d, e, f, g, h;
} Ctx;

extern void *ActCfgTableFindActionByName_223d20(void *p, s32 c);
extern void ScriptCallWithArgs_302770(void *e, Ctx *ctx, s32 z);

void ActCfgTableRunExitEvnt_222430(void *p, void *q, s32 c)
{
    Ctx ctx;
    void *obj;
    u8 *e;
    s32 i;

    obj = ActCfgTableFindActionByName_223d20(p, c);
    if (obj != 0) {
        e = *(u8 **)((u8 *)obj + 0x18);
        if (e != 0) {
            ctx.p = q;
            ctx.a = 0;
            ctx.b = 0;
            ctx.c = 0;
            ctx.d = 0;
            ctx.e = 0;
            ctx.f = 0;
            ctx.g = 0;
            ctx.h = 0;
            for (i = 0; i < *(s16 *)((u8 *)obj + 0x22); i++, e += 0xC) {
                ScriptCallWithArgs_302770(e, &ctx, 0);
            }
        }
    }
}
