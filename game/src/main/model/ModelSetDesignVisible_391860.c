/* rgp:protos */
#define RGP_SELF_ModelSetDesignVisible_391860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 Sprintf_1343b8(void *, void *, s32);
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00464228[];
extern u8 D_00464230[];
extern u8 D_00464238[];
extern u8 D_00464248[];

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
};

struct Obj1 {
    u8 pad000[0x24];
    u8 m24;
};

struct Obj2 {
    u8 pad000[0x24];
    u8 m24;
};

struct Obj3 {
    u8 pad000[0x24];
    u8 m24;
};

void ModelSetDesignVisible_391860(s32 p0, struct Obj0 *p1, s32 p2)
{
    u128 v50;
    s16 t0;
    s32 r0;
    s32 l1;
    s32 rv9;
    struct Obj1 *r3;
    struct Obj1 * rv4;
    s32 r5;
    struct Obj2 *r6;
    struct Obj2 * rv7;
    s32 r8;
    struct Obj3 *r10;

    if (p0 != 0) {
        if (p1 == 0) {
            return;
        }
        t0 = p1->m04;
        if (t0 != 0x7DC) {
            if (t0 != 0x7E1) {
                return;
            }
        }
        r0 = ModelGetRootFrame_1511a0(p0);
        if (r0 != 0) {
            l1 = 0;
            do {
                if (t0 == 0x7DC) {
                    Sprintf_1343b8(&v50, D_00464228, (l1 + 1));
                }
                rv9 = 0x7E1;
                if (t0 == 0x7E1) {
                    r3 = FrameFindByName_149ed0(r0, D_00464230);
                    rv4 = 0;
                    if (r3 != 0) {
                        if (p2 != -1) {
                            r3->m24 = 1;
                        } else {
                            r3->m24 = 0;
                        }
                        rv4 = (struct Obj1 *)r3;
                    }
                    r5 = Sprintf_1343b8(&v50, D_00464238, l1);
                    r6 = FrameFindByName_149ed0(r0, &v50);
                    rv7 = 0;
                    if (r6 != 0) {
                        if (l1 == p2) {
                            r6->m24 = 1;
                        } else {
                            r6->m24 = 0;
                        }
                        rv7 = (struct Obj2 *)r6;
                    }
                    r8 = Sprintf_1343b8(&v50, D_00464248, l1);
                    rv9 = r8;
                }
                r10 = FrameFindByName_149ed0(r0, &v50);
                if (r10 != 0) {
                    if (l1 == p2) {
                        r10->m24 = 1;
                    } else {
                        r10->m24 = 0;
                    }
                }
                l1 = (l1 + 1);
            } while (l1 < 8);
        }
        return;
    }
}
