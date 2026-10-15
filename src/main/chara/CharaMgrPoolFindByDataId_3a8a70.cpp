#include "types.h"

class Unit {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual s32 GetType();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual s32 IsA();
    virtual s32 IsB();
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
