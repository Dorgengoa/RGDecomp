#include "types.h"

class Obj {
public:
    Obj *next;
    Obj *prev;
    u8 pad8[8];
    u8 sub[0x38];
    virtual void v0();
};

typedef struct {
    s32 count;
    u8 pad4[0xC0];
    Obj *head[48];
    Obj *tail[48];
} Tbl;

extern "C" {
void *MemStackNew_14e230(s32, s32);
void TexAnimKeyInit_164080(void *);
}
extern void *D_004701B0[];

extern "C" Obj *TexAnimSeqNewKey_162d00(Tbl *arg0, s32 arg1, s32 arg2)
{
    Obj *o;
    Obj *p;
    Obj *n;

    if (arg1 < 0 || arg1 >= arg0->count) {
        return 0;
    }
    o = (Obj *)MemStackNew_14e230(0x4C, arg2);
    if (o != 0) {
        *(void **)((u8 *)o + 0x48) = D_004701B0;
        TexAnimKeyInit_164080(o->sub);
        o->v0();
    }
    if (o == 0) {
        return 0;
    }
    if (o->sub == 0) {
        return 0;
    }
    o->v0();
    if (arg0->head[arg1] == 0) {
        arg0->head[arg1] = o;
        arg0->tail[arg1] = o;
    } else {
        p = arg0->head[arg1];
        while (p != 0) {
            n = p->next;
            if (n == 0) {
                break;
            }
            p = n;
        }
        p->next = o;
        if (o != 0) {
            o->prev = p;
        }
    }
    return o;
}
