#include "types.h"
class NObj {
public:
    u8 pad0[0x60];
    VC_VPTR_MEMBER; void f8() { VCM0(void, 0x8); }
};
extern "C" {

typedef struct Node10 {
    struct Node10 *unk0;
    struct Node10 *unk4;
    s32 unk8;
    u32 unkC;
} Node10;

typedef struct VT8 {
    u8 pad[8];
    void (*unk8)(void *);
} VT8;

Node10 *MemStackNew_14e230(s32, s32);
void MotionPlayerReset_173870(void *);
extern VT8 D_00470330;
}

static inline Node10 *find(Node10 *p, s32 id)
{
    if (id == -1) {
        if (p != 0) {
            return p;
        }
    } else {
        while (p != 0) {
            if (id == p->unkC) {
                return p;
            }
            p = p->unk0;
        }
    }
    return 0;
}

static inline u8 *data(Node10 *n)
{
    if (n != 0) {
        return (u8 *)n + 0x10;
    }
    return 0;
}

extern "C" u8 *MotionListGetOrAddPlayer_172580(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 *r;
    Node10 *n;
    Node10 *q;
    Node10 *nx;
    VT8 *vt;

    r = data(find(*(Node10 **)(arg0 + 4), arg1));
    if (r != 0) {
        return r;
    }
    n = MemStackNew_14e230(0x64, arg2);
    if (n != 0) {
        *(VT8 **)((u8 *)n + 0x60) = &D_00470330;
        ((NObj *)n)->f8();
    }
    if (n == 0) {
        return 0;
    }
    n->unk8 = arg3;
    r = (u8 *)n + 0x10;
    n->unkC = arg1;
    *(s32 *)((u8 *)n + 0x58) = 0;
    MotionPlayerReset_173870(r);
    q = *(Node10 **)(arg0 + 4);
    if (q == 0) {
        *(Node10 **)(arg0 + 4) = n;
    } else {
        while (q != 0) {
            nx = q->unk0;
            if (nx == 0) {
                break;
            }
            q = nx;
        }
        q->unk0 = n;
        if (n != 0) {
            n->unk4 = q;
        }
    }
    return r;
}
