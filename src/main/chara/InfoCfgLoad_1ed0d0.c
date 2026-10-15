#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 InfoCfgParseAll_1afd00(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B6D8[];

struct Obj0;

struct Obj0 {
    s32 m00;
    void *m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
};

s32 InfoCfgLoad_1ed0d0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 rv4;
    s32 rv3;
    s32 rv2;
    s32 r0;
    s32 r1;

    rv4 = rv3;
    if (p4 == 0) {
        rv4 = 0;
    } else {
        rv3 = rv2;
        if (p1 == 0) {
            rv3 = 0;
        } else {
            rv2 = 1;
            if (p2 == 0) {
                rv2 = 0;
            } else {
                r0 = GetDrawCtxNameTable_15de40();
                p0->m00 = p1;
                p0->m04 = D_0045B6D8;
                p0->m08 = p2;
                p0->m0C = p2;
                p0->m10 = p2;
                p0->m14 = p3;
                p0->m18 = 0;
                r1 = InfoCfgParseAll_1afd00(p4, p0);
                rv2 = 1;
            }
            rv3 = rv2;
        }
        rv4 = rv3;
    }
    return rv4;
}
