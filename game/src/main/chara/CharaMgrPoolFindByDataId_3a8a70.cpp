#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 GetType() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 IsA() { return VCM0(s32, 0xBC); }
    s32 IsB() { return VCM0(s32, 0xC0); }
};

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
} Container;

typedef struct {
    u8 pad0[0x8];
    Container *unk8;
} Obj1;

extern "C" Unit *PoolGetUsedElem_36acb0(Container *, s32);
extern "C" s32 D_004837EC;

static inline bool Match(Unit *o, const s32 &type, const u8 &a, const u8 &b)
{
    bool ok = true;
    if (type >= 0 && type != o->GetType()) {
        ok = false;
    }
    if (ok && !a && o->IsA()) {
        ok = false;
    }
    if (ok && !b && o->IsB()) {
        ok = false;
    }
    return ok;
}

static inline void SetOut(s32 *const &out, s32 idx)
{
    if (out != 0) {
        *out = idx;
    }
}

extern "C" Unit *CharaMgrPoolFindByDataId_3a8a70(Obj1 *self, s32 type, u8 a, u8 b, s32 start, s32 *out, s32 rev)
{
    s32 step;
    s32 u;
    Unit *found;
    Container *c;
    s32 n;
    s32 idx;
    s32 last;
    s32 i;
    s32 count;
    Unit *o;

    if (!a && !b) {
        return 0;
    }
    if (D_004837EC == 0 || (c = self->unk8) == 0) {
        return 0;
    }
    n = c->unk1C;
    if (n <= 0) {
        return 0;
    }
    last = c->unk14 - 1;
    if (rev == 0) {
        u = (start < 0) ? 0 : start;
        step = 1;
        count = last - u + 1;
    } else {
        if (start < 0) u = last; else u = start;
        step = -1;
        count = u + 1;
    }
    idx = u;
    found = 0;
    for (i = 0; i < count; i++) {
        o = PoolGetUsedElem_36acb0(self->unk8, idx);
        if (o != 0) {
            if (Match(o, type, a, b)) {
                found = o;
                SetOut(out, idx);
                break;
            }
            if (--n <= 0) {
                break;
            }
        }
        idx += step;
    }
    return found;
}
