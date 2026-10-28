/* rgp:protos */
#line 1
/* PARK (round 0, not attempted): m2c fails with "Unable to determine jump
   table for jr instruction" - needs the .rodata jump table read alongside
   the raw asm and a manual switch reconstruction. Not started. */
/* s49m: MATCH (two-entry, multi-.text scored with agent15/mscore.py) */
#pragma opt_propagation off
#pragma divbyzerocheck on
#include "types.h"

struct Sub;
struct Sub {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 get460() { return VCM0(u8, 0x460); }  /* +0x460 */
};

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct Sub * get7C() { return VCM0(struct Sub *, 0x7C); }  /* +0x7C */
};

extern "C" void *memset(void *, s32, u32);
extern "C" u8 *EquipSlotGetAbilityKind0Rec_3a0780(Obj *);
extern "C" char D_00483770[16] __attribute__((section(".sdata")));

extern "C" Sub *__attribute__((naked)) EquipSlotGetOwnerThunk_39f840(Obj *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *124(%eax)"); 

}

extern "C" char *func_0039F840_e1(Obj *o)
{
    u8 *p;
    Sub *sub;
    u8 idx;
    s16 v;
    char *s;

    p = EquipSlotGetAbilityKind0Rec_3a0780(o);
    if (p == 0) {
        return 0;
    }
    sub = o->get7C();
    idx = 0;
    if (sub != 0) {
        idx = sub->get460();
    }
    memset(D_00483770, 0, 0x10);
    v = ((s16 *)(p + 0x4C))[idx];
    if (v >= 0) {
        s = D_00483770;
    D_00483770[0] = 'C';
    s[1] = 'H';
    s[2] = '_';
    s[3] = v / 100 % 10 + '0';
    s[4] = v / 10 % 10 + '0';
    s[6] = 0;
    s[5] = v % 10 + '0';
    }
    return D_00483770;
}
