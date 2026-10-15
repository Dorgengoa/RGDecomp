#include "types.h"
/* insect 0x004F1790 -- 152 bytes, 38 instructions, 6 calls, 1 conditional
 * branch.  A 0x3C-byte scratch buffer at $29+0x30 (frame 0x70) is cleared,
 * filled from a formatted lookup, and handed to the drawer.  The `sb $0,
 * 0x40($16)` sits in the LAST call's delay slot, so it precedes that call in
 * the source.
 */

typedef struct Sub {
    u8  pad00[0x40];
    s8  f40;                        /* +0x40 */
    u8  pad41[0x5C - 0x41];
    s32 f5C;                        /* +0x5C */
} Sub;

typedef struct Obj {
    u8  pad00[0x506C];
    u8  f506C[0x5080 - 0x506C];     /* +0x506C */
    u8  f5080[4];                   /* +0x5080 */
} Obj;

extern void insect_InsectPieceClearStatus_513340(Sub *s, s32 k);
extern s32  insect_InsectMsgGet_512b70(void *p, s32 k);
extern void insect_InsectPieceSetYawTarget_5156d0(Sub *s, f32 a, f32 b);
extern void insect_InsectBattleLogPush_51c2f0(void *p, char *t, s32 a, s32 b, s32 c);
extern void func_131B60(void *p, s32 c, s32 n);
extern void func_1343B8(char *t, s32 a, s32 b);

void insect_InsectBattleStatusCureFlip_4f1790(Obj *o, Sub *s)
{
    char buf[0x3C];

    if (s != 0) {
        func_131B60(buf, 0, 0x3C);
        func_1343B8(buf, insect_InsectMsgGet_512b70(o->f506C, 0x68), s->f5C);
        insect_InsectBattleLogPush_51c2f0(o->f5080, buf, -5, -1, 0);
        insect_InsectPieceClearStatus_513340(s, 4);
        s->f40 = 0;
        insect_InsectPieceSetYawTarget_5156d0(s, 0.0f, 4.0f);
    }
}
