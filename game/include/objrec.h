#ifndef OBJREC_H
#define OBJREC_H

#include "types.h"

/* The record ObjRecLookup_1c3ef0 hands back, and the two tables it indexes.

   ObjRecLookup_1c3ef0 is a three-way switch on its second argument that picks which
   of three tables to index; the wrappers around it each poke one flag word in
   whatever record comes back. Bit 1 (mask 2) and bit 2 (mask 4) are the two
   the wrappers touch, and the predicate below tests for BOTH. */
typedef struct ObjRec {
    s32 flags;         /* +0x00 */
} ObjRec;

/* Two tables of 0x28-byte records, each preceded by its own count. */
typedef struct ObjRecTable {
    s32 count;
    ObjRec rec[1];
} ObjRecTable;

extern ObjRec *ObjRecLookup_1c3ef0(void *owner, s32 which, s32 index);

#endif
