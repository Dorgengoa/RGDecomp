#include "types.h"

struct H314e10;
struct B314e10 {
    u8 pad0[0x84];
    s16 m84;
    u8 pad86[0xB0 - 0x86];
    virtual s32 f8(H314e10 *, f32);
    virtual void _vc();
    virtual void _v10();
    virtual void _v14();
    virtual void _v18();
    virtual void _v1c();
    virtual void _v20();
    virtual void _v24();
    virtual void _v28();
    virtual void _v2c();
    virtual void _v30();
    virtual void _v34();
    virtual void _v38();
    virtual void _v3c();
    virtual void _v40();
    virtual void _v44();
    virtual void _v48();
    virtual void _v4c();
    virtual void _v50();
    virtual void _v54();
    virtual void _v58();
    virtual void _v5c();
    virtual void _v60();
    virtual void _v64();
    virtual void _v68();
    virtual void f6c(s32);
};

struct O314e10 : B314e10 {
    s16 mB4;
    s16 mB6;
};

struct R314e10 {
    O314e10 *obj;
    s32 cnt;
};

struct P314e10 {
    s32 m0;
    R314e10 *ref;
    bool valid() { return ref != 0; }
    bool isNull() { return !valid(); }
    O314e10 *get() { return ref ? ref->obj : 0; }
    s32 count() { return ref ? ref->cnt : 0; }
    void release() {
        if (ref) {
            ref->cnt--;
        }
        if (count() == 0 && ref) {
            if (ref->obj) {
                ref->obj->f6c(-1);
            }
            ref->cnt = 0;
            ref = 0;
        }
        ref = 0;
    }
};

struct H314e10 {
    virtual void _v8();
    virtual void fc(s32, R314e10 **);
};

extern "C" {
u8 *GetGameData_1fede0(void);
void CharaSysEventLogKeyRemove_3a3380(s32, s32);
}

extern "C" void HandleRegistryStepAll_314e10(P314e10 *p, H314e10 *h, f32 f)
{
    u8 *top;
    s32 i;
    s32 r;

    top = GetGameData_1fede0();
    i = 0;
    do {
        if (p->isNull()) {
            continue;
        }
        r = p->get()->f8(h, f);
        if (r != 0 && h != 0) {
            h->fc(r, &p->ref);
        }
        if (p->get()->mB6 == 0) {
            continue;
        }
        CharaSysEventLogKeyRemove_3a3380(*(s32 *)(top + 0x20), p->get()->m84);
        if (p->isNull()) {
            continue;
        }
        p->release();
    } while (p++, ++i < 0x200);
}
