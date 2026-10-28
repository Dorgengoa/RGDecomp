/* rgp:protos */
#define RGP_SELF_GameResumeFieldControl_27bca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct EntryFUN_0027bca0 {
    u8 pad0[0x4];
    s32 unk4;
} EntryFUN_0027bca0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GameResumeFieldControl_27bca0(void)
{
    s32 base;
    s32 i;
    EntryFUN_0027bca0 *e;
    s32 v;

    SetFieldControlActive_27bd30(0);
    ((void)(GetCurrentScene_1f5be0()), FieldControlActivate_27a960());
    base = ((s32)GetMesMgr_277e90());
    for (i = 0; i < 8; i++) {
        e = *(EntryFUN_0027bca0 **)((u8 *)base + (i * 4) + 0x1E00);
        if (e != NULL) {
            v = e->unk4;
            if (v != 0) {
                MesWinClose_2774f0(v);
            }
        }
    }
    MesWinClose_2774f0(base);
}
