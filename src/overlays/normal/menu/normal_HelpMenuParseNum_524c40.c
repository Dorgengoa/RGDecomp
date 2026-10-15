#include "types.h"
/* normal 0x00524C40 -- sizes the shop's stock arena: the base row count minus
 * one for each of the two optional catalogues that is absent, times 118 bytes.
 * Pass-33 LIST rank: 148 bytes, 37 instructions, TWO conditional branches,
 * 5 calls.
 *
 * Both `bnel`s skip the decrement when the catalogue IS present, so the
 * decrement is what retail FALLS THROUGH into and the source guard is
 * `== 0`.  118 is the `sll 4 / subu / sll 2 / subu / sll 1` chain, not a
 * multiply instruction. */

typedef struct Root { u8 pad00[0x10]; void *f10; } Root;

extern void *D_0048499C;          /* gp - 0x7D4 */
extern s32   D_004849E8;          /* gp - 0x788 */
extern s32   D_004849F0;          /* gp - 0x780 */

extern void *func_14E1B0(s32 size, void *heap);
extern s32   func_15F780(void);
extern Root *func_1FEDE0(void);
extern s32   func_3CCD70(void *a, s32 id);

extern s32 normal_HelpMenuParseNum_524c40(void);

s32 normal_HelpMenuParseNum_524c40(void)
{
    Root *r;

    D_004849F0 = func_15F780();
    r = func_1FEDE0();
    if (func_3CCD70(r->f10, 0x186) == 0) {
        D_004849F0 = D_004849F0 - 1;
    }
    if (func_3CCD70(r->f10, 0x187) == 0) {
        D_004849F0 = D_004849F0 - 1;
    }
    D_004849E8 = (s32)func_14E1B0(D_004849F0 * 118, D_0048499C);
    return 1;
}
