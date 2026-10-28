#include "types.h"

/* clone group cg06-003: store the two arguments, allocate an object of a
   fixed size out of the pool the first argument points at, run its
   constructor, park it at +0x0C, then hand it to virtual slot 0x0C with a
   FIVE-argument call (the 5th lands in $8) whose 4th operand is the
   `!= 0` test on a global word.  Members differ only in the allocation
   size, the constructor and that global. */

class VObj {
public:
    VC_VPTR_MEMBER;
    void slot0C(void *a, s32 b, s32 c, s32 d) { VCM(void, (void *, void *, s32, s32, s32), 0xC, a, b, c, d); }
};

typedef struct Holder {
    void *f00;
    s32 f04;
    s32 f08;
    VObj *f0C;
} Holder;

extern "C" s32 D_00465838[4];
extern "C" void *MemStackNew_14e130(s32 size, void *pool);
extern "C" VObj *DataTableCtor_410ed0(void *p);
extern "C" void DataTableInitWithCount_368b00(VObj *p, s32 x);

extern "C" s32 WorldSubsysInit_410b90(Holder *self, void *a1, s32 a2)
{
    VObj *p;

    if (a1 == 0) return 0;
    self->f00 = a1;
    self->f04 = a2;
    p = (VObj *)MemStackNew_14e130(0x94, self->f00);
    if (p != 0) p = DataTableCtor_410ed0(p);
    self->f0C = p;
    if (p == 0) return 0;
    p->slot0C(self->f00, 0, D_00465838[0] != 0, 0);
    DataTableInitWithCount_368b00(self->f0C, self->f04);
    return 1;
}
