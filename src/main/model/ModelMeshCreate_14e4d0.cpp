#include "types.h"

class V14e4d0 {
public:
    u8 pad[0x50];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void f5();
    virtual void d6();
    virtual void f7(s32, s32, s32);
};

extern "C" {
extern s32 ModelResGetMeshClass_14cea0(s32);
extern s32 ModelResGetMeshMode_14cec0(void);
extern void *MemStackNew_14e230(s32, s32);
extern u8 D_0046FFE0[0x400];
extern u8 D_0046FFF0[0x400];
extern u8 D_00470000[0x400];
extern u8 D_00470010[0x400];
extern u8 D_00470040[0x400];
extern u8 D_00470070[0x400];
extern u8 D_004701C0[0x400];
}

static inline V14e4d0 *mkA(s32 a)
{
    u8 *o = (u8 *)MemStackNew_14e230(0x120, a);
    if (o != 0) {
        *(void **)(o + 0x50) = D_00470070;
        *(void **)(o + 0x50) = D_004701C0;
        *(void **)(o + 0xA0) = D_00470000;
        *(void **)(o + 0xA0) = D_0046FFE0;
    }
    return (V14e4d0 *)o;
}

static inline V14e4d0 *mkB(s32 a)
{
    u8 *o = (u8 *)MemStackNew_14e230(0x140, a);
    if (o != 0) {
        *(void **)(o + 0x50) = D_00470070;
        *(void **)(o + 0x50) = D_00470040;
        *(void **)(o + 0x60) = D_00470000;
        *(void **)(o + 0x60) = D_0046FFF0;
        *(void **)(o + 0x50) = D_00470010;
    }
    return (V14e4d0 *)o;
}

static inline V14e4d0 *mkC(s32 a)
{
    u8 *o = (u8 *)MemStackNew_14e230(0x130, a);
    if (o != 0) {
        *(void **)(o + 0x50) = D_00470070;
        *(void **)(o + 0x50) = D_00470040;
        *(void **)(o + 0x60) = D_00470000;
        *(void **)(o + 0x60) = D_0046FFF0;
    }
    return (V14e4d0 *)o;
}

extern "C" void *ModelMeshCreate_14e4d0(s32 arg0, s32 arg1, s32 arg2)
{
    V14e4d0 *r;
    V14e4d0 *o;

    r = 0;
    switch (ModelResGetMeshMode_14cec0()) {
    case 0:
        if (ModelResGetMeshClass_14cea0(arg0) & 1) {
            o = mkC(arg1);
            if (o != 0) {
                o->f5();
                o->f7(arg0, arg1, arg2);
                r = o;
            }
        } else {
            o = mkB(arg1);
            if (o != 0) {
                o->f5();
                o->f7(arg0, arg1, arg2);
                r = o;
            }
        }
        break;
    case 1:
        o = mkA(arg1);
        if (o != 0) {
            o->f5();
            o->f7(arg0, arg1, arg2);
            r = o;
        }
        break;
    }
    return r;
}
