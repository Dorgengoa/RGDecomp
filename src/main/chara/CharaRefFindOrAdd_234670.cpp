#include "types.h"

class Base {
public:
    u8 pad0[0xC];
    virtual s32 v08(s32 obj);
};

class Mgr : public Base {
public:
    u8 pad10[0x2C];
    s32 p3C;
};

extern "C" {
void MemStackReturnToOwnerMaybe_14dad0(s32);
s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
void MemStackHeapFree_14dcb0(s32, s32);
s32 MemStackNew_14e130(s32, s32);
s32 CharaRefGetId_3121c0(s32);
s32 CharaRefClone_3121e0(s32, s32, s32, s32);
void CharaRefReset_312390(s32);
s32 IntCompare_42ca30(s32, s32);
s32 DListGetHead_42ea60(void *);
s32 DListGetCountPow2_42ea70(void *);
s32 DListNodeAdvance_42eb00(s32, s32);
void DListNodeInit_42ec10(s32);
}

static inline s32 create(s32 ctx) {
    s32 p;
    if ((p = MemStackNew_14e130(0x1C, ctx)) != 0) {
        DListNodeInit_42ec10(p);
        DListNodeInit_42ec10(p);
        CharaRefReset_312390(p + 0x10);
    }
    return p;
}

static inline s32 add(Mgr *m, s32 name) {
    s32 ctx;
    s32 res;
    s32 obj;

    ctx = m->p3C;
    if (name == 0 || ctx == 0) {
        return 0;
    }
    res = MemStackHeapAlloc_14db10(ctx, 2, 0, 0x40);
    if (res != 0) {
        obj = create(ctx);
        if (obj != 0) {
            DListNodeInit_42ec10(obj);
            CharaRefReset_312390(obj + 0x10);
            if (CharaRefClone_3121e0(obj + 0x10, res, name, ctx) != 0) {
                MemStackReturnToOwnerMaybe_14dad0(ctx);
                if (m->v08(obj) != 0) {
                    return obj;
                }
            }
        }
    }
    MemStackReturnToOwnerMaybe_14dad0(ctx);
    MemStackHeapFree_14dcb0(ctx, res);
    return 0;
}

static inline s32 find(Mgr *m, s32 key) {
    s32 node;
    s32 n;
    s32 cur;
    s32 r;
    s32 found;

    if ((node = DListGetHead_42ea60(m)) == 0) {
        found = 0;
    } else {
        found = 0;
        n = DListGetCountPow2_42ea70(m);
        while (n > 0) {
            n >>= 1;
            cur = DListNodeAdvance_42eb00(node, n);
            if (cur != 0) {
                r = IntCompare_42ca30(key, CharaRefGetId_3121c0(cur + 0x10));
                if (r == 0) {
                    found = cur;
                    break;
                }
                if (r > 0) {
                    node = cur;
                }
            }
        }
    }
    return found;
}

extern "C" s32 CharaRefFindOrAdd_234670(Mgr *arg0, s32 arg1) {
    s32 ctx;
    s32 found;
    s32 r;
    s32 n;
    s32 node;
    s32 cur;
    s32 key;
    s32 res;

    if (arg1 == 0) {
        return 0;
    }
    key = CharaRefGetId_3121c0(arg1);
    found = find(arg0, key);
    if (found == 0) {
        found = add(arg0, arg1);
    }
    if (found == 0) {
        return 0;
    }
    return found + 0x10;
}
