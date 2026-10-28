#include "types.h"

class V {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00c */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01c */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02c */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03c */ 
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04c */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05c */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06c */ 
    /* +0x070 */ 
    /* +0x074 */ 
    /* +0x078 */ 
    /* +0x07c */ 
    /* +0x080 */ 
    /* +0x084 */ 
    /* +0x088 */ 
    /* +0x08c */ 
    /* +0x090 */ 
    /* +0x094 */ 
    /* +0x098 */ 
    /* +0x09c */ 
    /* +0x0a0 */ 
    /* +0x0a4 */ 
    /* +0x0a8 */ 
    /* +0x0ac */ 
    /* +0x0b0 */ 
    /* +0x0b4 */ 
    /* +0x0b8 */ 
    /* +0x0bc */ 
    /* +0x0c0 */ 
    /* +0x0c4 */ 
    /* +0x0c8 */ 
    /* +0x0cc */ 
    /* +0x0d0 */ 
    /* +0x0d4 */ 
    /* +0x0d8 */ 
    /* +0x0dc */ 
    /* +0x0e0 */ 
    /* +0x0e4 */ 
    /* +0x0e8 */ 
    /* +0x0ec */ 
    /* +0x0f0 */ 
    /* +0x0f4 */ 
    /* +0x0f8 */ 
    /* +0x0fc */ 
    /* +0x100 */ 
    /* +0x104 */ 
    /* +0x108 */ 
    /* +0x10c */ 
    /* +0x110 */ 
    /* +0x114 */ 
    /* +0x118 */ s32 slot118(s32 a) { return VCM(s32, (void *, s32), 0x118, a); }
};

struct Buf;
extern "C" s32 MsgFormat_28a9a0(s32 a, s32 b, Buf *c, s32 d);
extern "C" void MsgFormatParamsCtor_28aa00(Buf *a);
extern "C" void UiSetWidgetVisible_290010(s32 a, s32 b, s32 c, s32 d);
extern "C" void UiSetWidgetsVisibleById_291110(s32 a, s32 b, s32 c, s32 d);
extern "C" void UiFitCenterWindow_388270(s32 a, s32 b);
extern "C" s32 InsectCageMenuMsgLookup_389d30(s16 a);
extern "C" s32 D_00483304;
extern "C" s32 D_0048330C;
extern "C" s16 D_004833C8;
extern "C" V *D_004833CC;

typedef struct Buf {
    u8 pad00[0x14];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
    u8 pad20[0xB0 - 0x20];
} Buf;

extern "C" s32 InsectCageMenuMoveSlotErrorMsgShow_38d410(s32 unused, s32 arg1)
{
    Buf buf __attribute__((aligned(16)));

    UiSetWidgetVisible_290010(D_0048330C, 0x7602, 0, -1);
    MsgFormatParamsCtor_28aa00(&buf);
    buf.f14 = 0;
    if (D_004833CC != NULL) {
        buf.f1C = D_004833CC->slot118(0);
    }
    MsgFormat_28a9a0(D_00483304 + 0x800, InsectCageMenuMsgLookup_389d30(D_004833C8), &buf, 1);
    UiFitCenterWindow_388270(0x75DA, 2);
    UiSetWidgetsVisibleById_291110(arg1, 0x75DA, 1, 1);
    return 1;
}
