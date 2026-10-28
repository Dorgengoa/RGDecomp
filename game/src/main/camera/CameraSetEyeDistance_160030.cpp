/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

extern "C" {
double Cos_128278(double);
double Sin_128880(double);
double dpmul(double, double);
double dpadd(double, double);
f32 dptofp(double);
double fptodp(f32);
}

class Base160030 {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetA(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x94, a0); }
    void GetB(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0x98, a0); }
    
    
    
    
    
    
    
    f32 GetF() { return VCM0(f32, 0xB8); }
};

class Obj160030 : public Base160030 {
public:
    u8 padC4[0x2C];
    Vec4 xF0;
};

extern "C" void CameraSetEyeDistance_160030(Obj160030 *self, f32 f)
{
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    double k;

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
