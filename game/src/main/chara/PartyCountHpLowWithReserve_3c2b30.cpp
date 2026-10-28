#include "types.h"

class V003c2b30 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x228); }
};

typedef struct S003c2b30 {
    u8 pad0[0x18C];
    s16 n;
    u8 pad18E[2];
    s16 a[3];
    s16 b[7];
} S003c2b30;

typedef struct G003c2b30 {
    u8 pad0[0x14];
    s32 unk14;
} G003c2b30;

extern "C" V003c2b30 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" G003c2b30 *D_00483890;

extern "C" s32 PartyCountHpLowWithReserve_3c2b30(S003c2b30 *o)
{
    s32 c1;
    s32 c2;
    s32 i;
    s32 n;
    s32 id;
    V003c2b30 *v;

    if (D_00483890 == 0) {
        c1 = 0;
    } else {
        n = o->n;
        c1 = 0;
        for (i = 0; i < n; i++) {
            id = o->a[i];
            if (id < 0) {
                continue;
            }
            v = CharaMgrPoolFindById_3a8c60(D_00483890->unk14, id);
            if (v == 0) {
                continue;
            }
            if (v->f() == 0) {
                continue;
            }
            c1++;
        }
    }
    if (D_00483890 == 0) {
        c2 = 0;
    } else {
        c2 = 0;
        for (i = 0; i < 7; i++) {
            id = o->b[i];
            if (id < 0) {
                continue;
            }
            v = CharaMgrPoolFindById_3a8c60(D_00483890->unk14, id);
            if (v == 0) {
                continue;
            }
            if (v->f() == 0) {
                continue;
            }
            c2++;
        }
    }
    return c1 + c2;
}
