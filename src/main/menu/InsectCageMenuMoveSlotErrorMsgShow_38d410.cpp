#include "types.h"

class V {
public:
    /* +0x008 */ virtual void slot008();
    /* +0x00c */ virtual void slot00C();
    /* +0x010 */ virtual void slot010();
    /* +0x014 */ virtual void slot014();
    /* +0x018 */ virtual void slot018();
    /* +0x01c */ virtual void slot01C();
    /* +0x020 */ virtual void slot020();
    /* +0x024 */ virtual void slot024();
    /* +0x028 */ virtual void slot028();
    /* +0x02c */ virtual void slot02C();
    /* +0x030 */ virtual void slot030();
    /* +0x034 */ virtual void slot034();
    /* +0x038 */ virtual void slot038();
    /* +0x03c */ virtual void slot03C();
    /* +0x040 */ virtual void slot040();
    /* +0x044 */ virtual void slot044();
    /* +0x048 */ virtual void slot048();
    /* +0x04c */ virtual void slot04C();
    /* +0x050 */ virtual void slot050();
    /* +0x054 */ virtual void slot054();
    /* +0x058 */ virtual void slot058();
    /* +0x05c */ virtual void slot05C();
    /* +0x060 */ virtual void slot060();
    /* +0x064 */ virtual void slot064();
    /* +0x068 */ virtual void slot068();
    /* +0x06c */ virtual void slot06C();
    /* +0x070 */ virtual void slot070();
    /* +0x074 */ virtual void slot074();
    /* +0x078 */ virtual void slot078();
    /* +0x07c */ virtual void slot07C();
    /* +0x080 */ virtual void slot080();
    /* +0x084 */ virtual void slot084();
    /* +0x088 */ virtual void slot088();
    /* +0x08c */ virtual void slot08C();
    /* +0x090 */ virtual void slot090();
    /* +0x094 */ virtual void slot094();
    /* +0x098 */ virtual void slot098();
    /* +0x09c */ virtual void slot09C();
    /* +0x0a0 */ virtual void slot0A0();
    /* +0x0a4 */ virtual void slot0A4();
    /* +0x0a8 */ virtual void slot0A8();
    /* +0x0ac */ virtual void slot0AC();
    /* +0x0b0 */ virtual void slot0B0();
    /* +0x0b4 */ virtual void slot0B4();
    /* +0x0b8 */ virtual void slot0B8();
    /* +0x0bc */ virtual void slot0BC();
    /* +0x0c0 */ virtual void slot0C0();
    /* +0x0c4 */ virtual void slot0C4();
    /* +0x0c8 */ virtual void slot0C8();
    /* +0x0cc */ virtual void slot0CC();
    /* +0x0d0 */ virtual void slot0D0();
    /* +0x0d4 */ virtual void slot0D4();
    /* +0x0d8 */ virtual void slot0D8();
    /* +0x0dc */ virtual void slot0DC();
    /* +0x0e0 */ virtual void slot0E0();
    /* +0x0e4 */ virtual void slot0E4();
    /* +0x0e8 */ virtual void slot0E8();
    /* +0x0ec */ virtual void slot0EC();
    /* +0x0f0 */ virtual void slot0F0();
    /* +0x0f4 */ virtual void slot0F4();
    /* +0x0f8 */ virtual void slot0F8();
    /* +0x0fc */ virtual void slot0FC();
    /* +0x100 */ virtual void slot100();
    /* +0x104 */ virtual void slot104();
    /* +0x108 */ virtual void slot108();
    /* +0x10c */ virtual void slot10C();
    /* +0x110 */ virtual void slot110();
    /* +0x114 */ virtual void slot114();
    /* +0x118 */ virtual s32 slot118(s32 a);
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
    Buf buf;

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
