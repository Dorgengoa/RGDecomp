#include "types.h"

class V419 {
public:
    virtual void s08();
    virtual void s0C();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1C(void *p, bool b, s32 z);
};

struct O419 { s32 m0; s32 m4; V419 *m8; V419 *mC; V419 *m10; };

extern struct BigA419 { void *v; s32 pad[3]; } D_00465790;
extern struct BigB419 { void *v; s32 pad[3]; } D_00465788;
extern struct BigC419 { void *v; s32 pad[3]; } D_00465798;

extern "C" s32 WorldSubsysLoad_419a10(O419 *o, void *a1, s32 a2, s32 a3)
{
    if (a1 == 0) {
        return 0;
    }
    if (o->m0 == 0) {
        return 0;
    }
    o->m4 = a3;
    if (o->mC != 0) {
        o->mC->s1C(a1, D_00465790.v != 0, 0);
    }
    if (o->m8 != 0) {
        o->m8->s1C(a1, D_00465788.v != 0, 0);
    }
    if (o->m10 != 0) {
        o->m10->s1C(a1, D_00465798.v != 0, 0);
    }
    return 1;
}
