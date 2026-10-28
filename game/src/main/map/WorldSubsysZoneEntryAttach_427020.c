/* rgp:protos */
#define RGP_SELF_WorldSubsysZoneEntryAttach_427020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj41c510 { s32 f0; void *f4; u8 pad8[4]; u8 *fC; };
struct Ent41c510 { u8 pad0[0x10]; s16 f10; };

extern s32 D_004644A8[];
extern s32 D_00465800[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysZoneEntryAttach_427020(struct Obj41c510 *p0, struct Ent41c510 *p1)
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
        r = ((s32)MemStackArrayGet_3f23f0(p, (int)(idx)));
        if (r != 0 && e != 0 && D_00465800[0] == 0) {
            DataTableInitWithCount_368b00(e, r);
        }
    }
    if (e != 0) {
        WorldSubsysZoneEntryBind_427480(e, p1, D_00465800[0] != 0);
    }
    return 1;
}
