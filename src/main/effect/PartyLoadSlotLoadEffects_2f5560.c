#include "types.h"

/* MAIN PartyLoadSlotLoadEffects_2f5560.  `lh 0x6($19)` is re-loaded at every bottom test
   (the calls in the body can move it), and the 16-byte scratch at
   0x50($29) is an uninitialised out-parameter of EffectRequestByName_2e29d0. */

typedef struct Obj5560 {
    u8  pad00[4];
    s16 m04;            /* 0x04 */
    s16 m06;            /* 0x06 */
    u8  pad08[0x40];
    s32 m48[1];         /* 0x48 */
} Obj5560;

typedef struct Tmp5560 {
    u8 d[0x10];
} Tmp5560;

extern void *GetEffectMgr_2d9040(void);
extern void *PartyLoadSlotGetEffectGroup_2f5540(Obj5560 *);
extern void EffectReleaseByGroup_2e12f0(void *, void *);
extern void *GetLoaderMgr_1f59d0(void);
extern void LoaderQueueAppendSeparator_1cd670(void *);
extern void *GetCharaResMgr_1fdb60(void);
extern void *PartyLoadSlotGetId_2f5550(Obj5560 *);
extern void *CharaResGetRestMemStackById_1f0060(void *, void *);
extern void EffectRequestByName_2e29d0(Tmp5560 *, void *, void *, s32, void *);

void PartyLoadSlotLoadEffects_2f5560(Obj5560 *o)
{
    Tmp5560 t;
    void *a;
    void *b;
    void *c;
    s32 i;

    a = GetEffectMgr_2d9040();
    if (o->m04 > 0) {
        EffectReleaseByGroup_2e12f0(a, PartyLoadSlotGetEffectGroup_2f5540(o));
    }
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    b = GetCharaResMgr_1fdb60();
    c = CharaResGetRestMemStackById_1f0060(b, PartyLoadSlotGetId_2f5550(o));
    if (c == 0) {
        return;
    }
    for (i = 0; i < o->m06; i++) {
        EffectRequestByName_2e29d0(&t, a, c, o->m48[i], PartyLoadSlotGetEffectGroup_2f5540(o));
    }
}
