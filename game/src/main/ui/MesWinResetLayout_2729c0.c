/* rgp:protos */
#define RGP_SELF_MesWinResetLayout_2729c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T002729c0 {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x1D74 - 0x5C];
    s16 arr1[0x14];
    s16 arr2[0x14];
} T002729c0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinResetLayout_2729c0(T002729c0 *arg0)
{
    s32 i;

    MesWinSetShownEnd_271690(arg0, 0);
    MesWinSetShownStart_2716b0(arg0, 0);
    MesWinSetTypeCursor_272b10(arg0, 0.0f);
    MesWinSetOpenRate_277550(arg0, 0.0f);
    MesWinSetPageWait_272200(arg0, 0);
    MesWinSetPageFrames_271ed0(arg0, 0);
    MesWinSetPage_272240(arg0, 0);
    arg0->unk5A = 0;
    MesWinClearPageLineCounts_272a70(arg0);
    MesWinSetLastGlyphPos_272320(arg0, 0, 0);

    i = 0;
    do {
        arg0->arr1[i] = 0;
        arg0->arr2[i] = -1;
        i += 1;
    } while (i < 0x14);
}
