#include "types.h"

/* factory.bin overlay, 0x004FAFE0 -- attach one item record to a dialog page.
 *
 * ★ `msg.f0C = *item->f04;` written BEFORE the clear of D_0050FF10 is what puts
 * the `sw $2, 0x3C($29)` in that call's delay slot.
 * ★ `D_0050CCC8` / `D_0050FF10` are overlay data, outside the gp window, so the
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
extern u8    D_0050CCC8[];
extern u8    D_0050FF10[];

extern void  func_28AA00(void *p);
extern void  func_131B60(void *p, s32 v, s32 n);
extern s32   func_28AA30(void *ctx, s32 id);
extern void  func_28A9A0(void *p, s32 a, void *src, s32 n);
extern void  func_28F510(void *w, s32 id, void *p, s32 a);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_290F60(void *w, s32 id, s32 a, s32 b);
extern void  func_2907A0(void *w, s32 id, f32 v);
extern Job  *func_367EC0(void);

void factory_FactoryBlueprintSelect_4fafe0(Page *o, Item *item)
{
    Msg msg;
    Job *job;

    o->f70 = item;
    func_28AA00(&msg);
    func_131B60(&msg, 0, 0xAC);
    msg.f0C = *item->f04;
    func_131B60(D_0050FF10, 0, 0x40);
    func_28A9A0(D_0050FF10, func_28AA30(D_00484A70, 0x23), &msg, 1);
    func_28F510(o->f80, 0x91, D_0050CCC8, 0);
    func_28F510(o->f80, 0x91, D_0050FF10, 0);
    func_290010(o->f80, 0x91, 1, -1);
    func_290F60(o->f80, 0x91, 0xBA, 0x191);
    func_2907A0(o->f80, 0x91, 1.0f);
    job = func_367EC0();
    job->f10 = o->f70;
}
