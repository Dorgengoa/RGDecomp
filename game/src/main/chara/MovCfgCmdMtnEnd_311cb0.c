/* rgp:protos */
#define RGP_SELF_MovCfgCmdMtnEnd_311cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct { u8 d[0x14]; } E20_311cb0;
typedef struct { u8 d[0xC]; } E12_311cb0;

/*rgp*/
/*rgp*/
extern E20_311cb0 *D_004829A0;
extern s32 D_004829A4;
extern E12_311cb0 *D_004829A8;
extern s32 D_004829AC;

s32 MovCfgCmdMtnEnd_311cb0(void)
{
    E12_311cb0 *e;
    E20_311cb0 *r;

    if (D_004829A8 == NULL || D_004829A0 == NULL) {
        return 1;
    }
    e = &D_004829A8[D_004829AC];
    r = ((E20_311cb0 *)NamedCompListGetEntries_3124a0(e));
    NamedCompListSetCount_312480(e, &D_004829A0[D_004829A4] - r);
    D_004829AC++;
    return 1;
}
