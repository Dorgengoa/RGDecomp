/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuOpenBurstStart_4fb890 1
#include "port/game_protos.h"
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 62 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/f1..f6.py):
 *  - each block is `m = rand() % 100; fr = (f32)m / K - D; p = &normal_D_005275A0[..];
 *    p->f00 = cx; p->f02 = cy; p->f18 = ang + fr;` -- the named float temp
 *    BEFORE `p` is what schedules retail's constants ahead of p's address
 *    (s31's move deck had placed `p` before the rand call in block 1).
 *  - block 2 uses its OWN `j2, y2, x2` (declared in that order, after m):
 *    reusing j/x/y rotates three callee-saved registers.
 *  - `idx = *(Four *)&D_004804E0;` -- a 16-byte AGGREGATE copy; the four
 *    elementwise stores let the scheduler hoist the ang0/ang1 loads above them.
 * Everything below predates this session. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `D_x_at12_dec` from the declaration sweep.
 *   before: 356 words, 82 bad   after: 356 words, 72 bad   (retail 356 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_p_L99_T98_DEREF_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 357 words, ? bad   after: 356 words, 82 bad   (retail 356 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004FB890 -- FRESH unit, session 31 lane a1.  The 0x45 spray
 * seeder: eight passes, each seeding TWO normal_D_005275A0 sprite records (rows
 * n and n+1) with a func_133710 random phase/size, then registering four
 * widget ids per row out of the u16 id table D_004804C8 indexed through a
 * local 4-word copy of the gp table at 0x004804E0.
 *
 * Reading notes:
 *   - `adda.s`/`madd.s` at 0x004FB950 is `372.0f + 22.0f * (f32)g`
 *     ([[ps2-float-accumulator]]); the inner-loop `adda.s`/`msub.s` is
 *     `1.0f - K * (f32)j`.
 *   - the four INDEPENDENT gp `lwc1`/`swc1` pairs at the top are four scalar
 *     copies, each with its own gp displacement -- so the four table words
 *     are separate <= 8 B gp symbols ([[im-gp-array-sdata-threshold]]), and
 *     the local is read back with `lw`, i.e. it is a union.
 *   - `addiu $17,$16,0x1C` / `addiu $18,$16,0x20` with the accesses at
 *     `0x0($17)` / `0x0($18)` are MEMBER-ADDRESS temporaries
 *     ([[mwcc-member-address-no-cse]]), not plain member accesses.
 *   - `.word 0x46000024` is `cvt.w.s`, i.e. a plain (s32) cast
 *     ([[asm-listing-word-mnemonics]]).
 */

typedef struct Spr {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
} Spr;

typedef union Four {
    f32 f[4];
    s32 i[4];
} Four;

extern Spr  normal_D_005275A0[];
extern u16  D_004804C8[2];        /* gp - 0x4CA8 */
extern f32  D_004804E0;           /* gp - 0x4C90 */
extern f32  D_004804E4;           /* gp - 0x4C8C */
extern f32  D_004804E8;           /* gp - 0x4C88 */
extern f32  D_004804EC;           /* gp - 0x4C84 */
extern s32  D_00484460;           /* gp - 0xD10  */
extern f32  D_0047D5D0;           /* gp - 0x7BA0 */
extern f32  D_0047DA90;           /* gp - 0x76E0 */
extern f32  D_0047DADC;           /* gp - 0x7694 */
extern f32  D_0047DB7C;           /* gp - 0x75F4 */
extern f32  D_0047DD08;           /* gp - 0x7468 */
extern f32  D_0047DD0C;           /* gp - 0x7464 */
extern f32  D_0047DD10;           /* gp - 0x7460 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuOpenBurstStart_4fb890(void *w, s32 cx, s32 cy)
{
    Four idx __attribute__((aligned(16)));
    f32  ang0;
    f32  ang1;
    f32  dx;
    f32  dy;
    f32  fr;
    f32 *pw;
    f32 *ph;
    Spr *p;
    s32  n;
    s32  k;
    s32  j;
    s32  y;
    s32  x;
    u16  id;
    s32  r;
    s32  m;
    s32 j2;
    s32 y2;
    s32 x2;

    n = 0;
    idx = *(Four *)&D_004804E0;
    ang0 = D_0047DD08;
    ang1 = D_0047DD0C;
    UiSetWidgetAlpha_2907a0(w, 0x45, 0.0f);
    UiSetWidgetsVisibleById_291110(w, 0x45, 1, 1);
    UiSetWidgetPos_290f60(w, 0x45, D_00484460 * 7 + 0x10,
                (s32)(372.0f + 22.0f * (f32)D_00484460));

    for (k = 0; k < 8; k++) {
        m = Rand_133710() % 100;
        fr = (f32)m / 1000.0f - D_0047DD10;
        p = &normal_D_005275A0[n];
        p->f00 = cx;
        p->f02 = cy;
        p->f18 = ang0 + fr;
        pw = &p->f1C;
        r = Rand_133710();
        *pw = 150.0f + (f32)(r % 30);
        ph = &p->f20;
        r = Rand_133710();
        *ph = 150.0f + (f32)(r % 30);
        p->f24 = 1.25f;
        p->f14 = 1.0f;
        p->f10 = 1.0f;
        p->f0C = 1.0f;
        dx = *pw * Cosf_128d30(ang0);
        dy = *ph * Sinf_128fd0(ang0);
        x = (s32)((f32)cx + dx);
        p->f04 = x;
        p->f08 = x;
        y = (s32)((f32)cy + dy);
        p->f06 = y;
        p->f0A = y;
        for (j = 0; j < 3; j++) {
            id = n + D_004804C8[idx.i[j]];
            UiSetWidgetsVisibleById_291110(w, id, 1, 1);
            UiSetWidgetPos_290f60(w, id, x, y);
            UiFadeWidgetAlpha_290690(w, id, 1.0f - D_0047DB7C * (f32)j, D_0047D5D0, -1.0f);
        }
        id = n + D_004804C8[idx.i[3]];
        UiSetWidgetsVisibleById_291110(w, id, 1, 1);
        UiSetWidgetPos_290f60(w, id, x, y);
        UiFadeWidgetAlpha_290690(w, id, D_0047D5D0, D_0047DD10, -1.0f);

        m = Rand_133710() % 100;
        fr = (f32)m / 500.0f - D_0047DADC;
        p = &normal_D_005275A0[n + 1];
        p->f00 = cx;
        p->f02 = cy;
        p->f18 = ang1 + fr;
        pw = &p->f1C;
        r = Rand_133710();
        *pw = 135.0f + (f32)(r % 30);
        ph = &p->f20;
        r = Rand_133710();
        *ph = 135.0f + (f32)(r % 30);
        p->f24 = 1.25f;
        p->f14 = 1.0f;
        p->f10 = 1.0f;
        p->f0C = 1.0f;
        dx = *pw * Cosf_128d30(ang1);
        dy = *ph * Sinf_128fd0(ang1);
        x2 = (s32)((f32)cx + dx);
        p->f04 = x2;
        p->f08 = x2;
        y2 = (s32)((f32)cy + dy);
        p->f06 = y2;
        p->f0A = y2;
        for (j2 = 0; j2 < 3; j2++) {
            id = (n + 1) + D_004804C8[idx.i[j2]];
            UiSetWidgetsVisibleById_291110(w, id, 1, 1);
            UiSetWidgetPos_290f60(w, id, x2, y2);
            UiFadeWidgetAlpha_290690(w, id, 0.5f - 1.5f * (f32)j2, D_0047DD10, -1.0f);
        }
        id = (n + 1) + D_004804C8[idx.i[3]];
        UiSetWidgetsVisibleById_291110(w, id, 1, 1);
        UiSetWidgetPos_290f60(w, id, x2, y2);
        UiFadeWidgetAlpha_290690(w, id, D_0047D5D0, D_0047DD10, -1.0f);

        n += 2;
        ang0 += D_0047DA90;
        ang1 += D_0047DA90;
    }
    return 0;
}
