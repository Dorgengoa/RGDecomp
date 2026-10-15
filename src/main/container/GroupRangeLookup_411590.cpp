#include "types.h"

/* jalr $25: vptr at offset 0; slot 0x70 = 8 + 4*26 -> the 27th declared
   virtual. */
struct Obj {
    virtual void *v00();
    virtual void *v01();
    virtual void *v02();
    virtual void *v03();
    virtual void *v04();
    virtual void *v05();
    virtual void *v06();
    virtual void *v07();
    virtual void *v08();
    virtual void *v09();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *v25();
    virtual void *v26(s32 i);
    u8  pad004[0x98 - 4];
    s16 m98;
    s16 m9A;
};

extern "C" Obj *GroupFindByKey_4117d0(void);

extern "C" void *GroupRangeLookup_411590(void *a, void *b, s16 idx)
{
    Obj *p;
    bool ok;

    if (idx < 0) {
        return 0;
    }
    p = GroupFindByKey_4117d0();
    if (p != 0) {
        ok = idx >= p->m98;
        if (ok) {
            ok = idx <= p->m9A;
        }
        if (ok) {
            return p->v26(idx);
        }
    }
    return 0;
}
