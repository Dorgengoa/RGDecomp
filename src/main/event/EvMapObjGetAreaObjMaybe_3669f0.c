#include "types.h"

typedef struct S_003669f0 {
    u8 pad0[0xA0];
    s32 fA0;
} S_003669f0;

extern void *GetMapMgr_201a90(void);
extern void *TargetRefGetId_2e7120(s32 *);
extern void *MapSlotsFindById_1e4b90(void *, void *, s32);
extern s32 MapDataIsLoaded_1e79d0(void *);
extern void *EvMapObjGetName_366b90(S_003669f0 *);
extern s32 MapDataFindObjsByName_1e6d40(void *, void *, s32 *, s32);

s32 EvMapObjGetAreaObjMaybe_3669f0(S_003669f0 *self, s32 i)
{
    s32 buf[0x140];
    void *a;
    void *b;
    s32 n;
    a = GetMapMgr_201a90();
    b = TargetRefGetId_2e7120(&self->fA0);
    a = MapSlotsFindById_1e4b90(a, b, 0);
    if (a == 0) goto zeroA;
    if (MapDataIsLoaded_1e79d0(a) != 0) goto ok;
zeroA:
    return 0;
ok:
    n = MapDataFindObjsByName_1e6d40(a, EvMapObjGetName_366b90(self), buf, 0x140);
    if (i < 0) goto zero;
    if (n > i) goto ok2;
zero:
    return 0;
ok2:
    return buf[i];
}
