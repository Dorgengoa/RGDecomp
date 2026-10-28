#include "types.h"

typedef struct {
    s8 *name;
} Ent;

typedef struct {
    s32 count;
    Ent **arr;
} Tbl;

typedef struct {
    u8 pad0[0x104];
    Tbl *tbl;
} Obj;

extern "C" s32 ModelMeshTagUnderFrame_152700(s32 arg0, Tbl *arg1, s32 arg2, s32 arg3);

#pragma opt_loop_invariants off

extern "C" s32 ModelTagMeshesUnderFrameName_1516e0(Obj *arg0, s32 arg1, s8 *name, s32 arg3)
{
    s32 k;
    s32 kk;
    s32 cnt;
    Ent *e;
    s8 *s;
    s8 *a;
    s8 *b;
    Tbl *t;
    s8 c;
    bool r;

    t = arg0->tbl;
    if (name == 0 || t == 0) {
        kk = -1;
    } else {
        cnt = t->count;
        for (k = 0; k < cnt; k++) {
            e = t->arr[k];
            if (e == 0) {
                continue;
            }
            s = e->name;
            if (s == 0) {
                continue;
            }
            a = s;
            b = name;
            if (*a != *b) {
                r = false;
                goto done;
            }
            while ((c = *a) != 0 || *b != 0) {
                if (c != *b) {
                    r = false;
                    goto done;
                }
                a++;
                b++;
            }
            r = true;
        done:
            if (r) {
                kk = k;
                goto found;
            }
        }
        kk = -1;
    }
found:
    return ModelMeshTagUnderFrame_152700(arg1, t, kk, arg3);
}
