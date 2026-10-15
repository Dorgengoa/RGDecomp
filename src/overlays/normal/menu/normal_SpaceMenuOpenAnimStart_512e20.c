/* normal 0x00512E20 -- MATCH (byte-identical, 117 words, nscore.py --tag nc32l,
 * session 32 lane nc32l).  Do not "simplify" the two lines called out below.
 *
 * THE CLOSING LEVER: the signed halving is `f6 / 2`, NOT a hand-written
 * `>> 1` plus an `if (f6 < 0)` bias.  Both spellings emit the same five
 * instructions, but they are not the same program to the register allocator:
 *   hand-written bias -> lw $3 (spAC) / sra $4 (half)   -- 5 bad, a pure
 *                        $3<->$4 TRANSPOSITION against retail;
 *   `f6 / 2`          -> lw $4 (spAC) / sra $3 (half)   -- retail exactly.
 * mwcc builds the divide idiom's temporaries itself, after the statement's
 * other operands, so the quotient vreg is created before the `spAC` load even
 * though the load is EMITTED first; a source-level bias creates them in
 * source order and colours them the other way round.  The whole residue of
 * this unit was that one colour pair.
 *
 * Screened around it, 65 arms over two bulk decks (identity armed both times,
 * reproduced 5 bad):
 *   * moving the DEFINING STATEMENT of `half` above `x` (`b1`, 5 spellings of
 *     the surrounding `p` block): 8 bad, ONE object -- mwcc then puts the
 *     first `sra` in the `bgez` delay slot where retail puts x's `addiu $17`.
 *   * ternary bias (`half = (s32)(f6 < 0 ? f6 + 1 : f6) >> 1;` with x last):
 *     7 bad but RETAIL'S REGISTER MAP -- the arm that proved the colour pair
 *     was source-reachable and pointed at a compiler-generated quotient.
 *   * else-form of the bias: 8-9 bad, worse l1 (the branch shape moves).
 *   * `y = half + spA8 - 0xA` flips the `addu` operands to `addu $2,$4,$2`;
 *     retail is `addu $2,$2,$3`, so the identity operand order was right.
 *   * INERT at MATCH (11 arms on one object): where `half` is declared, whether
 *     it is named at all (`y = (spA8 + f6 / 2) - 0xA` matches too), `s16` vs
 *     `s32` f6, and all five spellings of the `func_290460` result / `p` test.
 *
 * `D_0047D7CC` is a float LITERAL POOL entry, not a global: it is written
 * `0.1000000015f` here (lit4 ok/3).  Measured object-identical either way on
 * this unit -- it is retail's spelling, not a lever.
 *
 * Drafted s26 by ORACLE TRANSFER from normal_SpaceMenuAnimStep_513000 (same `Obj` layout,
 * same 9-entry D_00525AF0 walk, same func_2910A0 / func_290460 lookup pair).
 * D_00525AF0's stride is EIGHT, not four -- retail indexes it with
 * `sll $2, $6, 3`, and a mnemonic diff cannot see a wrong stride.
 * Callee-saved map, used as the DECLARATION order (declare DESCENDING):
 * $20 id, $19 lookup/n, $18 arg0, $17 x, $16 y.
 * The `id = 0x28` after the guarded block is ONE statement; retail duplicates
 * it into the `beql` annulled slot and the `bltz` landing pad.  The
 * per-iteration dsll32/dsra32 ,16 is the s16 re-narrowing of `id`.
 */
