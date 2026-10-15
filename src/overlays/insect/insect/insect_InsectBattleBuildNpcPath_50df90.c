#include "types.h"
/* insect 0x0050DF90 -- 288 B / 72 words.  Mid-tier member of the func_134A98
 * loader/name-builder family seeded by src/wf/insect/insect_InsectAbilityTableLoad_51d0b0.c.
 *
 * Reading of the family calls, settled by the string data this unit points at:
 *   func_134A98(dst, src)  D_005250B0 = "chara/npc/"   -- copy
 *   func_134690(dst, src)  D_005250C0 = "e336" ...     -- append
 *   func_1343B8(dst, fmt)  D_005250E0 = "chara/npc/%s.chr"
 *   func_134BB0(s)                                     -- length (u32)
 * so THIS member has no 134BB0 guard at all; the guard idiom transfers only as
 * the extern spellings.  The buffer is a->name at +0x5F02 (note the ODD
 * alignment: the struct must be u8/s16 based or the member will not land).
 *
 * Frame proof: 3 sq'd callee-saved GPRs (0x30) + sd $31 at 0x30 -> 0x38,
 * rounded to 0x40, NO stack locals.  Matches `addiu $29,$29,-0x40`.
 *
 * !! MEASURED, build 1 (the unit's ONLY residue, 2 words): retail loads the
 * guarded member into $6, not $2, and $6 is NEVER CLOBBERED between the `beqz`
 * and `jal func_1343B8` -- so it is not an allocation tie-break, it is
 * ARGUMENT THREE.  D_005250E0 is "chara/npc/%s.chr" and the %s is e->m08, so
 * the call is func_1343B8(name, FMT, e->m08) and the member is a char *.
 * Spelling the call with two arguments is exactly 2 words wrong.
 * (Generalisation: when a guarded load lands in an ARGUMENT register and
 * survives to the call, the loaded value IS an argument.)
 *
 * The mode dispatch is `beql` INTO each arm ([[insect-dispatch-branch-polarity]]),
 * so it is a SWITCH and the compare chain is the source case order REVERSED:
 * retail tests 1 then 0 then falls to default, so the source is 0, 1, default.
 * The arm BODIES are laid out 0 / 1 / default, i.e. source order, which is the
 * independent confirmation.
 */

typedef struct Rec2 {
    u8    pad00[0x8];
    char *m08;                  /* +0x08 -- the %s the format string wants */
} Rec2;

typedef struct Rec {
    u8    pad00[0xC];
    Rec2 *m0C;                  /* +0x0C */
} Rec;

typedef struct Obj {
    u8   pad0000[0x5EFC];
    s16  m5EFC;                 /* +0x5EFC */
    s16  m5EFE;                 /* +0x5EFE */
    u8   pad5F00[0x2];
    char name[0x40];            /* +0x5F02 */
} Obj;

extern const char D_005250B0[];
extern const char D_005250C0[];
extern const char D_005250C8[];
extern const char D_005250D0[];
extern const char D_005250D8[];
extern const char D_005250E0[];

extern void  insect_InsectBattleClearTextBuf_50e120(Obj *a, s32 b);
extern s32   insect_InsectBattleTestFlag_50da40(Obj *a, s32 b);
extern void  func_134A98(char *d, const char *s);
extern void  func_134690(char *d, const char *s);
extern void  func_1343B8(char *d, const char *fmt, const char *s);
extern u32   func_134BB0(const char *s);
extern void *func_1FEDE0(void);
extern Rec  *func_3E8490(void *p, s32 x, s32 y);

char *insect_InsectBattleBuildNpcPath_50df90(Obj *a, s32 mode)
{
    char *name;
    Rec  *r;
    Rec2 *e;

    insect_InsectBattleClearTextBuf_50e120(a, 0);
    name = a->name;
    if (insect_InsectBattleTestFlag_50da40(a, 2) != 0) {
        func_134A98(name, D_005250B0);
        switch (mode) {
        case 0:
            func_134690(name, D_005250C0);
            break;
        case 1:
            func_134690(name, D_005250C8);
            break;
        default:
            func_134690(name, D_005250D0);
            break;
        }
        func_134690(name, D_005250D8);
        return name;
    }
    r = func_3E8490(func_1FEDE0(), a->m5EFC, a->m5EFE + 1);
    if (r == 0) {
        return 0;
    }
    e = r->m0C;
    if (e != 0 && e->m08 != 0) {
        func_1343B8(name, D_005250E0, e->m08);
    }
    return name;
}
