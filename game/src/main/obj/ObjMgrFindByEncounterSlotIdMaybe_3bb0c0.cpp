#include "types.h"
class VO {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f378() { return VCM0(s32, 0x378); }
};

typedef struct Sub {
    u8 pad0[0x1C];
    s32 m1C;
} Sub;

typedef struct Own {
    u8 pad0[8];
    s32 m8;
    s32 padC;
    Sub *m10;
} Own;

extern "C" VO *PoolGetUsedElem_36acb0(Sub *, s32);

extern "C" VO *ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(Own *arg0, s32 arg1)
{
    s32 n;
    s32 i;
    VO *o;

    if ((arg0->m8 == 0) || (arg0->m10 == 0)) {
        return 0;
    }
    n = arg0->m10->m1C;
    if (n <= 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        o = PoolGetUsedElem_36acb0(arg0->m10, i);
        if ((o != 0) && (arg1 == o->f378())) {
            return o;
        }
    }
    return 0;
}
