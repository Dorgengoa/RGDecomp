/* rgp:protos */
#define RGP_SELF_EvCmdNameTableFreeGroup_268b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct E8_FUN_00268b20 {
    u8 raw[0x8];
} E8_FUN_00268b20;

typedef struct World_FUN_00268b20 {
    u8 pad0[0x5CF0];
    s32 base;    /* +0x5CF0 */
    s32 count;   /* +0x5CF4 */
} World_FUN_00268b20;

/*rgp*/
/*rgp*/
/*rgp*/
extern World_FUN_00268b20 *D_00481F78;

s32 EvCmdNameTableFreeGroup_268b20(E8_FUN_00268b20 *arg0)
{
    s32 a;
    s32 base;
    s32 c;
    volatile s32 sp3C;
    World_FUN_00268b20 *w;

    a = ScriptGetInt_26a2a0(arg0);
    w = D_00481F78;
    c = w->count;
    base = w->base;
    sp3C = c;
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), base + a);
    return 1;
}
