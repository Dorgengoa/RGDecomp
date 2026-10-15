#include "types.h"

/* Start a script at an entry point and run it.

   A negative id means the blob's default entry; anything else is looked up in
   the label table, a flat array of {id, offset} pairs. Either way the entry
   record that comes back says how many stack slots the routine wants and how
   many of those are already filled by arguments -- the frame is carved out
   below the current stack top, and the slots past the arguments are zeroed.

   Running past the end of the operand stack is fatal, not silent: it prints
   "RUNTIME ERROR: %s" / "stack overflow" and exits. */

typedef struct Label {
    s32 id;        /* +0x00 */
    s32 offset;    /* +0x04 */
} Label;

typedef struct Entry {
    s32 code;      /* +0x00, offset into the code section */
    u8 pad04[0x4];
    s32 slots;     /* +0x08, total stack slots */
    s32 args;      /* +0x0C, of which this many arrive filled */
} Entry;

typedef struct ScriptBlob {
    u8 pad00[0x4];
    s32 defaultEntry;  /* +0x04 */
    u8 pad08[0x4];
    s32 labels;        /* +0x0C, offset to the label table */
    s32 labelCount;    /* +0x10 */
} ScriptBlob;

typedef struct ScriptVm {
    u8 pad00[0x10];
    u8 *stack;         /* +0x10 */
    u8 *stackTop;      /* +0x14 */
    u8 *stackEnd;      /* +0x18 */
    u8 pad1c[0x8];
    u8 *frames;        /* +0x24 */
    u8 *frameTop;      /* +0x28 */
    u8 pad2c[0x4];
    u8 *frameBase;     /* +0x30 */
    Entry *entry;      /* +0x34 */
    u8 pad38[0x4];
    s32 halted;        /* +0x3C */
    s32 unk40;         /* +0x40 */
    ScriptBlob *blob;  /* +0x44 */
    u8 *code;          /* +0x48 */
    u8 pad4c[0x4];
    s32 unk50;         /* +0x50 */
} ScriptVm;

typedef struct Console {
    u8 pad00[0xC];
    void *out;         /* +0x0C */
} Console;

/* `const` is what keeps these OUT of small data: mwcc gives any 4-byte extern
   a %gp_rel relocation, and retail addresses this one with %hi/%lo. The two
   strings have to be declared as the externals the reference names, or the
   relocation points at mwcc's own @N label instead. */
extern Console *const D_00449858;
extern const char D_00459230[];   /* the "RUNTIME ERROR: %s" format */
extern const char D_00459248[];   /* "stack overflow" */

extern void Fprintf_12f9a0(void *out, const char *fmt, const char *what);
extern void Exit_12f4e0(s32 code);
extern void memset(void *dst, s32 fill, s32 len);
extern void ScriptVmExec_173b00(ScriptVm *vm, u8 *pc);

s32 ScriptVmRunEntry_176940(ScriptVm *vm, s32 id)
{
    u8 *pc;
    ScriptBlob *blob;
    Label *label;
    s32 i;

    if (vm->blob == NULL) {
        return -1;
    }

    vm->stackTop = vm->stack;
    vm->frameTop = vm->frames;
    vm->entry = NULL;

    if (id < 0) {
        blob = vm->blob;
        vm->entry = (Entry *)((u8 *)blob + blob->defaultEntry);
    } else {
        blob = vm->blob;
        label = (Label *)((u8 *)blob + blob->labels);
        for (i = 0; i < blob->labelCount; i++, label++) {
            if (label->id == id) {
                vm->entry = (Entry *)((u8 *)blob + label->offset);
                break;
            }
        }
    }

    if (vm->entry == NULL) {
        return -1;
    }

    vm->frameBase = vm->stackTop - vm->entry->args * 8;
    vm->stackTop = vm->frameBase + vm->entry->slots * 8;
    if (vm->stackTop >= vm->stackEnd) {
        Fprintf_12f9a0(D_00449858->out, D_00459230, D_00459248);
        Exit_12f4e0(-1);
    }

    memset(vm->frameBase + vm->entry->args * 8, 0,
                 (vm->entry->slots - vm->entry->args) * 8);

    /* The entry point is resolved BEFORE the flags are cleared: retail's three
       zero stores sit in the load-delay slots of this address computation, and
       clearing first pins them ahead of it instead.

       ★ And the code base is its OWN statement. Retail holds it in v0 and the
       entry chain in v1; written as one expression we get them the other way
       round, because mwcc hands out v0/v1 in the order the values are FIRST
       ASSIGNED and `vm->entry->code` is then the first thing it computes.
       ⚠ FIVE spellings now measured and ALL byte-identical to each other:
       reordering the operands, casting to integer arithmetic, moving the
       declaration, hoisting `vm->code` into its own named local first (mwcc
       folds it), and `&vm->code[vm->entry->code]`. The residue is exactly
       FOUR WORDS -- the two loads, the second deref and the addu -- and it is
       a pure v0/v1 mirror. Do not retry the statement-granularity lever here;
       it is not that.

       ⚠⚠ 2026-08-22: TEN more spellings measured, and one of them is a TRAP.
       `pc = (u8 *)(vm->entry->code + (s32)vm->code)` -- integer arithmetic with
       the OFFSET first -- scores 99.78% with THREE bad words instead of four,
       and the word it buys is the addu. It is a COMPENSATING ERROR and is
       deliberately not used: by the addu-operand-order rule, retail's
       `addu a1, v0, v1` with the pointer FIRST is the pointer-arithmetic form,
       i.e. the spelling below. Swapping the source operands only re-mirrors the
       addu on top of the already-mirrored registers, so the two wrongs cancel
       in the encoding -- and fixing the register mirror would then BREAK it.
       Same treatment as QuatSlerp_13c270's `&qa` hoist: recorded, left out.
       Also measured, all worse or flat: hoisting either or both sides into
       named locals (flat, mwcc folds every one), moving `pc` to the end of the
       declaration list (flat), inlining the expression into the ScriptVmExec_173b00 call
       (7 bad), and putting the pc computation after one, two or all three of
       the flag clears (6, 6 and 7 bad).
       ⚠ THREE MORE measured 2026-08-22 (third session), all byte-identical to
       this baseline -- EIGHTEEN spellings now: hoisting the INTERMEDIATE
       `Entry *e = vm->entry` (not either side of the `+`, which is the one the
       older list had not covered); a `static inline CodeAt(u8 *base, s32 off)`
       to force left-to-right argument-evaluation order; and plain
       POINTER-arithmetic with the offset written first,
       `vm->entry->code + vm->code` (distinct from the recorded integer-cast
       trap -- mwcc canonicalises it back, so it is inert rather than a
       compensating error).
       ⇒ The four words are entirely "which of v0/v1 holds `vm->code`". Both
       builds issue the two loads in the SAME order, 0x34 then 0x48; retail
       gives the FIRST-issued load v1 and the second v0, we do the reverse.
       Source-level ordering levers do not reach it. Look for a mechanism that
       changes mwcc's ALLOCATION, not its evaluation order. */
    {
        s32 off = *(volatile s32 *)&vm->entry->code;
        pc = vm->code + off;
    }
    vm->halted = 0;
    vm->unk40 = 0;
    vm->unk50 = 0;
    ScriptVmExec_173b00(vm, pc);

    if (vm->halted != 0) {
        return 0;
    }
    return 1;
}
