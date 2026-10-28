/* rgp:protos */
#define RGP_SELF_MesWinScrollToPage_270650 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED on four crossed levers -- MesWinAddPenY_272ab0 takes TWO args (its merged
   definition), temp_5 is s32 fed by a REDUNDANT `temp_2_2 = (s16) temp_2_2;` (buys the
   dsll32/dsra32 pair), and the row address is `(temp_2 << 3) + arg0` (only the shift
   spelling with the index FIRST gives addu v0,v0,s0). */
/* PARK (round 3): right length (65 words), 5 bad words remain. Tried swapping the add operand order and the pointer-arithmetic operand order (arg0+temp_2*8 vs temp_2*8+arg0); neither changed the diff. Residue looks like an unrelated scheduling difference around the (temp_2*8)+arg0 truncated-int-to-pointer cast. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinScrollToPage_270650(s32 arg0)
{
    s16 temp_2_2;
    s32 temp_17;
    s32 temp_2;
    s32 var_6;
    s32 temp_5;
    u8 *temp_4;
    u8 *base;

    temp_2 = MesWinFindPageStart_270840(arg0, ((short)MesWinGetPage_272230(arg0)));
    MesWinShiftChars_270900(arg0, temp_2);
    MesWinSetShownStart_2716b0(arg0, MesWinFindPageStart_270840(arg0, ((short)MesWinGetPage_272230(arg0))));
    temp_17 = MesWinFindPageEnd_270760(arg0, ((short)MesWinGetPage_272230(arg0)));
    MesWinSetShownEnd_271690(arg0, 1 + (temp_17 - MesWinGetShownStart_2716a0(arg0)));
    base = (u8 *)(u32)((temp_2 << 3) + arg0);
    temp_2_2 = *(s16 *)(base + 0xC8);
    if (temp_2_2 != 0) {
        var_6 = 0;
        temp_2_2 = (s16) temp_2_2;
        temp_5 = temp_2_2;
        do {
            temp_4 = (u8 *)(u32)arg0 + (var_6 * 8);
            var_6 += 1;
            *(s16 *)(temp_4 + 0xC8) = (s16) (*(s16 *)(temp_4 + 0xC8) - temp_5);
        } while (var_6 < 0x300);
        MesWinAddPenY_272ab0(arg0, -temp_5);
    }
    MesWinSetScrollY_271710(arg0, 0);
    MesWinSetScrollTarget_2716e0(arg0, 0);
}
