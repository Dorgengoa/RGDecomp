/* rgp:protos */
#line 1
#include "types.h"

class VE {
    u8 pad_[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f5C() { VCM0(void, 0x5C); }
};

/* Two independent `arg4 >= 0` tests (retail recomputes the slti).
   Indirect call: table pointer at 0x1B0 of the new object, slot 0x5C. */


extern "C" void *GetDrawCtxNameTable_15de40(void);
extern "C" void NameTableFreeGroup_158ac0(void *, void *);
extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" void ModelObjExCtor_1c4920(void *, int, int, int);
extern "C" void Sprintf_1343b8(char *, char *, s32);
extern "C" char *strcpy(char *, char *);
extern "C" s32 GetEffectMgr_2d9040(void);
extern "C" void InfoCfgParseAll_1afd00(void *, void *);
extern "C" u8 D_00470F50[];
extern "C" char D_0045B6D8[];
extern "C" char D_0045B6E8[];
extern "C" s32 D_0047E180;

extern "C" void *Character2NewFromInfoCfg_1ed270(u8 *desc, void *a1, void *heap, void *a3, s32 idx)
{
    char name[0x20] __attribute__((aligned(16)));
    u8 *g;
    u8 *n;
    s32 t;
    s32 u;

    if (a1 == 0) {
        return 0;
    }
    if (heap == 0) {
        return 0;
    }
    g = (u8 *)GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(g, a3);
    n = (u8 *)MemStackNew_14e230(0x790, heap);
    if (n != 0) {
        ModelObjExCtor_1c4920(n, 0, 0, 0);
        *(u8 **)(n + 0x1B0) = D_00470F50;
    }
    if (n == 0) {
        return 0;
    }
    if (idx > -1) {
        Sprintf_1343b8(name, D_0045B6E8, idx);
        strcpy((char *)(g + 0x1E4), name);
    }
    *(void **)(desc + 0x00) = a1;
    *(char **)(desc + 0x04) = D_0045B6D8;
    *(void **)(desc + 0x08) = heap;
    *(void **)(desc + 0x0C) = heap;
    *(void **)(desc + 0x10) = heap;
    *(void **)(desc + 0x14) = a3;
    *(s32 *)(desc + 0x18) = 1;
    ((VE *)n)->f5C();
    t = GetEffectMgr_2d9040() + 0x58;
    *(s32 *)(n + 0x53C) = t;
    if (t != 0) {
        u = D_0047E180;
        D_0047E180 = u + 1;
        *(s32 *)(n + 0x538) = u;
    }
    InfoCfgParseAll_1afd00(n, desc);
    *(void **)(n + 0x4DC) = a3;
    if (idx > -1) {
        *(u8 *)(g + 0x1E4) = 0;
    }
    return n;
}
