#include "types.h"

/* MATCHED.  0xB0/0x6C smart-pointer RELEASE FAMILY, STACK-SLOT variant
 * (levers.d/main-session24-levers names the 14-unit family; this is the
 * sub-family whose handle lives in a STACK SLOT, not in a member).
 *
 * FOUR load-bearing spellings, all measured on ix82.  Do not "clean" any of
 * them away -- each is worth words:
 *
 * 1. THE UNION ADDRESS PUN (levers.d/mwcc-union-address-pun).
 *      { HPun34 hu; hu.i = (s32)&sp24; temp_2 = *hu.p; }
 *    mwcc's IRO propagator is MEMBER-TYPED and will not forward a value
 *    stored through `.i` to a load of `.p`, so the frame address stays
 *    opaque, is materialised at the USE (after the call) and lands in a
 *    CALLER-SAVED register -- retail's
 *        addiu $v0,$sp,0x24 ; lw $v0,0($v0)
 *    A plain `temp_2 = sp24;` folds to `lw $v0,0x24($sp)`: one word short
 *    AND it pins the value in a callee-saved register.  A named pointer
 *    (`h = &sp24; f(h); temp_2 = *h;`) and a plain `(s32)` round-trip both
 *    FOLD -- measured, arms c1-c4 / rt_read.
 *
 * 2. `volatile` ON sp2C.  Retail stores temp_2 to 0x2C and reloads it after
 *    two calls; mwcc otherwise keeps it in a SECOND callee-saved register
 *    ($s1), which costs the sq/lq pair AND +16 of frame.  volatile is the
 *    only spelling found that forces the slot: a struct-typed Ref, a
 *    one-member union read back through the other member, and the folded
 *    `*(T **)(s32)&sp2C` round-trip were all enregistered anyway.
 *
 * 3. `volatile` ON sp28.  Retail emits `sw $0,0x28($29)` THREE times (the
 *    inner one, the shared outer one, and the branch-likely threaded copy).
 *    Without volatile mwcc cross-jumps the inner store into the outer one
 *    and the unit is one word short.
 *
 * 4. DECLARATION ORDER IS THE STACK SLOT (levers.d/mwcc-stack-slot-decl-order):
 *    mwcc assigns the slots top-down in REVERSE declaration order, so the
 *    list must read sp2C, sp28, sp24 to land them at 0x2C, 0x28, 0x24.
 *
 * Plus the family's own two: the MATERIALISED BOOL `((p != NULL) ^ 1) != 0`
 * and the SINGLE EXIT `goto done`.  Writing `return temp_16;` at the early
 * exit instead gives mwcc a sinkable copy for the branch's delay slot, so it
 * emits the plain branch + a second `b` where retail threads one `bnel`.
 */


struct Obj34;

class VE34 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct Obj34 { VE34 *unk0; s32 unk4; };
union HPun34 { Obj34 **p; s32 i; };

extern "C" void AttackObjBaseAssign_22e710(void *, s32);
extern "C" void HandleHeapPoolAlloc_312880(Obj34 **, s32, s32);
extern "C" s32 GetObjRefTable_313de0(void);
extern "C" s32 GetJudgeObjectHeap_313df0(void);
extern "C" s32 HandleRegistryRegister_3147e0(s32, Obj34 **);
extern "C" void *AttackObjCopyCtor_317600(void *);

extern "C" s32 AttackObjCloneAndRegister_3348e0(s32 arg0) {
    Obj34 *volatile sp2C;
    Obj34 *volatile sp28;
    Obj34 *sp24;
    Obj34 *temp_2;
    void *var_4;
    s32 temp_16;
    s32 rc;
    VE34 *q;
    Obj34 *p;
    Obj34 *p2;

    HandleHeapPoolAlloc_312880(&sp24, GetJudgeObjectHeap_313df0(), 0x1A0);
    { HPun34 hu; hu.i = (s32)&sp24; temp_2 = *hu.p; }
    sp2C = temp_2;
    if (temp_2 != NULL) {
        var_4 = (void *)temp_2->unk0;
    } else {
        var_4 = NULL;
    }
    if (var_4 != NULL) {
        var_4 = AttackObjCopyCtor_317600(var_4);
    }
    if (var_4 == NULL) {
        return 0;
    }
    AttackObjBaseAssign_22e710(var_4, arg0);
    sp28 = sp2C;
    temp_16 = HandleRegistryRegister_3147e0(GetObjRefTable_313de0(), (Obj34 **)&sp28);
    p = sp28;
    if (((p != NULL) ^ 1) != 0) {
        goto done;
    }
    if (p != NULL) {
        p->unk4 = p->unk4 - 1;
    }
    p2 = sp28;
    rc = (p2 != NULL) ? p2->unk4 : 0;
    if ((rc == 0) && (p2 != NULL)) {
        q = p2->unk0;
        if (q != NULL) {
            q->v25(-1);
        }
        sp28->unk4 = 0;
        sp28 = (Obj34 *)NULL;
    }
    sp28 = (Obj34 *)NULL;
done:
    return temp_16;
}
