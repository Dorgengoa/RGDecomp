#include "types.h"
/* insect 0x005088C0 -- 344 bytes.  A phase teardown: seven fixed 0x0050DAD0
 * notifications, then a three-way choice of ONE id for the shared trailing
 * 0x0050D8C0 call; the id lands in $5 through each branch's delay slot and the
 * last arm returns instead of falling into that call. */

typedef struct Ins {
    u8    pad0000[0x870];
    void *f870;                     /* +0x0870 */
    u8    pad0874[0x3F8C - 0x874];
    u8    f3F8C[0x5B08 - 0x3F8C];   /* +0x3F8C */
    u8    f5B08[0x5DA8 - 0x5B08];   /* +0x5B08 */
    s32   f5DA8;                    /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                    /* +0x5EF1 */
} Ins;

extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern void *insect_InsectTeamGetName_5138b0(u8 *p);
extern void  insect_InsectLiveTalkTableFind_523490(u8 *p, void *h);
extern void  func_1CF740(void *h, s32 k);

void insect_InsectBattleFlowBattleBegin_5088c0(Ins *o)
{
    s32 id;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        if (o->f5DA8 == 0) {
            insect_InsectLiveTalkTableFind_523490(o->f5B08, insect_InsectTeamGetName_5138b0(o->f3F8C));
        }
        func_1CF740(o->f870, 0xF);
        insect_InsectBattleSetFlag_50dad0(o, 9);
        insect_InsectBattleSetFlag_50dad0(o, 0xA);
        insect_InsectBattleSetFlag_50dad0(o, 0x14);
        insect_InsectBattleSetFlag_50dad0(o, 0x16);
        insect_InsectBattleSetFlag_50dad0(o, 0x17);
        insect_InsectBattleSetFlag_50dad0(o, 0x18);
        insect_InsectBattleSetFlag_50dad0(o, 0x19);
        o->f5EF1 = 0;
        id = 5;
        switch (o->f5DA8) {
        case 3:
            id = 0x21;
            break;
        case 0:
            break;
        default:
            insect_InsectBattleSetFlag_50dad0(o, 0x38);
            if (o->f5DA8 == 5) {
                insect_InsectBattleSetState_50d8c0(o, 0xF, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
                insect_InsectBattleSetState_50d8c0(o, 0xE, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                return;
            }
            id = 0x22;
            break;
        }
        insect_InsectBattleSetState_50d8c0(o, id, 0, -1);
        break;
    }
}
