/* rgp:protos */
#define RGP_SELF_RankingCommitPoints_3e8b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Callee-saved order, descending from the highest, is tag($18), lim($17),
   obj($16) -- so that is the DECLARATION order even though the assignments
   run lim, obj, tag.  `lim` is an s32 local fed by an `lh`: retail compares it
   with a plain `slt` and no dsll32/dsra32 widening, so it is NOT s16.
   p->m18 is re-read before every store; mwcc cannot prove the stores do not
   alias it, and retail's repeated `lw $2,0x18($19)` is the tell. */

s32 RankingCommitPoints_3e8b80(u8 *p, int rgp_a1)
{
    s32 tag;
    s32 lim;
    s32 obj;
    u8 *h;
    s32 r;
    u8 *e;
    s32 v;
    s32 *slot;

    h = *(u8 **)(p + 0x18);
    /* the FIRST of the three loads is the one mwcc sinks into the jal delay
       slot, so the source order is rotated one step from the listing's. */
    tag = *(s32 *)(h + 0x180);
    lim = *(s16 *)(h + 0x4C9C);
    obj = *(s32 *)(h + 0x4C90);
    PartyAddRankingPointsMaybe_3c3240(h, (int)rgp_a1);
    r = ((short)StateGetChapter_3cd5b0(*(void **)(p + 0x10)));
    *(s16 *)(*(u8 **)(p + 0x18) + 0x4C9C) = r;
    if (lim < r) {
        *(s32 *)(*(u8 **)(p + 0x18) + 0x4C8C) = tag;
        *(s16 *)(*(u8 **)(p + 0x18) + 0x4C88) = lim;
        *(s32 *)(*(u8 **)(p + 0x18) + 0x4CA4) = obj;
    }
    PartySetPrevRankingPointsMaybe_3c3210(*(void **)(p + 0x18), tag);
    *(s16 *)(*(u8 **)(p + 0x18) + 0x4C88) = lim;
    *(s32 *)(*(u8 **)(p + 0x18) + 0x4C94) = obj;
    RankingUpdateMaybe_3e8ce0(p);
    e = ((u8 *)RankingFindPlayerEntryMaybe_3e8c70(p));
    if (e == 0) {
        return 0;
    }
    v = *(s16 *)(e + 0xC);
    *(s32 *)(*(u8 **)(p + 0x18) + 0x4C90) = v;
    slot = (s32 *)(*(u8 **)(p + 0x18) + 0x4C98);
    if (v < *slot) {
        *slot = v;
        RankingUpdateMaybe_3e8ce0(p);
    }
    return 1;
}
