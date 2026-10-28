/* rgp:protos */
#define RGP_SELF_MesWinClearState_277030 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
extern void *memset(void *d, s32 c, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinClearState_277030(void *p)
{
    u8 *q;
    s32 i;
    s32 j;

    q = (u8 *)p;
    MesWinSetClipRows_271ee0(q, 0, 0x1BF);
    *(s16 *)(q + 0x54) = 0;
    *(s16 *)(q + 0x56) = 0;
    MesWinSetPage_272240(q, 0);
    *(s16 *)(q + 0x5A) = 0;
    MesWinClearPageLineCounts_272a70(q);
    MesWinSetLastGlyphPos_272320(q, 0, 0);
    MesWinSetFlush_2775f0(q, 0);
    MesWinSetPageWait_272200(q, 0);
    MesWinSetTypeCursor_272b10(q, 0.0f);
    MesWinSetShownEnd_271690(q, 0);
    MesWinSetShownStart_2716b0(q, 0);
    MesWinClearChars_2744b0(q);
    *(s32 *)(q + 0x194C) = -1;
    *(s32 *)(q + 0x1950) = 0;
    MesWinSetPageFrames_271ed0(q, 0);
    *(q + 0x195C) = 0x80;
    for (i = 0; i < 0x10; i++) {
        memset(q + i * 0x20 + 0x195D, 0, 0x20);
    }
    for (i = 0; i < 0x10; i++) {
        *(s32 *)(q + i * 4 + 0x1B60) = -1;
    }
    for (i = 0; i < 0x14; i++) {
        *(s32 *)(q + i * 4 + 0x1BA0) = 0;
        *(s16 *)(q + i * 2 + 0x1BF0) = 0;
    }
    *(s32 *)(q + 0x1C18) = 0;
    *(q + 0x1C1C) = 0;
    *(q + 0x1C1D) = 1;
    *(s16 *)(q + 0x1C1E) = 0;
    *(s16 *)(q + 0x1C20) = -1;
    *(s16 *)(q + 0x1C22) = -1;
    *(s32 *)(q + 0x1C24) = -1;
    MesWinSetArrowTarget_271b40(q, 0, 0);
    MesWinSetArrowPos_271b30(q, 0, 0);
    *(q + 0x1C38) = 0;
    *(q + 0x1C39) = 0;
    *(q + 0x1C3A) = 0;
    *(s32 *)(q + 0x1C3C) = 0;
    *(s32 *)(q + 0x1C40) = 0;
    *(s32 *)(q + 0x1C44) = 0;
    MesWinSetActive_2774e0(q, 1);
    MesWinSetClipMode_2721e0(q, 0);
    MesWinClearRect_2776d0(q + 0x1C4C);
    for (j = 0; j < 0x14; j++) {
        *(s16 *)(q + j * 2 + 0x1C5C) = 0;
        *(s16 *)(q + j * 4 + 0x1C84) = 0;
        *(s16 *)(q + j * 4 + 0x1C86) = 0;
        MesWinSetLineFixedPos_272470(q, j, 0);
        *(s8 *)(q + j + 0x1CE8) = -1;
        *(s32 *)(q + j * 4 + 0x1CFC) = 0;
        *(s16 *)(q + j * 2 + 0x1D4C) = 0;
        *(s16 *)(q + j * 2 + 0x1D74) = 0;
        *(s16 *)(q + j * 2 + 0x1D9C) = -1;
    }
}
