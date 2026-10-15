#include "types.h"

/* MAIN EffTableCtor_1a11b0 -- zero-branch sub-object constructor, BYTE-IDENTICAL.

   Four 0x34-byte slots at 0x14 / 0x48 / 0x7C / 0xB0.  Each clears its own nine
   leading words and then constructs the 0x10-byte node at slot+0x24 with two
   by-address empty arguments; the node constructors are the already-matched
   StrMapCtor_1a25d0 / StrMapCtor_1a2940 / StrMapCtor_1a2cb0 / StrMapCtor_1a3020 (src/leaves2),
   which read one byte through the second argument and ignore the third.  The
   eight stack slots at sp+0x20..sp+0x3C are those four argument pairs, one
   pair per inline expansion, allocated in declaration order downwards.

   THE ONE LEVER HERE: retail builds each node address in TWO steps --
   `addiu $2, $16, 0x14` then `addiu $4, $2, 0x24` -- and mwcc FOLDS that pair
   into a single `addiu $4, $16, 0x38` unless the SLOT pointer is a named local
   assigned in a statement of its own.  Naming the pointer at the call site
   (here), inside the helper, or writing the whole thing flat all restore the
   two-step; naming the NODE pointer instead does not.  See the sweep in the
   report: 17 spellings, 6 byte-identical (one identical object, sha1 41153a7d),
   11 four words short or worse. */

struct Node {
    s32 m00;
    s32 m04;
    u8 m08;
    u8 pad09[0x3];
    struct Node *m0C;
};

struct Empty {
    u8 m00;
};

struct Slot {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    struct Node m24;
};

struct Owner {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    struct Slot m14;
    struct Slot m48;
    struct Slot m7C;
    struct Slot mB0;
    s32 mE4;
    s32 mE8;
    s32 mEC;
    s32 mF0;
    s32 mF4;
    s32 mF8;
    s32 mFC;
    s32 m100;
    s32 m104;
    s32 m108;
    s32 m10C;
    s32 m110;
    s32 m114;
    s32 m118;
};

extern struct Node *StrMapCtor_1a25d0(struct Node *, struct Empty *, struct Empty *);
extern struct Node *StrMapCtor_1a2940(struct Node *, struct Empty *, struct Empty *);
extern struct Node *StrMapCtor_1a2cb0(struct Node *, struct Empty *, struct Empty *);
extern struct Node *StrMapCtor_1a3020(struct Node *, struct Empty *, struct Empty *);

static inline void slot0Init(struct Slot *s)
{
    struct Empty a;
    struct Empty b;

    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0C = 0;
    s->m10 = 0;
    s->m14 = 0;
    s->m18 = 0;
    s->m1C = 0;
    s->m20 = 0;
    StrMapCtor_1a25d0(&s->m24, &a, &b);
}

static inline void slot1Init(struct Slot *s)
{
    struct Empty a;
    struct Empty b;

    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0C = 0;
    s->m10 = 0;
    s->m14 = 0;
    s->m18 = 0;
    s->m1C = 0;
    s->m20 = 0;
    StrMapCtor_1a2940(&s->m24, &a, &b);
}

static inline void slot2Init(struct Slot *s)
{
    struct Empty a;
    struct Empty b;

    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0C = 0;
    s->m10 = 0;
    s->m14 = 0;
    s->m18 = 0;
    s->m1C = 0;
    s->m20 = 0;
    StrMapCtor_1a2cb0(&s->m24, &a, &b);
}

static inline void slot3Init(struct Slot *s)
{
    struct Empty a;
    struct Empty b;

    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0C = 0;
    s->m10 = 0;
    s->m14 = 0;
    s->m18 = 0;
    s->m1C = 0;
    s->m20 = 0;
    StrMapCtor_1a3020(&s->m24, &a, &b);
}

struct Owner *EffTableCtor_1a11b0(struct Owner *p)
{
    struct Slot *s;

    s = &p->m14;
    slot0Init(s);
    s = &p->m48;
    slot1Init(s);
    s = &p->m7C;
    slot2Init(s);
    s = &p->mB0;
    slot3Init(s);
    p->mE4 = 0;
    p->mE8 = 0;
    p->mEC = 0;
    p->mF0 = 0;
    p->mF4 = 0;
    p->mF8 = 0;
    p->mFC = 0;
    p->m100 = 0;
    p->m104 = 0;
    p->m08 = 0;
    p->m0C = 0;
    p->m10 = 0;
    p->m108 = 0;
    p->m00 = 0;
    p->m04 = 0;
    p->m110 = 0;
    p->m114 = 0;
    p->m118 = 0;
    p->m10C = 0;
    return p;
}
