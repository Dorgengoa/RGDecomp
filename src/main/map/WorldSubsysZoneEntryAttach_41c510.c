#include "types.h"

struct Obj41c510 { s32 f0; void *f4; u8 pad8[4]; u8 *fC; };
struct Ent41c510 { u8 pad0[0x10]; s16 f10; };

extern s32 D_004644A8[];
extern s32 D_004657B8[];
extern s32 MemStackArrayGet_3f23f0(void *p);
extern void DataTableInitWithCount_368b00(void *e, s32 r);
extern void WorldSubsysZoneEntryBind_41cc70(void *e, struct Ent41c510 *p1, s32 flag);

s32 WorldSubsysZoneEntryAttach_41c510(struct Obj41c510 *p0, struct Ent41c510 *p1)
{
    u8 *e;
    s32 idx;
    void *p;
    s32 r;

    if (p1 == 0) {
        return 0;
    }
    idx = p1->f10;
    if (idx < 0 || idx >= D_004644A8[0]) {
        return 0;
    }
    if (p0->f0 == 0) {
        return 0;
    }
    e = 0;
    if (p0->fC != 0) {
        e = p0->fC + idx * 152;
    }
    p = p0->f4;
    if (p != 0) {
        r = MemStackArrayGet_3f23f0(p);
        if (r != 0 && e != 0 && D_004657B8[0] == 0) {
            DataTableInitWithCount_368b00(e, r);
        }
    }
    if (e != 0) {
        WorldSubsysZoneEntryBind_41cc70(e, p1, D_004657B8[0] != 0);
    }
    return 1;
}
