/* rgp:protos */
#define RGP_SELF_AiCmdInvHasCategory_2c6540 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2c6540;
struct Obj0 { u8 pad000[0x18]; s32 m18; };
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdInvHasCategory_2c6540(E8_2c6540 *p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;

    r0 = ((struct Obj0 *)GetGameData_1fede0());
    r1 = ScriptSlotGetInt_2cc9c0(p0++);
    r2 = ((s32)InvFindInCategoryRange_3c8370(r0->m18, r1, 0, -1, 0, 0));
    if (r2 != 0) {
        ScriptSlotStoreIntRef_2cc900(p0, 1);
    } else {
        ScriptSlotStoreIntRef_2cc900(p0, 0);
    }
    return 1;
}
