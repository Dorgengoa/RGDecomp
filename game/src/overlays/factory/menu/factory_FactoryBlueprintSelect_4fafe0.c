/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintSelect_4fafe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FAFE0 -- attach one item record to a dialog page.
 *
 * ★ `msg.f0C = *item->f04;` written BEFORE the clear of factory_D_0050FF10 is what puts
 * the `sw $2, 0x3C($29)` in that call's delay slot.
 * ★ `factory_D_0050CCC8` / `factory_D_0050FF10` are overlay data, outside the gp window, so the
 * incomplete-array spelling is deliberate: it is what buys `lui %hi`/`addiu %lo`
 * instead of a %gp_rel relocation that could not be resolved at link time.
 * ★ `lui $2, 0x3F80` + `mtc1` is how mwcc materialises a float constant whose
 * low half is zero -- it is a plain `1.0f`.
 */

typedef struct Msg {
    u8  pad00[0xC];
    s32 f0C;
    u8  pad10[0x9C];
} Msg;                                          /* 0xAC */

typedef struct Item {
    u8   pad00[0x4];
    s16 *f04;
} Item;

typedef struct Page {
    u8    pad00[0x70];
    Item *f70;
    u8    pad74[0xC];
    void *f80;
} Page;

typedef struct Job {
    u8    pad00[0x10];
    Item *f10;
} Job;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    factory_D_0050CCC8[];
extern u8    factory_D_0050FF10[];

/*rgp*/
extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintSelect_4fafe0(Page *o, Item *item)
{
    Msg msg __attribute__((aligned(16)));
    Job *job;

    o->f70 = item;
    MsgFormatParamsCtor_28aa00(&msg);
    memset(&msg, 0, 0xAC);
    msg.f0C = *item->f04;
    memset(factory_D_0050FF10, 0, 0x40);
    MsgFormat_28a9a0(factory_D_0050FF10, MsgTableLookup_28aa30(D_00484A70, 0x23), &msg, 1);
    UiSetTextString_28f510(o->f80, 0x91, factory_D_0050CCC8, 0);
    UiSetTextString_28f510(o->f80, 0x91, factory_D_0050FF10, 0);
    UiSetWidgetVisible_290010(o->f80, 0x91, 1, -1);
    UiSetWidgetPos_290f60(o->f80, 0x91, 0xBA, 0x191);
    UiSetWidgetAlpha_2907a0(o->f80, 0x91, 1.0f);
    job = ((Job *)FactoryGetRequestPtr_367ec0());
    job->f10 = o->f70;
}
