/* rgp:protos */
#define RGP_SELF_normal_TransSaveSlotListEnterCb_519d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519D50 -- two field stores through the parameter before it is
 * copied to a callee-saved register, then four calls. */
typedef struct Obj {
    u8  pad00[0xA];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveSlotListEnterCb_519d50(Obj *p, void *q)
{
    p->f0E = 0x31;
    p->f0A = 2;
    SaveUiWidgetFadeIn_37b490(0x75A2);
    normal_TransSaveSlotCursorBob_518990(p, q, 1);
    normal_TransSaveSlotMoveCb_519dd0(p);
    SaveUiScrollBarThumbPlace_3777a0(p, 0x75A1, 0);
    return 1;
}
