#pragma opt_propagation off
#include "types.h"

/* insmenu 0x004F95D0 (176 bytes, 44 instructions, 13 calls, ZERO conditional
 * branches) -- tear the insect-menu screen down and hand the display list back.
 *
 * ★ `sll $3, $6, 4` on an index that is then added to a base pointer is an
 * ARRAY SUBSCRIPT with a 16-byte element, not a shift: `&p->f28[p->f2C]`.
 * Written as a shift mwcc would keep the multiply visible.
 *
 * ★ `ori $4, $0, 0x8909` rather than `addiu` because 0x8909 does not fit a
 * signed 16-bit immediate -- it is a plain literal argument, not a mask.
 *
 * ★★★★★ THE gp-TO-gp COPY IS SPLIT ACROSS A CALL, AND $16 IS THE PROOF.
 * `lw $16, -0xE58($28)` sits in insmenu_InsectVsGetSaveCtx_4f3850's delay slot and
 * `sw $16, -0x1FE8($28)` in the NEXT call's.  A CALLEE-SAVED register for a
 * value with one producer and one consumer means the value crosses a call, so
 * the read is a statement BEFORE the call and the store one after it.  Written
 * as a single `D_00483188 = D_00484318;` between the two calls there is
 * nothing to sink into the first slot and the unit is a word LONG.
 *
 * ★ The member reads are named locals in the listing's load order.
 *
 * ⚠⚠ PARKED AT 5 WORDS AND THE LENGTH IS RIGHT (44 words) -- deliberately OUT
 * of config/ocunits/insmenu.txt, because the link's length guard would pass it
 * and the link would emit a DIFFERING image.
 * The residue is which argument computation goes first: retail loads f34
 * second, computes `n - i` BEFORE the address, and fills the `jal`'s delay
 * slot with the ADDRESS; we compute the address first and fill the slot with
 * the count.  TEN statement forms were enumerated (scripts/i_f95d0try.py --
 * address as a local or inline; the count as a local before or after the
 * address; n read first; the count with n inline; everything inline; a
 * base-pointer local; `q + i`) and ALL TEN produce a BYTE-IDENTICAL object.
 * That is a measured negative on statement order: the scheduler tie-break
 * class of [[insect-scheduler-tiebreak]], not a spelling.
 */

typedef struct Elem {
    u8 pad00[0x10];
} Elem;

typedef struct List {
    u8 pad00[0x28];
    Elem *f28;
    s32 f2C;
    u8 pad30[4];
    s32 f34;
} List;

typedef struct Buf {
    u8 pad00[0x60];
} Buf;

extern List *D_004842E0;        /* gp - 0xE90 */
extern s32 D_00484318;          /* gp - 0xE58 */
extern s32 D_00483188;          /* gp - 0x1FE8 */
extern const u8 D_004FA180[];

extern void func_14E030(Buf *b);
extern void func_14D810(Buf *b, Elem *e, s32 n);
extern void func_37BC50(const void *a);
extern void *insmenu_InsectVsGetSaveCtx_4f3850(void);
extern void *insmenu_InsectVsGetSaveIconData_4f3840(void);
extern void func_37BC60(void *a, Buf *b);
extern void func_377790(s32 a);
extern void func_3774C0(s32 a);
extern void func_375B10(void *a, void *b);
extern void func_375D10(void *a);

void insmenu_InsectVsSaveSysInit_4f95d0(void)
{
    Buf b;
    List *p;
    s32 i;
    s32 n;
    Elem *e;
    s32 t;

    func_14E030(&b);
    p = D_004842E0;
    i = p->f2C;
    n = p->f34;
    e = &p->f28[i];
    func_14D810(&b, e, n - i);
    func_37BC50(D_004FA180);
    func_37BC60(insmenu_InsectVsGetSaveCtx_4f3850(), &b);
    t = D_00484318;
    insmenu_InsectVsGetSaveCtx_4f3850();
    D_00483188 = t;
    func_377790(0x8909);
    func_3774C0(0x8908);
    func_375B10(insmenu_InsectVsGetSaveCtx_4f3850(), insmenu_InsectVsGetSaveIconData_4f3840());
    func_375D10(insmenu_InsectVsGetSaveCtx_4f3850());
}
