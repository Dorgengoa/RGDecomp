/* rgp:protos */
#line 1
#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v15(f32 a0) { return VCM(s32, (void *, f32), 0x44, a0); }
};

extern "C" void GetDrawCtxNameTable_15de40(void);
extern "C" void InfoCfgParseModelsThunk_1abfe0(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_0045B6D8[];

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    void *m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

struct Obj1 {
    u8 pad000[0x474];
    s32 m474;
};

extern "C" s32 Character2LoadInfoCfgModels_1ed190(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, struct Obj1 *p4)
{
    s32 rv4;
    s32 rv3;
    s32 t0;
    s32 r1;
    s32 r2;

    GetDrawCtxNameTable_15de40();
    if (p4 == 0) {
        return 0;
    }
    if (p1 == 0) {
        rv4 = 0;
    } else {
        rv3 = 1;
        if (p2 == 0) {
            rv3 = 0;
        } else {
            p0->m00 = p1;
            p0->m04 = D_0045B6D8;
            p0->m08 = p2;
            p0->m0C = p2;
            p0->m10 = p2;
            p0->m14 = p3;
            p0->m18 = 1;
            t0 = p4->m474;
            p0->m1C = t0;
            r1 = (InfoCfgParseModelsThunk_1abfe0(p4, p0), (s32)0);
            r2 = ((struct C432 *)p4)->v15(0.0f);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
