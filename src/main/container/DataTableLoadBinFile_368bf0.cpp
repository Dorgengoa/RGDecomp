#include "types.h"
extern "C" {

extern s32 ArchiveGetFileByPath_1c2800(s32 arg0, void *arg1, s32 *arg2);
extern s32 PathFindFileName_368b60(void *arg0, s32 arg1);
extern void strcat(void *arg0, s32 arg1);
extern void strcpy(void *arg0, s32 arg1);
extern s32 D_0047F990;

class VC {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void h();
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
    virtual void d18();
    virtual void d19();
    virtual s32 g(s32 x0, s32 x1, s32 x2);
};

s32 DataTableLoadBinFile_368bf0(VC *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    volatile s32 sp8C;
    s8 sp40[0x4C];
    s32 r;
    s32 t;
    s32 s;
    void *p;

    t = *(s32 *)((u8 *)arg0 + 0x8);
    if (t == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return 0;
    }
    p = *(void **)((u8 *)arg0 + 0x10);
    if (p == NULL) {
        return 0;
    }
    if (*(s32 *)((u8 *)p + 0x34) <= 0) {
        return 0;
    }
    if (arg3 == 0) {
        arg3 = t;
    }
    if (arg3 == 0) {
        return 0;
    }
    s = PathFindFileName_368b60(arg0, arg3);
    sp8C = 0;
    strcpy(sp40, s);
    strcat(sp40, D_0047F990);
    r = ArchiveGetFileByPath_1c2800(arg1, sp40, (s32 *)&sp8C);

    if (r == 0 || sp8C <= 0) {
        arg0->h();
        return 0;
    }
    return arg0->g(r, sp8C, arg2);
}

}
