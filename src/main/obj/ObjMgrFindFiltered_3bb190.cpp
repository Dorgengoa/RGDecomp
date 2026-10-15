
#include "types.h"

class Obj2 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 v5C();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual s32 vBC();
    virtual s32 vC0();
};

struct List {
    u8 pad0[0x14];
    s32 count;
    u8 pad18[4];
    s32 tries;
};

struct Arg0 {
    u8 pad0[8];
    s32 x8;
    u8 padC[4];
    List *list;
};

typedef bool (*Filter)(Obj2 *);

extern "C" Obj2 *PoolGetUsedElem_36acb0(List *, s32);

extern "C" Obj2 *ObjMgrFindFiltered_3bb190(Arg0 *arg0, s32 arg1, s32 arg2, bool arg3, s32 arg4, s32 *arg5, s32 arg6, Filter cb)
{
    s32 a;
    s32 last;
    s32 step;
    Obj2 *found;
    s32 cnt;
    s32 tries;
    s32 idx;
    s32 i;
    List *l;
    Obj2 *obj;
    bool ok;

    if (arg2 == 0 && !arg3) {
        return 0;
    }
    if (arg0->x8 == 0 || (l = arg0->list) == 0) {
        return 0;
    }
    tries = l->tries;
    if (tries <= 0) {
        return 0;
    }
    last = l->count - 1;
    if (arg6 == 0) {
        a = arg4 < 0 ? 0 : arg4;
        step = 1;
        cnt = last - a + 1;
    } else {
        if (arg4 < 0) {
            a = last;
        } else {
            a = arg4;
        }
        step = -1;
        cnt = a + 1;
    }
    idx = a;
    found = 0;
    for (i = 0; i < cnt; i++) {
        obj = PoolGetUsedElem_36acb0(arg0->list, idx);
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
            if (ok && cb != 0) {
                ok = cb(obj);
            }
            if (ok) {
                found = obj;
                if (arg5 != 0) {
                    *arg5 = idx;
                }
                break;
            }
            tries--;
            if (tries <= 0) {
                break;
            }
        }
        idx += step;
    }
    return found;
}
