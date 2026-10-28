#include "types.h"

class Obj {
public:
    Obj *next;
    Obj *prev;
    s32 x8;
    s32 xC;
    u8 data[0xC];
    u8 sub[0x14];
    VC_VPTR_MEMBER; void v08() { VCM0(void, 0x8); }
};

typedef struct Owner {
    u8 pad0[0x48];
    Obj *head;
} Owner;

extern "C" {
Obj *MemStackNew_14e230(s32, s32);
void MotResHandleCtorMaybe_154700(void *);
void AmixerInit_170dd0(void *);
extern u8 D_00470320[0x400];
}

static inline Obj *find(Owner *o, s32 id)
{
    Obj *p;
    for (p = o->head; p != 0; p = p->next) {
        if (id == p->xC) {
            return p;
        }
    }
    return 0;
}

static inline u8 *findData(Owner *o, s32 id)
{
    Obj *p = find(o, id);
    return p ? p->data : 0;
}

extern "C" u8 *MotionPlayerAddEntryUnique_172850(Owner *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Obj *n;
    Obj *p;
    Obj *t;
    u8 *d;

    if (findData(arg0, arg1) != 0) {
        return 0;
    }
    n = MemStackNew_14e230(0x34, arg2);
    if (n != 0) {
        *(void **)((u8 *)n + 0x30) = D_00470320;
        MotResHandleCtorMaybe_154700(n->data);
        AmixerInit_170dd0(n->sub);
        *(s32 *)(n->data + 4) = 0;
        *(s32 *)(n->data + 8) = 0;
        AmixerInit_170dd0(n->sub);
        n->v08();
    }
    if (n == 0) {
        return 0;
    }
    n->x8 = arg3;
    d = n->data;
    n->xC = arg1;
    *(s32 *)(n->data + 4) = 0;
    *(s32 *)(n->data + 8) = 0;
    AmixerInit_170dd0(d + 0xC);
    if (arg0->head == 0) {
        arg0->head = n;
    } else {
        p = arg0->head;
        while (p != 0) {
            if (p->next == 0) {
                break;
            }
            p = p->next;
        }
        p->next = n;
        if (n != 0) {
            n->prev = p;
        }
    }
    return d;
}
