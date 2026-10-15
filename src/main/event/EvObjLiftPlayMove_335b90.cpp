#include "types.h"

class Obj00335B90 {
public:
    u8 pad0[0xD0];
    s32 unkD0;
    u8 padD4[0xDC - 0xD4];
    virtual void v0();
    virtual void v1();
    virtual void v2(s32);
    u8 padE0[0xF0 - 0xE0];
    s32 unkF0;
    u8 padF4[0xF8 - 0xF4];
    char unkF8[0x108 - 0xF8];
    s16 unk108;
    s16 unk10A;
    s16 unk10C;
    s16 unk10E;
};

extern "C" {
extern s32 EventPathRecFindPathByName_2e4040(s32, char *);
extern s32 EventPathGetTotalLength_2e4550(s32);
extern s32 EvObjLiftSnapClosed_335b50(void);
extern char *strcpy(char *, const char *);
extern char D_00462570[];
extern char D_00462578[];
extern char D_00462580[];
}

extern "C" s32 EvObjLiftPlayMove_335b90(Obj00335B90 *arg0, s32 arg1, s32 arg2)
{
    s32 h;

    if (arg0->unk10C == arg1) {
        return 0;
    }
    if (arg0->unkD0 & 0x80000) {
        h = EventPathRecFindPathByName_2e4040(arg0->unkF0, D_00462570);
        if (h == 0) {
            return 0;
        }
        arg0->unk10C = arg2;
        arg0->unk10E = arg1;
        arg0->unk10A = EventPathGetTotalLength_2e4550(h) >> 1;
        if (arg0->unkD0 & 0x1000) {
            if (arg2 == 0) {
                strcpy(arg0->unkF8, D_00462578);
            } else {
                strcpy(arg0->unkF8, D_00462580);
            }
        } else {
            strcpy(arg0->unkF8, D_00462570);
        }
        arg0->unk108 = 7;
        arg0->v2(0);
        goto one;
    }
    if (EvObjLiftSnapClosed_335b50() == 0) {
        return 0;
    }
    arg0->unk10A = 0x7FFF;
one:
    return 1;
}