#include "types.h"
/* normal 0x00512E20 -- drafted s26 by ORACLE TRANSFER from normal_SpaceMenuAnimStep_513000,
 * which shares this unit's whole idiom set: the same `Obj` layout, the same
 * 9-entry `D_00525AF0` key/val table walk, the same `func_2910A0` / `func_290460`
 * lookup pair off `D_004806A0` / `D_00480690`, and the same `f6 >> 1` signed
 * halving with the `if (f6 < 0)` bias.  Types, prototypes and the spAC/spA8
 * declaration order are lifted verbatim rather than re-derived.
 *
 * ⚠ `D_00525AF0`'s stride is EIGHT, not four -- retail indexes it with
 * `sll $2, $6, 3`.  A 4-byte `{s16 key; s16 val;}` Pair compiles to `sll ..,2`
 * and a MNEMONIC diff CANNOT SEE IT (both are `sll`), so the oracle's own
 * 4-byte Pair is not transferable here; read the shift amount off the object.
 *
 * Register map, read off the listing and used as the DECLARATION ORDER
 * ([[mwcc-gpr-decl-order-map]]: a LATER declaration takes a LOWER callee-saved
 * register, so declare DESCENDING): $20 id, $19 lookup/n, $18 arg0 (param),
 * $17 x, $16 y.
 *
 * ⚠⚠ PARKED s26 at the RIGHT LENGTH (117 words) and 34 bad, and the object is
 * INSTRUCTION-FOR-INSTRUCTION equal to retail -- every one of the 34 is the same
 * opcode with a different register.  The residue is a TWO-BLOCK SWAP of the
 * callee-saved run:
 *      ours    id $20 | x $19  y $18 | n+lookup $17  arg0 $16
 *      retail  id $20 | n+lookup $19  arg0 $18 | x $17  y $16
 * Both PAIRS already carry retail's INTERNAL order ($19>$18 and $17>$16); only
 * the two blocks are inverted.  29 arms, five decks, all read through
 * build/wf-normal/s26/rmap.py, which prints the ASSIGNED REGISTER beside the
 * length -- a bad-count sweep cannot see this axis at all.
 *   * declaration POSITION of the pointer: 9 arms, ONE map (inert), including an
 *     explicit `Obj *o = arg0;` copy swept through every slot in the list.
 *   * x/y initialisation shape and statement order: 5 arms, ONE map.
 *   * loop shape (`for`, plain add, reordered body, non-verbatim arguments):
 *     5 arms, ONE map.
 *   * counter live range (reuse `lookup`, reuse `i`, live-after, uninitialised):
 *     5 arms, ONE map at the right length.
 *   * pointer live range (tail on the parameter, tail on a second local, stores
 *     hoisted before the calls): 3 arms, ONE map.
 * ★★ THE CLASS IS LIVE, and this is the arm that proves it: `n` counting DOWN
 * to zero drops the counter out of the callee-saved run entirely and the
 * remaining three shift UP one place each, to arg0 $19, x $18, y $17 -- which is
 * retail's RELATIVE order.  It is one word short (the `slti` goes), so it is not
 * the answer, but it refutes "the run is not source-controllable".  The open
 * question is narrow: what makes an UP-counting counter rank SECOND rather than
 * second-from-last.  Same family as normal_FUN_005115C0 / normal_FUN_0051D780.
 * ⚠ Four of the 34 (0x00512FC0-0x00512FCC) are the tail SCHEDULE, not the map:
 * retail hoists the `lwc1` of -0.03500000015f above the `sh` and sinks the `daddu $2`
 * return value; statement order there is inert (see `stores_before_calls`).
 *
 * The `id = 0x28` after the guarded block is ONE statement; retail duplicates
 * it into the `beql` annulled slot and into the `bltz` landing pad
 * ([[mwcc-branch-likely-duplication]]).  The per-iteration `dsll32/dsra32 ,16`
 * is an s16 `id` re-narrowing -- the CONVERSE of normal_SpaceMenuAnimStep_513000's lever 2,
 * where retail had no narrowing and the local had to be `s32`.
 */

typedef struct Obj {
    u8   pad00[0x14];
    u8   f14;
    u8   pad1C[0x20 - 0x15];
    f32  f20;
    u8   pad24[0x3C - 0x24];
    s16  f3C;
    s16  f3E;
    f32  f40;
    f32  f44;
    s16  f48;
    s16  f4A[3][4];
    s16  f62;
    u8   pad64[0x68 - 0x64];
    f32  f68;
} Obj;

typedef struct { s16 key; s16 val; u8 pad04[4]; } Pair;

extern Pair D_00525AF0[9];
extern u16  D_004806A0[4];        /* gp - 0x4AD0 */
extern u16  D_00480690[4];        /* gp - 0x4AE0 */

extern void *func_290460(void *p, u16 id);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_2907A0(void *w, u16 id, f32 v);
extern void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern void  func_2910A0(void *p, u16 id, s32 *x, s32 *y);

s32 normal_SpaceMenuOpenAnimStart_512e20(Obj *arg0)
{
    s32 x;
    s32 y;
    s32 spAC;
    s32 spA8;
    s32 id;
    s32 n;
    Obj *o;
    s32 lookup;
    s16 idKey;
    s32 i;

    o = arg0;
    x = 0;
    y = 0;
    idKey = o->f4A[o->f3E][o->f3C];
    if (idKey >= 0) {
        i = 0;
        do {
            if (idKey == D_00525AF0[i].key) {
                idKey = D_00525AF0[i].val;
            }
            i++;
        } while (i < 9);

        lookup = (s32)idKey;
        func_2910A0(o, D_004806A0[lookup], &spAC, &spA8);
        {
            void *pRes = func_290460(o, D_00480690[lookup]);
            void *p = *(void **)((u8 *)pRes + 0x20);

            if (p != NULL) {
                s16 f6 = *(s16 *)((u8 *)p + 6);
                s32 half;

                x = spAC - 0xA;
                half = f6 / 2;
                y = (spA8 + half) - 0xA;
            }
        }
    }

    id = 0x28;
    n = 0;
    do {
        func_290F60(o, id & 0xFFFF, x, y);
        id = (s16)(id + 1);
        n++;
    } while (n < 4);

    func_2907A0(o, 0x27, 0.0f);
    func_290690(o, 0x27, 1.0f, 0.03999999911f, -1.0f);
    func_290F60(o, 2, 0, 0);
    func_2907A0(o, 2, 0.0f);
    func_290690(o, 2, 1.0f, 0.1000000015f, -1.0f);

    o->f20 = 0.0f;
    o->f48 = 0;
    o->f40 = 0.0f;
    o->f44 = -0.03500000015f;
    return 0;
}
