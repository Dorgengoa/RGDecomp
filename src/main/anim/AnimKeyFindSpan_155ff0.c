#include "types.h"

/* The animation clip clock. Resolves the clip's current time to a pair of
   adjacent keyframes and the blend between them, and clamps at both ends.

   The frame index is `(s32)c->t` -- a `cvt.w.s` at 0x0015600C, which on the
   EE TRUNCATES. Rounding it to nearest instead is the defect the symptom
   backlog records as the character-animation jerk.

   Two shapes of clip feed this. With no key-time table the keys are on a
   uniform interval and the index is just the frame. With one (type 0x10) the
   table is s16 key times and the position is found by binary search.

   The 0.001 / 0.999 epsilons snap a blend that has all but arrived: past
   0.999 the clock reports the LATER key with a blend of zero rather than a
   blend of almost-one against the earlier one.

   MATCHED on b210, from 55.13. The last instruction pair -- retail's
   `slt at, v1, a3` where we got `slt a3, ...` -- was NOT the liveness signal
   it was read as. It is the OPERAND ORDER of the binary search's compare:
   the source tests `keys[mid] <= frame`, not `frame >= keys[mid]`. All four
   spellings were measured, and only that one closes it:

       if (k <= frame) { lo = mid + 1; } else { hi = mid; }   MATCH
       if (frame >= k) { lo = mid + 1; } else { hi = mid; }   2 words bad
       if (frame <  k) { hi = mid; } else { lo = mid + 1; }   3 words bad
       if (k >  frame) { hi = mid; } else { lo = mid + 1; }   3 words bad

   The dead end it replaces: declaring mid/k at function scope, and inlining
   keys[mid] into the condition, both leave the two words EXACTLY unchanged. */

/* The two epsilons as the gp-relative externals the reference names -- as
   literals they become mwcc's own @N labels and can never take the same
   relocation. */
extern f32 D_0047D24C;   /* 0.001f */
extern f32 D_0047D264;   /* 0.999f */

typedef struct AnimClock {
    f32 t;        /* +0x00  clip time, in frames */
    s32 type;     /* +0x04  0x10 = the key-time table below is present */
    s16 *keys;    /* +0x08  key times, ascending; NULL = uniform interval.
                     SIGNED: retail reads them with `lh`, not `lhu`. */
    s32 base;     /* +0x0C  first frame of the clip */
    s32 count;    /* +0x10  key count */
    s32 keyA;     /* +0x14  the key at or before t */
    s32 keyB;     /* +0x18  the key after it */
    s32 timeA;    /* +0x1C  keyA's time */
    s32 timeB;    /* +0x20  keyB's time */
} AnimClock;

f32 AnimKeyFindSpan_155ff0(AnimClock *c)
{
    s32 lo = 0;
    s32 hi = c->count;
    /* Retail hoists both addresses into registers before the first branch and
       writes through them for the rest of the function -- `addiu $6, $4, 0x1C`
       / `addiu $5, $4, 0x20` in the prologue. The two zeroing stores below are
       the exception: those go direct. */
    s32 *timeA = &c->timeA;
    s32 *timeB = &c->timeB;
    f32 t;
    s32 frame;
    s16 *keys;
    f32 blend;

    c->timeA = 0;
    c->timeB = 0;
    t = c->t;
    frame = (s32)t;
    keys = c->keys;

    if (keys == NULL) {
        s32 a = frame - c->base;
        s32 last;
        s32 b;

        c->keyA = a;
        /* One `count - 1`, not three: retail computes it once into a register
           and stores the SAME register into both keyB and keyA. */
        last = c->count - 1;
        /* Inverted against the obvious reading: retail FALLS THROUGH into the
           clamp and branches away to the main path, so the source condition is
           the clamp's, not the main path's. 57% -> 67% on this alone. */
        if (a >= last) {
            c->keyB = last;
            c->keyA = last;
            return 0.0f;
        }
        b = a + 1;
        c->keyB = b;
        if (b <= 0) {
            c->keyA = 0;
            return 0.0f;
        }
        if (b >= c->count) {
            c->keyB = c->keyA;
            return 0.0f;
        }
        *timeA = frame;
        *timeB = frame + 1;
        blend = t - (f32)frame;
        goto snap;
    }

    if (c->type != 0x10) {
        goto noTable;
    }

    /* The compare is spelled key-first -- `k <= frame`, not `frame >= k`.
       That is what puts retail's result in $at rather than back into the
       register that held k; see the table at the top of the file. */
    while (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 k = keys[mid];

        if (k <= frame) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    c->keyA = lo - 1;
    c->keyB = lo;
    if (lo == 0) {
        c->keyA = 0;
        return 0.0f;
    }
    /* Both clamps are the FALL-THROUGH here too, exactly as in the uniform
       path: retail branches away to the main path and drops into the clamp. */
    if (lo >= c->count) {
        c->keyB = c->keyA;
        return 0.0f;
    }
    if (c->keyA >= c->count) {
        s32 last = c->count - 1;

        c->keyB = last;
        c->keyA = last;
        return 0.0f;
    }
    {
        {
            *timeA = keys[c->keyA];
            *timeB = keys[c->keyB];
            goto blendIt;

            /* Retail puts the "no table" clamp HERE -- at 0x0015616C, between
               the table path's stores and the shared blend block, which is why
               the stores end in an explicit `b` to 0x00156178. Placing it at
               the end of the function instead scored 65.94 against 66.75. */
        noTable:
            c->keyB = 0;
            c->keyA = 0;
            return 0.0f;

        blendIt:
            blend = (f32)(*timeB - *timeA);
            if (blend > 0.0f) {
                blend = (t - (f32)*timeA) / blend;
            }
        snap:
            if (blend < D_0047D24C) {
                return 0.0f;
            }
            if (blend > D_0047D264) {
                blend = 0.0f;
                c->keyA = c->keyB;
                /* Direct, NOT through the hoisted pointers -- retail reads
                   0x20(a0) and writes 0x1c(a0) here. */
                c->timeA = c->timeB;
            }
            return blend;
        }
    }
}
