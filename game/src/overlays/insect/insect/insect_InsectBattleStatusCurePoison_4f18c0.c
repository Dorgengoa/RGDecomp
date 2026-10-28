/* rgp:protos */
#define RGP_SELF_insect_InsectBattleStatusCurePoison_4f18c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F18C0 -- 132 bytes, 33 instructions.  A 0x3C-byte stack scratch
 * is cleared, formatted from the label the 0x506C table hands back, then
 * queued through 0x51C2F0.  The formatter's second argument is a NESTED CALL,
 * which is what keeps the third argument's load after it. */

typedef struct Sub {
    u8  pad00[0x3C];
    s8  f3C;                        /* +0x3C */
    u8  pad3D[0x5C - 0x3D];
    s32 f5C;                        /* +0x5C */
} Sub;

typedef struct Ins {
    u8 pad0000[0x506C];
    u8 f506C[4];                    /* +0x506C */
    u8 pad5070[0x5080 - 0x5070];
    u8 f5080[4];                    /* +0x5080 */
} Ins;

extern void  memset(void *d, s32 c, s32 n);
extern void  Sprintf_1343b8(void *d, const char *t, s32 v);
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleStatusCurePoison_4f18c0(Ins *o, Sub *s)
{
    char t[0x3C] __attribute__((aligned(16)));

    if (s != 0) {
        memset(t, 0, 0x3C);
        Sprintf_1343b8(t, ((const char *)insect_InsectMsgGet_512b70(o->f506C, 0x64)), s->f5C);
        insect_InsectBattleLogPush_51c2f0(o->f5080, t, -5, -1, 0);
        insect_InsectPieceClearStatus_513340(s, 0);
        s->f3C = 0;
    }
}
