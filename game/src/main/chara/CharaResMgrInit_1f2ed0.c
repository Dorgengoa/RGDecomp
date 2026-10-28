/* rgp:protos */
#define RGP_SELF_CharaResMgrInit_1f2ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0xD00];
    s32 mD00;
    u8 padD04[0x10];
    s16 mD14;
};

void CharaResMgrInit_1f2ed0(struct Obj0 *p0)
{
    struct Obj0 * l1;
    s32 l0;

    l1 = (struct Obj0 *)p0;
    l0 = 0;
    do {
        CharaResRecInit_1f4ad0(l1);
        l0 = (l0 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x68);
    } while (l0 < 0x20);
    p0->mD00 = 0;
    IdBitmapInit_1f5250((struct Obj0 *)((u8 *)p0 + 0xD04), 0x261, 0x281, (struct Obj0 *)((u8 *)p0 + 0xD10), 4);
    p0->mD14 = 1;
}
