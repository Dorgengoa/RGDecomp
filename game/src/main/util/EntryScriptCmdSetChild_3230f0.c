/* rgp:protos */
#define RGP_SELF_EntryScriptCmdSetChild_3230f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct E8 { u8 b[8]; };

s32 EntryScriptCmdSetChild_3230f0(struct E8 *p0)
{
    struct E8 *q;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv9;
    s32 r4;
    s32 r5;
    s32 r7;

    q = p0;
    r0 = GetEntryTableGlobal_32c2e0();
    if (r0 == 0) {
        return 0;
    }
    r1 = ((short)EntryListGetChildCursor_3233a0(r0));
    r2 = ((s32)EntryListGetChild_3233c0(r0, r1));
    EntryListStepChildCursor_323390(r0);
    rv9 = 1;
    if (r2 == 0) {
        rv9 = 0;
    } else {
        r4 = EntryListGetHeap_3237d0(r0);
        r5 = SlotGetInt_15f720(q++);
        EntryChildSetName_323d10(r2, r4, r5);
        r7 = VariantGetInt_15f780(q);
        EntryChildSetField4Related_323d00(r2, r7);
        rv9 = 1;
    }
    return rv9;
}
