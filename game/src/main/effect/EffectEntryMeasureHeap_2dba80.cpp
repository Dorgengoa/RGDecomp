/* rgp:protos */
#line 1
#include "types.h"

class Obj1B0 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v58() { VCM0(void, 0x58); }
    void v5C() { VCM0(void, 0x5C); }
};

class Obj190 {
public:
    u8 pad0[0x190];
    VC_VPTR_MEMBER; void v8() { VCM0(void, 0x8); }
    
    
    
    Obj1B0 * v18() { return VCM0(Obj1B0 *, 0x18); }
};

struct Mgr {
    u8 pad0[0x28];
    s32 m28;
};

extern "C" {
s32 MemStackAllocQw_14d950(Mgr *, s32);
void MemStackReturnToOwnerMaybe_14dad0(Mgr *);
s32 MemStackHeapAlloc_14db10(Mgr *, s32, s32, s32);
void MemStackHeapFree_14dcb0(Mgr *, s32);
u8 *MemStackNew_14e230(s32, Mgr *);
void ScriptVmSetCmdTable_176ae0(void *, void *, s32);
void ScriptVmInit_176af0(void *, s32, s32, s32, s32, s32);
void ScriptVmCtor_176be0(void *);
void ModelObjExCopy_1aff40(s32, Obj1B0 *, Mgr *);
void ModelObjExEffectsStopAll_1b0870(Obj1B0 *);
s32 MemStackGetFree_1c6d50(Mgr *);
void Character2Ctor_1ef2d0(void *, int, int, int);
Mgr *GetReadBuffHeap_2025e0(void);
void TargetRefCtorWrap_2db800(void *);
void EffectInstanceCtor_2db830(void *);
void TargetRefCtor_2e71f0(void *);
extern u8 D_00471670[0x400];
extern u8 D_004716F0[0x400];
extern u8 D_00471760[0x400];
extern u8 D_004E8050[0x400];
}

static inline s32 busy(Mgr *m)
{
    return m->m28 != 0;
}

