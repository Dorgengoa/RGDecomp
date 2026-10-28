/* rgp:protos */
#define RGP_SELF_TextEntrySetPageTexts_434160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x8];
    s32 m0C;
    u8 pad010[0xD0];
    s16 mE0;
    s16 mE2;
};

void TextEntrySetPageTexts_434160(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s16 t1;
    s32 e;
    s32 rv0;
    s32 r1;
    s32 r3;
    s32 r5;

    t0 = p0->mE0;
    if (t0 != 1) {
        if (t0 != 3) goto go;
    }
    return;
go:
    {
        p0->mE2 = p1;
        t1 = p0->mE0;
        rv0 = 0x406;
        if (t1 == 0) {
            rv0 = 0x1E;
        }
        r1 = MsgTableLookup_28aa30(p0->m0C, ((s16)rv0 + *(volatile s16 *)&p0->mE2));
        UiSetTextString_28f510(p0->m00, 5, r1, 0);
        r3 = MsgTableLookup_28aa30(p0->m0C, p0->mE2);
        UiSetTextString_28f510(p0->m00, 6, r3, 0);
        r5 = MsgTableLookup_28aa30(p0->m0C, (p0->mE2 + 0xA));
        UiSetTextString_28f510(p0->m00, 8, r5, 0);
    }
}
