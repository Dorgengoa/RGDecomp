/* rgp:protos */
#line 1
/* PARKED: 1 round trip: mechanical conversion, 2 vtable calls; length 0xF8 vs retail 0x104. */
#include "types.h"
extern "C" {

extern s32 CharaGetAtkPrmName_1fb3c0(s16, s16, s32);
extern void ExecInfoInit_3a7940(void *);
extern void **CharaMgrPoolFindById_3a8c60(s32, s16);
extern s32 TableFindByNameHashed_3f86e0(s32, s32);
extern void *D_004837B0;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s16 x0) { return VCM(void *, (void *, s16), 0x384, x0); }
};
struct S003a7830 {
    u8 pad0[4];
    u16 x4;
    u8 pad6[2];
    s16 x8;
    s16 xA;
    s16 xC;
    u8 padE[4];
    u8 b0 : 1;
    u8 brest : 7;
    u8 pad13[5];
    s32 x18;
};
struct S003a7830b {
    u8 pad0[4];
    u16 x4;
    u8 pad6[2];
    s16 x8;
    s16 xA;
    s16 xC;
    u8 padE[4];
    u8 x12;
    u8 pad13[5];
    s32 x18;
};
s32 ExecInfoInitFromChara_3a7830(S003a7830 *arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4)
{
    s32 temp_2_2;
    void **temp_2;
    void *temp_20;

    ExecInfoInit_3a7940((void *)arg0);
    if (D_004837B0 == NULL) {
        return 0;
    }
    temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_004837B0 + 0x14), arg1);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_20 = ((VC_0 *)(temp_2))->f(arg2);
    temp_2_2 = TableFindByNameHashed_3f86e0(
        *(s32 *)((u8 *)(*(void **)((u8 *)(*(void **)((u8 *)D_004837B0 + 0x8)) + 0x50)) + 0x8),
        CharaGetAtkPrmName_1fb3c0(arg1, arg2, arg4));
    arg0->x4 = 1;
    arg0->x8 = arg1;
    arg0->xA = arg2;
    if (temp_20 != NULL) {
        arg0->xC = *(s16 *)((u8 *)temp_20 + 0x4);
    } else {
        arg0->xC = -1;
    }
    arg0->b0 = arg3;
    arg0->x18 = temp_2_2;
    return 1;
}

}
