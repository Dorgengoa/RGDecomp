#pragma opt_propagation off
#include "types.h"

class Obj2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5C() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vBC() { return VCM0(s32, 0xBC); }
    s32 vC0() { return VCM0(s32, 0xC0); }
};

struct Handle {
    u8 pad0[0x14];
    s32 x14;
};

struct Arg0 {
    u8 pad0[0x18C];
    s16 count;
    s16 pad18E;
    s16 ids[1];

    s32 GetId(s32 i) {
        s32 n = count;
        if (i < 0 || i >= n) {
            return -1;
        }
        return ids[i];
    }
};

extern "C" Obj2 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" Handle *D_00483890;

static inline Obj2 *Find(Arg0 *a, s32 idx)
{
    s32 id;
    if (D_00483890 == 0) {
        return 0;
    }
    id = a->GetId(idx);
    if (id < 0) {
        return 0;
    }
    return CharaMgrPoolFindById_3a8c60(D_00483890->x14, id);
}

extern "C" Obj2 *PartyFindMember_3c2130(Arg0 *arg0, s32 arg1, s32 arg2, bool arg3, s32 arg4, s32 *arg5, s32 arg6)
{
    s32 step;
    s32 u;
    s32 tries;
    s32 idx;
    s32 i;
    bool ok;
    Obj2 *obj;
    s32 cnt;
    u16 last;
    Obj2 *found;

    if (arg2 == 0 && !arg3) {
        return 0;
    }
    if (D_00483890 == 0) {
        return 0;
    }
    if (arg6 == 0) {
        if (arg4 < 0) u = 0; else u = arg4;
        step = 1;
        { s32 l2 = 2; cnt = l2 - u + 1; }
    } else {
        if (arg4 < 0) u = 2; else u = arg4;
        step = -1;
        cnt = u + 1;
    }
    idx = u;
    found = 0;
    tries = 3;
    for (i = 0; i < cnt; i++) {
        if (D_00483890 == 0) {
            obj = 0;
        } else {
            s32 id = arg0->GetId(idx);
            if (id < 0) {
                obj = 0;
            } else {
                obj = CharaMgrPoolFindById_3a8c60(D_00483890->x14, id);
            }
        }
        if (obj != 0) {
            ok = true;
            if (arg1 >= 0 && arg1 != obj->v5C()) {
                ok = false;
            }
            if (ok && arg2 == 0 && obj->vBC() != 0) {
                ok = false;
            }
            if (ok && !arg3 && obj->vC0() != 0) {
                ok = false;
            }
            if (ok) {
                found = obj;
                if (arg5 != 0) {
                    *arg5 = idx;
                }
                break;
            }
            tries--;
            if (tries < 1) {
                break;
            }
        }
        idx += step;
    }
    return found;
}
