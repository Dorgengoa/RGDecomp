/* rgp:protos */
#define RGP_SELF_factory_FactorySlotFill_500160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec {
    s16 f00;
    s16 f02;
    u16 f04;
} Rec;

typedef struct Src {
    s16 f00;
} Src;

typedef struct Slot {
    Src *f00;
    s16  f04;
    s16  f06;
    s16  f08;
    s16  f0A;
    s16  f0C;
} Slot;

typedef struct Job {
    f32 f00;
    f32 f04;
    f32 f08;
    s32 f0C;
    s16 f10;
} Job;

extern f32 D_0045B080[4];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactorySlotFill_500160(void *w, Src *b, s32 c, s32 d, s32 e)
{
    Job   job __attribute__((aligned(16)));
    Slot *s;
    Rec  *r;

    if (b == 0 || c <= 0) {
        return 0;
    }
    factory_FactorySlotPickUp_5000f0(w, d, e);
    s = ((Slot *)factory_FactorySlotFindFree_503630(w));
    if (s == 0) {
        return 0;
    }
    r = ((Rec *)factory_FactoryGridCellAt_5037f0(w, d, e));
    if (r == 0) {
        return 0;
    }
    if (!(r->f04 & 0x8000) == 0) {
        return 0;
    }
    if (r->f00 != 0xD) {
        return 0;
    }
    if (((s32)factory_FactoryPartGroupGetObjById_5035b0(w, r->f00, r->f02)) == 0) {
        return 0;
    }
    job.f00 = factory_FactoryGridCellCenterX_503760(w, d);
    job.f04 = D_0045B080[0];
    job.f08 = factory_FactoryGridCellCenterZ_503730(w, e);
    job.f0C = b->f00;
    job.f10 = 0;
    factory_FactorySlotClear_4ff5d0(s);
    s->f00 = b;
    s->f04 = b->f00;
    s->f06 = c;
    s->f08 = factory_FactoryMarkerAdd_4ea1a0(&job);
    s->f0A = d;
    s->f0C = e;
    return 1;
}
