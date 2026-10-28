/* rgp:protos */
#define RGP_SELF_MenuPartyReserveFaceSprites_29ea50 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted. Animation-frame table lookup w/ a local s16[]
   array (`sp90`, filled from a `D_004508C0` template via a 2-wide rotated
   copy loop) indexed by a computed `var_20` selector, feeding a per-entry
   struct fill keyed off a match against a `D_00450820` table. Needs a
   careful asm read of asm/matchings/main/MenuPartyReserveFaceSprites_29ea50.s; not attempted this
   lane. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    s16 v[3][7];
} Tbl;

typedef struct {
    s16 id;
    s16 y;
    s16 x;
} Pos;

typedef struct {
    s16 x;
    s16 pad2;
    s16 h;
    s16 w;
    s16 y;
    s16 x2;
    s16 h2;
    s16 w2;
} Item;

extern Tbl D_004508C0 __attribute__((aligned(2)));
extern Pos D_00450820[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuPartyReserveFaceSprites_29ea50(u8 *s, u16 base)
{
    Tbl t __attribute__((aligned(16)));
    s32 b;
    u8 *g;
    s32 n;
    s32 i;
    s32 row;
    s16 *rp;
    Item *e;
    u8 *u;
    s16 id;
    s32 k;
    s32 j;
    Pos *p;

    g = ((u8 *)GetGameData_1fede0());
    n = PartyCountReserve_3c1c20(*(s32 *)(g + 0x18), 1, 1);
    t = D_004508C0;
    b = base;
    for (i = 0; i < 7; i++) {
        UiSetSpriteSizeUvSize_28f670(*(s32 *)(s + 0x4C4), (u16)(b + i), 0, 0, 0, 0, 0);
    }
    row = n - 5;
    if (row <= 0) {
        row = 0;
    }
    rp = t.v[row];
    for (j = 0; j < n; j++) {
        e = ((Item *)UiGetWidgetSprite_28fe10(*(s32 *)(s + 0x4C4), (u16)(b + j), 0));
        if (e == 0) {
            return 0;
        }
        u = ((u8 *)PartyGetReserveChara_3c1d20(*(s32 *)(g + 0x18), j));
        if (u == 0) {
            return 0;
        }
        id = *(s16 *)(((u8 *)CharaGetIconRecMaybe_3ae3e0(u)) + 0x2C);
        e->y = 0;
        e->x2 = 0;
        for (k = 0; k < 10; k++) {
            p = &D_00450820[k];
            if (id == p->id) {
                e->x = rp[j];
                e->x2 = p->x;
                e->w2 = 0x40;
                e->w = 0x40;
                if (row == 2) {
                    e->y = p->y + 4;
                    e->h2 = 0x2E;
                    e->h = 0x2E;
                } else {
                    e->y = p->y;
                    e->h2 = 0x36;
                    e->h = 0x36;
                }
            }
        }
    }
    return 1;
}
