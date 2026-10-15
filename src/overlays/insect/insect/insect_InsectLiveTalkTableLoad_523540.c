#include "types.h"
/* insect 0x00523540 -- the insect-record script runner.  Same shape as
 * 0x00522CC0 but on the func_42Fxxx VM and the D_00524620 command table, which
 * is the table insect_InsectLiveTalkTableCmdName_523970 and its ten siblings are registered in --
 * a free cross-check that D_00485208 really is that VM's context pointer and
 * that its +0x0C is the record count those handlers index with. */
typedef struct InsectRec {
    s32 f00, f04, f08, f0C, f10, f14, f18, f1C, f20, f24, f28, f2C;   /* 0x30 */
} InsectRec;

typedef struct InsectCtx {
    InsectRec *base;   /* +0x00 */
    void *f04;         /* +0x04 */
    s32 f08;
    s32 count;         /* +0x0C */
} InsectCtx;

typedef struct RecVm { u8 raw[0x830]; } RecVm;

extern InsectCtx *D_00485208;
extern const u8 D_00524620[];
extern void func_14D830(void *h);
extern void func_42FC10(RecVm *vm);
extern void func_42FB00(RecVm *vm, const u8 *cmds);
extern void func_42FAC0(RecVm *vm, s32 b, s32 c);
extern void func_42FA20(RecVm *vm);

void insect_InsectLiveTalkTableLoad_523540(InsectCtx *ctx, s32 b, s32 c)
{
    RecVm sp40;

    ctx->count = 0;
    func_14D830(ctx->f04);
    func_42FC10(&sp40);
    func_42FB00(&sp40, D_00524620);
    func_42FAC0(&sp40, b, c);
    D_00485208 = ctx;
    func_42FA20(&sp40);
    D_00485208 = 0;
    ctx->count = 0;
}
