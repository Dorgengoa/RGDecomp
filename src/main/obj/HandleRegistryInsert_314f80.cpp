#include "types.h"

class ObjB {
public:
    u8 pad0[0x84];
    s16 m84;
    u8 pad86[0xB0 - 0x86];
    virtual void v8();
    virtual void vc();
    virtual void v10();
    virtual void v14();
    virtual void f18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void f6c(s32);
};

class Obj : public ObjB {
public:
    s16 mB4;
};

struct Ref {
    Obj *obj;
    s32 cnt;
};

struct Handle {
    Ref *r;

    s32 isNull() const {
        return (r != 0) ^ 1;
    }
    s32 count() const {
        return r ? r->cnt : 0;
    }
    Obj *get() const {
        return r ? r->obj : 0;
    }
    Handle &operator=(const Handle &o)
    {
        if (this != &o) {
            if (!isNull()) {
                if (r) {
                    r->cnt--;
                }
                if (count() == 0) {
                    if (r) {
                        if (r->obj) {
                            r->obj->f6c(-1);
                        }
                        r->cnt = 0;
                        r = 0;
                    }
                }
                r = 0;
            }
            r = o.r;
            if (r) {
                r->cnt++;
            }
        }
        return *this;
    }
};

struct Slot {
    s32 id;
    Handle h;
};

extern "C" s32 HandleRegistryInsert_314f80(Slot *slot, Handle *h, s32 id)
{
    s32 i;
    Slot *p = slot;
    Handle *q = h;
    s32 v = id;

    for (i = 0; i < 0x200; i++, p++) {
        if (!p->h.isNull()) {
            continue;
        }
        p->h = *q;
        p->id = v;
        p->h.get()->mB4 = v;
        p->h.get()->m84 = v;
        p->h.get()->f18();
        return 1;
    }
    return 0;
}
