#include "types.h"
/* normal 0x005173C0 -- label bring-up: set the string from the name table,
 * and when the item type is 10 append the count through the format string. */

typedef struct Act { u8 pad00[0x4CA0]; s16 f4CA0; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;

extern char       D_00527F60[];
extern const char D_00526720[];

extern void *D_004846E8;          /* gp - 0xA88 */
extern void *D_00484774;          /* gp - 0x9FC */

extern void  func_290010(void *w, void *p, s32 a, s32 b);
extern Ent  *func_1FEDE0(void);
extern char *func_28AA30(void *t, s32 k);
extern void  func_28F510(void *w, void *p, const char *s, s32 a);
extern s32   func_3CB150(Act *p);
extern s32   func_3CB000(Act *p);
extern void  func_1343B8(char *dst, const char *fmt, const char *s, s32 n);
extern void  func_290A80(void *w, void *p, s32 a, s32 b);
extern void  func_290A40(void *w, void *p, s32 col, s32 a);

void normal_TransMenuLocationNameSet_5173c0(void *p)
{
    Ent *e;
    s32  n;

    func_290010(D_004846E8, p, 1, -1);
    e = func_1FEDE0();
    func_28F510(D_004846E8, p, func_28AA30(D_00484774, e->f18->f4CA0), 0);
    if (func_3CB150(e->f18) == 10) {
        n = func_3CB000(e->f18);
        if (n > 0) {
            func_1343B8(D_00527F60, D_00526720,
                        func_28AA30(D_00484774, e->f18->f4CA0), n);
            func_28F510(D_004846E8, p, D_00527F60, 0);
        }
    }
    func_290A80(D_004846E8, p, 2, 0);
    func_290A40(D_004846E8, p, 0xFF303030, 0);
}
