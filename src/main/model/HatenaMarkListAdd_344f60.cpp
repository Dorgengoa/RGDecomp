#include "types.h"

extern "C" {
extern void *MemStackNew_14e230(s32);
extern void HatenaMarkCtor_345d20(void *);
extern u8 D_00471E08[];
}

class V {
public:
    u8 pad[0xC0];
    virtual void f();
};

extern "C" void *HatenaMarkListAdd_344f60(void **arg0, s32 arg1, s32 arg2)
{
    u8 *p;
    void **q;
    void **n;
    void *r;

    if ((p = (u8 *)MemStackNew_14e230(0xD0)) != NULL) {
        *(void **)(p + 0xC0) = D_00471E08;
        HatenaMarkCtor_345d20(p + 0x10);
        ((V *)p)->f();
    }
    if (p == NULL) {
        r = NULL;
    } else {
    *(s32 *)(p + 0xC) = arg2;
    *(s32 *)(p + 8) = 0;
    arg0[1] = 0;
    arg0[2] = 0;
    q = (void **)arg0[0];
    if (q != NULL) {
        while (q != NULL) {
            n = (void **)*q;
            if (n == NULL) {
                break;
            }
            q = n;
        }
        *q = p;
        if (p != NULL) {
            *(void ***)(p + 4) = q;
        }
    } else {
        arg0[0] = p;
    }
        r = p + 0x10;
    }
    if (r == NULL) {
        return NULL;
    }
    return r;
}
