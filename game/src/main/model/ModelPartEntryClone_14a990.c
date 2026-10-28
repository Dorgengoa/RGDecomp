/* rgp:protos */
#define RGP_SELF_ModelPartEntryClone_14a990 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clone.  The top field moves are INTERLEAVED lw/sw -> N separate member
   assignments; the 0x20 and 0x30 groups are batched lwc1x4/swc1x4 -> ONE
   4-float struct assignment each (4-byte aligned, so not lq/sq).
   The 0x60 blob is one 0x58 align-8 struct assignment (11 unrolled ld/sd)
   plus two word members. */

typedef struct F4 { f32 x, y, z, w; } F4;

/* The 0x60 blob is copied with INTERLEAVED ld/sd pairs -- that is thirteen
   separate member assignments, not one struct assignment (a struct
   assignment of 0x58 bytes comes out as an 11-trip block-copy LOOP). */
struct B16 { s64 a, b; };

struct Blob {
    struct B16 m00;  /* batched ld,ld,sd,sd = ONE 16-byte sub-struct assign */
    s64 m10, m18, m20, m28, m30, m38, m40, m48, m50;
    s32 m58;         /* 0x58 */
    s32 m5C;         /* 0x5C */
};

struct Thing {
    s32 m00;         /* 0x00 */
    s16 m04;         /* 0x04 */
    s8  m06;
    s8  m07;
    u16 m08;
    u16 m0A;
    s32 m0C;
    void *m10;       /* 0x10 */
    struct Blob *m14;/* 0x14 */
    s16 m18;
    s16 m1A;
    s32 m1C;
    F4  m20;         /* 0x20 */
    F4  m30;         /* 0x30 */
    void *m40;       /* 0x40 vtable */
};

/*rgp*/
/*rgp*/
extern u32 D_0046FF90[];

struct Thing *ModelPartEntryClone_14a990(struct Thing *o, void *ctx)
{
    struct Thing *n;
    struct Blob *b;
    struct Blob *sb;

    n = (struct Thing *)MemStackNew_14e230(0x50, ctx);
    if (n != 0) {
        n->m40 = D_0046FF90;
    }
    if (n == 0) {
        return 0;
    }
    n->m00 = o->m00;
    n->m04 = o->m04;
    n->m06 = o->m06;
    n->m07 = o->m07;
    n->m08 = o->m08;
    n->m0A = o->m0A;
    n->m0C = o->m0C;
    n->m10 = o->m10;
    n->m14 = o->m14;
    n->m18 = o->m18;
    n->m1A = o->m1A;
    n->m1C = o->m1C;
    n->m20 = o->m20;
    n->m30 = o->m30;
    n->m10 = MemStackStrDup_14cf10(o->m10, ctx);
    if (o->m14 != 0) {
        b = (struct Blob *)MemStackNew_14e230(0x60, ctx);
        n->m14 = b;
        if (b != 0) {
            sb = o->m14;
            b->m00 = sb->m00;
            b->m10 = sb->m10;
            b->m18 = sb->m18;
            b->m20 = sb->m20;
            b->m28 = sb->m28;
            b->m30 = sb->m30;
            b->m38 = sb->m38;
            b->m40 = sb->m40;
            b->m48 = sb->m48;
            b->m50 = sb->m50;
            b->m58 = sb->m58;
            b->m5C = sb->m5C;
        }
    }
    return n;
}
