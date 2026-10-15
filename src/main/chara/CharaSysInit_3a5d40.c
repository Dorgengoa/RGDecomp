#include "types.h"
#pragma opt_loop_invariants off

typedef struct Obj {
    u8 pad0[0x238];
    u8 *m238;       /* 0x238 */
    s32 m23C;       /* 0x23C */
    u8 pad240[4];
    u8 *m244;       /* 0x244 */
    u8 *m248;       /* 0x248 */
    u8 pad24C[0xB94 - 0x24C];
    u8 *mB94;       /* 0xB94 */
} Obj;

extern u8 *MemStackNew_14e130(s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void CharaSysReset_3a5ec0(void);
extern void CharaEventLogTimerReset_3a6940(u8 *);
extern void CharaEventLogReset_3a6960(u8 *);
extern void CharaEventLogEntryReset_3a6bf0(u8 *);
extern void CharaEventLogKeyReset_3a6c20(u8 *);
extern void CharaStateReset_3a79b0(u8 *, s32, s32, s32, s32);
extern void BattleRecordReset_3a7fd0(u8 *);
extern s32 D_00465C88[];

s32 CharaSysInit_3a5d40(Obj *o, s32 heap)
{
    u8 *p;
    u8 *x;

    if (heap == 0) {
        return 0;
    }
    CharaSysReset_3a5ec0();
    p = MemStackNew_14e130(0x1D0, heap);
    if (p != 0) {
        *(s64 *)p = 0;
        BattleRecordReset_3a7fd0(p + 0x168);
        CharaStateReset_3a79b0(p, 1, 1, 1, 1);
    }
    o->m238 = p;
    if (p == 0) {
        return 0;
    }
    if ((o->m23C = MemStackNew_14e1b0(D_00465C88[0] * 16, heap)) == 0) {
        return 0;
    }
    if ((p = MemStackNew_14e130(0x2CC, heap)) != 0) {
        x = p + 2;
        do {
            CharaEventLogKeyReset_3a6c20(x);
            x += 4;
        } while (x < p + 0x42);
        x = p + 0x46;
        do {
            CharaEventLogEntryReset_3a6bf0(x);
            x += 8;
        } while (x < p + 0x246);
        x = p + 0x248;
        do {
            CharaEventLogTimerReset_3a6940(x);
            x += 8;
        } while (x < p + 0x2C8);
        CharaEventLogReset_3a6960(p);
    }
    o->m244 = p;
    if (p == 0) {
        return 0;
    }
    if ((o->m248 = MemStackNew_14e130(0x284, heap)) == 0) {
        return 0;
    }
    o->mB94 = MemStackNew_14e130(0x104, heap);
    return o->mB94 != 0;
}
