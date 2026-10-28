/* rgp:protos */
#define RGP_SELF_LoadHandlePoll_1ccb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj001ccb00 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
} Obj001ccb00;

/*rgp*/
/*rgp*/
/*rgp*/

void LoadHandlePoll_1ccb00(Obj001ccb00 *arg0)
{
    s32 t;
    s64 t2;

    if (arg0->unk0 >= 0) {
        t = ((s32)GetLoaderMgr_1f59d0());
        t2 = LoaderGetStatus_1cd4f0(t, arg0->unk0);
        arg0->unk2 = (s16) t2;
        if ((s16) t2 != 0) {
            arg0->unk4 = ((s32)LoaderGetData_1cd490(t, arg0->unk0, (u8 *)arg0 + 8));
        }
    }
}
