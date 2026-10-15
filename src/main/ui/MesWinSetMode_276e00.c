#include "types.h"

extern void TextStyleSetFontType_26edf0(void *, s32);
extern void MesWinSetKind_276c80(void *, s32);
extern void MesWinSetStyle_276d60(void *, s32);
extern void MesWinReset_276eb0(void *);
extern void MesWinSetFlush_2775f0(void *, s32);
extern void MesWinSetCharSpeed_277630(void *, f32);
extern f32 D_0047DAB4;

void MesWinSetMode_276e00(void *arg0, s32 arg1) {
    MesWinReset_276eb0(arg0);
    switch (arg1) {
    case 0:
        MesWinSetCharSpeed_277630(arg0, D_0047DAB4);
        MesWinSetFlush_2775f0(arg0, 0);
        *(s16 *)((u8 *)arg0 + 0x1C4A) = 1;
        MesWinSetKind_276c80(arg0, 1);
        MesWinSetStyle_276d60(arg0, 0);
        TextStyleSetFontType_26edf0(arg0, 1);
            break;
    }
}
