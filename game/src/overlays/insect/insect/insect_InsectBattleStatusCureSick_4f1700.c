/* rgp:protos */
#define RGP_SELF_insect_InsectBattleStatusCureSick_4f1700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1700 -- 132 bytes, 33 instructions, 5 calls, 1 conditional
 * branch.  The sibling of 0x004F1790 / 0x004F1830: same 0x3C-byte scratch
 * buffer at $29+0x30 (frame 0x70), same clear / format / draw / refresh
 * chain, a different format id (0x65) and a different flag byte (0x3F).
 * Here the trailing `sb $0, 0x3F($16)` is a real instruction after the last
 * `jal`, not a delay slot, so it is the LAST statement.
 */

typedef struct Sub {
    u8  pad00[0x3F];
    s8  f3F;                        /* +0x3F */
    u8  pad40[0x5C - 0x40];
    s32 f5C;                        /* +0x5C */
} Sub;

typedef struct Obj {
    u8  pad00[0x506C];
    u8  f506C[0x5080 - 0x506C];     /* +0x506C */
    u8  f5080[4];                   /* +0x5080 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *p, s32 c, s32 n);
extern void Sprintf_1343b8(char *t, s32 a, s32 b);

void insect_InsectBattleStatusCureSick_4f1700(Obj *o, Sub *s)
{
    char buf[0x3C] __attribute__((aligned(16)));

    if (s != 0) {
        memset(buf, 0, 0x3C);
        Sprintf_1343b8(buf, ((s32)insect_InsectMsgGet_512b70(o->f506C, 0x65)), s->f5C);
        insect_InsectBattleLogPush_51c2f0(o->f5080, buf, -5, -1, 0);
        insect_InsectPieceClearStatus_513340(s, 3);
        s->f3F = 0;
    }
}
