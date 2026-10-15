#ifndef VM_SLOT_H
#define VM_SLOT_H

#include "types.h"

/* The 8-byte {type, value} variant the script VM passes natives in and out
   through. The layout is ScriptVmExec_173b00's own Slot -- read off the interpreter's
   opcode handlers and reproduced here so the marshalling accessors around it
   can share it. Kept in its own header rather than folded into script_vm.h
   because ScriptVmExec_173b00.cpp is under active work; merge the two once it settles.

   Type tags, from ScriptVmExec_173b00's operand decode:
       0 int   1 float   2 code address   3 reference to another slot */
typedef struct Slot {
    s32 type;          /* +0x00 */
    union {
        s32 i;
        f32 f;
        u8 *p;
    } u;               /* +0x04 */
} Slot;

#endif
