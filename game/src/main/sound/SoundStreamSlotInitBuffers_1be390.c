/* rgp:protos */
#define RGP_SELF_SoundStreamHandleCreate_1bf990 1
#define RGP_SELF_SoundStreamSlotInitBuffers_1be390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define ALIGN64(x) (((x) + 0x3F) / 64 * 64)

typedef union {
    s32 w;
    struct {
        u16 lo;
        u16 hi;
    } h;
} Ret001BE390;

typedef struct {
    u8 pad0[0x78];
    u8 *unk78;
} Sub001BE390;

typedef struct {
    s32 unk0;
    Ret001BE390 unk4;
    Sub001BE390 *unk8;
    u8 unkC[4];
    u8 *unk10;
    u8 pad14[0x38];
    u8 unk4C;
    u8 pad4D[0x27];
    f32 unk74;
    f32 unk78;
    u8 pad7C[0x68];
    s32 unkE4;
    f32 unkE8;
    s32 unkEC;
    u8 unkF0;
    u8 padF1[3];
    s32 unkF4;
    u8 *unkF8[2];
    s32 unk100;
    s32 unk104;
    u8 unk108;
    u8 pad109[3];
    u8 *unk10C;
    s32 unk110;
    u8 *unk114;
    s32 unk118;
    s32 unk11C;
    s32 unk120;
    u8 *unk124;
} Obj001BE390;

/*rgp*/
void SoundStreamHandleCreate_1bf990(void *, void *, int, int);
/*rgp*/
void *memset(void *, s32, u32);

s32 SoundStreamSlotInitBuffers_1be390(Obj001BE390 *self, u8 *mem, u32 size, s32 a3) {
    u8 *base;
    s32 rem;
    s32 off;
    s32 i;

    if (size < 0x16B6) {
        return 0;
    }
    off = 0x100;
    base = (u8 *)(((u32)mem + 0x3F) & ~0x3F);
    self->unk0 = a3;
    self->unk10 = base;
    rem = size - (base - mem);
    *base = 0;
    self->unkF4 = 0x880;
    self->unk100 = 0;
    self->unk104 = 0;
    self->unk108 = 1;
    for (i = 0; i < 2; i++) {
        self->unkF8[i] = base + off;
        off = ALIGN64(off + self->unkF4);
    }
    self->unk110 = 0x100;
    self->unk10C = base + off;
    off = ALIGN64(off + self->unk110);
    self->unk118 = 0x12;
    self->unk114 = base + off;
    off = ALIGN64(off + self->unk118);
    self->unk11C = 0x1000;
    self->unk124 = base + off;
    self->unk120 = 0;
    off = ALIGN64(off + self->unk11C);
    self->unk8 = (Sub001BE390 *)(base + off);
    memset(base + off, 0, 0xD0);
    off = ALIGN64(off + 0xD0);
    self->unk8->unk78 = base + off;
    off = ALIGN64(off + 0x190);
    self->unk4.w = ({ Ret001BE390 rgp_sret; SoundStreamHandleCreate_1bf990((void *)&rgp_sret, (void *)(((s32)GetSoundStreamTable_1bf7c0())), (int)(base + off), (int)(rem - off)); rgp_sret; }).w;
    if (self->unk4.h.hi == 0) {
        return 0;
    }
    self->unkF0 = 1;
    self->unk4C = 0;
    self->unk78 = 1.0f;
    self->unk74 = 1.0f;
    self->unkE4 = 0;
    self->unkE8 = 1.0f;
    self->unkEC = 0;
    SemaHandleCreate_1c2190(self->unkC);
    return 1;
}
