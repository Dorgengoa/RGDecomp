/* rgp:protos */
#define RGP_SELF_McLoadStep_373890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8 pad[0x1C];
} Ent;

typedef struct Strm {
    u8 pad0[0x4A4];
    Ent ent[2];
    u8 pad4DC[4];
    s32 state;
    u8 pad4E4[4];
    s32 fd;
    s16 f4EC;
    s16 f4EE;
    s16 f4F0;
    u8 pad4F2[0x1A];
    s32 f50C;
    u8 pad510[4];
    s32 f514;
    s32 f518;
    s32 f51C;
} Strm;

extern s32 sceMcOpen_12ca58(s32, s32, void *, s32);
extern s32 sceMcClose_12cbb8(s32);
extern s32 sceMcRead_12ce08(s32, s32, s32);
extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004658F8[];
extern void (*D_0047FAA4)(Strm *, s32, s32);

s32 McLoadStep_373890(Strm *self)
{
    s32 spBC;
    s32 spB8;
    s32 spB4;
    u8 sp30[0x84] __attribute__((aligned(16)));
    Ent *ent;
    s32 r;
    s32 n;

    GetGameData_1fede0();
    ent = &self->ent[self->f4EC];
    switch (self->state) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) == 0) {
            break;
        }
        if (McCardIsReady_376280(ent, 1) == 0) {
            self->f4F0 = 8;
            return 1;
        }
        SaveMgrClearResult_3759d0(self);
        self->f518 = D_004658F8[0];
        self->f51C = 0;
        self->f514 = self->f50C;
        MemcardBuildSavePath_376380(self->f4EE, sp30);
        r = sceMcOpen_12ca58(self->f4EC, 1, sp30, 1);
        self->state++;
        if (r != 0 && r != -200) {
            self->f4F0 = 12;
            return 1;
        }
        break;
    case 1:
        if (sceMcSync_12d098(1, &spB8, &spBC) == 0) {
            break;
        }
        if (spBC < 0) {
            McSetErrorResult_375890(self, spBC);
            return 1;
        }
        self->fd = spBC;
        n = 0x800;
        if (self->f518 < 0x800) {
            n = self->f518;
        }
        if (sceMcRead_12ce08(self->fd, self->f514, n) == 0) {
            self->state++;
            break;
        }
        self->f4F0 = 2;
        return 1;
    case 2:
        if (sceMcSync_12d098(1, &spB8, &spB4) == 0) {
            break;
        }
        if (spB4 < 0) {
            McSetErrorResult_375890(self, spB4);
            *((s16 *)SaveMgrGetResult_375a00(self)) = 2;
            return 1;
        }
        self->f51C += spB4;
        SaveProgressAdd_373650(self, spB4);
        if (self->f51C >= self->f518 || spB4 == 0) {
            if (sceMcClose_12cbb8(self->fd) == 0) {
                self->state++;
                break;
            }
            *((s16 *)SaveMgrGetResult_375a00(self)) = 2;
            return 1;
        } else {
            sceMcRead_12ce08(self->fd, self->f514 + self->f51C, 0x800);
        }
        break;
    case 3:
        if (sceMcSync_12d098(1, &spB8, &spBC) == 0) {
            break;
        }
        if (spBC < 0) {
            McSetErrorResult_375890(self, spBC);
            return 1;
        }
        D_0047FAA4(self, self->f50C, self->f518);
        SaveSetLastSlot_376210(self->f4EC, self->f4EE);
        return 1;
    }
    return 0;
}
