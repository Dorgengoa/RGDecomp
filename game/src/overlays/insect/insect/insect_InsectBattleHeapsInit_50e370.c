/* rgp:protos */
#define RGP_SELF_insect_InsectBattleHeapsInit_50e370 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E370 -- 604 B / 151 words.  Largest clean member of the
 * func_134A98 loader family (seed src/wf/insect/insect_InsectAbilityTableLoad_51d0b0.c); it
 * carries the guard TWICE, once per table loop.
 *
 * Guard spelling verbatim from the seed:
 *     if (func_134BB0(NAME) < 0x10) { func_134A98(obj, NAME); }
 * u32 func_134BB0 gives sltiu $1,$2,0x10.  Loop 2 gets beql (its join block
 * daddu $4,$17 hoists into the likely slot), loop 3 gets beqz + nop -- that
 * difference is scheduling, not source.
 *
 * Element stride is 88 = 0x58 (sll 2 / addu / sll 1 / addu / sll 3) off a base
 * at +0xE0, so the object holds Ent arr[0x15] there; the tail 0x190 / 0x2F0 /
 * 0x608 are &arr[2] / &arr[6] / &arr[15].
 *
 * The two index tables are GP-RELATIVE bytes (addiu $2,$28,-0x42D8 / -0x42C8
 * with lb), i.e. _gp = 0x00485170 -> D_00480E98 (9 entries: 0,1,2,7,11,12,13,
 * 14,16) and D_00480EA8 (10 entries: 3,4,5,6,8,9,10,15,17,18) -- both verified
 * against asm/data/main_data.data.s.  They are declared as INCOMPLETE,
 * NON-CONST arrays SIZED 8 so they stay in small data
 * (im-gp-array-sdata-threshold: a gp extern declared >8 B leaves sdata and
 * costs a %hi/%lo pair; const would put them in .rodata instead).
 * !! MEASURED, build 1: the INCOMPLETE form `extern s8 D_00480E98[];` is NOT a
 * small-data escape for this mwcc -- it emitted lui/addiu %hi/%lo, +1 word per
 * loop.  Declare the SIZE and make it <= 8 (both tables are really 9 and 10
 * bytes long, so this is shorter than the truth on purpose).
 *
 * sll 10 then bgez / addiu 0xF / sra 4 is signed / 16, NOT >> 4.
 * !! LOOP 3 HAS NO `sll 10`: its size is insect_D_00523CA0[j] / 16 flat, where loop 2
 * is (insect_D_00523C40[j] << 10) / 16.  Measured -- the two loops are NOT the same
 * expression and copying loop 2 into loop 3 is exactly one word long.
 *
 * !! DECLARATION ORDER IS LOAD-BEARING AND IT IS A THREE-WAY ORDER, not a pair
 * swap.  MEASURED: all 720 permutations of the six locals, in one round trip
 * (build/wf33_vsweep.py --perm).  The bad-word count is a FUNCTION OF THE
 * RELATIVE ORDER OF h, o AND j ALONE -- i, t and n are completely inert, and
 * the six buckets are exactly 120 variants each:
 *     h < j < o -> 0   (this file)      o < h < j -> 24
 *     h < o < j -> 10                   o < j < h -> 23
 *     j < h < o -> 19                   j < o < h -> 28
 * The wrong orders swap $17/$18 between the LOOP COUNTER and the derived
 * element pointer in LOOP 2 ONLY (loop 3 is already right in every arm), so a
 * 10-word residue here is register allocation, not code.
 *
 * Frame proof: 6 sq callee-saved GPRs (0x60) + sd $31 at 0x60 -> 0x68, rounded
 * to 0x70, NO stack locals.  Matches addiu $29,$29,-0x70.
 */

typedef struct Ent { u8 raw[0x58]; } Ent;

typedef struct Obj {
    u8    pad0000[0xD8];
    void *mD8;                          /* +0x00D8 */
    u8    pad00DC[0x4];
    Ent   arr[0x15];                    /* +0x00E0 .. +0x0818 */
    u8    pad0818[0x502C - 0x818];
    u8    f502C[1];                     /* +0x502C */
    u8    pad502D[0x5058 - 0x502D];
    u8    f5058[1];                     /* +0x5058 */
    u8    pad5059[0x51C4 - 0x5059];
    u8    f51C4[1];                     /* +0x51C4 */
} Obj;

extern s8 D_00480E98[8];                 /* _gp - 0x42D8 */
extern s8 D_00480EA8[8];                 /* _gp - 0x42C8 */

extern s32          insect_D_00523C40[];
extern const char *const  insect_D_00523C70[];
extern s32          insect_D_00523CA0[];
extern const char *const  insect_D_00523CD0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  strcpy(Ent *o, const char *t);
extern u32   strlen(const char *t);

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleHeapsInit_50e370(Obj *a)
{
    void       *h;
    s32         i;
    s32         j;
    Ent        *o;
    const char *t;
    s32         n;

    h = a->mD8;
    if (h != 0) {
        for (i = 0; i < 0x15; i++) {
            MemStackClear_14dff0(&a->arr[i]);
        }
        for (j = 0; j < 9; j++) {
            o = &a->arr[D_00480E98[j]];
            MemStackHeapAlloc_14db10(h, 2, 0, 0x40);
            n = (insect_D_00523C40[j] << 10) / 16;
            MemStackHeapInit_14dee0(o, MemStackAllocQw_14d950(h, n), n);
            t = insect_D_00523C70[j];
            if (strlen(t) < 0x10) {
                strcpy(o, t);
            }
            MemStackHeapReinit_14de90(o);
            MemStackReturnToOwnerMaybe_14dad0(h);
        }
        for (j = 0; j < 10; j++) {
            o = &a->arr[D_00480EA8[j]];
            if (((s32)MemStackHeapAlloc_14db10(h, 2, 0, 0x40)) != 0) {
                n = insect_D_00523CA0[j] / 16;
                MemStackInit_14d810(o, MemStackAllocQw_14d950(h, n), n);
                MemStackReset_14d830(o);
                t = insect_D_00523CD0[j];
                if (strlen(t) < 0x10) {
                    strcpy(o, t);
                }
            }
            MemStackReturnToOwnerMaybe_14dad0(h);
        }
    }
    insect_InsectCmdMenuInit_4efd80(a->f502C, &a->arr[2]);
    insect_InsectFormationInit_4efe50(a->f5058, &a->arr[6]);
    insect_InsectAiSetHeap_522c30(a->f51C4, &a->arr[15]);
}
