#include "types.h"

class V48 {
public:
    VC_VPTR_MEMBER;   
       
       
       
    s32 f16() { return VCM0(s32, 0x48); }
};

class VBig {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x14() { VCM0(void, 0x40); }
    
    
    
    void x18() { VCM0(void, 0x50); }
    void x19() { VCM0(void, 0x54); }
    void x20() { VCM0(void, 0x58); }
    
    
    
    
    
    
    
    
    
    
    
    void x32() { VCM0(void, 0x88); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x64() { VCM0(void, 0x108); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x86() { VCM0(void, 0x160); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x100() { VCM0(void, 0x198); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 g304() { return VCM0(s32, 0x4C8); }
    
    
    
    
    
    
    s32 g311() { return VCM0(s32, 0x4E4); }
    void g312(s32 a0) { VCM(void, (void *, s32), 0x4E8, a0); }
};

struct Obj20 {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x20 - 0x18];
    s32 unk20;
};

extern "C" {
f32 RandFloat_13c010(void);
Obj20 *GetGameData_1fede0(void);
void ScriptSlotStoreIntRef_2cc900(s32, s32);
s32 CharaSysStateUnitFlag7EBit3Related_3a38e0(s32);
VBig *CharaMgrPoolFindById_3a8c60(s32, s32);
V48 *CharaFindSlotByCompositeId_3ad300(VBig *, s32);
extern s32 D_004DB928[0x100];
}

typedef s32 (*VF0)(void *);
typedef void (*VF1)(void *, s32);
#define VSLOT(o, off) (*(void **)(*(u8 **)(o) + (off)))

extern "C" s32 AiCmdCharaGaugeLevelRollMaybe_2c2ff0(s64 *arg0, s32 arg1)
{
    bool hit;
    s32 lvl;
    s32 th;
    V48 *p;
    Obj20 *g;
    VBig *o;

    g = GetGameData_1fede0();
    if (CharaSysStateUnitFlag7EBit3Related_3a38e0(g->unk20) == 0) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
        return 1;
    }
    o = CharaMgrPoolFindById_3a8c60(g->unk14, D_004DB928[0]);
    if (o == NULL) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
        return 1;
    }
    hit = 0;
    lvl = 0;
    if (o->g304() != 0) {
        p = CharaFindSlotByCompositeId_3ad300(o, 0x86);
        if (p != NULL && p->f16() != 0) {
            lvl = o->g311();
            th = 0xA;
            if (lvl == 3) {
                th = 0x64;
            } else if (lvl == 2) {
                th = 0x32;
            } else if (lvl == 1) {
                th = 0x19;
            }
            if ((s32)(100.0f * RandFloat_13c010()) < th) {
                hit = 1;
                o->g312(lvl - 1);
            }
        }
    }
    if (arg1 >= 1) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0++, hit);
    }
    if (arg1 >= 2) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0, lvl);
    }
    return 1;
}
