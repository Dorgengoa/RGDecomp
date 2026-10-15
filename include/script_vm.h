#ifndef SCRIPT_VM_H
#define SCRIPT_VM_H

#include "types.h"

/* The script VM, as ScriptVmInit_176af0 lays it out and ScriptVmRunEntry_176940 uses it.
   Both were reconstructed separately and agree; this is the union of the two.

   The operand stack is 8-byte {type, value} slots and the call frames are
   12 bytes. Each gets a base, a moving top, and a precomputed end so the
   interpreter can bounds-check by comparison. */

typedef struct Label {
    s32 id;            /* +0x00 */
    s32 offset;        /* +0x04 */
} Label;

typedef struct Entry {
    s32 code;          /* +0x00, offset into the code section */
    u8 pad04[0x4];
    s32 slots;         /* +0x08, total stack slots */
    s32 args;          /* +0x0C, of which this many arrive filled */
} Entry;

typedef struct ScriptBlob {
    u8 pad00[0x4];
    s32 defaultEntry;  /* +0x04 */
    s32 codeOffset;    /* +0x08 */
    s32 labels;        /* +0x0C, offset to the label table */
    s32 labelCount;    /* +0x10 */
    u8 pad14[0x4];
    s32 globalCount;   /* +0x18, in 8-byte slots */
} ScriptBlob;

typedef struct ScriptVm {
    s32 state;         /* +0x00, 2 = loaded */
    u8 pad04[0x8];
    s32 stackSlots;    /* +0x0C */
    u8 *stack;         /* +0x10 */
    u8 *stackTop;      /* +0x14 */
    u8 *stackEnd;      /* +0x18 */
    u8 *globals;       /* +0x1C */
    s32 frameCount;    /* +0x20 */
    u8 *frames;        /* +0x24 */
    u8 *frameTop;      /* +0x28 */
    u8 *framesEnd;     /* +0x2C */
    u8 *frameBase;     /* +0x30 */
    Entry *entry;      /* +0x34 */
    u8 *pc;            /* +0x38, 0 = not running */
    s32 halted;        /* +0x3C */
    s32 unk40;         /* +0x40 */
    ScriptBlob *blob;  /* +0x44 */
    u8 *code;          /* +0x48 */
    u8 pad4c[0x4];
    s32 unk50;         /* +0x50 */
} ScriptVm;

#endif
