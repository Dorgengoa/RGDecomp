#include "types.h"

struct C44 {
    u8 pad000[0x2C];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
};

extern "C" s32 DebugMenuWidgetGetChildArray_209d80(void *);
extern "C" s32 DebugMenuWidgetGetChildCount_209d70(void *);

struct Obj0;

struct Obj0 {
    u8 pad000[0x2A];
    u16 m2A;
};

extern "C" void DebugMenuWidgetOpen_209210(struct Obj0 *p0)
{
    if (DebugMenuWidgetGetChildArray_209d80(p0) != 0) {
        if (DebugMenuWidgetGetChildCount_209d70(p0) > 0) {
            ((struct C44 *)p0)->v2();
        }
    }
    p0->m2A = (u16)(p0->m2A | 0x80);
}
