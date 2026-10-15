#include "types.h"

struct Ent {
    s16 unk0;
    s16 unk2;
    u8 pad4[4];
    s16 unk8;
};

class Tbl {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual Ent *v70(s32);
};

struct Sub {
    u8 pad0[0x1C];
    Tbl *tbl;
};

struct Obj {
    u8 pad0[4];
    Sub *sub;
    u8 pad8[0x340];
    s16 n;
    u8 pad34A[2];
    s32 ids[4];
};

extern "C" s32 StateBlockMapMarkerSetRemoveMatchingMaybe_3cc050(Obj *arg0, s32 arg1)
{
    s32 tmp[4];
    Ent *ref;
    Ent *e;
    s32 n;
    s32 i;
    s32 id;

    if (arg1 < 0) {
        arg0->n = 0;
        return 1;
    }
    ref = arg0->sub->tbl->v70(arg1);
    if (ref == NULL) {
        return 0;
    }
    {
        n = 0;
        for (i = 0; i < arg0->n; i++) {
            id = arg0->ids[i];
            e = arg0->sub->tbl->v70(id);
            if (e == NULL) {
                continue;
            }
            if (e->unk2 != ref->unk2 || e->unk8 != ref->unk8) {
                tmp[n++] = id;
            }
        }
        arg0->n = n;
        for (i = 0; i < n; i++) {
            arg0->ids[i] = tmp[i];
        }
    }
    return 1;
}
