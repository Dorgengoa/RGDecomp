#include "types.h"
/* normal 0x00520CA0 */

typedef struct Sel { u8 pad00[0x14]; s16 f14; s16 f16; } Sel;
typedef struct Cur { u8 pad00[0x10]; s16 f10; s16 f12; } Cur;
typedef struct Act { u8 pad00[0x18]; void *f18; } Act;
typedef struct Cfg { u8 pad00[0x11]; s8 f11; } Cfg;

extern u8        D_00528030[];
extern u8        D_00528060[];
extern const s16 D_00526090[];
extern const u8  D_004B2570[];

extern s16   D_00480798[4];       /* gp - 0x49D8, declared short to stay in small data */
extern s32   D_00484948;          /* gp - 0x828  */
extern s32   D_00484928;          /* gp - 0x848  */
extern Cfg  *D_00484934;          /* gp - 0x83C  */
extern void *D_00484920;          /* gp - 0x850  */
extern s32   D_0048494C;          /* gp - 0x824  */
extern s32   D_00484950;          /* gp - 0x820  */

extern void  func_28EA90(u8 *w, u16 id, s32 a);
extern Sel  *func_28EA40(u8 *w, u16 id);
extern void  func_28DB40(u8 *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void *func_1F5BE0(void);
extern f32   func_1CEBA0(void *a);
extern void  normal_ThinkMenuPromptScrollStep_521660(f32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32   func_28E170(u8 *w, const u8 *p, s32 a, s32 b);
extern Cur  *func_28EC60(u8 *w);
extern Act  *func_1FEDE0(void);
extern s32   func_3C86E0(void *a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_ThinkMenuGridState_520ca0(void *a, s32 b)
{
    s16 b2[8];
    s16 b1[16];
    const s16 *src1;
    s16 *dst1;
    const s16 *src2;
    s16 *dst2;
    s32 i;
    Sel *sel;
    Cur *cur;
    Act *act;
    s32 st;

    if (b != 0) {
        func_28EA90(D_00528030, 0x7531, 0);
        sel = func_28EA40(D_00528030, 0x7531);
        src1 = D_00526090;
        dst1 = b1;
        for (i = 9; i > 0; i--) {
            *dst1 = *src1;
            src1++;
            dst1++;
        }
        src2 = D_00480798;
        dst2 = b2;
        for (i = 5; i > 0; i--) {
            *dst2 = *src2;
            src2++;
            dst2++;
        }
        func_28DB40(D_00528060, 0x753B, b1[sel->f14], b2[sel->f16],
                    0x2A, 0x30, 0x46, 0x4B);
    }
    normal_ThinkMenuPromptScrollStep_521660(func_1CEBA0(func_1F5BE0()));
    if (D_00484948 == 0) {
        func_28EDE0(&D_00484928, 0x7533, 1);
    }
    st = func_28E170(D_00528030, D_004B2570, 6, 0);
    cur = func_28EC60(D_00528030);
    if (st == 1) {
        act = func_1FEDE0();
        if (func_3C86E0(act->f18, 0, D_00484934->f11, cur->f10, cur->f12, 0) != 0) {
            func_290690(D_00484920, 0x7544, 0.0f, -0.1f, -1.0f);
            func_28EDE0(&D_00484928, 0x7534, 0);
        }
    } else if (st == 2) {
        D_00484948 = 1;
        D_0048494C = -1;
        D_00484950 = -1;
        func_28EDE0(&D_00484928, 0x7533, 1);
    }
    return 1;
}
