#include "types.h"
/* normal 0x005201A0 -- the shop caption page tick.  `daddu $16,$2,$0` sits in
 * func_28EC60's DELAY SLOT, so `m` is func_28E170's result and the pointer the
 * f10 test reads is func_28EC60's -- the classic wrong-call misread.
 * `addiu $4,$28,-0x848` is the ADDRESS of D_00484928, so that global has to be
 * declared at or under the 8-byte small-data threshold or the addiu becomes a
 * lui/%lo pair. */

typedef struct Box  { u8 pad00[8]; s16 f08; u8 pad0A[0x28 - 0x0A]; s16 f28; } Box;
typedef struct Hdl  { u8 pad00[0x14]; s16 f14; s16 f16; } Hdl;
typedef struct Vw   { u8 pad00[0x10]; s16 f10; } Vw;
typedef struct Sess { u8 pad00[0x11]; s8 f11; } Sess;
typedef struct Sub  { s16 f00; } Sub;
typedef struct Rec  { u8 pad00[4]; s16 f04; u8 pad06[0x10 - 0x06]; Sub *f10; } Rec;
typedef struct Root { u8 pad00[0x18]; void *f18; } Root;

extern const u8 D_004B2570;
extern const u8 D_00528030[];

extern s32   D_00484948;          /* gp - 0x828 */
extern s32   D_0048494C;          /* gp - 0x824 */
extern s32   D_00484950;          /* gp - 0x820 */
extern void *D_00484920;          /* gp - 0x850 */
extern void *D_00484928;          /* gp - 0x848 */
extern Sess *D_00484934;          /* gp - 0x83C */

extern f32   func_1CEBA0(void *p);
extern void *func_1F5BE0(void);
extern Root *func_1FEDE0(void);
extern s32   func_28E170(const u8 *p, const u8 *q, s32 c, s32 d);
extern Hdl  *func_28EA40(const u8 *p, s32 id);
extern void  func_28EA90(const u8 *p, s32 id, s32 a);
extern Vw   *func_28EC60(const u8 *p);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern Box  *func_28FE10(void *p, u16 id, s32 n);
extern Rec  *func_3C86E0(void *p, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  normal_ThinkMenuPromptScrollStep_521660(f32 x);

s32 normal_ThinkMenuConfirmState_5201a0(void *a, s32 b)
{
    Root *h;
    Hdl  *w;
    Box  *q;
    Rec  *e;
    Vw   *r;
    s32   m;

    if (b != 0) {
        func_28EA90(D_00528030, 0x7532, 0);
        func_28EA40(D_00528030, 0x7532)->f14 = 0;
        q = func_28FE10(D_00484920, 0x753E, 0);
        if (q == 0) {
            return 0;
        }
        q->f08 = 0x4C;
        q->f28 = 0x18;
    }
    normal_ThinkMenuPromptScrollStep_521660(func_1CEBA0(func_1F5BE0()));
    m = func_28E170(D_00528030, &D_004B2570, 0, 0);
    r = func_28EC60(D_00528030);
    if (m == 1) {
        if (r->f10 == 0) {
            h = func_1FEDE0();
            w = func_28EA40(D_00528030, 0x7531);
            e = func_3C86E0(h->f18, 0, D_00484934->f11, w->f14, w->f16, 0);
            if (e != 0) {
                D_0048494C = e->f10->f00;
                D_00484950 = e->f04;
                D_00484948 = 0;
            }
        } else if (r->f10 == 1) {
            D_00484948 = 1;
        }
        func_28EDE0(&D_00484928, 0x7536, 0);
    } else if (m == 2) {
        D_00484948 = 1;
        func_28EDE0(&D_00484928, 0x7536, 0);
    }
    return 1;
}
