/* rgp:protos */
#define RGP_SELF_MapDefCmdBlockSetName_1eb9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x3A];
    s16 m3A;
    u8 pad03C[0x8];
    s32 m44;
};

struct Obj1 {
    s32 m00;
};

s32 MapDefCmdBlockSetName_1eb9d0(s32 p0, s32 p1)
{
    s32 t0;
    struct Obj0 *r0;
    s32 t2;
    s16 t3;
    s16 t4;
    struct Obj1 *r1;
    s32 r2;
    s32 r3;

    if (p1 != 1) {
        return 1;
    }
    t0 = D_004818FC;
    if (t0 != 0) {
        if (D_004818F8 != 0) goto k1;
    }
    return 1;
k1:
    r0 = (struct Obj0 *)MapAreaDefGetRecTable_1dcf20(t0);
    t2 = r0->m44;
    if (t2 != 0) {
        t3 = r0->m3A;
        t4 = D_00481904;
        if (t3 > t4) goto k2;
    }
    return 1;
k2:
    r1 = (struct Obj1 *)MapBlockGetInfo_1e00b0(t2 + t4 * 204);
    r2 = ScriptArgGetStr_1ecb80(p0);
    r3 = ((s32)MemStackStrDup_14cff0(r2, D_004818F8));
    r1->m00 = r3;
    return 1;
}
