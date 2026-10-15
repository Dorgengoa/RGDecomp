#include "types.h"
struct Half {u16 pad:2;u16 val:10;u16 rest:4;};
extern "C" {

extern void *WeaponCombineLogAdd_3cbd10(s32, void *, s32, s32, s8 *);
extern void *RecTableBinSearch_407bb0(s32, s32, s32);
extern s32 RecTableFindByByteId_407c70(s32, u8);
extern s32 ListFindByKey_407ee0(s32, s8);
extern void *D_00483890;
extern void *D_00483894;

class VC_0 {
public:
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
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual s32 f();
};
class VC_1 {
public:
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
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual s32 f(s16 x0);
};
s32 WeaponCombineAddResult_3c3520(s32 pd0, void *arg1, s8 *arg2, s32 *arg3, s8 *arg4)
{
    void *p10;
    s32 mode;
    s32 t2;
    s32 t24;
    s32 f8;
    void *vtbl;
    void *p4;
    s8 f2;
    s32 t23;
    void *t25;
    s32 f0;
    void *t26;

    if (arg1 == NULL) {
        return 0;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    p10 = *(void **)((u8 *)arg1 + 0x10);
    f8 = *(s16 *)((u8 *)p10 + 0x8);
    f2 = *(s8 *)((u8 *)p10 + 0x2);
    f0 = *(s16 *)((u8 *)p10 + 0x0);
    vtbl = *(void **)((u8 *)arg1 + 0x0);
    mode = ((VC_0 *)(arg1))->f() & 0xFF;
    p4 = *(void **)((u8 *)*(void **)((u8 *)D_00483894 + 0x90) + 0xC);
    vtbl = *(void **)p4;
    t23 = ((VC_1 *)(p4))->f(f8);
    if (t23 == 0) {
        return 0;
    }
    t24 = ListFindByKey_407ee0(t23, f2);
    if(t24==0)return 0;
    t25=RecTableBinSearch_407bb0(t24,f0,mode);
    if(t25==0)return 0;
    t2=RecTableFindByByteId_407c70(t24,*(u8 *)((u8 *)t25+2));
    if(t2==0){*arg4=1;return 0;}
    t26=WeaponCombineLogAdd_3cbd10(*(s32 *)((u8 *)D_00483890+0x10),t25,1,0,arg2);
    if(t26==0)return 0;
    *arg3=((Half *)((u8 *)t26+2))->val;
    return t2;
}
}
