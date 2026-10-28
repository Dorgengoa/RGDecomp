#include "types.h"

class V400 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void s1C(void *p, bool b, s32 z) { VCM(void, (void *, void *, bool, s32), 0x1C, p, b, z); }
};

struct O400 { s32 m0; s32 m4; V400 *m8; V400 *mC; V400 *m10; };

extern "C" struct BigA400 { void *v; s32 pad[3]; } D_00465770;
extern "C" struct BigB400 { void *v; s32 pad[3]; } D_00465778;
extern "C" struct BigC400 { void *v; s32 pad[3]; } D_00465780;

extern "C" s32 WorldSubsysLoad_4004a0(O400 *o, void *a1, s32 a2, s32 a3)
{
    if (a1 == 0) {
        return 0;
    }
    if (o->m0 == 0) {
        return 0;
    }
    o->m4 = a3;
    if (o->m8 != 0) {
        o->m8->s1C(a1, D_00465770.v != 0, 0);
    }
    if (o->mC != 0) {
        o->mC->s1C(a1, D_00465778.v != 0, 0);
    }
    if (o->m10 != 0) {
        o->m10->s1C(a1, D_00465780.v != 0, 0);
    }
    return 1;
}
