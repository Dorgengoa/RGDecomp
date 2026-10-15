#include "types.h"

/* jalr through obj->vtbl[0x20] (index 6, vtable starts 8 bytes in) over two
   arrays of embedded 0x98-byte objects (arg0+8, arg0+0xC). */
class V {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
};

struct Obj : V {
    u8 pad[0x98 - 4];
};

struct S {
    u8 pad0[8];
    Obj *a;
    Obj *b;
};

extern "C" s32 D_004644A8[3];

extern "C" void WorldSubsysZoneEntryReleaseAll_41e1c0(S *arg0)
{
    Obj *p;
    s32 n;
    s32 i;

    p = arg0->a;
    if (p != NULL) {
        n = D_004644A8[0];
        i = 0;
        while (i < n) {
            p->v6();
            i++;
            p = (Obj *)((u8 *)p + 0x98);
        }
    }
    p = arg0->b;
    if (p != NULL) {
        n = D_004644A8[0];
        i = 0;
        while (i < n) {
            p->v6();
            i++;
            p = (Obj *)((u8 *)p + 0x98);
        }
    }
}
