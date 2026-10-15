#include "types.h"

extern s32 Strcasecmp_1345b8(s32, void *);
extern u8 D_00495FD0[];

struct Obj0 {
    u8 pad000[0x120];
    s32 m120;
};

void *FileReqFindByName_182720(s32 p0)
{
    s32 i;
    struct Obj0 *e;

    i = 0;
    e = (struct Obj0 *)D_00495FD0;
    while (i < 0x20) {
        if (e->m120 != 0) {
            if (Strcasecmp_1345b8(p0, (u8 *)e + 0x8C) == 0)
                return e;
        }
        i = i + 1;
        e = (struct Obj0 *)((u8 *)e + 0x128);
    }
    return 0;
}
