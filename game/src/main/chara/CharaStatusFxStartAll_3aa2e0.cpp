#include "types.h"

typedef struct E3aa2e0 {
    u8 pad0[4];
    s8 unk4;
} E3aa2e0;

class M3aa2e0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    E3aa2e0 * get(s16 a0) { return VCM(E3aa2e0 *, (void *, s16), 0x70, a0); }
};

typedef struct H3aa2e0 {
    u8 pad0[8];
    M3aa2e0 *unk8;
} H3aa2e0;

typedef struct T3aa2e0 {
    u8 pad0[0x58];
    H3aa2e0 *unk58;
} T3aa2e0;

typedef struct G3aa2e0 {
    u8 pad0[0xC];
    s32 unkC;
} G3aa2e0;

typedef struct A3aa2e0 {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0xC8 - 0x10];
    s64 bits;
} A3aa2e0;

extern "C" {
void Abort_12de80(void);
void Fprintf_12f9a0(s32, const char *);
s32 GetStatusEffect_2d9010(void);
void StatusEffectStart_33c240(s32, s8, s32, s32);
extern G3aa2e0 *D_00449858[4];
extern char D_0045CB40[];
extern T3aa2e0 *D_0048381C;
s32 CharaStatusFxStartAll_3aa2e0(A3aa2e0 *arg0);
}

class BitRef {public: s64 *p;u32 i; BitRef(s64 *pp,u32 ii):p(pp),i(ii){} s64 Get(){u32 n=i;if(n>=0x30){Fprintf_12f9a0(D_00449858[0]->unkC,D_0045CB40);Abort_12de80();}return *p&(1LL<<n);}};
s32 CharaStatusFxStartAll_3aa2e0(A3aa2e0 *arg0)
{
    s32 h;
    u32 i;
    volatile u32 ri;
    s64 *volatile rp;
    M3aa2e0 *m;
    E3aa2e0 *e;

    h = GetStatusEffect_2d9010();
    i = 0;
    do {
        if(BitRef(&arg0->bits,i).Get()){
            m = D_0048381C->unk58->unk8;
            if (m != 0) {
                e = m->get(i);
            } else {
                e = 0;
            }
            if (e != 0) {
                s8 k = e->unk4;
                if (h != 0) {
                    StatusEffectStart_33c240(h, k, arg0->unkC, -1);
                }
            }
        }
        i++;
    } while ((s32)i < 0x30);
    return 0;
}
