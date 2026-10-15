#include "types.h"

typedef struct Ctx {
    u8    pad00[0x70];
    u8    f70;
    u8    pad71[0x1B];
    void *f8C;
    void *f90;
} Ctx;

extern Ctx *D_00484A5C;                         /* _gp - 0x714 */
extern const u8 D_004B2570[];

extern void func_28EA90(void *w, s32 id, s32 a);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern s32  func_28E170(void *w, const u8 *p, s32 a, s32 b);
extern void factory_FactoryHelpPageLoadPoll_4f1ce0(Ctx *c);
extern void factory_FactoryHelpPageArrowBlink_4f1510(Ctx *c);
extern void factory_FactoryHelpRelease_4f1a40(Ctx *c);
extern void factory_FactoryMenuTexReload_4ebf90(void);
extern void factory_FactoryHelpPageClose_4f16b0(Ctx *c);
extern void factory_FactoryHelpTopicOpen_4f1ab0(Ctx *c);
extern void factory_FactoryHelpPageNext_4f17e0(Ctx *c);

s32 factory_FactoryHelpStateTick_4ecee0(s32 unused, s32 start)
{
    Ctx *c;
    s16 sel;
    s32 r;

    if (start != 0) {
        func_28EA90(D_00484A5C->f8C, 0x8944, 1);
    }
    factory_FactoryHelpPageLoadPoll_4f1ce0(D_00484A5C);
    factory_FactoryHelpPageArrowBlink_4f1510(D_00484A5C);
    r = func_28E170(D_00484A5C->f8C, D_004B2570, 0, 0);
    if (r == 2) {
        c = D_00484A5C;
        switch (c->f70) {
        case 0:
            sel = 0;
            break;
        case 1:
            sel = 1;
            break;
        default:
            sel = -1;
            break;
        }
        if (sel == 0) {
            func_28EDE0(c->f90, 0x89D0, 0);
            factory_FactoryHelpRelease_4f1a40(D_00484A5C);
            factory_FactoryMenuTexReload_4ebf90();
        } else if (sel == 1) {
            factory_FactoryHelpPageClose_4f16b0(c);
        }
    } else if (r == 1) {
        c = D_00484A5C;
        switch (c->f70) {
        case 0:
            sel = 0;
            break;
        case 1:
            sel = 1;
            break;
        default:
            sel = -1;
            break;
        }
        if (sel == 0) {
            factory_FactoryHelpTopicOpen_4f1ab0(c);
        } else if (sel == 1) {
            factory_FactoryHelpPageNext_4f17e0(c);
        }
    }
    return 1;
}
