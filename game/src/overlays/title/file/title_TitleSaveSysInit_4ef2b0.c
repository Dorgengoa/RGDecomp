/* rgp:protos */
#define RGP_SELF_title_TitleSaveSysInit_4ef2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF2B0 -- straight-line setup: publish six gp fields,
 * build a 0x60-byte descriptor on the stack, hand it to the two 0x14xxxx
 * builders, then run a fixed sequence of 0x37xxxx calls.  No conditional
 * branches at all, so this was close to transcription -- but both of its two
 * residues were STATEMENT ORDER, and neither was visible to a length check.
 *
 * 1. The six gp publishes emit in source order EXCEPT that `D_004841F4 = 0`
 *    sinks to the jal's delay slot unless the FIRST pointer copy is written
 *    before `D_00484200 = 0x20`.  Twelve orders were measured: every one with
 *    D_004841E0's copy ahead of D_00484200's store is exact and every one with
 *    it behind is 12 words wrong.  A `sw $0` has no register dependency, so it
 *    is the scheduler's cheapest delay-slot filler; giving it a loaded value to
 *    queue behind is what stops it winning that race.
 *
 * 2. The two computed arguments of func_14D810.  Retail loads field02C, then
 *    field034, issues the shift, loads field028, subtracts, and puts the
 *    ADDITION in the delay slot; written inline mwcc mirrors it exactly the
 *    other way round.  Twenty-nine spellings were measured and the lever is
 *    that BOTH loads are named locals AND the subtraction is its own statement:
 *    `n = p->field034 - k;` is 5 words wrong, `n = p->field034; n = n - k;` is
 *    byte-identical.  (`q = p->field028; q = q + k;` in place of the second
 *    split works too, and so does hoisting `q` above the subtraction.)
 *
 * `sll $3, $6, 4 / addu $5, $2, $3` is pointer arithmetic on a 16-byte element
 * type, not an explicit shift.  title_D_004F1900 is overlay data at 0x4F1900, which
 * is 0x6C790 past _gp and so CANNOT take a %gp_rel relocation -- it must be
 * `const` or the object compiles clean and dies at link time.
 */

typedef struct Ent_title_FUN_004ef2b0 {
    u8 pad00[0x10];
} Ent_title_FUN_004ef2b0;

typedef struct Src_title_FUN_004ef2b0 {
    u8 pad00[0x28];
    Ent_title_FUN_004ef2b0 *field028;
    s32 field02C;
    s32 field030;
    s32 field034;
} Src_title_FUN_004ef2b0;

typedef struct Buf_title_FUN_004ef2b0 {
    u8 pad00[0x60];
} Buf_title_FUN_004ef2b0;

extern s32 D_004841F4;
extern s32 D_004841FC;
extern s32 D_00484200;
extern void *D_004841E0;
extern void *D_004841E4;
extern void *D_004841E8;
extern void *D_00484158;
extern void *D_00484170;
extern void *D_0048415C;
extern Src_title_FUN_004ef2b0 *D_00484150;
extern u8 title_D_004F1900;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleSaveSysInit_4ef2b0(void)
{
    Buf_title_FUN_004ef2b0 sp10 __attribute__((aligned(16)));
    Src_title_FUN_004ef2b0 *p;
    s32 k;
    s32 n;

    D_004841FC = 0x40;
    D_004841F4 = 0;
    D_004841E0 = D_00484158;
    D_00484200 = 0x20;
    D_004841E4 = D_00484170;
    D_004841E8 = D_0048415C;
    MemStackCtor_14e030(&sp10);
    p = D_00484150;
    k = p->field02C;
    n = p->field034;
    n = n - k;
    MemStackInit_14d810(&sp10, p->field028 + k, n);
    SaveUiSetRoot_37bc50(D_004841E4);
    SaveMgrInit_37bc60(title_TitleGetSaveCtx_4ef380(), &sp10);
    SaveProgressSetWidget_377790(0xC9);
    SaveMsgBoxSetWidget_3774c0(0xC8);
    SaveIconFilesSetAll_375b10(title_TitleGetSaveCtx_4ef380(), &title_D_004F1900);
    SaveIconSysBuild_375d10(title_TitleGetSaveCtx_4ef380());
    SaveSetBusy_376b10(0);
}
