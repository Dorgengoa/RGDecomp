#include "types.h"
struct Half {__extension__ unsigned short pad:2;unsigned short val:10;unsigned short rest:4;} __attribute__((aligned(2)));
extern "C" {

extern void *WeaponCombineLogAdd_3cbd10(s32, void *, s32, s32, s8 *);
extern void *RecTableBinSearch_407bb0(s32, s32, s32);
extern s32 RecTableFindByByteId_407c70(s32, u8);
extern s32 ListFindByKey_407ee0(s32, s8);
extern void *D_00483890;
extern void *D_00483894;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xA8); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x0) { return VCM(s32, (void *, s16), 0x70, x0); }
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
