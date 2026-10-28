/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemInitHeap_512900 1
#include "port/game_protos.h"
#line 1
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
 * it is a plain positive `if (... < 0x10)`.  insect_D_00525260 is `const char []` so
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

extern char insect_D_00525260[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  strcpy(Ctx *a, const char *t);
extern u32   strlen(const char *t);

void insect_InsectModelMemInitHeap_512900(Obj *a, void *h, s32 n)
{
    s32 r;

    a->c.m5C = h;
    r = ((s32)MemStackHeapAlloc_14db10(h, 2, 0, 0x40));
    a->c.m58 = r;
    if (r != 0) {
        MemStackClear_14dff0(&a->c);
        MemStackHeapInit_14dee0(&a->c, MemStackAllocQw_14d950(h, n), n);
        if (strlen(insect_D_00525260) < 0x10) {
            strcpy(&a->c, insect_D_00525260);
        }
        MemStackHeapReinit_14de90(&a->c);
        a->c.m3F8 = n;
    }
    MemStackReturnToOwnerMaybe_14dad0(h);
}
