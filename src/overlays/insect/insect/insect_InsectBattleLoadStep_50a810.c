#include "types.h"
/* insect 0x0050A810 -- 476 bytes, 119 instructions, 21 calls, 6 conditional
 * branches, jtbl_00524EF0 (17 entries).
 *
 * THREE OF THE SEVENTEEN ENTRIES POINT AT THE SHARED EXIT 0x0050A9DC, so cases
 * 11, 12 and 16 are EMPTY CASES PRESENT IN THE SOURCE
 * ([[insect-jump-table-density]]).  `sltiu $1, $2, 0x11` bounds the raw value
 * with no bias, so the set is 0..16 and case 0 is in it.
 *
 * BLOCK ORDER IS NOT ASCENDING and it is the source's case order:
 *   0 1 2 3 4 5 6 7 8 13 14 15 9 10
 * -- cases 13, 14 and 15 sit between 8 and 9.  Read the order off the
 * addresses, never off the case values.
 *
 * `slti $1, $5, 0x9` at 0x0050A8C4 feeds `bnez`, so its destination is $at and
 * the source token is `> 8`, not `>= 9` ([[at-compare-class]]); x_at.py flags
 * this site.  It is the only lever site in the function.
 *
 * The counter is `n = ++o->f5DD0` in an s16 LOCAL, not a re-read.  The
 * `dsll32 16 / dsra32 16` narrowing lands in $5 and is then used TWICE -- once
 * by the compare and once as insect_InsectBattleSetState_50d8c0's second argument.  Writing
 * the guard against `o->f5DD0` instead makes mwcc reload it with `lh`.
 */

typedef struct Ins Ins;

struct Ins {
    u8  pad0000[0x5000];
    u8  f5000[0x5DD0 - 0x5000];     /* +0x5000 */
    s16 f5DD0;                      /* +0x5DD0 */
};

extern void insect_InsectFileSlotStep_512060(void *p);
extern s32  insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);
extern s32  insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleLoadJasterCfg_4f7530(Ins *o);
extern void insect_InsectBattleLoadSpecialChara_4f76b0(Ins *o);
extern void insect_InsectBattleSpawnPlacedPiece_4f7b60(Ins *o);
extern void insect_InsectBattleLoadPreviewModel_4f7ea0(Ins *o, s32 k);
extern void insect_InsectBattleLoadSoundBank_4f8260(Ins *o);
extern void insect_InsectBattleLoadTrainerCharas_4f83f0(Ins *o);
extern void insect_InsectBattleLoadTeams_4f88a0(Ins *o);
extern void insect_InsectBattleLoadMarkerModels_4f8e50(Ins *o);
extern void insect_InsectBattleLoadEffectModels_4f90b0(Ins *o);
extern void insect_InsectBattleLoadResources_4f9370(Ins *o);
extern void insect_InsectBattleLoadWorldData_4f9900(Ins *o);

void insect_InsectBattleLoadStep_50a810(Ins *o)
{
    s16 n;

    insect_InsectFileSlotStep_512060(o->f5000);
    switch (insect_InsectBattleGetState_50d6f0(o, 1)) {
    case 0:
        if (insect_InsectBattleTestFlag_50da40(o, 5) == 0) {
            break;
        }
        if (o->f5DD0 >= 2) {
            insect_InsectBattleSetFlag_50dad0(o, 6);
        }
        if (insect_InsectBattleTestFlag_50da40(o, 6) != 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 7) == 0) {
                break;
            }
        }
        n = ++o->f5DD0;
        if (n > 8) {
            insect_InsectBattleClearFlag_50da90(o, 5);
            o->f5DD0 = -1;
        } else {
            insect_InsectBattleSetState_50d8c0(o, n, 1, -1);
        }
        break;
    case 1:
        insect_InsectBattleLoadWorldData_4f9900(o);
        break;
    case 2:
        insect_InsectBattleLoadResources_4f9370(o);
        break;
    case 3:
        insect_InsectBattleLoadEffectModels_4f90b0(o);
        break;
    case 4:
        insect_InsectBattleLoadMarkerModels_4f8e50(o);
        break;
    case 5:
        insect_InsectBattleLoadTeams_4f88a0(o);
        break;
    case 6:
        insect_InsectBattleLoadTrainerCharas_4f83f0(o);
        break;
    case 7:
        insect_InsectBattleLoadSoundBank_4f8260(o);
        break;
    case 8:
        insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        break;
    case 13:
        insect_InsectBattleLoadPreviewModel_4f7ea0(o, 0);
        break;
    case 14:
        insect_InsectBattleLoadPreviewModel_4f7ea0(o, 1);
        break;
    case 15:
        insect_InsectBattleSpawnPlacedPiece_4f7b60(o);
        break;
    case 9:
        insect_InsectBattleLoadSpecialChara_4f76b0(o);
        break;
    case 10:
        insect_InsectBattleLoadJasterCfg_4f7530(o);
        break;
    case 11:
        break;
    case 12:
        break;
    case 16:
        break;
    }
}
