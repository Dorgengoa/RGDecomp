#include "types.h"

extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
extern char *D_00453E50[];
extern u16 D_00453E54[];
extern s32 D_00453E58[];
extern u8 D_00453E60[];
extern u8 D_00453EA0[];
extern u8 D_00453ED0[];
extern u8 D_00453F00[];
extern char D_004639D0[];

typedef struct {
    char name[6];
    u16 f6;
    u8 pad8[4];
    s32 fC;
    u8 f10[0x40];
    u8 f50[0x30];
    u8 f80[0x30];
    u8 fB0[0x10];
    char fC0[0x44];
    char f104[0x40];
    char f144[0x40];
    char f184[0x40];
    u8 pad1C4[0x3C4 - 0x1C4];
} Sub;

typedef struct {
    char s0[0x20];
    char s20[0x20];
    char s40[0x20];
    u8 pad60[0x80];
    Sub sub;
} Obj;

void SaveIconSysBuild_375d10(Obj *arg0) {
    memset(&arg0->sub, 0, sizeof(Sub));
    strcpy(arg0->sub.name, D_004639D0);
    strcpy(arg0->sub.fC0, D_00453E50[0]);
    arg0->sub.f6 = D_00453E54[0];
    arg0->sub.fC = D_00453E58[0];
    memcpy(arg0->sub.f10, D_00453E60, 0x40);
    memcpy(arg0->sub.f50, D_00453EA0, 0x30);
    memcpy(arg0->sub.f80, D_00453ED0, 0x30);
    memcpy(arg0->sub.fB0, D_00453F00, 0x10);
    strcpy(arg0->sub.f104, arg0->s0);
    strcpy(arg0->sub.f144, arg0->s20);
    strcpy(arg0->sub.f184, arg0->s40);
}
