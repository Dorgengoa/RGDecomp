#include "types.h"

typedef struct E_001e2fd0 { u8 b[0x1CC]; } E_001e2fd0;

typedef struct S_001e2fd0 {
    u8 pad0[0x1928];
    E_001e2fd0 arr1928[1];
} S_001e2fd0;

extern s32 MapDataIsLoaded_1e79d0(E_001e2fd0 *);
extern void MapAreaInit_1dcf90(E_001e2fd0 *);
extern void MapAreaApplyDef_1dc9f0(E_001e2fd0 *, s32, s32);
extern s32 MapMgrGetHeap_1e5810(S_001e2fd0 *);
extern s32 MapAreaBeginLoad_1da380(E_001e2fd0 *, s32, s32, s32);

s32 MapAreaSlotLoad_1e2fd0(S_001e2fd0 *self, s32 i, s32 p2, s32 p3, s32 p4, s32 p5)
{
    E_001e2fd0 *e;
    if (p2 == 0) return 0;
    if (i < 0) goto zero;
    if (i < 4) goto ok;
zero:
    return 0;
ok:
    if (MapDataIsLoaded_1e79d0(&self->arr1928[i]) != 0) return 0;
    e = &self->arr1928[(u32)i];
    MapAreaInit_1dcf90(e);
    MapAreaApplyDef_1dc9f0(e, p2, p3);
    return MapAreaBeginLoad_1da380(e, MapMgrGetHeap_1e5810(self), p4, p5);
}
