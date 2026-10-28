/* rgp:protos */
#line 1
#include "types.h"

class OBase {
public:
    u8 pad000[0x68];
};

class O : public OBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v22(void *p, void *d, s32 n) { return VCM(s32, (void *, void *, void *, s32), 0x60, p, d, n); }
};

typedef struct Rec {
    u8  pad000[0x54];
    s32 m54;
    u8  pad058[0x8];
} Rec;

extern "C" O * MapDataGetModel_1e7810(void *);
extern "C" s32 MapDataGetId_1e7bd0(void *a);

extern "C" s32 MapDataCollectCollTrisMaybe_1e6c80(void *a, Rec *p, s32 n, void *d)
{
    O  *o;
    s32 cnt;
    s32 i;

    if (p == 0 || n <= 0) {
        return 0;
    }
    o = MapDataGetModel_1e7810((void *)a);
    if (o == 0) {
        return 0;
    }
    cnt = o->v22(p, d, n);
    for (i = 0; i < cnt; i++) {
        p->m54 = ((short)MapDataGetId_1e7bd0(a));
        p++;
    }
    return cnt;
}
