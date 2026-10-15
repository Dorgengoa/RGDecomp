#include "types.h"
/* insect 0x00512900 -- 188 B / 47 words.  Third and shortest clean member of
 * the func_134A98 loader family whose seed is src/wf/insect/insect_InsectAbilityTableLoad_51d0b0.c.
 *
 * Differences from the seed, all read off this listing:
 *   - the object handed to the 14Dxxx API is `&a->c` (`addiu $4,$18,0x4`), not
 *     the parameter itself, so the parameter's type has the Ctx at +4.  Every
 *     struct write in this unit is therefore inside that Ctx: 0x5C -> c.m58,
 *     0x60 -> c.m5C, 0x3FC -> c.m3F8.
 *   - func_14DB10's return is LIVE here (`beqz $2` + `sw $2,0x5C($18)` in the
 *     delay slot), so it is named in a local, stored, and tested.  The seed
 *     discards it; the brief says read the $2 use per member.
 *   - the size is the third PARAMETER, not a constant, and it appears three
 *     times (func_14D950 arg 2, func_14DEE0 arg 3, the 0x3FC store).
 *
 * Guard spelling copied verbatim from the seed: `u32 func_134BB0` gives the
 * `sltiu $1,$2,0x10`, and the call is the FALL-THROUGH side of the `beql`, so
 * it is a plain positive `if (... < 0x10)`.  D_00525260 is `const char []` so
 * it gets the %hi/%lo pair rather than a gp slot.
 *
 * Frame proof: 3 sq-saved GPRs + `sd $31` = 0x10*3 + 8 -> 0x40, so there are
 * NO stack locals -- `r` lives in a register.
 */

typedef struct Ctx {
    u8    pad00[0x58];
    s32   m58;                  /* +0x58 (obj +0x5C) */
    void *m5C;                  /* +0x5C (obj +0x60) */
    u8    pad60[0x3F8 - 0x60];
    s32   m3F8;                 /* +0x3F8 (obj +0x3FC) */
} Ctx;

typedef struct Obj {
    u8  pad00[0x4];
    Ctx c;                      /* +0x04 */
} Obj;

extern const char D_00525260[];

extern s32   func_14DB10(void *h, s32 b, s32 c, s32 d);
extern void  func_14DFF0(Ctx *a);
extern void *func_14D950(void *h, s32 n);
extern void  func_14DEE0(Ctx *a, void *p, s32 n);
extern void  func_14DE90(Ctx *a);
extern void  func_14DAD0(void *h);
extern void  func_134A98(Ctx *a, const char *t);
extern u32   func_134BB0(const char *t);

void insect_InsectModelMemInitHeap_512900(Obj *a, void *h, s32 n)
{
    s32 r;

    a->c.m5C = h;
    r = func_14DB10(h, 2, 0, 0x40);
    a->c.m58 = r;
    if (r != 0) {
        func_14DFF0(&a->c);
        func_14DEE0(&a->c, func_14D950(h, n), n);
        if (func_134BB0(D_00525260) < 0x10) {
            func_134A98(&a->c, D_00525260);
        }
        func_14DE90(&a->c);
        a->c.m3F8 = n;
    }
    func_14DAD0(h);
}
