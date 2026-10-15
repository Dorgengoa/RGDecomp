#include "types.h"

class VO {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void f();
};

extern "C" {

typedef struct {
    s32 w0;
    void *p4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0x10];
    void *p2C;
    s32 w30;
    u8 pad34[4];
    void *p38;
    s32 w3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
} Desc;

typedef struct {
    u8 **pp0;
    s32 *p4;
    s32 w8;
    s32 wC;
    u8 b10;
} Arg;

extern void ModelResRelocate_14bfd0(s32 *, s32);
extern u8 *MemStackNew_14e230(s32, s32);
extern s32 CollFrameTreeBuild_16ba00(s32 *, s32);
extern void InfoCfgParseAll_1afd00(u8 *, Desc *);
extern s32 ArchiveGetFileByPath_1c2800(s32, s32, s32 *);
extern void ModelObjExCtor_1c4920(u8 *);
extern void *memset(void *, s32, u32);
extern u8 D_0045BEA0[0x10];
extern u8 D_00470F50[0x400];

s32 Character2NewFromInfoCfgWithColl_1fd8f0(Arg *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Desc desc;
    s32 spF0[2];
    s32 cnt;
    s32 heap;
    u8 *o;
    s32 r;

    if (arg0 == NULL || arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    heap = arg0->w8;
    if (heap == 0) {
        return 0;
    }    if (arg0->pp0 == NULL) {
        goto skip;
    }
    {
        o = MemStackNew_14e230(0x790, heap);
        if (o != NULL) {
            ModelObjExCtor_1c4920(o);
            *(u8 **)(o + 0x1B0) = D_00470F50;
        }
        *arg0->pp0 = o;
        memset(&desc, 0, 0x88);
        desc.w30 = 8;
        desc.p2C = desc.buf40;
        desc.w3C = 8;
        desc.w0 = arg1;
        desc.p38 = desc.buf60;
        desc.p4 = D_0045BEA0;
        desc.w8 = heap;
        desc.wC = heap;
        desc.w10 = heap;
        desc.w14 = arg0->wC;
        desc.w18 = arg0->b10;
        o = *arg0->pp0;
        ((VO *)o)->f();
        InfoCfgParseAll_1afd00(*arg0->pp0, &desc);
        *(s32 *)(*arg0->pp0 + 0x4DC) = desc.w14;
    }
skip:
    if (arg0->p4 != NULL && arg3 != 0) {
        r = ArchiveGetFileByPath_1c2800(arg1, arg3, &cnt);
        if (r != 0 && cnt > 0) {
            spF0[0] = 0;
            ModelResRelocate_14bfd0(spF0, r);
            *arg0->p4 = CollFrameTreeBuild_16ba00(spF0, heap);
        }
    }
    return 1;
}
}
