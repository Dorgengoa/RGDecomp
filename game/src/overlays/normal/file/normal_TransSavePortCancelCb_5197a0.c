/* rgp:protos */
#define RGP_SELF_normal_TransSavePortCancelCb_5197a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005197A0 -- linear prologue then a two-arm split on
 * normal_TransMenuIsQuickOpen_514a00's result. */

typedef struct Obj {
    u8  pad000[0x12];
    s16 f12;
} Obj;

extern s8    D_00484804;   /* gp - 0x96C */
extern void *D_004847D8;   /* gp - 0x998 */
extern void *D_004847D0;   /* gp - 0x9A0 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSavePortCancelCb_5197a0(Obj *p)
{
    D_00484804 = 1;
    normal_TransSaveShowMsg_519ff0(-1);
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 0);
    if (normal_TransMenuIsQuickOpen_514a00() != 0) {
        UiEntryListSelectByTag_28ea90(D_004847D8, 7, 0);
    } else {
        SaveMgrRelease_37bb70();
        StateMachineSetState_28ede0(D_004847D0, 7, 0);
    }
    return 1;
}
