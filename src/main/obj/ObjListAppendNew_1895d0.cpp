#include "types.h"

extern "C" void *MemStackNew_14e230(s32 arg0, s32 arg1);
extern u8 D_00470538[0x40];

class C1895d0 {
public:
    u8 pad0[0x14];
    virtual void v08();
};

typedef struct {
    u8 pad0[0x284];
    void **lists[7];
} O1895d0;

extern "C" void *ObjListAppendNew_1895d0(O1895d0 *arg0, s32 arg1, s32 arg2)
{
    u8 *p;
    void **n;
    void **t;
    s32 ok;

    if (arg2 == 0) {
        return NULL;
    }
    if (arg1 >= 0) {
        if (arg1 >= 7) {
            ok = 0;
        } else {
            ok = 1;
        }
    } else {
        ok = 0;
    }
    if (ok == 0) {
        return NULL;
    }
    p = (u8 *)MemStackNew_14e230(0x18, arg2);
    if (p != NULL) {
        *(void **)(p + 0x14) = D_00470538;
        ((C1895d0 *)p)->v08();
    }
    if (p == NULL) {
        return NULL;
    }
    *(s32 *)(p + 0x10) = 0;
    n = arg0->lists[arg1];
    if (n != NULL) {
        while (n != NULL) {
            t = (void **)*n;
            if (t == NULL) {
                break;
            }
            n = t;
        }
        *n = p;
        if (p != NULL) {
            *(void **)(p + 0x4) = n;
        }
    } else {
        arg0->lists[arg1] = (void **)p;
    }
    return p;
}
