#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Res003A72D0;

class VObj003A72D0 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual Res003A72D0 *slot70(s32);
};

typedef struct {
    u8 pad0[0xC];
    VObj003A72D0 *unkC;
} Holder003A72D0;

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
} Sub50_003A72D0;

typedef struct {
    u8 pad0[0x48];
    Holder003A72D0 *unk48;
    u8 pad4C[4];
    Sub50_003A72D0 *unk50;
} Mgr003A72D0;

typedef struct {
    u8 pad0[0x8];
    Mgr003A72D0 *unk8;
} Root003A72D0;

typedef struct {
    u8 pad0[0x4];
    s16 unk4;
    u8 pad6[2];
    s16 unk8;
    s16 unkA;
    s32 unkC;
    u8 pad10[0xC];
    s16 unk1C;
    u8 pad1E[2];
    Res003A72D0 *unk20;
    u8 pad24[0x8];
    s16 unk2C;
    u8 bit0 : 1;
    u8 bits : 7;
    u8 pad2F[0x1];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    s16 unk44;
    s16 unk46[5];
    s32 unk50;
} T003A72D0;

extern "C" {
extern void ExecEffInfoListAdd_3a6cc0(void *arg0, s32 arg1);
extern void ExecInfoInit_3a7940(void);
extern s32 TableFindByNameHashed_3f86e0(s32 arg0, s32 arg1);
extern Root003A72D0 *D_004837B0;
}

extern "C" s32 ExecInfoInitKind5Maybe_3a72d0(T003A72D0 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    Mgr003A72D0 *m;
    Res003A72D0 *r;
    s32 v;
    s32 i;

    ExecInfoInit_3a7940();
    if (D_004837B0 == NULL) {
        return 0;
    }
    m = D_004837B0->unk8;
    if (m == NULL) {
        return 0;
    }
    v = 0;
    if (arg2 != 0) {
        v = TableFindByNameHashed_3f86e0(m->unk50->unk8, arg2);
    }
    arg0->unk4 = 5;
    arg0->unk8 = arg1;
    arg0->unkA = arg3;
    arg0->unkC = v;
    arg0->unk1C = 5;
    arg0->unk20 = 0;
    r = m->unk48->unkC->slot70((s16)arg1);
    if (r == NULL) {
        return 0;
    }
    arg0->unk20 = r;
    arg0->unk50 = r->unk8;
    ExecEffInfoListAdd_3a6cc0(&arg0->unk1C, r->unk10);
    arg0->unk2C = arg3;
    i = 0;
    arg0->bit0 = i;
    arg0->unk30 = 1.0f;
    arg0->unk34 = 1.0f;
    arg0->unk38 = 1.0f;
    arg0->unk3C = 1.0f;
    arg0->unk40 = 0;
    do {
        arg0->unk46[i] = 0;
        i++;
    } while (i < 5);
    if (arg0->unkC == 0 && r != NULL) {
        arg0->unkC = r->unkC;
    }
    return 1;
}
