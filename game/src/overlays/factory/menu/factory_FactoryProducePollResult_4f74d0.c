/* rgp:protos */
#define RGP_SELF_factory_FactoryProducePollResult_4f74d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F74D0 -- advance the assembly-bench state machine
 * one step.  720 bytes, 180 instructions, 8 conditional branches, 27 calls
 * (br/ins 0.044): the branch-light band.
 *
 * ★ The two `1` operands of `func_290010` in the 0x12 and default arms are
 * mwcc's CSE of the `job->f04 == 1` test's own constant -- an argument never
 * materialised in its own block is not a missing instruction.
 *
 * ★ `o->f74 = 0;` is NOT a dead store: the three loads that follow go through
 * a global pointer that may alias it, so mwcc keeps it.
 *
 * ★ `o->f68 = 1.0f` is stored with `lui` + `sw`, a constant store into an f32
 * field; `o->f6C` takes the gp float and `swc1`.
 *
 * ★ `*p` is spelled out at BOTH compares, not read into a local: a named `v`
 * puts the dereferenced value in the wrong FP register in the second arm.
 * The tail's gp float IS a named local -- written inline it lands after the
 * two constant stores instead of before them.  Eight spellings, one probe
 * build, one exact.
 *
 * _gp = 0x00485170, so -0x7E14 is D_0047D35C, -0x7C94 D_0047D4DC, -0x7C90
 * D_0047D4E0, -0x7F94 D_0047D1DC and -0x728 D_00484A48.
 */

typedef struct Rec {
    s16 f00;
    u8  pad02[0x1C];
    s8  f1E;
} Rec;

typedef struct Panel {
    u8    pad00[0x64];
    u8    f64;
    u8    pad65[0x3];
    f32   f68;
    f32   f6C;
    s16   f70;
    u8    f72;
    u8    pad73[0x1];
    Rec  *f74;
    u8    pad78[0xC];
    void *f84;
} Panel;

typedef struct Job { s32 f00; s32 f04; u8 pad08[0x8]; s32 f10; } Job;

typedef struct Node { u8 pad00[0x88]; u8 f88; } Node;
typedef struct Area { u8 pad00[0xC]; Node *f0C; } Area;
typedef struct Zone { u8 pad00[0xA4]; Area *fA4; } Zone;
typedef struct Ctx  { u8 pad00[0x8]; Zone *f08; u8 pad0C[0x4]; void *f10; u8 pad14[0x4]; void *f18; } Ctx;

typedef struct Head { u8 pad00[0x70]; Rec **f70; } Head;

typedef struct Iter { u8 pad00[0x8]; } Iter;
typedef struct Blk  { u8 pad00[0x20]; } Blk;

extern Head *D_00484A48;                        /* _gp - 0x728  */
extern f32   D_0047D1DC;                        /* _gp - 0x7F94 */
extern f32   D_0047D35C;                        /* _gp - 0x7E14 */
extern f32   D_0047D4DC;                        /* _gp - 0x7C94 */
extern f32   D_0047D4E0;                        /* _gp - 0x7C90 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryProducePollResult_4f74d0(Panel *o)
{
    Iter  it __attribute__((aligned(16)));
    Iter  it2 __attribute__((aligned(16)));
    Blk   blk __attribute__((aligned(16)));
    f32  *p;
    f32   w;
    Job  *job;
    Ctx  *ctx;
    u8   *n;

    if (o->f72 != 0) {
        return;
    }
    p = ((f32 *)UiGetWidgetColor_2904b0(o->f84, 0x88));
    if (o->f64 != 0) {
        if (1.0f == *p) {
            UiFadeWidgetColor_2904e0(o->f84, 0x88, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f, D_0047D4DC);
            o->f64 = 0;
        }
    } else {
        if (D_0047D35C == *p) {
            UiFadeWidgetColor_2904e0(o->f84, 0x88, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D4E0);
            o->f64 = 1;
        }
    }
    job = ((Job *)FactoryGetRequestPtr_367ec0());
    if (job->f00 != 0) {
        return;
    }
    UiSetWidgetVisible_290010(o->f84, 0x88, 0, -1);
    UiSetWidgetVisible_290010(o->f84, 0x87, 0, -1);
    o->f74 = 0;
    o->f74 = D_00484A48->f70[1];
    if (job->f04 == 1) {
        factory_FactoryProduceSetProductStateFlags_4f4e90(o, o->f74->f00);
        UiSetWidgetVisible_290010(o->f84, 0x89, 1, -1);
        ctx = ((Ctx *)GetGameData_1fede0());
        InvAddItemRepeat_3c47b0(ctx->f18, o->f74->f00, 0, 1);
        ItemGroupUnlock_3cbac0(ctx->f10, o->f74->f1E, 0, 0);
        factory_FactoryBlueprintClearChosen_4faf10(D_00484A48);
        ((Job *)FactoryGetRequestPtr_367ec0())->f10 = 0;
        FactoryCompletionUpdate_3e7ae0(ctx, 0, 0, 0);
        n = (u8 *)ctx->f08->fA4->f0C;
        if (n != 0) {
            n = n + 0x88;
        }
        IterInit_370170(&it, n, 0, 0);
        IterAttach_370100(&it, 0, 0, 0);
        ContainerViewItemFilterCtor_40c410(&blk, ctx, 0x12, -1, 1, 1, 0, 1);
        IterInit_370170(&it2, &blk, 0, 0);
        IterAttach_370100(&it2, 0, 0, 0);
        o->f72 = 1;
        factory_FactoryProduceConsumeMaterials_4f4f80(o);
        return;
    }
    if (job->f04 == 0x12) {
        o->f70 = job->f04;
        UiSetWidgetVisible_290010(o->f84, 0x8B, 1, -1);
        UiSetWidgetVisible_290010(o->f84, 0x8E, 0, -1);
        UiSetWidgetVisible_290010(o->f84, 0x8D, 0, -1);
        UiSetWidgetVisible_290010(o->f84, 0x8F, 0, -1);
        UiSetWidgetVisible_290010(o->f84, 0x90, 0, -1);
        o->f72 = 9;
        factory_FactoryProduceShowMessage_4f62d0(o, 4);
        return;
    }
    UiSetWidgetVisible_290010(o->f84, 0x8C, 1, -1);
    w = D_0047D1DC;
    o->f70 = job->f04;
    o->f68 = 1.0f;
    o->f6C = w;
    o->f72 = 7;
}
