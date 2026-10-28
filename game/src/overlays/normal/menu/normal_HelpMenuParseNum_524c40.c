/* rgp:protos */
#define RGP_SELF_normal_HelpMenuParseNum_524c40 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_HelpMenuParseNum_524c40(void * rgp_a0);

s32 normal_HelpMenuParseNum_524c40(void *rgp_a0)
{
    Root *r;

    D_004849F0 = VariantGetInt_15f780((void *)rgp_a0);
    r = ((Root *)GetGameData_1fede0());
    if (StateFlagTest_3ccd70(r->f10, 0x186) == 0) {
        D_004849F0 = D_004849F0 - 1;
    }
    if (StateFlagTest_3ccd70(r->f10, 0x187) == 0) {
        D_004849F0 = D_004849F0 - 1;
    }
    D_004849E8 = (s32)MemStackNew_14e1b0(D_004849F0 * 118, D_0048499C);
    return 1;
}
