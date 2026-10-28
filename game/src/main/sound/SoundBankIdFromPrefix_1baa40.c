/* rgp:protos */
#define RGP_SELF_SoundBankIdFromPrefix_1baa40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(s32, void *);

extern u8 D_0045ABA8[];
extern u8 D_0045ABB0[];
extern u8 D_0045ABB8[];
extern u8 D_0045ABC0[];
extern u8 D_0045ABC8[];

s32 SoundBankIdFromPrefix_1baa40(s32 p0)
{
    s32 v;

    if (strcmp(p0, D_0045ABA8) == 0) {
        v = 9;
    } else if (strcmp(p0, D_0045ABB0) == 0) {
        v = 3;
    } else if (strcmp(p0, D_0045ABB8) == 0) {
        v = 4;
    } else if (strcmp(p0, D_0045ABC0) == 0) {
        v = 6;
    } else if (strcmp(p0, D_0045ABC8) == 0) {
        v = 8;
    } else {
        v = -1;
    }
    if (v < 0) {
        return -1;
    }
    return ((v & 0xFF) << 0x18);
}
