/* rgp:protos */
#define RGP_SELF_MesWinCalcLineCentering_273a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00273a10 {
    u8 pad000[0x54];
    s16 unk54;
} Obj00273a10;

/*rgp*/

void MesWinCalcLineCentering_273a10(Obj00273a10 *arg0)
{
    s32 i;
    s32 temp3;
    s32 v;

    i = 0;
    do {
        temp3 = arg0->unk54 - ((short)MesWinGetLineWidth_272350(arg0, i));
        v = temp3 >> 1;
        if (temp3 < 0) {
            v = (temp3 + 1) >> 1;
        }
        *(s16 *)((u8 *)arg0 + i * 2 + 0x1C5C) = (s16) v;
        i += 1;
    } while (i < 0x14);
}
