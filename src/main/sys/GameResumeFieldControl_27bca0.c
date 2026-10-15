#include "types.h"

typedef struct EntryFUN_0027bca0 {
    u8 pad0[0x4];
    s32 unk4;
} EntryFUN_0027bca0;

extern s32 GetCurrentScene_1f5be0(void);
extern void MesWinClose_2774f0(s32 arg0);
extern s32 GetMesMgr_277e90(void);
extern void FieldControlActivate_27a960(s32 arg0);
extern void SetFieldControlActive_27bd30(s32 arg0);

void GameResumeFieldControl_27bca0(void)
{
    s32 base;
    s32 i;
    EntryFUN_0027bca0 *e;
    s32 v;

    SetFieldControlActive_27bd30(0);
    FieldControlActivate_27a960(GetCurrentScene_1f5be0());
    base = GetMesMgr_277e90();
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
