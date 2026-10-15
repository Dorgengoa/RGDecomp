#include "types.h"

typedef struct Slot {
    s32 f0;
    s32 f4;
} Slot;

extern Slot  D_00480810[1];                     /* _gp - 0x4960 */
extern void *D_00484A2C;                        /* _gp - 0x744  */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_00484A70;                        /* _gp - 0x700  */
extern void *D_00484A88;                        /* _gp - 0x6E8  */
extern u8    D_00484A64;                        /* _gp - 0x70C  */
extern u8    D_00484A68;                        /* _gp - 0x708  */
extern void *D_004807F8;                        /* _gp - 0x4978 */

extern const u8 D_0050CA70[];
extern const u8 D_0050CA88[];
extern const u8 D_0050CAA0[];

extern void *func_1F59D0(void);
extern s32   func_1CD4F0(void *h, s32 id);
extern void  func_14D8E0(void *p);
extern void *func_1CD490(void *h, s32 id, s32 *sz);
extern void *func_15DE40(void);
extern void  func_289C60(void *a, s32 b, void *c, s32 d);
extern void  func_1594D0(void *a, void *b, s32 c, void *d, s32 e);
extern void *func_206A40(void);
extern void  func_42B840(void *a, s32 b, s32 c, void *d, void *e);
extern void *func_202A50(void *a, const u8 *b, void *c);
extern void  func_202BE0(void *a, const u8 *b, void *c, s32 d, void *e);
extern void  func_1CD340(void *h, s32 id);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  factory_FactoryMenuBuildWidgets_4ea1d0(void);

s32 factory_FactoryMenuResReady_4ec0e0(void)
{
    void *h;
    s32   total;
    s32   i;
    Slot *e;
    void *p;
    void *q;
    s32   sz;
    s32   k;

    h = func_1F59D0();
    total = 0;
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        if (e->f4 == 0) {
            if (e->f0 != -1) {
                e->f4 = func_1CD4F0(h, e->f0);
                if (e->f4 == 1) {
                    if (i != 1) {
                        func_14D8E0(D_00484A2C);
                        p = func_1CD490(h, e->f0, &sz);
                    }
                    if (i == 1) {
                        p = func_1CD490(h, e->f0, &sz);
                        q = func_15DE40();
                        func_289C60(p, sz, D_00484A88, 0xF081);
                        func_1594D0(q, D_00484A88, 0x32E, D_00484A30, 0);
                    } else if (i == 0) {
                        func_42B840(func_206A40(), 2, 5, D_00484A2C, p);
                        D_00484A70 = func_202A50(p, D_0050CA70, D_00484A2C);
                        func_202BE0(p, D_0050CA88, D_00484A2C, 0x32D, 0);
                        func_202BE0(p, D_0050CAA0, D_00484A2C, 0x32F, D_00484A2C);
                        factory_FactoryMenuBuildWidgets_4ea1d0();
                    }
                    func_1CD340(h, e->f0);
                    e->f0 = -1;
                }
            }
        }
    }
    for (k = 0; k < 2; k++) {
        total += D_00480810[k].f4;
    }
    if (total == 2) {
        D_00484A64 = 1;
        D_00484A68 = 1;
        func_28EDE0(D_004807F8, 0x88B8, 0);
        return 1;
    }
    return 0;
}
