#include "types.h"

/* factory.bin overlay, 0x004FCB60 -- 240 bytes / 60 words, 7 branches,
 * 8 calls.  Translate the pad reading for the current dialog state into the
 * one command code the dialog handler wants.
 *
 * * The `Dlg` container is the byte-identical `factory_FactoryRemoveWaitRequest_4fcc50` /
 *   `factory_FactoryRemoveDialogOpen_4fcee0` verbatim: `f64` is the `u8` state, `f6C` the widget
 *   handle, and `ori $5,$0,0x8912` is the same plain `s32` id in
 *   [0x8000,0xFFFF].
 * * `addiu $6, $2, 0x4` on the returned pointer is a SUB-STRUCT address taken
 *   once and reused on every arm; it rides the state compare's delay slot.
 * * `bne`/`bnel` branch PAST each arm, so the state dispatch is an if/else-if
 *   CHAIN with the cases in the order WRITTEN (1, 2, 3), not a switch
 *   ([[insect-dispatch-branch-polarity]]).
 * * `addiu $5, $0, 0x1` is materialised ONCE for the `state == 1` compare and
 *   then reused as the literal argument 1 and as the inner `f12 == 1` compare
 *   -- one constant, three uses, so `1` must be spelled as a plain literal
 *   everywhere.
 */

typedef struct Sub {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} Sub;

typedef struct Pad {
    u8  pad00[0x4];
    Sub f04;
} Pad;

typedef struct Dlg {
    u8    pad00[0x64];
    u8    f64;
    u8    pad65[0x7];
    void *f6C;
} Dlg;

extern Pad *func_28EA40(void *w, s32 id);
extern void factory_FactoryRemoveDialogAnswer_4fc8d0(Dlg *o, s32 cmd);

void factory_FactoryRemoveDialogConfirm_4fcb60(Dlg *o)
{
    Sub *b;

    b = &func_28EA40(o->f6C, 0x8912)->f04;
    if (o->f64 == 1) {
        if (b->f12 == 0) {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, 1);
        } else if (b->f12 == 1) {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, 2);
        } else {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, -1);
        }
    } else if (o->f64 == 2) {
        if (b->f10 == 0) {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, 3);
        } else {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, -1);
        }
    } else if (o->f64 == 3) {
        if (b->f10 == 0) {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, 4);
        } else {
            factory_FactoryRemoveDialogAnswer_4fc8d0(o, -1);
        }
    }
}
