#include "types.h"

extern void *GetCharaResMgr_1fdb60(void);
extern void *GetEffectMgr_2d9040(void);
extern void *CharaResFindById_1f0530(void *a, s32 id);
extern void  EffectGroupSetPaused_2e2c80(void *b, s32 id, s32 v);
extern void  EffectGroupSetHidden_2e2bd0(void *b, s32 id, s32 v);

void CharaEffectGroupsSetPausedHidden_27a300(s32 id, s32 p1, s32 p2, s32 flags)
{
    void *a;
    void *b;
    u8 *e;

    a = GetCharaResMgr_1fdb60();
    b = GetEffectMgr_2d9040();
    e = (u8 *)CharaResFindById_1f0530(a, id);
    if (e == 0) {
        return;
    }
    if (flags & 1) {
        EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4), p1);
        EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4), p2);
    }
    if (id >= 0 && id < 0xC) {
        if (flags & 2) {
            EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4) - 0x3D1, p1);
            EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4) - 0x3D1, p2);
        }
        if (flags & 4) {
            EffectGroupSetPaused_2e2c80(b, *(s16 *)(e + 4) - 0x3DD, p1);
            EffectGroupSetHidden_2e2bd0(b, *(s16 *)(e + 4) - 0x3DD, p2);
        }
    }
}
