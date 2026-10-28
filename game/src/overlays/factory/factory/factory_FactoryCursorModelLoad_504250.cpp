/* rgp:protos */
#line 1
#include "types.h"

#pragma optimization_level 3

/* factory.bin overlay, 0x00504250 -- 312 B.  Create one panel sub-object in
 * slot `k`, plant its table pointer, then build the 0x88-byte descriptor on
 * the stack and hand it to the sub-object.
 *
 * .cpp for the ONE `jalr $25` (target in $t9 = a real `virtual`): vptr at the
 * object's own 0x1B0, i.e. a 0x1B0-byte non-polymorphic base with the vptr
 * after it, exactly as factory_FactoryShutdown_504850.cpp records.  Slot 0x50 is index
 * (0x50-8)/4 = 18.  The 0x1B0 word is ALSO written by hand (an extern table
 * address, not mwcc's own vtable), so the field writes go through the plain
 * `Raw` view and only the call goes through the polymorphic one.
 */

struct ObjBase { u8 d[0x1B0]; };

struct Obj : ObjBase {
    VC_VPTR_MEMBER;    
        
        
        
        
        
    void f50() { VCM0(void, 0x50); }
};

struct Raw {
    u8    pad000[0x1B0];
    void *t1B0;
    u8    pad1B4[0x4DC - 0x1B4];
    s32   f4DC;
};

struct Ent12 { s32 f00; s32 f04; s32 f08; };

struct P1 {
    u8    pad000[0x24];
    Ent12 arr[4];                       /* 0x24 */
    Raw  *slot[8];                       /* 0x54 */
};

struct Desc {
    s32   f00;
    s32   f04;
    s32   f08;
    s32   f0C;
    s32   f10;
    s32   f14;
    s32   f18;
    u8    pad1C[0x2C - 0x1C];
    void *f2C;
    s32   f30;
    u8    pad34[0x38 - 0x34];
    void *f38;
    s32   f3C;
    u8    f40[0x20];
    u8    f60[0x28];
};                                       /* 0x88 */

extern "C" u8 D_00470F50[];

extern "C" void *MemStackNew_14e230(s32 sz, s32 tag);
extern "C" void  memset(void *p, s32 v, s32 n);
extern "C" void  InfoCfgParseAll_1afd00(Raw *o, Desc *d);
extern "C" void factory_ModelObjExCtor_504390(Raw *, int, int, int);

extern "C" s32 factory_FactoryCursorModelLoad_504250(P1 *p, s32 k, s32 j, s32 a, s32 b, s32 c);

s32 factory_FactoryCursorModelLoad_504250(P1 *p, s32 k, s32 j, s32 a, s32 b, s32 c)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    Raw *o;

    o = (Raw *)MemStackNew_14e230(0x790, c);
    if (o != NULL) {
        factory_ModelObjExCtor_504390(o, 0, 0, 0);
        o->t1B0 = D_00470F50;
    }
    p->slot[k] = o;
    if (o == NULL) {
        return 0;
    }

    memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, 0x88);
    (*(Desc *)(rgp_blk1 + 0x0)).f30 = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).f3C = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).f2C = (*(Desc *)(rgp_blk1 + 0x0)).f40;
    (*(Desc *)(rgp_blk1 + 0x0)).f38 = (*(Desc *)(rgp_blk1 + 0x0)).f60;
    (*(Desc *)(rgp_blk1 + 0x0)).f00 = p->arr[j].f00;
    (*(Desc *)(rgp_blk1 + 0x0)).f04 = b;
    (*(Desc *)(rgp_blk1 + 0x0)).f08 = c;
    (*(Desc *)(rgp_blk1 + 0x0)).f0C = c;
    (*(Desc *)(rgp_blk1 + 0x0)).f10 = c;
    (*(Desc *)(rgp_blk1 + 0x0)).f14 = a;
    (*(Desc *)(rgp_blk1 + 0x0)).f18 = 0;
    ((Obj *)p->slot[k])->f50();
    InfoCfgParseAll_1afd00(p->slot[k], &(*(Desc *)(rgp_blk1 + 0x0)));
    p->slot[k]->f4DC = a;
    return 1;
}
