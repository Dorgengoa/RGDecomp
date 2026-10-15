#include "types.h"

s32 ModelResGetSkinInfluenceCount_14cdb0(void **arg0) {
    void *p;
    u8 t;
    void *v2;

    p = *arg0;
    if (p == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)p + 0x13) != 0x10) {
        return 0;
    }
    t = *(u8 *)((u8 *)p + 0x14);
    if (t != 8 && t != 0x10) {
        return 0;
    }
    if (p != 0) {
        v2 = *(void **)((u8 *)p + 0x60);
    } else {
        v2 = 0;
    }
    if (v2 == 0) {
        return 0;
    }
    return *(s32 *)((u8 *)v2 + 0x20);
}
