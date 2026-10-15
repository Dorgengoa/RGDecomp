#include "types.h"

typedef struct Ent {
    s32 f00;
    s32 f04;
} Ent;                                          /* 8 */

extern Ent   D_00480810[1];                     /* _gp - 0x4960 */
extern s32   D_00484A70;                        /* _gp - 0x700  */
extern void *D_00484A58;                        /* _gp - 0x718  */
extern void *D_00484A2C;                        /* _gp - 0x744  */
extern void *D_00484A30;                        /* _gp - 0x740  */
extern u8    D_00484A68;                        /* _gp - 0x708  */

extern void *func_15DE40(void);
extern void *func_1F59D0(void);
extern void  func_1CD340(void *h, s32 id);
extern u8 D_004B2570[0x10];

extern void  func_183960(void *p);
extern void  func_183940(void *p);
extern void  func_14D830(void *h);
extern void  func_158AC0(void *w, s32 id);

void factory_FactoryMenuRelease_4ec4e0(void)
{
    void *w;
    void *h;
    s32   i;
    Ent  *e;

    w = func_15DE40();
    for (i = 0; i < 2; i++) {
        e = &D_00480810[i];
        if (e->f04 >= 0) {
            if (e->f00 != -1) {
                h = func_1F59D0();
                func_1CD340(h, e->f00);
                e->f00 = -1;
                e->f04 = 0;
            }
        }
    }
    D_00484A70 = 0;
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    D_00484A58 = 0;
    if (D_00484A2C != 0) {
        func_14D830(D_00484A2C);
    }
    if (D_00484A30 != 0) {
        func_14D830(D_00484A30);
    }
    func_158AC0(w, 0x32D);
    func_158AC0(w, 0x32F);
    func_158AC0(w, 0x32E);
    D_00484A68 = 0;
}
