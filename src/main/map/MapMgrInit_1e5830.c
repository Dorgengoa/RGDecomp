#include "types.h"

extern void MapLocInit_1e5b10(void *);
extern void MapPendingLoadReset_1e5b40(void *);
extern s32 MapEnvSlotsInit_1e5f40(void *);
extern void MapSkyInit_1e6360(void *);
extern void WarpMenuReset_39e020(void *);
extern void MapCaptionInit_33fd90(void *);
extern void MapAreaInit_1dcf90(void *);
extern void MapDataInit_1e7c50(void *);
extern void MapIdListClear_1e5ac0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x60];
    s32 m60;
    s32 m64;
    u8 pad068[0x64];
    s32 mCC;
    s32 mD0;
    u8 pad0D4[0x21CC];
    s32 m22A0;
    s32 m22A4;
    s32 m22A8;
    s32 m22AC;
};

void MapMgrInit_1e5830(struct Obj0 *p0)
{
    s32 r3;
    s32 l7;

    MapLocInit_1e5b10(p0);
    MapLocInit_1e5b10((struct Obj0 *)((u8 *)p0 + 0x30));
    MapPendingLoadReset_1e5b40((struct Obj0 *)((u8 *)p0 + 0x20AC));
    p0->m60 = 0;
    p0->m64 = 0;
    r3 = MapEnvSlotsInit_1e5f40((struct Obj0 *)((u8 *)p0 + 0x68));
    p0->mCC = -1;
    p0->mD0 = -1;
    MapSkyInit_1e6360((struct Obj0 *)((u8 *)p0 + 0xE0));
    WarpMenuReset_39e020((struct Obj0 *)((u8 *)p0 + 0x18B0));
    MapCaptionInit_33fd90((struct Obj0 *)((u8 *)p0 + 0x18E8));
    l7 = 0;
    do {
        MapAreaInit_1dcf90((struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)p0 + (l7 * 0x1CC)) + 0x1928));
        l7 = (l7 + 1);
    } while (l7 < 4);
    MapDataInit_1e7c50((struct Obj0 *)((u8 *)p0 + 0x2058));
    MapIdListClear_1e5ac0((struct Obj0 *)((u8 *)p0 + 0x20B0));
    MapIdListClear_1e5ac0((struct Obj0 *)((u8 *)p0 + 0x2154));
    MapIdListClear_1e5ac0((struct Obj0 *)((u8 *)p0 + 0x21F8));
    p0->m22A0 = 0;
    p0->m22A4 = 0;
    p0->m22A8 = 0;
    p0->m22AC = 0x3F800000;
}
