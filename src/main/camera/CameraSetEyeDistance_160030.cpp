#include "types.h"
#include "vec.h"

extern "C" {
s32 Cos_128278(s32 arg0);
s32 Sin_128880(s32 arg0);
s32 dpmul(s32 arg0, s32 arg1);
s32 dpadd(s32 arg0, s32 arg1);
f32 dptofp(s32 arg0);
s32 fptodp(f32 arg0);
}

class Base160030 {
public:
    u8 pad0[0xC0];
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
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void GetA(Vec4 *);
    virtual void GetB(Vec4 *);
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual f32 GetF();
};

class Obj160030 : public Base160030 {
public:
    u8 padC4[0x2C];
    Vec4 xF0;
};

extern "C" void CameraSetEyeDistance_160030(Obj160030 *self, f32 f)
{
    Vec4 b;
    Vec4 a;
    s32 k;

    self->GetA(&a);
    self->GetB(&b);
    k = Sin_128880(fptodp(self->GetF()));
    k = dpmul(fptodp(f), k);
    b.x = dptofp(dpadd(fptodp(a.x), k));
    k = Cos_128278(fptodp(self->GetF()));
    k = dpmul(fptodp(f), k);
    b.z = dptofp(dpadd(fptodp(a.z), k));
    self->xF0 = b;
}
