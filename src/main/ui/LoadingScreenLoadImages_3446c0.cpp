/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/LoadingScreenLoadImages_3446c0.s and build/b_drafts/LoadingScreenLoadImages_3446c0.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

struct Buf {
    u8 pad0[0x28];
    u8 *base;
    s32 pos;
    u8 pad30[0x2C];
};

extern "C" {
u8 *GetDrawCtx_15de80(void);
void MemStackCtor_14e030(Buf *);
void MemStackInit_14d810(Buf *, s32, s32);
void MemStackAlign64_14d8e0(Buf *);
void MemStackAllocQw_14d950(Buf *, s32);
s32 ResidentFileReadLocalizedMaybe_1c2860(char *, u8 *, s32 *);
void NameTableRegisterImArchive_1594d0(s32, u8 *, s32, s32, s32);
s32 IsTgsDemoBuild_207f20(void);
s16 *SysGetModeMsg_1c39b0(void);
extern s32 D_004E896C[];
extern s32 D_004E8970[];
extern s32 D_004E8974[];
extern u8 D_0047F654;
extern char *D_00482D8C;
extern s32 D_00482D78;
extern s32 D_0045B090[];
extern s32 D_0045B098[];
extern char D_00462870[];
extern char D_00462890[];
extern char D_004628A8[];
extern char D_004628C0[];
extern char D_004628D8[];
}

extern "C" void LoadingScreenLoadImages_3446c0(void)
{
    Buf b;
    s32 size;
    s32 dst;
    u8 *p;
    s16 *q;
    bool ok;

    dst = *(s32 *)(GetDrawCtx_15de80() + 0x3BA0);
    MemStackCtor_14e030(&b);
    MemStackInit_14d810(&b, D_004E8970[0], D_004E8974[0]);
    MemStackAlign64_14d8e0(&b);
    D_0047F654 = 1;
    D_00482D8C = 0;
    p = b.base + b.pos * 16;
    if (ResidentFileReadLocalizedMaybe_1c2860(D_00462870, p, &size)) {
        MemStackAllocQw_14d950(&b, size / 16 + 1);
        NameTableRegisterImArchive_1594d0(dst, p, D_004E896C[0], 0, 0);
    }
    if (IsTgsDemoBuild_207f20()) {
        p = b.base + b.pos * 16;
        if (ResidentFileReadLocalizedMaybe_1c2860(D_00462890, p, &size)) {
            MemStackAllocQw_14d950(&b, size / 16 + 1);
            NameTableRegisterImArchive_1594d0(dst, p, D_004E896C[0], 0, 0);
            D_00482D8C = D_004628A8;
        }
    }
    q = SysGetModeMsg_1c39b0();
    if (q != 0) {
        ok = false;
        if (q[0] == 2) {
            ok = true;
        } else if (q[0] == 6 && q[2] == 4 && (q[5] == D_0045B090[0] || q[5] == D_0045B098[0])) {
            ok = true;
        }
        if (ok) {
            p = b.base + b.pos * 16;
            if (ResidentFileReadLocalizedMaybe_1c2860(D_004628C0, p, &size)) {
                MemStackAllocQw_14d950(&b, size / 16 + 1);
                NameTableRegisterImArchive_1594d0(dst, p, D_004E896C[0], 0, 0);
                D_0047F654 = 0;
                D_00482D8C = D_004628D8;
            }
        }
    }
    D_00482D78 = 0;
}
