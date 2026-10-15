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
    virtual void s00();  virtual void s01();  virtual void s02();
    virtual void s03();  virtual void s04();  virtual void s05();
    virtual void s06();  virtual void s07();  virtual void s08();
    virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();
    virtual void s15();  virtual void s16();  virtual void s17();
    virtual void f50();
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

extern "C" void *func_14E230(s32 sz, s32 tag);
extern "C" void  func_131B60(void *p, s32 v, s32 n);
extern "C" void  func_1AFD00(Raw *o, Desc *d);
extern "C" void  factory_ModelObjExCtor_504390(Raw *o);

extern "C" s32 factory_FactoryCursorModelLoad_504250(P1 *p, s32 k, s32 j, s32 a, s32 b, s32 c);

s32 factory_FactoryCursorModelLoad_504250(P1 *p, s32 k, s32 j, s32 a, s32 b, s32 c)
{
    Desc d;
    Raw *o;

    o = (Raw *)func_14E230(0x790, c);
    if (o != NULL) {
        factory_ModelObjExCtor_504390(o);
        o->t1B0 = D_00470F50;
    }
    p->slot[k] = o;
    if (o == NULL) {
        return 0;
    }

    func_131B60(&d, 0, 0x88);
    d.f30 = 8;
    d.f3C = 8;
    d.f2C = d.f40;
    d.f38 = d.f60;
    d.f00 = p->arr[j].f00;
    d.f04 = b;
    d.f08 = c;
    d.f0C = c;
    d.f10 = c;
    d.f14 = a;
    d.f18 = 0;
    ((Obj *)p->slot[k])->f50();
    func_1AFD00(p->slot[k], &d);
    p->slot[k]->f4DC = a;
    return 1;
}
