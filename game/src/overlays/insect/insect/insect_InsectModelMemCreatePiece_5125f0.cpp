/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x005125F0 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x5C =
 * virtual #21.  [[jalr-is-cpp-virtual]]  The 0x790-byte allocation, the
 * inlined vptr store of D_00470F50 and the 0x88-byte descriptor handed to
 * func_1AFD00 are the same shape as factory 0x00504250. */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
     void s16() { VCM0(void, 0x48); } 
      
    void s21() { VCM0(void, 0x5C); }               /* slot 0x5C */
};

struct Ent {
    u8  pad000[0x58];
    s32 f58;
};

struct A {
    void *f000;
    u8    f004[0x64 - 4];
    Ent   ent[10];
    u8    pad3FC[4];
    s16   w400[1];
};

struct W {
    u8   pad000[0x1E4];
    char f1E4[1];
};

struct Desc {
    void *f00;
    void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    u8    pad1C[0x2C - 0x1C];
    void *f2C;
    s32   f30;
    u8    pad34[4];
    void *f38;
    s32   f3C;
    u8    b40[0x20];
    u8    b60[0x28];
    u8    b88[0x14];
};

extern "C" u8 D_00470F50[];
extern "C" char insect_D_00525238[];
extern "C" char insect_D_00525248[];
extern "C" u8 insect_D_00525250[];
extern "C" s32 insect_InsectModelMemFindFreeIndex_5128b0(void *);
extern "C" void insect_ModelObjExCtor_4f78f0(void *, int, int, int);
extern "C" void *MemStackHeapAlloc_14db10(void *p, s32 a, s32 b, s32 c);
extern "C" void MemStackClear_14dff0(Ent *e);
extern "C" void *MemStackAllocQw_14d950(void *p, s32 n);
extern "C" void MemStackHeapInit_14dee0(Ent *e, void *p, s32 n);
extern "C" void MemStackReturnToOwnerMaybe_14dad0(void *p);
extern "C" void MemStackHeapReinit_14de90(Ent *e);
extern "C" u32 strlen(const char *s);
extern "C" void strcpy(void *d, const char *s);
extern "C" void *MemStackNew_14e230(s32 size, void *pool);
extern "C" void Sprintf_1343b8(char *d, const char *f, s32 n);
extern "C" W *GetDrawCtxNameTable_15de40(void);
extern "C" void memset(void *d, s32 c, s32 n);
extern "C" void InfoCfgParseAll_1afd00(VE *o, Desc *d);
extern "C" void GameSceneObjBindMaybe_1cfcd0(void *h, s32 id, VE *o, s32 n);

extern "C" s32 insect_InsectModelMemCreatePiece_5125f0(A *a, void *b)
{
    Desc d __attribute__((aligned(16)));
    char nm[4];
    s32  idx;
    s32  id;
    Ent *e;
    VE  *m;
    W   *w;
    void *r;

    if (b == 0) {
        return -1;
    }
    idx = insect_InsectModelMemFindFreeIndex_5128b0((void *)a);
    id = idx + 0x80;
    a->w400[idx] = id;
    r = MemStackHeapAlloc_14db10(a->f004, 2, 0, 0x40);
    if (r != 0) {
        /* ix18e LEVER: the STORE must come FIRST.  With `e = &a->ent[idx];`
         * first, mwcc emits `addu base,index`; with the store first it emits
         * retail's `addu index,base`.  Four other spellings of the pointer
         * (`idx + a->ent`, `a->ent + idx`, both-sides, `e->f58`) are ONE
         * object d596cd0e. */
        a->ent[idx].f58 = (s32)r;
        e = &a->ent[idx];
        MemStackClear_14dff0(e);
        MemStackHeapInit_14dee0(e, MemStackAllocQw_14d950(a->f004, 0x2580), 0x2580);
        MemStackReturnToOwnerMaybe_14dad0(a->f004);
        MemStackHeapReinit_14de90(e);
        if (strlen(insect_D_00525238) < 0x10) {
            strcpy(e, insect_D_00525238);
        }
        MemStackHeapAlloc_14db10(e, 2, 0, 0x40);
        m = (VE *)MemStackNew_14e230(0x790, e);
        if (m != 0) {
            insect_ModelObjExCtor_4f78f0(m, 0, 0, 0);
            *(void **)((u8 *)m + 0x1B0) = D_00470F50;
        }
        Sprintf_1343b8(nm, insect_D_00525248, idx);
        w = GetDrawCtxNameTable_15de40();
        strcpy(w->f1E4, nm);
        memset(&d, 0, 0x88);
        d.f30 = 8;
        d.f2C = d.b40;
        d.f3C = 8;
        d.f38 = d.b60;
        d.f00 = b;
        d.f04 = insect_D_00525250;
        d.f08 = e;
        d.f0C = e;
        d.f10 = e;
        d.f14 = idx + 0x243;
        d.f18 = 1;
        m->s21();
        InfoCfgParseAll_1afd00(m, &d);
        w->f1E4[0] = 0;
        MemStackReturnToOwnerMaybe_14dad0(e);
        GameSceneObjBindMaybe_1cfcd0(a->f000, id, m, 0);
    }
    return a->w400[idx];
}
