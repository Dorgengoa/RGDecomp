#include "types.h"

/* One camera event, evaluated and applied.

   An event either resolves to a single track, or it expands into a list of
   them -- AmixerSampleEventsMaybe_170590 gathers the expansion into a small vector of
   {node, time} pairs and each one is applied in turn. Either way the work
   lands in CameraApplyMotionTrack_154170, which finds the matching keyframe track and installs
   the sample onto the camera.

   ★ The walk is an STL-SHAPED ITERATOR PAIR, not two pointers. Retail keeps
   both ends in memory and reloads them every iteration, and spells the test
   `xor / sltiu 1 / xori 1` -- that is `!(a == b)`, an inline `operator!=`
   built on `operator==` returning a bool, with both sides taken by reference
   so neither can live in a register. Two plain pointers compare with one
   `bne` and stay in registers, which is 72% against this 100%.

   ★★★★★★ MATCHED 2026-08-22 (third session), 95.49% -> byte-identical, in
   three edits. All three turn on ONE find:

   ⚠⚠ `volatile` ON THE POINTER MEMBER MEANS `T *volatile p`, NOT
   `volatile T *p`. The previous session recorded "volatile on the pointer
   member does NOT stop the forwarding" and closed the lead; that spelling had
   put the qualifier on the POINTEE, where it is a no-op for this. The pointer
   itself:

       GatherItem *volatile p;          -- 95.49 -> 97.32

   is what makes mwcc RELOAD the cursor from its stack slot instead of
   forwarding the just-stored register -- which is retail's whole loop shape,
   three `lw 0x6c(sp)` an iteration, and it retires the two `dsll32`/`dsra32`
   sign-extend pairs at a stroke (an `lw` sign-extends for free).
   ⇒ **A "volatile changed nothing" result is worth re-reading before it is
   believed: on a pointer there are two places to put the keyword and only one
   of them is the variable.**

   Volatile then costs back what it bought, twice, and both are real:

     2. It kills the CSE of the body's two `it->` reads. Retail loads the
        cursor ONCE (in the `bnel` delay slot) and uses it for both `->node`
        and `->t`; two volatile reads are two loads. One named local in the
        body restores it: 97.32 -> 98.73.
     3. It stops mwcc knowing `operator==`'s result is already 0/1, so `!`
        re-normalises with an extra `sltu v0, zero, v0` before the `xori`.
        Reading both members into ordinary non-volatile locals INSIDE
        `operator==` and comparing those: 98.73 -> **100.00%**.

   ⇒ The general shape: a `volatile` that fixes the memory traffic also
   disables value tracking through it. Put the volatile read in ONE place and
   hand a plain local to everything downstream.

   ★★★★ AND IT SUBSUMES THE COPY CONSTRUCTOR AND THE DESTRUCTOR. Both were
   recorded as load-bearing -- "either alone and mwcc promotes the iterator
   into a callee-saved register and the walk collapses to `bnel`" -- and that
   was true of the non-volatile class. With `*volatile` the object is pinned
   to memory by the qualifier, and removing BOTH leaves the output byte
   identical (measured separately, one at a time).
   ⚠⚠ REMOVING THE DESTRUCTOR IS NOT COSMETIC -- IT IS WHAT LETS THE FUNCTION
   ENTER THE LINK. A user-declared `~Iter()` makes mwcc emit an out-of-line
   `__dt__4IterFv` in a SECOND `.text` section (plus its `.mwcats` comdat
   marker) whose deleting-destructor path references `__dl__FPv`, i.e.
   `operator delete`. `scripts/link.py` places `CameraApplyMotion_171540.o (.text)`, so
   that second section would be laid into the image as 0x44 stray bytes, and
   the link fails first on the undefined `__dl__FPv` (RG's `operator delete` is
   not named -- Dark Cloud's is at 0x00122550, ours is unidentified).
   ⇒ **Run `nm` over a C++ object before adding it to `config/cunits.txt`: one
   `T` in `.text`, and no undefined symbol the reference does not already
   name.** */

typedef struct GatherItem {
    void *node;   /* +0x00 */
    f32 t;        /* +0x04 */
    s32 unk08;    /* +0x08 */
} GatherItem;

typedef struct Gather {
    s32 unk00;
    s32 count;         /* +0x04 */
    GatherItem *base;  /* +0x08 */
} Gather;

