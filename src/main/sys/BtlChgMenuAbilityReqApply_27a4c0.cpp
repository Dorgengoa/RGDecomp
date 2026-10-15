/* MATCH (s41m). Stale pre-match note follows -- PARK: 15 bad -> 5, right length.  Fixed: the vtable call is a real C++
   virtual (vptr 0, slot 0x30 = index 10); AbilityReqSet_27a450's THIRD argument is
   passed in $a2 with `lw`, so it is an INTEGER, not the f32 the draft had;
   and the two 8-byte stack structs are declared sp48-BEFORE-sp40 (slot
   order).  Residue: the 8-byte struct copy emits its two elements in the
   order 1,0 and retail emits 0,1 -- four spellings (aggregate assign, both
   element-wise orders, a u64 punned copy) are ONE object.  Same N=2
   rotation class as s23's MapSaveState_1e42a0. */
#include "types.h"
#pragma opt_propagation off

class VE27A4 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual s32 v10(void);
};

typedef struct { f32 val; f32 objf; } S_27a4c0;

extern "C" void func_4F9D60(S_27a4c0 *);
extern "C" s32 AbilityReqSet_27a450(s32, s16, s32, void *, s32);

extern "C" void BtlChgMenuAbilityReqApply_27a4c0(s32 arg0)
{
    S_27a4c0 sp48;
    S_27a4c0 sp40;
    s16 temp_17;
    VE27A4 *obj;
    s32 vres;
    S_27a4c0 *p;

    func_4F9D60(&sp40);
    sp48 = sp40;
    p = &sp48;
    obj = *(VE27A4 **)&p->objf;
    temp_17 = *(s16 *)((u8 *)obj + 0xA);
    vres = obj->v10();
    AbilityReqSet_27a450(arg0, temp_17, *(s32 *)&sp48.val, obj, vres);
}
