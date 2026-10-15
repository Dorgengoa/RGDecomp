#include "types.h"
/* normal 0x0051F630 -- the 0x763C list's pad handler.  func_28E170 returns
 * 1 (confirm) / 2 (cancel) / 0 (idle); the idle arm is four D_004B2570 pad
 * tests (0x8000 up, 0x2000 down, 0x1000 and 0x4000 the shoulder jumps) that
 * move rec->f12 (the cursor row) and rec->f16 (the scroll offset) and repaint
 * the 0x7637 caret plus the 0x763E bar.  The `(s16)(rec->f0A + 1)` step is a
 * narrowed intermediate -- that dsll32/dsra32 pair is the page stride, and
 * the SECOND pair is the stored rec->f16 forwarded to its own sign test.
 *
 * s32/nc32e: MATCH.  The last 2 bad words were the branch at 0x51F780
 * (ours b .L0051FC00 + li $2,1 ; retail b .L0051FBFC + nop).  mwcc threads
 * only the FIRST predecessor of the shared `return 1' block, duplicating that
 * block's li into the delay slot and retargeting to +4.  Spelling the close
 * arm as an early `return 1;' kept it OUT of that block, so the code==1 arm
 * became the first predecessor and ate the threading.  Wrapping the rest in
 * an `else' so the close arm FALLS THROUGH to one tail `return 1;' makes
 * 0x51F690 the first predecessor again.  `goto done;' out of the close arm
 * gives the SAME object (35f2df73f3e6); adding explicit `return 1;' to the
 * code==1 / code==2 arms instead reads 4-6 bad. */

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

typedef struct Pad  { u8 pad00[0x14]; s32 f14; } Pad;
typedef struct Slot { u8 pad00[8]; s32 f08; } Slot;
typedef struct Inner { u8 pad000[0x180]; s32 f180; } Inner;
typedef struct Ent  { u8 pad00[0x18]; Inner *f18; } Ent;

extern const u8 D_004B2570[];

extern Pad  *D_00484720;          /* gp - 0xA50  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern s32   D_004848BC;          /* gp - 0x8B4  */
extern s16   D_004848C0;          /* gp - 0x8B0  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D9D4;          /* gp - 0x779C */

extern void  func_28EA90(void *p, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern s32   func_28E170(void *p, const u8 *r, s32 c, s32 d);
extern Rec  *func_28EC60(void *p);
extern Ent  *func_1FEDE0(void);
extern Slot *func_28F2B0(void *w, u16 id, s32 k);
extern void  func_3E8B80(Ent *e, s32 a);
extern void  func_291250(void *w, u16 id, s32 slot, s32 v);
extern void  normal_TransHunterBountyMarkReported_51e480(void);
extern void *func_1F59D0(void);
extern void  func_1CD960(void *a, s32 b, s32 c, f32 d);
extern void  func_207340(s32 a, s32 b, f32 c);
extern void  func_3E8CE0(Ent *e);
extern void  func_3E9050(Ent *e);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern s32   func_1839F0(const u8 *r, s32 mask);
extern s32   func_183DD0(const u8 *r, s32 mask);
extern void  func_28E9E0(void *p, s32 a);
extern void  func_28FD10(void *w, u16 id, s32 a, s32 b, s32 c);
extern void  normal_TransHunterBountyListFill_51efe0(s32 a);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);

s32 normal_TransHunterBountyListState_51f630(void *unused, s32 close)
{
    s32   code;
    Rec  *rec;
    Ent  *e;
    Slot *sl;

    if (close != 0) {
        func_28EA90(D_00484720, 9, 0);
        func_290690(D_00484710, 0x7637, D_0047D248, D_0047D9D4, -1.0f);
        func_290690(D_00484710, 0x764D, 1.0f, D_0047D9D4, -1.0f);
    } else {
        code = func_28E170(D_00484720, D_004B2570, 0, 0);
        rec = func_28EC60(D_00484720);
        if (code == 1) {
            e = func_1FEDE0();
            sl = func_28F2B0(D_00484710, 0x763C, 0);
            if (sl == NULL) {
                return 0;
            }
            func_3E8B80(e, sl->f08);
            func_291250(D_00484710, 0x763C, 1, e->f18->f180);
            normal_TransHunterBountyMarkReported_51e480();
            func_1CD960(func_1F59D0(), 0, 0xF, 0.0f);
            func_207340(0x324, 0, 1.0f);
            func_3E8CE0(e);
            func_3E9050(e);
            D_004848BC = 3;
            D_004848C0 = 0x16;
            func_28EDE0(D_0048470C, 0x13, 0);
        } else if (code == 2) {
            func_28EDE0(D_0048470C, 0x12, 0);
        } else if (func_1839F0(D_004B2570, 0x8000) != 0) {
            if (rec->f12 > 0 || rec->f16 > 0) {
                func_28E9E0(D_00484720, 0);
            }
            if (rec->f16 > 0) {
                rec->f16 = rec->f16 - (s16)(rec->f0A + 1);
                if (rec->f16 < 0) {
                    rec->f16 = 0;
                    rec->f12 = 0;
                    func_28FD10(D_00484710, 0x7637, 0x1E, rec->f02, 0);
                }
                normal_TransHunterBountyListFill_51efe0(rec->f16);
            } else {
                rec->f16 = 0;
                rec->f12 = 0;
                func_28FD10(D_00484710, 0x7637, 0x1E, rec->f02, 0);
            }
            if (rec->f16 < 0) {
                rec->f16 = 0;
            }
            func_290F50(D_00484710, 0x763E, 0,
                        (s32)((f32)rec->f16 * D_004848B8), 0, D_0047D9D4);
        } else if (func_1839F0(D_004B2570, 0x2000) != 0) {
            if (rec->f12 < rec->f0A || rec->f16 < rec->f0E - rec->f0A) {
                func_28E9E0(D_00484720, 0);
            }
            if (rec->f16 < rec->f0E - rec->f0A) {
                rec->f16 = rec->f16 + (s16)(rec->f0A + 1);
                if (rec->f16 > rec->f0E - rec->f0A) {
                    rec->f12 = rec->f0A;
                    rec->f16 = rec->f0E - rec->f0A;
                    func_28FD10(D_00484710, 0x7637, 0x1E,
                                rec->f02 + rec->f12 * rec->f06, 0);
                }
                normal_TransHunterBountyListFill_51efe0(rec->f16);
            } else {
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                func_28FD10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
            }
            if (rec->f16 < 0) {
                rec->f16 = 0;
            }
            func_290F50(D_00484710, 0x763E, 0,
                        (s32)((f32)rec->f16 * D_004848B8), 0, D_0047D9D4);
        } else if ((D_00484720->f14 & 1) &&
                   func_1839F0(D_004B2570, 0x1000) != 0 &&
                   func_183DD0(D_004B2570, 0x1000) == 0) {
            if (rec->f12 == 0 && rec->f16 == 0 && rec->f0E > 0) {
                func_28E9E0(D_00484720, 0);
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                func_28FD10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
                normal_TransHunterBountyListFill_51efe0(rec->f16);
                func_290F60(D_00484710, 0x763E, 0,
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
                func_28FD10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
                normal_TransHunterBountyListFill_51efe0(rec->f16);
                func_290F60(D_00484710, 0x763E, 0,
                            (s32)((f32)rec->f16 * D_004848B8));
            }
        }
    }
    return 1;
}
