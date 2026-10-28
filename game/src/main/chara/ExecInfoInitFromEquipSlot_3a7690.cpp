#include "types.h"

extern "C" s32 ExecInfoInit_3a7940(void *);

extern "C" s32 TableFindByNameHashed_3f86e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_004837B0;

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;
struct Obj4;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj2 *m08;
    u8 pad00C[0xC];
    s32 m18;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj2 {
    u8 pad000[0x50];
    struct Obj3 *m50;
};

struct Obj3 {
    u8 pad000[0x8];
    s32 m08;
};

struct Obj4 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x2];
    s16 m08;
    s16 m0A;
    s32 m0C;
    s32 m10;
};

class V { public:
VC_VPTR_MEMBER;
















































































































































































void * lookup(s32 a0) { return VCM(void *, (void *, s32), 0x2CC, a0); }
};
extern "C" V *ActorFindById_3eb870(Obj0 *,s32);
extern "C" s32 EquipSlotGetRec_3a0790(void *);
extern "C" s32 ExecInfoInitFromEquipSlot_3a7690(Obj4 *self,s32 id,s32 idx,s32 name){
    V *v;
    void *p;
    s32 handle;
    s32 r;
    ExecInfoInit_3a7940(self);
    if(D_004837B0==0)return 0;
    v=ActorFindById_3eb870(D_004837B0,id);
    if(v==0)return 0;
    p=v->lookup(idx);
    if(p==0)return 0;
    handle=EquipSlotGetRec_3a0790(p);
    if(handle==0)return 0;
    r=0;
    if(name!=0)r=TableFindByNameHashed_3f86e0(D_004837B0->m08->m50->m08,name);
    self->m04=3;self->m08=id;self->m0C=handle;self->m10=r;
    return 1;
}
