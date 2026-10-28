/* rgp:protos */
#define RGP_SELF_DebugFontLoad_313130 1
#define RGP_SELF_reset 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00462318[];
extern u8 D_00462328[];
extern Ent D_004E74F0[128];
extern s32 D_004E7AF0[];
extern s32 D_004E7AF4[];
extern s32 D_004E7AF8[];
extern s32 D_004E7AFC[];
extern s32 D_004E7B00[];
extern s32 D_004E7B04[];
extern s32 D_004E7B08[];
extern s32 D_004E7B0C[];
extern s32 D_004E7B10[];
extern s32 D_004E7B14[];
extern s32 D_004E7B20[];
extern s32 D_004E7B24[];
extern s32 D_004E7B28[];
extern s32 D_004E7B2C[];
extern s32 D_004E7B30[];

static inline void reset(void) {
    s32 i;
    D_004E7B00[0] = 0;
    D_004E7AFC[0] = 0;
    D_004E7B04[0] = 0x10;
    D_004E7B08[0] = 0x14;
    D_004E7B14[0] = 4;
    D_004E7AF8[0] = 0;
    D_004E7AF0[0] = 0;
    D_004E7B20[0] = 0x80;
    D_004E7B24[0] = 0x80;
    D_004E7B28[0] = 0x80;
    D_004E7B2C[0] = 0xFF;
    D_004E7B30[0] = 0x3F800000;
    for (i = 0; i < 128; i++) {
        D_004E74F0[i].b = -1;
        D_004E74F0[i].a = -1;
        D_004E74F0[i].c = 0;
    }
}

s32 DebugFontLoad_313130(s8 *arg0, s32 arg1, s32 arg2) {
    s32 h;
    s32 n;
    s32 size;

    reset();
    h = GetDrawCtxNameTable_15de40();
    MemStackAlign64_14d8e0(arg0);
    n = MemStackPeekQw_14d9d0(arg0, 1);
    if (ResidentFileReadLocalizedMaybe_1c2860(D_00462318, n, &size) == 0) {
        return 0;
    }
    MemStackAllocAligned64_14da10(arg0, size / 16 + 1);
    NameTableRegisterImArchive_1594d0(h, n, arg2, arg0, 0);
    reset();
    D_004E7AF8[0] = ((s32)NameTableFindByName_159fb0(h, D_00462328, arg2));
    D_004E7AF4[0] = arg2;
    D_004E7B04[0] = 8;
    D_004E7B08[0] = 0x12;
    D_004E7B0C[0] = 0x10;
    D_004E7B10[0] = 0x14;
    D_004E7B14[0] = 8;
    return 1;
}
