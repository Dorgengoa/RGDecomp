#include "types.h"
/* normal 0x0051E720 -- the 0x7919/0x791A result banner: picks the win/lose
 * colour pair, formats both scores into two 8-byte gp buffers and starts the
 * 90-frame hold.  `slti $1, $3, 0x5B` puts the clamp compare in $at, so the
 * source token is `> 0x5A` and not `>= 0x5B` ([[at-compare-class]]).
 * The two format buffers are SEPARATE 8-byte gp objects -- one 16-byte array
 * is over the small-data threshold and comes out lui/%lo.
 * Three placement levers, all needed together:
 *  - the score-EQUAL arm is the `else` (`if (mine != theirs)`), or mwcc lays
 *    it inline and the whole function shifts;
 *  - `D_004848D0 = 90.0f` is written at the END OF BOTH arms, which is what
 *    puts the `sw` in the `b`'s delay slot instead of the next call's `lw`;
 *  - the hold test is `> 0.0f` with the SUBTRACT as the `if` body, so the
 *    expire call is the cold block.  Changing this one alone re-laid out the
 *    score-equal arm 130 words earlier -- block placement here is global.
 * Declarations: `i` FIRST and `theirs` BEFORE `mine` is what puts mine in $16,
 * theirs in $17 and the loop counter in $18 (11 -> 8 -> 0 bad). */

extern const u8 D_00526850;

extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */
extern void *D_00484770;          /* gp - 0xA00  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern s16   D_0048075C;          /* gp - 0x4A14 */
extern f32   D_004848D0;          /* gp - 0x8A0  */
extern s32   D_004848D4;          /* gp - 0x89C  */
extern u8    D_004848E0[8];       /* gp - 0x890  */
extern u8    D_004848E8[8];       /* gp - 0x888  */
extern f32   D_0047D288;          /* gp - 0x7EE8 */

typedef struct Rec {
    u8   pad000[0x1A];
    s16  f01A;
} Rec;

typedef struct Root {
    u8   pad000[0x18];
    s32  f018;
} Root;

typedef struct Game {
    u8   pad0000[0x4C90];
    s16  f4C90;
    u8   pad4C92[2];
    s16  f4C94;
} Game;

extern void  func_131B60(u8 *p, s32 v, s32 n);
extern void  func_1343B8(u8 *p, const u8 *fmt, s16 a);
extern void  func_1CD960(s32 a, s32 b, s32 c, f32 x);
extern f32   func_1CEBA0(s32 a);
extern s32   func_1F59D0(void);
extern s32   func_1F5BE0(void);
extern Root *func_1FEDE0(void);
extern void  func_207340(s32 a, s32 b, f32 x);
extern void *func_28AA30(void *p, s32 a);
extern Rec  *func_28EA40(void *p, s32 id);
extern void  func_28EA90(void *p, s32 id, s32 a);
extern void  func_28EDE0(void *p, u16 id, s32 a);
extern void  func_28F510(void *p, s32 id, void *q, s32 b);
extern void  func_2905B0(void *p, s32 id, f32 r, f32 g, f32 b, f32 a);
extern void  func_2907A0(void *p, s32 id, f32 x);
extern void  func_290A40(void *p, s32 id, s32 c, s32 d);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);

s32 normal_TransHunterRankResultState_51e720(void *a, s32 b)
{
    s32 i;
    Game *g;
    s16 theirs;
    s16 mine;
    Rec *r;
    s16 v;
    f32 t;
    f32 hold;

    if (b != 0) {
        func_1CD960(func_1F59D0(), 0, 0xF, 1.0f);
        func_2907A0(D_00484718, 0x7919, 0.0f);
        func_28EA90(D_00484720, 0xF, 0);
        D_0048075C = 0x64;
        g = (Game *)func_1FEDE0()->f018;
        mine = g->f4C90;
        theirs = g->f4C94;
        if (mine != theirs) {
            func_1CD960(func_1F59D0(), 0, 0xF, 0.0f);
            if (mine < theirs) {
                func_28F510(D_00484718, 0x7919, func_28AA30(D_00484770, 4), 0);
                func_290A40(D_00484718, 0x791A, 0xFF004F4F, 0);
                func_290A40(D_00484718, 0x791A, 0xFF004F4F, 1);
                func_2905B0(D_00484718, 0x791A, 1.0f, 1.0f, 1.0f, 1.0f);
                func_207340(0x327, 0, 1.0f);
                D_004848D0 = 90.0f;
            } else {
                func_28F510(D_00484718, 0x7919, func_28AA30(D_00484770, 0xB), 0);
                func_290A40(D_00484718, 0x791A, 0xFF00002F, 0);
                func_290A40(D_00484718, 0x791A, 0xFF00002F, 1);
                t = D_0047D288;
                func_2905B0(D_00484718, 0x791A, t, t, t, 1.0f);
                func_207340(0x329, 0, 1.0f);
                D_004848D0 = 90.0f;
            }
            func_28F510(D_00484718, 0x791A, func_28AA30(D_00484770, 5), 0);
            i = 0;
            do {
                func_131B60(&D_004848E0[i * 8], 0, 8);
                i += 1;
            } while (i < 2);
            func_1343B8(D_004848E0, &D_00526850, mine);
            func_28F510(D_00484718, 0x791A, D_004848E0, 1);
            func_1343B8(D_004848E8, &D_00526850, theirs);
            func_28F510(D_00484718, 0x791A, D_004848E8, 2);
            func_291110(D_00484718, 0x791A, 1, 1);
            D_004848D4 = 0x17;
        } else {
            D_004848D0 = 0.0f;
            D_004848D4 = 0x18;
        }
        D_0048075C = mine;
        r = func_28EA40(D_00484720, 0xA);
        v = mine - 1;
        if (v > 0x5A) {
            v = 0x5A;
        }
        r->f01A = v;
    }
    t = func_1CEBA0(func_1F5BE0());
    hold = D_004848D0;
    if (hold > 0.0f) {
        D_004848D0 = hold - t;
    } else {
        func_28EDE0(D_0048470C, (u16)D_004848D4, 0);
    }
    return 1;
}
