/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecCallAbility_518e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00518E30 -- 224 bytes.  The 0x3C-byte scratch buffer / format /
 * draw chain of 0x004F1700 with a fourth format argument, guarded by two
 * `||`-joined null pairs.  The 0x43 string id is fetched twice: once
 * unconditionally and once more when the flag byte is set. */

typedef struct Obj {
    u8 pad00[0xC];
    s8 f0C;                         /* +0x0C */
} Obj;

typedef struct Ent {
    u8  pad00[0x5C];
    s32 f5C;                        /* +0x5C */
} Ent;

typedef struct Ctx {
    u8 pad0000[0x506C];
    u8 f506C[0x5080 - 0x506C];      /* +0x506C */
    u8 f5080[4];                    /* +0x5080 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  Sprintf_1343b8(char *t, s32 a, s32 b, void *c);

s32 insect_InsectSeqExecCallAbility_518e30(Obj *o)
{
    char  buf[0x3C] __attribute__((aligned(16)));
    void *b;
    u8   *p;
    u8   *q;
    Ctx  *g;
    Ent  *a;
    s32   t;

    g = ((Ctx *)InsectBattleGet_31a8d0());
    if (o == 0 || g == 0) {
        return 1;
    }
    p = g->f506C;
    q = g->f5080;
    a = ((Ent *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    b = insect_InsectBattleGetSpecialRec_50db30(g);
    if (a == 0 || b == 0) {
        return 1;
    }
    t = ((s32)insect_InsectMsgGet_512b70(p, 0x43));
    if (o->f0C != 0) {
        t = ((s32)insect_InsectMsgGet_512b70(p, 0x43));
    }
    Sprintf_1343b8(buf, t, a->f5C, b);
    insect_InsectBattleLogPush_51c2f0(q, buf, -5, -1, 0);
    return 1;
}