extern "C" void EffectEntryMeasureHeap_2dba80(u8 *arg0)
{
    u8 buf1[0x60] __attribute__((aligned(16)));
    u8 buf2[0x60] __attribute__((aligned(16)));
    Mgr *m;
    s32 t0;
    bool nolock;
    bool locked;
    s32 h1;
    s32 h2;
    u8 *o;
    Obj1B0 *sub;
    s32 a;
    s32 b;
    s32 i;

    m = GetReadBuffHeap_2025e0();
    if (*(s16 *)(arg0 + 0xB4) != 0 && *(s16 *)(arg0 + 0xB6) == 0) {
        t0 = MemStackGetFree_1c6d50(m);
        locked = false;
        h2 = 0;
        nolock = !(bool)busy(m);
        if (*(s16 *)(arg0 + 0xC) == 1) {
            if (nolock) {
                h1 = MemStackHeapAlloc_14db10(m, 3, 0x29, 0x40);
                locked = true;
            } else {
                h1 = 0;
            }
            if (h1 != 0) {
                if ((o = MemStackNew_14e230(0x280, m)) != 0) {
                    *(void **)(o + 0x190) = D_004716F0;
                    *(s32 *)(o + 0x2C) = 0;
                    *(s32 *)(o + 0xC) = -1;
                    *(s16 *)(o + 4) = -1;
                    *(s32 *)(o + 8) = -1;
                    *(s16 *)(o + 2) = -1;
                    *(s16 *)(o + 6) = 1;
                    *(s32 *)(o + 0x14) = 0;
                    *(s32 *)(o + 0x18) = -1;
                    *(u8 *)(o + 0x170) = 0;
                    i = 0;
                    do {
                        *(s32 *)(o + 0xF0 + i * 4) = 0;
                        *(s32 *)(o + 0x130 + i * 4) = 0;
                        i++;
                    } while (i < 4);
                    *(s32 *)(o + 0x1C) = 0;
                    *(s16 *)(o + 0x20) = 0;
                    *(void **)(o + 0x190) = D_00471670;
                    ScriptVmCtor_176be0(o + 0x1A8);
                    TargetRefCtor_2e71f0(o + 0x200);
                    ((Obj190 *)o)->v8();
                }
                if (o != 0) {
                    if (nolock) {
                        MemStackReturnToOwnerMaybe_14dad0(m);
                    }
                    locked = false;
                    if (nolock) {
                        h2 = MemStackHeapAlloc_14db10(m, 3, 0x103, 0x40);
                        locked = true;
                    } else {
                        h2 = 0;
                    }
                    if (h2 != 0) {
                        *(s32 *)(o + 0x1FC) = h2;
                        a = MemStackAllocQw_14d950(m, 0x80);
                        b = MemStackAllocQw_14d950(m, 1);
                        ScriptVmCtor_176be0(buf1);
                        ScriptVmInit_176af0(buf1, *(s32 *)(arg0 + 0x90), a, 0x100, b, 2);
                        ScriptVmSetCmdTable_176ae0(buf1, D_004E8050, 0x200);
                        if (nolock) {
                            MemStackReturnToOwnerMaybe_14dad0(m);
                        }
                        locked = false;
                        *(s32 *)(arg0 + 0xB0) = t0 - MemStackGetFree_1c6d50(m);
                    }
                }
            }
        } else {
            if (nolock) {
                h1 = MemStackHeapAlloc_14db10(m, 3, 0x9E, 0x40);
                locked = true;
            } else {
                h1 = 0;
            }
            if (h1 != 0) {
                if ((o = MemStackNew_14e230(0x9D0, m)) != 0) {
                    EffectInstanceCtor_2db830(o);
                    *(void **)(o + 0x190) = D_00471760;
                    Character2Ctor_1ef2d0(o + 0x1A0, 0, 0, 0);
                    ScriptVmCtor_176be0(o + 0x930);
                    TargetRefCtorWrap_2db800(o + 0x98C);
                    ((Obj190 *)o)->v8();
                }
                if (o != 0) {
                    sub = ((Obj190 *)o)->v18();
                    ((Obj190 *)o)->v8();
                    if (sub != 0) {
                        sub->v5C();
                        ModelObjExCopy_1aff40(*(s32 *)(arg0 + 0x80), sub, m);
                    }
                    if (nolock) {
                        MemStackReturnToOwnerMaybe_14dad0(m);
                    }
                    locked = false;
                    if (nolock) {
                        h2 = MemStackHeapAlloc_14db10(m, 3, 0x103, 0x40);
                        locked = true;
                    } else {
                        h2 = 0;
                    }
                    if (h2 != 0) {
                        *(s32 *)(o + 0x988) = h2;
                        a = MemStackAllocQw_14d950(m, 0x80);
                        b = MemStackAllocQw_14d950(m, 1);
                        ScriptVmCtor_176be0(buf2);
                        ScriptVmInit_176af0(buf2, *(s32 *)(arg0 + 0x90), a, 0x100, b, 2);
                        ScriptVmSetCmdTable_176ae0(buf2, D_004E8050, 0x200);
                        if (nolock) {
                            MemStackReturnToOwnerMaybe_14dad0(m);
                        }
                        locked = false;
                        *(s32 *)(arg0 + 0xB0) = t0 - MemStackGetFree_1c6d50(m);
                        if (sub != 0) {
                            ModelObjExEffectsStopAll_1b0870(sub);
                            sub->v58();
                        }
                    }
                }
            }
        }
        if (locked) {
            MemStackReturnToOwnerMaybe_14dad0(m);
        }
        if (h2 != 0) {
            MemStackHeapFree_14dcb0(m, h2);
        }
        if (h1 != 0) {
            MemStackHeapFree_14dcb0(m, h1);
        }
    }
}
