/* rgp:protos */
#define RGP_SELF_SlotRecordReset_3eeca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A 0x350-byte object initialiser: memset the whole thing, then re-write the
   fields the constructor cares about.

   ONE -1 is materialised (`addiu $6, $0, -0x1`) and every 0xFFFF halfword
   uses it, so all of those fields are SIGNED s16 -- pass 33's "u8 vs s8
   decides whether 0xFF and -1 are the same constant", read from the side
   where only one constant exists.  `sd $0` is an s64 member and `sq $0` a
   u128 one.

   The 10-element loop is based on a POINTER at p + 0x50, not on p: retail
   spells the element address `addu $4, $5, $3` with $5 = p + 0x50 and then
   uses displacements 0x14/0x24/0x26/0x28, and re-uses that same $5 for the
   stores at 0x1BC..0x244.  Written as `p->sub.arr[i]` inside one big struct
   mwcc folds the 0x50 away, bases the loop on p itself and the unit comes out
   ONE WORD SHORT -- the missing word is exactly the `addiu $5, $16, 0x50`.
   So the sub-object is reached through a pointer local, and its array sits at
   sub + 0x14.

   The closing run is mwcc's 1-bit bitfield INSERT (`lbu / and ~1 / or / sb`):
   mask -2 => bit 0, and `andi $5, $0, 0x1` is the inserted VALUE masked to the
   field width, CSE'd across all four iterations even though it is a literal
   zero.  That loop walks a POINTER (`addiu $8, $8, 0x2` in the delay slot),
   it does not index.  The final `sb $0, 0x34E` is a whole-byte store over the
   last entry, so it is not a bitfield write.

   ** THE LAST 18 WORDS WERE ONE TOKEN: `i <= 3`, NOT `i < 4`.**
   [[at-compare-class]] -- a latch whose continue-condition is a bare `<`
   puts the `slti` in a GPR, and `<=` puts it in `$at`.  Retail's second loop
   has `slti $1, $7, 0x4`, the first has `slti $3, $7, 0xA`, so the two loops
   are written with DIFFERENT relational tokens.  Fixing the token also moved
   the two hoisted loop-2 constants four slots earlier and renumbered every
   register in the loop body -- 18 wrong words from one character. */


typedef rg_u128 u128;

extern void * memset(void *, s32, s32);

typedef struct {
    u8  f00;
    u8  pad01[0xF];
    s16 f10;
    s16 f12;
    s16 f14;
    u8  pad16[0x12];
} Elem;

typedef struct {
    u8 b0 : 1;
    u8 m01;
} Ent;

typedef struct {
    u8   pad00[0x14];
    Elem arr[10];
    u8   pad1A4[0x18];
    s16  m1BC;
    s16  m1BE;
    s16  m1C0;
    s16  m1C2;
    u8   m1C4;
    u8   pad1C5[0x7F];
    s16  m244;
} Sub;

typedef struct {
    s16  m000;
    s16  m002;
    s16  m004;
    s16  m006;
    s32  m008;
    s32  m00C;
    s64  m010;
    u8   pad018[0x8];
    u128 m020;
    s64  m030;
    u8   pad038[0x8];
    u128 m040;
    s64  m050;
    s64  m058;
    s16  m060;
    u8   pad062[0x236];
    s16  m298;
    u8   m29A;
    u8   pad29B[0x7F];
    s16  m31A;
    s16  m31C;
    s16  m31E;
    s16  m320;
    u8   pad322[0x2];
    s32  m324;
    s32  m328;
    s32  m32C;
    s32  m330;
    u8   pad334[0x4];
    s16  m338;
    s16  m33A;
    s16  m33C;
    s16  m33E;
    s64  m340;
    Ent  ent[4];
} Obj;

void * SlotRecordReset_3eeca0(Obj *p)
{ void * rgp_v0 = 0;
    s32 i;
    Sub *s;
    Ent *e;

    (rgp_v0 = memset(p, 0, 0x350));
    p->m000 = -1;
    p->m002 = -1;
    p->m004 = -1;
    p->m006 = -1;
    p->m008 = 0;
    p->m00C = 0;
    p->m010 = 0;
    p->m020 = 0;
    p->m030 = 0;
    p->m040 = 0;
    p->m050 = 0;
    p->m058 = 0;
    p->m060 = 0;
    s = (Sub *)((u8 *)p + 0x50);
    for (i = 0; i < 10; i++) {
        s->arr[i].f00 = 0;
        s->arr[i].f10 = -1;
        s->arr[i].f12 = -1;
        s->arr[i].f14 = 0;
    }
    s->m1BC = 0;
    s->m1BE = 0;
    s->m1C0 = 0;
    s->m1C2 = 0;
    s->m1C4 = 0;
    s->m244 = 0;
    p->m298 = -1;
    p->m29A = 0;
    p->m31A = -1;
    p->m31C = -1;
    p->m31E = -1;
    p->m320 = -1;
    p->m324 = 0;
    p->m328 = 0;
    p->m32C = 0;
    p->m330 = 0;
    p->m338 = 0;
    p->m33A = 0;
    p->m33C = 0;
    p->m33E = 0;
    p->m340 = 0;
    e = p->ent;
    for (i = 0; i <= 3; i++) {
        e->b0 = 0;
        e->m01 = 0;
        e++;
    }
    *((u8 *)p + 0x34E) = 0;
return rgp_v0; }
