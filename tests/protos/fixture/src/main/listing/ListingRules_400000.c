#include "types.h"
/* protos listing rules (docs/PROTOS-MISSING-ARGS.md A-G), checked against
 * asm/main.s of this fixture: every call below is missing an argument. */

extern void SetScale_400100();          /* def: (void *, f32, f32) */
extern void UseNothing_400200();        /* def: (void *, s32): never reads $5 */
extern void ReadsA1_400300();           /* def: (void *, s32): reads $5 */
extern s32 Other_400400(void);
extern void ClearClip_400500();         /* def: (void *) */
extern u8 D_00400800[];

/* C: FPR passthrough (a, b still in $f12/$f13) */
void ListingFpr_400000(void *o, f32 a, f32 b)
{
    SetScale_400100(o);
}

/* A: the callee never reads $5 -> 0 is exact (missing-unused) */
void ListingUnused_400020(void *o)
{
    UseNothing_400200(o);
}

/* B: $5 is left over from an earlier call -> 0 (missing-dead) */
void ListingDead_400040(void *o)
{
    Other_400400();
    ReadsA1_400300(o);
}

/* E: $4 = &D_00400800, which the C holds in the local p (missing-asm) */
void ListingLocal_400060(s32 e)
{
    u8 *p;

    p = D_00400800;
    if (p != NULL) {
        ClearClip_400500();
    }
}

/* F: an array local is a buffer, not an unset register */
typedef f32 VEC[4];
extern void VecFill_400600(f32 *dst, f32 *src);
void ListingArray_400080(f32 *s)
{
    VEC u;
    VecFill_400600(u, s);
}

/* G: an inline struct parameter type does not hide the definition */
extern s32 FindFree_400700();
s32 ListingStructParam_4000a0(struct { u8 pad[0x10]; s32 x; } *arg0)
{
    return FindFree_400700() + arg0->x;
}

/* def-vthunk-naked: retail is a bare virtual tail jump through slot 0x88 */
typedef struct VtObj { void **vt; } VtObj;
void VThunk_4000c0(VtObj *o)
{
    ((void (*)(VtObj *))o->vt[34])(o);
}

/* def-struct-by-ref: retail reads the aggregate through the pointer in $a0 */
typedef struct Big { s32 a[8]; } Big;
s32 BigByValue_4000e0(Big b)
{
    return b.a[1];
}
