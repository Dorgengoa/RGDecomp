#include "types.h"
/* normal 0x005194F0 -- travel-confirm dialog state machine on D_0048480C
 * (0/1), sibling of title_TitleLoadCardScanTickCb_4edec0's two-state confirm pattern.  Case 0
 * calls func_37B970() TWICE (short-circuit `||`, not cached) since its
 * result isn't needed again; case 1 caches it in `r` because the widget
 * block below re-tests `r != 7`. */

typedef struct Actor005194F0 {
    u8  pad000[0x4EC];
    s16 f4EC;
} Actor005194F0;

typedef struct Wid005194F0 {
    u8  pad000[0x16];
    s16 field016;
    u8  pad018[0x2];
    s16 field01A;
} Wid005194F0;

extern s8              D_0048480C;     /* gp - 0x964 */
extern void            *D_004847D8;    /* gp - 0x998 */
extern Actor005194F0   *D_00484724;    /* gp - 0xA4C */

extern void  normal_TransSaveSlotCursorBob_518990(void *a, void *b, s32 c);
extern s32   func_37BAA0(void);
extern u8    func_37B9B0(s32 a);
extern void  normal_TransSaveSetError_51a000(s32 a);
extern s32   func_37B970(void);
extern void  func_37B9E0(s32 a);
extern s32   func_37B980(void *p);
extern s32   func_373340(void *p);
extern void  normal_TransSaveShowMsg_519ff0(s32 a);
extern Wid005194F0 *func_28EA40(void *a, s32 id);
extern void  func_28EB40(void *a, void *b);
extern s32   func_376200(void);
extern void  func_37BA10(s32 *out);
extern void  func_28EA90(void *a, s32 id, s32 c);
extern void  normal_TransSavePanelFade_518700(s32 a);
extern void  func_376B20(s32 a);

s32 normal_TransSaveCardScanTickCb_5194f0(void *a, void *b)
{
    s32 r;
    s32 r2;
    s32 n;
    s32 f;
    s32 tmp;
    Wid005194F0 *o;
    Wid005194F0 *o2;

    normal_TransSaveSlotCursorBob_518990(a, b, 0);
    switch (D_0048480C) {
    case 0:
        if (func_37BAA0() == 0) {
            break;
        }
        if ((func_37B9B0(0) & 0xFF) == 0) {
            normal_TransSaveSetError_51a000(8);
            return 1;
        }
        if (func_37B970() == 0 || func_37B970() == 7) {
            func_37B9E0(3);
            D_0048480C = D_0048480C + 1;
        } else {
            normal_TransSaveSetError_51a000(5);
        }
        break;
    case 1:
        if (func_37BAA0() == 0) {
            break;
        }
        r = func_37B970();
        if (r == 0 || r == 7) {
            f = D_00484724->f4EC;
            r2 = func_37B980((u8 *)D_00484724 + 0x4A4 + f * 0x1C);
            n = func_373340(D_00484724);
            if (r2 == 2 && n <= 0) {
                normal_TransSaveSetError_51a000(4);
                break;
            }
            normal_TransSaveShowMsg_519ff0(-1);
            o = func_28EA40(D_004847D8, 4);
            if (o != 0) {
                func_28EB40(D_004847D8, o);
                if (r != 7) {
                    tmp = 0;
                    o2 = func_28EA40(D_004847D8, 2);
                    if (o2 != 0 && o2->field016 == func_376200()) {
                        func_37BA10(&tmp);
                    }
                    o->field016 = tmp;
                    while (o->field016 >= 3) {
                        o->field016 -= 1;
                        o->field01A += 1;
                    }
                }
            }
            func_28EA90(D_004847D8, 4, 0);
            normal_TransSavePanelFade_518700(1);
            func_376B20(0x23);
        } else {
            normal_TransSaveSetError_51a000(5);
        }
        break;
    }
    return 1;
}
