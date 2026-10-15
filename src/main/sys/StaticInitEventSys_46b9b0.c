#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void EventStaticRecInitRelated_258f40(void *);
extern void EventCastSlotTableCtor_258e50(void *);
extern void MemStackCtor_14e030(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482020;
extern s32 D_0048202C;
extern s32 D_00482030;
extern s32 D_0048203C;
extern u8 D_004BD950[];
extern u8 D_004BDDB0[];
extern u8 D_004BE0B0[];
extern u8 D_004BE110[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEventSys_46b9b0(void)
{
    IosBaseInitCtor_102bd0(&D_0048202C);
    RegisterGlobalObject_100dc0(&D_0048202C, IosBaseInitDtor_102ee0, &D_00482020);
    WIosBaseInitCtor_103110(&D_0048203C);
    RegisterGlobalObject_100dc0(&D_0048203C, WIosBaseInitDtor_103420, &D_00482030);
    EventStaticRecInitRelated_258f40(D_004BD950);
    EventCastSlotTableCtor_258e50(D_004BDDB0);
    MemStackCtor_14e030(D_004BE0B0);
    MemStackCtor_14e030(D_004BE110);
}
