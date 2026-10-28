#include "types.h"

typedef struct Hdr { s32 w[12]; } Hdr;
typedef struct Arr { s32 w[20]; } Arr;

class Prm {
public:
    Hdr hdr;
    s16 m30;
    s16 m32;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    VC_VPTR_MEMBER; s32 Type() { return VCM0(s32, 0x8); }
    s32 m50;
    s32 m54;
    f32 m58;
    f32 m5C;
    Arr arr;
};

typedef struct Node { struct Node *next; u8 pad4[0xC]; Prm *prm; } Node;
typedef struct Set { u8 pad0[4]; Node **lists; } Set;

extern "C" {
extern Prm *FuncDataTableNewEntry_190db0(Set *, s32, s32);
}

extern "C" s32 FuncDataTableClone_18fc10(Set *src, Set *dst, s32 arg2)
{
    s32 i;
    Node *n;
    Prm *d;
    Prm *s;
    s32 t;

    dst->lists = 0;
    if (src->lists == 0) {
        dst->lists = 0;
    } else {
    for (i = 0; i < 13; i++) {
        for (n = src->lists[i]; n != 0; n = n->next) {
            d = FuncDataTableNewEntry_190db0(dst, i, arg2);
            if (d == 0) {
                break;
            }
            s = n->prm;
            t = s->Type();
            if (t != d->Type()) {
                continue;
            }
            switch (s->Type()) {
            case 0x271B:
                d->hdr = s->hdr;
                d->m30 = s->m30;
                d->m32 = s->m32;
                d->m34 = s->m34;
                d->m38 = s->m38;
                d->m3C = s->m3C;
                d->m40 = s->m40;
                d->m44 = s->m44;
                d->m48 = s->m48;
                d->m50 = s->m50;
                d->m54 = s->m54;
                d->m58 = s->m58;
                d->m5C = s->m5C;
                d->arr = s->arr;
                break;
            case 0x271A:
                d->hdr = s->hdr;
                d->m30 = s->m30;
                d->m32 = s->m32;
                d->m34 = s->m34;
                d->m38 = s->m38;
                d->m3C = s->m3C;
                d->m40 = s->m40;
                d->m44 = s->m44;
                d->m48 = s->m48;
                break;
            case 0x271C:
                d->hdr = s->hdr;
                d->m30 = s->m30;
                d->m32 = s->m32;
                d->m34 = s->m34;
                d->m38 = s->m38;
                d->m3C = s->m3C;
                d->m40 = s->m40;
                d->m44 = s->m44;
                d->m48 = s->m48;
                d->m50 = s->m50;
                d->m54 = s->m54;
                break;
            }
        }
    }
    }
    return 1;
}
