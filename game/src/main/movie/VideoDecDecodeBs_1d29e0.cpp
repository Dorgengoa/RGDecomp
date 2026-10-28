/* rgp:spin */ extern "C" void rg_spin_hint(unsigned int); extern "C" void rg_spin_halt(unsigned int);
#line 1
#include "types.h"

struct Ent48 {
    u8 pad[0x40];
    s32 m40;
    s32 m44;
};

struct Ctx {
    s32 m0;
    s32 m4;
    s32 m8;
};

extern "C" void MpegGetPicture_111148(Ctx *, s32, s32);
extern "C" void MpegReset_1111e8(Ctx *);
extern "C" bool MpegIsEnd_111268(Ctx *);
extern "C" void GsUploadImage16Blocks_1d27a0(s32, s32, s32, s32, s32);
extern "C" void ThreadYield_1d2b70(void);
extern "C" s32 VoBufGetData_1d49c0(s32 *);
extern "C" void VoBufIncCount_1d4a10(s32 *);
extern "C" s32 D_004817CC;
extern "C" s32 D_004817D0;
extern "C" s32 D_004B3330[4];
extern "C" Ent48 *D_004B3338[4];
extern "C" s32 D_004B3344[4];

extern "C" s32 VideoDecDecodeBs_1d29e0(Ctx *c)
{
    s32 buf;
    s32 i;

    while (!MpegIsEnd_111268(c)) {
        while ((!(buf = VoBufGetData_1d49c0(D_004B3330))) && (rg_spin_hint(0x001D2A00), 1)) {
            ThreadYield_1d2b70();
        }
        MpegGetPicture_111148(c, buf, D_004817CC / 16 * D_004817D0 / 16);
        if (c->m8 == 0) {
            for (i = 0; i < D_004B3344[0]; i++) {
                GsUploadImage16Blocks_1d27a0(D_004B3338[0][i].m40, D_004B3330[0] + i * 0xE0000, 0, c->m0, c->m4);
                GsUploadImage16Blocks_1d27a0(D_004B3338[0][i].m44, D_004B3330[0] + i * 0xE0000, 0, c->m0, c->m4);
            }
        }
        VoBufIncCount_1d4a10(D_004B3330);
        ThreadYield_1d2b70();
    }
    MpegReset_1111e8(c);
    return 1;
}