typedef struct CamEvent {
    u8 pad00[0xC];
    s32 count;    /* +0x0C */
    u8 pad10[0xC];
    s32 flag;     /* +0x1C */
} CamEvent;

typedef struct Owner {
    u8 pad00[0x8];
    void *owner;  /* +0x08 */
} Owner;

/* `GatherItem *volatile p` -- the qualifier is on the POINTER, and it is the
   whole match; see the note above. It pins the cursor to its stack slot, which
   is where retail keeps it, so the copy constructor and destructor that the
   non-volatile version needed for the same effect are gone (and the
   destructor could not have stayed -- it emits a comdat that breaks the link).
   `bool` rather than `u8` is still what materialises the comparison as a value
   instead of folding it into the branch. */
class Iter {
public:
    GatherItem *volatile p;

    Iter() {}
    Iter(GatherItem *q) { p = q; }
    /* Assigning a bare pointer without this builds a TEMPORARY Iter and
       copy-assigns it, and the temporary costs 8 bytes of frame that move
       everything below it. */
    Iter &operator=(GatherItem *q) { p = q; return *this; }
    GatherItem *operator->() const { return p; }
    Iter &operator++() { p = p + 1; return *this; }
};

inline bool operator==(const Iter &a, const Iter &b)
{
    GatherItem *x = a.p;
    GatherItem *y = b.p;
    return x == y;
}
inline bool operator!=(const Iter &a, const Iter &b) { return !(a == b); }

extern "C" {
extern void Vec3VectorReserve_171230(Gather *g, s32 capacity);
extern void AmixerSampleEventsMaybe_170590(void *events, Gather *g, f32 t);
extern void Vec3VectorDeletingDtor_1713b0(Gather *g, s32 arg);
extern s32 CameraApplyMotionTrack_154170(void *camera, s32 id, void *owner, f32 t);
}

extern "C" s32 CameraApplyMotion_171540(s32 id, void *camera, CamEvent *event, f32 t)
{
    Iter it __attribute__((aligned(16)));
    Iter end __attribute__((aligned(16)));
    Gather gather __attribute__((aligned(16)));
    u8 wanted;
    s32 expanded;

    if (camera == NULL || event == NULL) {
        return 0;
    }

    gather.unk00 = 0;
    gather.count = 0;
    gather.base = 0;
    Vec3VectorReserve_171230(&gather, 0x20);

    /* The condition is MATERIALISED into a bool first -- retail spells it
       `sltu / slt / andi 0xff` and then branches on the value, where a plain
       `if (a && b)` short-circuits straight into two branches. */
    wanted = event->flag != 0 && event->count > 0;
    if (wanted == 0) {
        expanded = 0;
    } else {
        AmixerSampleEventsMaybe_170590(&event->count, &gather, t);
        expanded = 1;
    }

    if (expanded != 0) {
        /* Retail RELOADS the cursor from its stack slot three times an
           iteration -- once for the increment, once for the compare, once in
           the `bnel` delay slot for the body -- and `*volatile` above is what
           reproduces that. The body's ONE read is `e`: two `it->` uses would
           be two volatile loads where retail has one.

           ⚠ Measured and REJECTED before the volatile find, all at 81 words
           against retail's 79, and none of them is the answer: `volatile` on
           the POINTEE (`volatile GatherItem *p`, the no-op spelling), `++p`
           instead of `p = p + 1`, `void operator++()`, holding the address as
           an `s32` and adding 12, hoisting `(Owner *)it->node` into a local,
           and a POST-increment `it++` with a real `Iter operator++(int)` --
           that last one is 80 words, one closer, but only because mwcc STOPS
           INLINING and emits a `jal` to the copy constructor. ★ The tell for
           that failure mode is an `addiu $5, $29, <slot>` + `jal` +
           `daddu $6, $0, $0` where the reference has a store. */
        for (it = gather.base, end = gather.base + gather.count; it != end; ++it) {
            GatherItem *e = it.p;
            CameraApplyMotionTrack_154170(camera, id, ((Owner *)e->node)->owner, e->t);
        }
    } else {
        CameraApplyMotionTrack_154170(camera, id, event, t);
    }

    Vec3VectorDeletingDtor_1713b0(&gather, 0);
    return 1;
}
