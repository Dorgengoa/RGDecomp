/* rgp:protos */
#define RGP_SELF_TextEntryPaletteCursorBob_433dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Obj0Arg0 {
    s32 unk0;
    u8 pad4[0xC];
    f32 unk10;
    u8 pad14[0xC];
    f32 unk20;
    f32 unk24;
} Obj0Arg0;

typedef struct ObjArg1 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[8];
    s16 unk10;
    s16 unk12;
} ObjArg1;

#pragma usefloatacc off
s32 TextEntryPaletteCursorBob_433dc0(Obj0Arg0 *arg0, ObjArg1 *arg1) {
    s32 sp3C;
    s32 sp38;
    f32 t;

    UiGetWidgetPos_2910a0(arg0->unk0, 0x4, &sp3C, &sp38);
    PhaseAdvanceWrapPi_28b630((u8 *)arg0 + 0x10, arg0->unk20);
    t = 4.0f * Sinf_128fd0(arg0->unk10);
    UiMoveWidgetUniform_290f50(arg0->unk0, 0xC, (s32)(t + (f32)(sp3C + (arg1->unk0 + (arg1->unk10 * arg1->unk4)))), sp38 + (arg1->unk2 + (arg1->unk12 * arg1->unk6)), arg0->unk24, 0);
    return 1;
}
