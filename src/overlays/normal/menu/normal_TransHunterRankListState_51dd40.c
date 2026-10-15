#include "types.h"
/* normal 0x0051DD40 -- the 0x7642/0x7644 list pad handler.  FRESH unit,
 * session 31 lane a1.  Structural twin of normal_TransHunterBountyListState_51f630 (same
 * func_28E170 / func_28EC60 / four-D_004B2570-test shape, same Rec layout,
 * same (s16)(rec->f0A + 1) narrowed page stride), but:
 *   - takes no parameters (frame -0x30, sq $16 / sq $17 / sd $31 only),
 *   - the confirm arm (code == 1) is a func_290690 fade plus a
 *     func_3CCAC0 count clamped to 1..100 and stored decremented into
 *     D_00480784, then a normal_TransHunterRewardFindNext_51d320 poll,
 *   - every path falls through a shared tail `D_004848B4 = rec->f12;`.
 */

typedef struct Rec {
    u8  pad00[2];
    s16 f02;
    u8  pad04[2];
    s16 f06;
    u8  pad08[2];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
    u8  pad10[2];
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Rec;

typedef struct Pad { u8 pad00[0x14]; s32 f14; } Pad;
typedef struct Ent { u8 pad00[0x10]; void *f10; } Ent;

extern const u8 D_004B2570[];

extern f32   D_0047D998;          /* gp - 0x77D8 */
extern f32   D_0047D9B8;          /* gp - 0x77B8 */
extern s16   D_00480784;          /* gp - 0x49EC */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern Pad  *D_00484720;          /* gp - 0xA50  */
extern s16   D_004848B4;          /* gp - 0x8BC  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern s16   D_004848F0;          /* gp - 0x880  */

extern s32   func_28E170(void *p, const u8 *r, s32 c, s32 d);
extern Rec  *func_28EC60(void *p);
extern void  func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern Ent  *func_1FEDE0(void);
extern s32   func_3CCAC0(void *p, s32 a);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern s32   func_1839F0(const u8 *r, s32 mask);
extern s32   func_183DD0(const u8 *r, s32 mask);
extern void  func_28E9E0(void *p, s32 a);
extern void  func_28FD10(void *w, u16 id, s32 a, s32 b, s32 c);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern s32   normal_TransHunterRewardFindNext_51d320(void);
extern void  normal_TransHunterRankListFill_51d820(s32 a);

s32 normal_TransHunterRankListState_51dd40(void)
{
    s32  code;
    Rec *rec;
    s32  n;

    code = func_28E170(D_00484720, D_004B2570, 0, 0);
    rec = func_28EC60(D_00484720);
    if (code == 1) {
        func_290690(D_00484710, 0x764B, 0.0f, D_0047D9B8, -1.0f);
        n = func_3CCAC0(func_1FEDE0()->f10, 0xF);
        if (n <= 0 || n > 0x64) {
            n = 0x64;
        }
        D_00480784 = n - 1;
        if (normal_TransHunterRewardFindNext_51d320() > 0) {
            D_004848F0 = 0;
            func_28EDE0(D_0048470C, 0x1C, 0);
        } else {
            func_28EDE0(D_0048470C, 0x1B, 0);
        }
    } else if (func_1839F0(D_004B2570, 0x8000) != 0) {
        if (rec->f12 > 0 || rec->f16 > 0) {
            func_28E9E0(D_00484720, 0);
        }
        if (rec->f16 > 0) {
            rec->f16 = rec->f16 - (s16)(rec->f0A + 1);
            if (rec->f16 < 0) {
                rec->f16 = 0;
                rec->f12 = 0;
                func_28FD10(D_00484710, 0x7642, 0x1E, rec->f02, 0);
            }
            normal_TransHunterRankListFill_51d820(rec->f16);
        } else {
            rec->f16 = 0;
            rec->f12 = 0;
            func_28FD10(D_00484710, 0x7642, 0x1E, rec->f02, 0);
        }
        if (rec->f16 < 0) {
            rec->f16 = 0;
        }
        func_290F50(D_00484710, 0x7644, 0,
                    (s32)((f32)rec->f16 * D_004848B8), 0, D_0047D998);
    } else if (func_1839F0(D_004B2570, 0x2000) != 0) {
        if (rec->f12 < rec->f0A || rec->f16 < rec->f0E - rec->f0A) {
            func_28E9E0(D_00484720, 0);
        }
        if (rec->f16 < rec->f0E - rec->f0A) {
            rec->f16 = rec->f16 + (s16)(rec->f0A + 1);
            if (rec->f16 > rec->f0E - rec->f0A) {
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                func_28FD10(D_00484710, 0x7642, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
            }
            normal_TransHunterRankListFill_51d820(rec->f16);
        } else {
            rec->f12 = rec->f0A;
            rec->f16 = rec->f0E - rec->f0A;
            func_28FD10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
        }
        if (rec->f16 < 0) {
            rec->f16 = 0;
        }
        func_290F50(D_00484710, 0x7644, 0,
                    (s32)((f32)rec->f16 * D_004848B8), 0, D_0047D998);
    } else if ((D_00484720->f14 & 1) &&
               func_1839F0(D_004B2570, 0x1000) != 0 &&
               func_183DD0(D_004B2570, 0x1000) == 0) {
        if (rec->f12 == 0 && rec->f16 == 0 && rec->f0E > 0) {
            func_28E9E0(D_00484720, 0);
            rec->f12 = rec->f0A;
            rec->f16 = rec->f0E - rec->f0A;
            func_28FD10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
            normal_TransHunterRankListFill_51d820(rec->f16);
            func_290F60(D_00484710, 0x7644, 0,
                        (s32)((f32)rec->f16 * D_004848B8));
        }
    } else if ((D_00484720->f14 & 2) &&
               func_1839F0(D_004B2570, 0x4000) != 0 &&
               func_183DD0(D_004B2570, 0x4000) == 0) {
        if (rec->f12 == rec->f0A && rec->f16 == rec->f0E - rec->f0A &&
            rec->f0E > 0) {
            func_28E9E0(D_00484720, 0);
            rec->f12 = 0;
            rec->f16 = 0;
            func_28FD10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
            normal_TransHunterRankListFill_51d820(rec->f16);
            func_290F60(D_00484710, 0x7644, 0,
                        (s32)((f32)rec->f16 * D_004848B8));
        }
    }
    D_004848B4 = rec->f12;
    return 1;
}
