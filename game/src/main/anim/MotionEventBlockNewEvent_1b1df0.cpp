#include "types.h"

/* jalr $25 == C++ virtual dispatch; slot = 8 + 4*index (mwcc's vtable has two
   leading words).  Two classes here: the source object's vptr is at 0x24 and
   the list-node's vptr is at 0x14; both calls are virtual #0.
   Four near-identical arms => four DISTINCT struct types so the tail-merger
   cannot fuse them. */

class VT24 {
    u8 pad_[0x24];
public:
    VC_VPTR_MEMBER; s32 f8() { return VCM0(s32, 0x8); }
};

class VT14 {
    u8 pad_[0x14];
public:
    VC_VPTR_MEMBER; void f8() { VCM0(void, 0x8); }
};

struct T1 {
    s32 f0; s32 f4; f32 f8; f32 fC; u8 f10; u8 p11[3];
    s32 f14; s32 f18; f32 f1C; f32 f20; void *f24; s32 f28; s32 f2C;
    char n30[8];
};
struct T2 {
    s32 f0; s32 f4; f32 f8; f32 fC; u8 f10; u8 p11[3];
    s32 f14; s32 f18; f32 f1C; f32 f20; void *f24; s32 f28; s32 f2C;
};
struct T3 {
    s32 f0; s32 f4; f32 f8; f32 fC; u8 f10; u8 p11[3];
    s32 f14; s32 f18; f32 f1C; f32 f20; void *f24; s32 f28; s32 f2C; s32 f30;
};
struct T4 {
    s32 f0; s32 f4; f32 f8; f32 fC; u8 f10; u8 p11[3];
    s32 f14; s32 f18; f32 f1C; f32 f20; void *f24; s32 f28; s32 f2C; s32 f30;
    u8 f34; u8 f35;
};

struct Node { Node *f0; Node *f4; u8 p8[0x8]; void *f10; void *f14; };
struct Owner { u8 pad00[0x10]; Node *f10; };

extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" u32 strlen(char *);
extern "C" char *strcpy(char *, char *);
extern "C" u8 D_00471030[];
extern "C" u8 D_00471048[];
extern "C" u8 D_00471060[];
extern "C" u8 D_00471080[];
extern "C" u8 D_004710A0[];
extern "C" u8 D_004710C0[];

extern "C" void *MotionEventBlockNewEvent_1b1df0(Owner *own, void *heap, s32 kind, void *src)
{
    void *q;
    Node *nd;
    Node *cur;
    Node *nx;
    char *nm;

    q = 0;
    if (src != 0) {
        if (kind != ((VT24 *)src)->f8()) {
            src = 0;
        }
    }
    switch (kind) {
    case 1:
        {
            T1 *a = (T1 *)MemStackNew_14e230(0x38, heap);
            q = a;
            if (a != 0) {
                a->f24 = D_00471060;
                a->f0 = 0;
                a->f4 = 0;
                a->fC = 0.0f;
                a->f8 = 0.0f;
                a->f14 = 0;
                a->f1C = -1.0f;
                a->f20 = -1.0f;
                a->f18 = 0;
                a->f10 = 0;
                a->f24 = D_004710C0;
                a->f28 = 0;
                a->n30[0] = 0;
                a->f2C = -1;
            }
            if (src != 0 && a != 0) {
                T1 *s = (T1 *)src;
                nm = s->n30;
                a->f0 = s->f0;
                a->f8 = s->f8;
                a->fC = s->fC;
                a->f14 = s->f14;
                a->f1C = s->f1C;
                a->f20 = s->f20;
                a->f10 = s->f10;
                a->f4 = s->f4;
                a->f28 = s->f28;
                if (nm != 0) {
                    if (strlen(nm) <= 7) {
                        strcpy(a->n30, nm);
                    }
                }
            }
        }
        break;
    case 2:
        {
            T2 *a = (T2 *)MemStackNew_14e230(0x30, heap);
            if (a != 0) {
                a->f24 = D_00471060;
                a->f0 = 0;
                a->f4 = 0;
                a->fC = 0.0f;
                a->f8 = 0.0f;
                a->f14 = 0;
                a->f1C = -1.0f;
                a->f20 = -1.0f;
                a->f18 = 0;
                a->f10 = 0;
                a->f24 = D_004710A0;
                a->f28 = 0;
                a->f2C = -1;
            }
            q = a;
            if (src != 0 && a != 0) {
                T2 *s = (T2 *)src;
                a->f0 = s->f0;
                a->f8 = s->f8;
                a->fC = s->fC;
                a->f14 = s->f14;
                a->f1C = s->f1C;
                a->f20 = s->f20;
                a->f10 = s->f10;
                a->f4 = s->f4;
                a->f28 = s->f28;
                a->f2C = s->f2C;
            }
        }
        break;
    case 3:
        {
            T3 *a = (T3 *)MemStackNew_14e230(0x34, heap);
            if (a != 0) {
                a->f24 = D_00471060;
                a->f0 = 0;
                a->f4 = 0;
                a->fC = 0.0f;
                a->f8 = 0.0f;
                a->f14 = 0;
                a->f1C = -1.0f;
                a->f20 = -1.0f;
                a->f18 = 0;
                a->f10 = 0;
                a->f24 = D_00471080;
                a->f28 = 0;
                a->f2C = 1;
                a->f30 = 1;
            }
            q = a;
            if (src != 0 && a != 0) {
                T3 *s = (T3 *)src;
                a->f0 = s->f0;
                a->f8 = s->f8;
                a->fC = s->fC;
                a->f14 = s->f14;
                a->f1C = s->f1C;
                a->f20 = s->f20;
                a->f10 = s->f10;
                a->f4 = s->f4;
                a->f2C = s->f2C;
                a->f28 = s->f28;
            }
        }
        break;
    case 4:
        {
            T4 *a = (T4 *)MemStackNew_14e230(0x38, heap);
            if (a != 0) {
                a->f24 = D_00471060;
                a->f0 = 0;
                a->f4 = 0;
                a->fC = 0.0f;
                a->f8 = 0.0f;
                a->f14 = 0;
                a->f1C = -1.0f;
                a->f20 = -1.0f;
                a->f18 = 0;
                a->f10 = 0;
                a->f24 = D_00471030;
                a->f30 = 0;
                a->f28 = 0;
                a->f2C = 0;
                a->f30 = 0;
                a->f35 = 0;
                a->f34 = 0;
            }
            q = a;
            if (src != 0 && a != 0) {
                T4 *s = (T4 *)src;
                a->f0 = s->f0;
                a->f8 = s->f8;
                a->fC = s->fC;
                a->f14 = s->f14;
                a->f1C = s->f1C;
                a->f20 = s->f20;
                a->f10 = s->f10;
                a->f4 = s->f4;
                a->f28 = s->f28;
                a->f2C = s->f2C;
            }
        }
        break;
    }
    if (q != 0) {
        nd = (Node *)MemStackNew_14e230(0x18, heap);
        if (nd != 0) {
            nd->f14 = D_00471048;
            ((VT14 *)nd)->f8();
        }
        if (nd != 0) {
            nd->f10 = q;
            cur = own->f10;
            if (cur != 0) {
                while (cur != 0) {
                    nx = cur->f0;
                    if (nx == 0) {
                        break;
                    }
                    cur = nx;
                }
                cur->f0 = nd;
                if (nd != 0) {
                    nd->f4 = cur;
                }
            } else {
                own->f10 = nd;
            }
        }
    }
    return q;
}
