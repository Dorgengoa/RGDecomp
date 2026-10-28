#include "types.h"
extern "C" {

extern s32 ArchiveGetFileByPath_1c2800(s32 arg0, void *arg1, s32 *arg2);
extern s32 PathFindFileName_368b60(void *arg0, s32 arg1);
extern void strcat(void *arg0, s32 arg1);
extern void strcpy(void *arg0, s32 arg1);
extern s32 D_0047F990;

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void h() { VCM0(void, 0x20); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 g(s32 x0, s32 x1, s32 x2) { return VCM(s32, (void *, s32, s32, s32), 0x58, x0, x1, x2); }
};

s32 DataTableLoadBinFile_368bf0(VC *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    volatile s32 sp8C;
    s8 sp40[0x4C] __attribute__((aligned(16)));
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
