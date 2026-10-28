#include "types.h"
#undef NULL
#define NULL 0

struct Ent {
    __extension__ signed short a : 10;
    signed short pad : 6;
    u16 m2;
    u16 m4;
    u16 m6;
    u16 m8;
    u16 mA;
    u16 mC;
} __attribute__((aligned(2)));

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void f38() { VCM0(void, 0x38); }
    void f3C() { VCM0(void, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * f438() { return VCM0(Ent *, 0x438); }
    
    
    
    s32 f448() { return VCM0(s32, 0x448); }
    u8 pad4[0xC];
    s16 m10;
    u8 pad12[0xA];
    s32 m1C[2];
    u16 m24[2];
    u8 pad28[8];
    u16 m30[2];
    u16 m34[2];
    u16 m38[2];
    u8 pad3C[0x4B8 - 0x3C];
    s32 m4B8;
};

extern "C" s32 CharaApplyLevelUps_3ab070(Obj *o, s32 arg1, s32 *out)
{
    s32 skip;
    s32 total;
    s32 count;
    s32 n;
    s32 i;
    Ent *e;
    s32 t;

    skip = arg1;
    total = 0;
    count = 0;
    for (;;) {
        n = o->f448();
        if (n <= 0) {
            o->m4B8 = 0;
            break;
        }
        if (o->m4B8 < n) {
            total += o->m4B8 - skip;
            break;
        }
        e = o->f438();
        if (e == NULL) {
            o->m4B8 = n;
            total += n - skip;
            break;
        }
        count++;
        o->m10 = e->a;
        total += n - skip;
        o->m4B8 -= n;
        skip = 0;
        i = 0;
        do {
            o->m1C[i] += e->m4;
            o->m24[i] += e->m6;
            t = e->m8;
            o->m30[i] += t;
            t = e->mA;
            o->m34[i] += t;
            t = e->mC;
            o->m38[i] += t;
            i++;
        } while (i < 2);
    }
    if (count > 0) {
        o->f38();
        o->f3C();
    }
    if (out != NULL) {
        *out = total;
    }
    return count;
}
