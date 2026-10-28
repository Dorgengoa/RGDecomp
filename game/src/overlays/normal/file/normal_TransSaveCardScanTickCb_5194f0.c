/* rgp:protos */
#define RGP_SELF_normal_TransSaveCardScanTickCb_5194f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005194F0 -- travel-confirm dialog state machine on D_0048480C
 * (0/1), sibling of title_TitleLoadCardScanTickCb_4edec0's two-state confirm pattern.  Case 0
 * calls func_37B970() TWICE (short-circuit `||`, not cached) since its
 * result isn't needed again; case 1 caches it in `r` because the widget
 * block below re-tests `r != 7`. */

typedef struct Actor005194F0 {
    u8  pad000[0x4EC];
    s16 f4EC;
} Actor005194F0;

typedef struct Wid005194F0 {
    u8  pad000[0x16];
    s16 field016;
    u8  pad018[0x2];
    s16 field01A;
} Wid005194F0;

extern s8              D_0048480C;     /* gp - 0x964 */
extern void            *D_004847D8;    /* gp - 0x998 */
extern Actor005194F0   *D_00484724;    /* gp - 0xA4C */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveCardScanTickCb_5194f0(void *a, void *b)
{
    s32 r;
    s32 r2;
    s32 n;
    s32 f;
    s32 tmp;
    Wid005194F0 *o;
    Wid005194F0 *o2;

    normal_TransSaveSlotCursorBob_518990(a, b, 0);
    switch (D_0048480C) {
    case 0:
        if (((unsigned char)SaveModeChanged_37baa0()) == 0) {
            break;
        }
        if ((SavePortCardIsReady_37b9b0(0) & 0xFF) == 0) {
            normal_TransSaveSetError_51a000(8);
            return 1;
        }
        if (((short)SaveGetResultStatus_37b970()) == 0 || ((short)SaveGetResultStatus_37b970()) == 7) {
            SaveMgrSetMode_37b9e0(3);
            D_0048480C = D_0048480C + 1;
        } else {
            normal_TransSaveSetError_51a000(5);
        }
        break;
    case 1:
        if (((unsigned char)SaveModeChanged_37baa0()) == 0) {
            break;
        }
        r = ((short)SaveGetResultStatus_37b970());
        if (r == 0 || r == 7) {
            f = D_00484724->f4EC;
            r2 = SaveCheckCardFreeSpace_37b980((u8 *)D_00484724 + 0x4A4 + f * 0x1C);
            n = SaveCountUsedSlots_373340(D_00484724);
            if (r2 == 2 && n <= 0) {
                normal_TransSaveSetError_51a000(4);
                break;
            }
            normal_TransSaveShowMsg_519ff0(-1);
            o = ((Wid005194F0 *)UiEntryListFindByTag_28ea40(D_004847D8, 4));
            if (o != 0) {
                UiEntryListResetEntryRect_28eb40(D_004847D8, o);
                if (r != 7) {
                    tmp = 0;
                    o2 = ((Wid005194F0 *)UiEntryListFindByTag_28ea40(D_004847D8, 2));
                    if (o2 != 0 && o2->field016 == SaveGetLastPort_376200()) {
                        SaveFetchLastSlot_37ba10(&tmp);
                    }
                    o->field016 = tmp;
                    while (o->field016 >= 3) {
                        o->field016 -= 1;
                        o->field01A += 1;
                    }
                }
            }
            UiEntryListSelectByTag_28ea90(D_004847D8, 4, 0);
            normal_TransSavePanelFade_518700(1);
            PlayMenuSeThunk_289ef0(0x23);
        } else {
            normal_TransSaveSetError_51a000(5);
        }
        break;
    }
    return 1;
}
