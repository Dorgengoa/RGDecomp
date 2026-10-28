/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceOpen_4f77a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F77A0 -- enter the part-placement mode and seed
 * the anchor table from the current recipe.  476 bytes, 120 instructions, 3
 * conditional branches, 16 calls (br/ins 0.025): the branch-light band.
 *
 * ★ The loop counter and the two cursors are three distinct source variables
 * ([[overlay-normal]]); `i++` sits on BOTH paths, which is why the `beql`
 * carries it in its delay slot rather than a case body's store.
 *
 * ★★ DECLARATION ORDER, on a THREE-value permutation: `h`/`d`/`e` land in
 * $20/$18/$19 for retail and our first draft had `h` and `d` swapped.  Eight
 * orders in ONE probe build: `h, e, d, ...` is exact, `h, d, e` and two others
 * are 8 bad, and every order that puts `e` or `d` ahead of `h` is 11.  So the
 * rule in [[factory-declaration-order-works]] is not limited to a PAIR -- what
 * it needs is that the permutation be reachable by an ORDERING, and a probe
 * build prices the whole set for one round trip.
 *
 * D_00484A70 (_gp - 0x700) and D_00484A48 (_gp - 0x728) are inside the gp
 * window and stay plain.
 */

typedef struct Anchor { s32 x; s32 y; } Anchor;         /* 8 */
typedef struct Slot   { u8 pad00[0x40]; } Slot;         /* 0x40 */
typedef struct Hit    { u8 pad00[0x4]; s16 f04; s16 f06; } Hit;

typedef struct Group {
    u8    pad00[0xC];
    s16   f0C;
    u8    pad0E[0x2];
    Slot *f10;
} Group;

typedef struct Job  { s32 f00; u8 pad04[0xC]; void *f10; } Job;
typedef struct Head { u8 pad00[0x70]; void *f70; } Head;

typedef struct Panel {
    u8      pad00[0x64];
    u8      f64;
    u8      pad65[0xB];
    s16     f70;
    u8      f72;
    u8      pad73[0xD];
    Anchor *f80;
    void   *f84;
} Panel;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern Head *D_00484A48;                        /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void   memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryProduceOpen_4f77a0(Panel *o)
{
    s32     h;
    Slot   *e;
    Anchor *d;
    Group  *g;
    Hit    *r;
    Job    *job;
    s32     a;
    s32     b;
    s32     i;

    o->f72 = 0;
    UiSetWidgetVisible_290010(o->f84, 0x89, 0, -1);
    UiSetWidgetVisible_290010(o->f84, 0x8A, 0, -1);
    UiSetWidgetVisible_290010(o->f84, 0x8C, 0, -1);
    UiSetWidgetVisible_290010(o->f84, 0x8B, 0, -1);
    UiSetSpriteFlags_290bd0(o->f84, 0x87, (long long)(0x200), 1, 0, 0);
    UiSetSpriteFlags_290bd0(o->f84, 0x87, (long long)(0x200), 1, 1, 0);
    UiSetTextString_28f510(o->f84, 0x87, MsgTableLookup_28aa30(D_00484A70, 0x12), 0);
    job = ((Job *)FactoryGetRequestPtr_367ec0());
    job->f00 = 0xE;
    job->f10 = D_00484A48->f70;
    o->f64 = 1;
    UiSetWidgetColor_2905b0(o->f84, 0x88, 1.0f, 1.0f, 1.0f, 1.0f);
    o->f70 = -1;
    memset(o->f80, 0, 0x20);
    h = GetFactoryObj_367f30();
    g = ((Group *)factory_FactoryPartGroupFindById_504080(h, 0xD));
    if (g == 0) {
        return;
    }
    d = o->f80;
    e = g->f10;
    i = 0;
    while (i < g->f0C) {
        a = factory_FactoryPartObjGetGridX_4fe120(e);
        b = factory_FactoryPartObjGetGridY_4fe0c0(e);
        r = ((Hit *)factory_FactorySlotFindAt_502ad0(h, a, b));
        if (r != 0) {
            d->x = r->f04;
            d->y = r->f06;
        }
        i++;
        e = e + 1;
        d = d + 1;
    }
}
