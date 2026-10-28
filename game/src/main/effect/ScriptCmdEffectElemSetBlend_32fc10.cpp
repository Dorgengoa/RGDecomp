#include "types.h"

/* jalr $25 is C++ VIRTUAL DISPATCH: mwcc reaches $t9 only for a virtual call.
   The vptr sits at 0x190 of the object, so the class carries 0x190 bytes of
   padding BEFORE its first virtual and mwcc puts the vptr after them.
   Slot byte offset = 8 + 4*index (two leading vtable words). */
struct CMgr {
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * v22() { return VCM0(u8 *, 0x60); }
};

struct Slot { u32 lo, hi; };

extern "C" s32 ScriptSlotGetInt_3348b0(Slot *);
extern "C" void *D_004826E0;

extern "C" s32 ScriptCmdEffectElemSetBlend_32fc10(Slot *args, s32 argc)
{
    s32 i;
    s32 cnt;
    s32 v;
    u8 *base;
    s32 limit;

    i = ScriptSlotGetInt_3348b0(args++);
    v = ScriptSlotGetInt_3348b0(args++);
    cnt = 1;
    if (argc == 3) {
        cnt = ScriptSlotGetInt_3348b0(args);
    }
    base = ((CMgr *)D_004826E0)->v22();
    if (base == 0) {
        return 1;
    }
    limit = i + cnt;
    for (; i < limit; i++) {
        *(s32 *)(base + i * 0xC0 + 0xC) = v;
    }
    return 1;
}
