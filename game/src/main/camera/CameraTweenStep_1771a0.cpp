#include "types.h"

/* arg0->unkC0 is a vtable POINTER FIELD (not the object's own vtbl at
   offset 0) -- same "vptr lands wherever the first virtual is declared"
   shape as MenuItemModelDraw_2a7090/ObjMgrFindByEncounterSlotIdMaybe_3bb0c0. Kept as a SEPARATE view type from
   the plain-data view below: mixing named data fields into the same
   class as the virtuals would shift their offsets by the vptr's 4 bytes;
   two views over the same `arg0` pointer sidesteps that. */
struct Vtbl {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void v10(f32 a) { VCM(void, (void *, f32), 0x30, a); }
    
    
    
    void v14() { VCM0(void, 0x40); }
};

typedef struct {
    u8 pad00[0x50];
    u8 f50[0x10];
    u8 f60[0x10];
    f32 f70;
    u8 pad74[0xE0 - 0x74];
    u8 fE0[0x10];
    u8 fF0[0x10];
    f32 f100;
    f32 f104;
    s32 f108;
} Data;

extern "C" void VecSub_13be40(void *, void *, void *);
extern "C" void VecScale_13be00(void *, void *, f32);
extern "C" void VecAddInPlace_13e070(void *, void *);

extern "C" void CameraTweenStep_1771a0(void *arg0)
{
    Data *d = (Data *)arg0;
    Vtbl *v = (Vtbl *)arg0;
    u8 sp30[0x10] __attribute__((aligned(16)));
    u8 sp20[0x10] __attribute__((aligned(16)));
    f32 temp_f12;

    VecSub_13be40(sp30, d->fF0, d->f60);
    VecSub_13be40(sp20, d->fE0, d->f50);
    VecScale_13be00(sp30, sp30, 1.0f / d->f100);
    VecScale_13be00(sp20, sp20, 1.0f / d->f104);
    VecAddInPlace_13e070(d->f60, sp30);
    VecAddInPlace_13e070(d->f50, sp20);
    if (d->f108 != 0) {
        v->v14();
        temp_f12 = d->f70;
        if (temp_f12 != 0.0f) {
            v->v10(temp_f12);
        }
    }
}
