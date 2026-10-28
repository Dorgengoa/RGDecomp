/* rgp:protos */
#define RGP_SELF_normal_TransSaveSlotListConfirm_519c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519C60 -- map-warp entry.  The two failing probes share one
 * `func_376B20(6); return 0;` tail, so they are a `||` (the `bnel` delay slot
 * carries the shared `addiu $4,$0,6`). */

typedef struct Ent {
    u8  pad000[0x12];
    s16 f012;
    s16 f014;
    s16 f016;
} Ent;

extern void *D_00484724;          /* gp - 0xA4C */
extern void *D_004847D8;          /* gp - 0x998 */
extern volatile s16 D_004847E8;          /* gp - 0x988 */
extern s16   D_004847EC;          /* gp - 0x984 */

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

s32 normal_TransSaveSlotListConfirm_519c60(Ent *e)
{
    void *h;
    s32 t;

    D_004847EC = e->f016;
    t = e->f016 + e->f012;
    D_004847E8 = t;
    if (SaveSlotEntryIsBrokenAt_373540(D_00484724, t) != 0 || SaveSlotEntryIsNoSpaceAt_373480(D_00484724, D_004847E8) != 0) {
        PlayMenuSeThunk_289ef0(6);
        return 0;
    }
    ReturnZero_207fe0();
    PlayMenuSeThunk_289ef0(5);
    SaveMgrSetSlot_37b9c0(D_004847E8);
    h = SlotRecordFindById_3e4e80(GetGameData_1fede0(), D_004847E8);
    if (((unsigned char)SavePortCardIsFormatted_37b950()) == 0 || h == 0 || AnyOfFourIdsNegative_3eec60(h) != 0) {
        UiEntryListSelectByTag_28ea90(D_004847D8, 5, 1);
    } else {
        UiEntryListSelectByTag_28ea90(D_004847D8, 6, 1);
    }
    return 1;
}
