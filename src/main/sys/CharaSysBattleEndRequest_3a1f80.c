#include "types.h"

/* Reached from the SetGameModePhase_1f59a0 family.  The compare chain tests 3, 4, 2, 1,
   so the source order is 1, 2, 4, 3 with `default` sharing case 3's body.

   ★ Both accesses to the byte at 0x24C are BIT 1 of a bitfield:
   `dsll32 30 / dsrl32 31` is a 1-bit READ at 64-(30+32)-1 = 1, and the
   `and -3 / or 2 / sb` at the tail is the matching INSERT with the value
   materialised by `daddiu` -- the constant form.  See
   memory/levers.d/main-bitfield-insert.md. */

struct Sub {
    u8  pad0[0x168];
    s16 m168;
};

struct Obj {
    u8 pad0[0x238];
    struct Sub *m238;
    u8 pad23C[0x10];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 rest : 6;
};

extern s32 D_004837C0;

extern void SetGameModePhase_1f59a0(s32);
extern void GameDataBattleBroadcastPhase_3e6890(s32, s32);

s32 CharaSysBattleEndRequest_3a1f80(struct Obj *p, s32 mode, s32 flag)
{
    struct Sub *q;

    if (flag == 0 && p->b1 != 0) {
        return 0;
    }
    switch (mode) {
    case 1:
    case 2:
    case 4:
        break;
    case 3:
    default:
        GameDataBattleBroadcastPhase_3e6890(D_004837C0, 3);
        SetGameModePhase_1f59a0(0xC8);
        break;
    }
    q = p->m238;
    if (q != 0) {
        q->m168 = mode;
    }
    p->b1 = 1;
    return 1;
}
