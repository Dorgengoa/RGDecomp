#include "types.h"

/* beql INTO each arm => a switch; the compare chain 0,9,1,7 is the source
   case order reversed. */

extern void MesWinSetFrameType_272b30(void *o, s32 v);
extern void MesWinSetColor_276e80(void *o, s32 v);
extern void TextStyleSetOutlineMode_26f160(void *o, u8 v);

void MesWinSetKind_276c80(void *o, s32 mode)
{
    MesWinSetFrameType_272b30(o, mode);
    switch (mode) {
    case 7:
        MesWinSetColor_276e80(o, 1);
        *(s32 *)((u8 *)o + 0x1C44) = 0;
        TextStyleSetOutlineMode_26f160(o, 4);
        *(s8 *)((u8 *)o + 0x1DEE) = 0;
        *(s8 *)((u8 *)o + 0x1C39) = 0;
        break;
    case 1:
    case 9:
        MesWinSetColor_276e80(o, 1);
        *(s32 *)((u8 *)o + 0x1C44) = 0;
        TextStyleSetOutlineMode_26f160(o, 2);
        *(s8 *)((u8 *)o + 0x1C39) = -1;
        break;
    case 0:
    default:
        MesWinSetFrameType_272b30(o, 0);
        MesWinSetColor_276e80(o, 1);
        *(s32 *)((u8 *)o + 0x1C44) = 0;
        TextStyleSetOutlineMode_26f160(o, 4);
        *(s8 *)((u8 *)o + 0x1C39) = 0;
        break;
    }
}
