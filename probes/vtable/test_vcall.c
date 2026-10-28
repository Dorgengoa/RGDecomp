/* test_vcall.c -- self-contained check of vcall.h against vtables laid out exactly like
 * the generated data C (u32[] = {RTTI=0, offset=0, slot0, slot1, ...}), modelled on
 * real retail cases (see README.md evidence table).
 *
 *   clang --target=i686-pc-windows-msvc -std=c11 -O1 test_vcall.c -o test_vcall.exe
 *   clang -m32 -O1 test_vcall.c -o test_vcall          (Linux)
 *   cl /nologo /W3 /TC test_vcall.c                     (MSVC x86)
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "vcall.h"

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;
typedef unsigned long long u64;

static int g_fail;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); g_fail++; } } while (0)

/* ---- implementations: extern "C"-style, `this` first, like the decomp ---------------- */
static s32 Unit_isBusy(u8 *self)            { return *(s32 *)(self + 4); }
static void *Unit_getInfo(u8 *self)         { return self + 8; }
static s32 Unit_other(u8 *self)             { (void)self; return -999; }
static s32 g_cleared;
static void ListNodeClear_1b2270(u8 *self)  { g_cleared = *(s32 *)(self + 0x10); }
static s32 Item_v018(u8 *self, s32 a, s32 b){ return (s32)(self[4]) * 1000 + a + b; }
static s32 Item_v01C(u8 *self)              { return self[4]; }
static s32 Pool_Count(u8 *self)             { return *(s32 *)(self + 8); }        /* primary impl   */
static s32 Pool_ViewCountThunk(u8 *self)    { return Pool_Count(self - 4); }      /* game thunk -4  */
typedef struct Bits48 { u64 w; } Bits48;
static void Obj_v119(Bits48 *out, u8 *self) { out->w = *(u64 *)(self + 8); }      /* sret: out, this */
static s32 Obj_busyHigh(u8 *self)           { (void)self; return 0x100; }         /* low byte 0      */
static s32 Obj_busyOne(u8 *self)            { (void)self; return 0x101; }
static f32 Hnd_f8(u8 *self, void *h, f32 t) { (void)h; return *(f32 *)(self + 0x84) * t; }

/* ---- vtables, spelled the way data2c spells them ------------------------------------- */
#define F(fn) (u32)&fn
/* "Unit": vptr at 0; isBusy = virtual #46 (slot 0xC0), getInfo = #211 (0x354). */
static u32 VT_Unit[2 + 212];
/* D_00471048 verbatim shape: {0, 0, &ListNodeClear_1b2270, 0, 0, 0}. */
static u32 D_00471048[6] = { 0, 0, F(ListNodeClear_1b2270), 0, 0, 0 };
/* "Item": vptr at 0, v018 = #4 (0x18), v01C = #5 (0x1C). */
static u32 VT_Item[8] = { 0, 0, 0, 0, 0, 0, F(Item_v018), F(Item_v01C) };
/* MI blob, like D_00472260 (+0x1C == D_0047227C, the secondary vtable). */
static u32 VT_Pool[7 + 9] = {
    0, 0, F(Pool_Count), 0, 0, 0, 0,                 /* primary   @ +0x00 (vptr @ obj+0) */
    0, 0, F(Pool_ViewCountThunk), 0, 0, 0, 0, 0, 0,  /* secondary @ +0x1C (vptr @ obj+4) */
};
static u32 VT_Obj[2 + 120];
static u32 VT_Hnd[3] = { 0, 0, F(Hnd_f8) };

int main(void)
{
    /* rule */
    CHECK(VC_SLOT_OFF(0) == 0x8);
    CHECK(VC_SLOT_OFF(46) == 0xC0);
    CHECK(VC_SLOT_OFF(211) == 0x354);
    CHECK(VC_SLOT_OFF(320) == 0x508);
    CHECK(VC_SLOT_OFF(119) == 0x1E4);
    CHECK(sizeof(void *) == 4);   /* D1: i686 only */

    { int i; for (i = 2; i < 2 + 212; i++) VT_Unit[i] = F(Unit_other); }
    VT_Unit[2 + 46] = F(Unit_isBusy);
    VT_Unit[2 + 211] = F(Unit_getInfo);
    VT_Obj[2 + 119] = F(Obj_v119);
    VT_Obj[2 + 0] = F(Obj_busyHigh);
    VT_Obj[2 + 1] = F(Obj_busyOne);

    /* 1. ActionMgrFindLiftableInFrontMaybe_232de0: lw $25,0($21); lw $25,0xC0/0x354($25) */
    {
        u32 u[4];
        u[0] = (u32)VT_Unit; u[1] = 7; u[2] = 0; u[3] = 0;
        CHECK(VCALL0(u, 0x0, 0xC0, s32) == 7);
        CHECK(VCALL0(u, 0x0, 0x354, void *) == (void *)&u[2]);
        CHECK(VCALL0(u, 0x0, VC_SLOT_OFF(5), s32) == -999);
    }
    /* 2. MotionEventBlockAppendEvent_1b2370: vptr at 0x14, this unadjusted, slot 0x8 */
    {
        u32 nd[6];
        memset(nd, 0, sizeof nd);
        nd[4] = 1234;
        VC_SET_VPTR(nd, 0x14, D_00471048);
        CHECK(nd[5] == (u32)D_00471048);
        VCALL0(nd, 0x14, 0x8, void);
        CHECK(g_cleared == 1234);
    }
    /* 3. CharaDeserialize_3a9c50: embedded Item items[10] at self+0x308, stride 0x28,
     *    `lw $25,0x308($2)` / `addiu $4,$2,0x308` -> this = &items[k], vptr at item+0 */
    {
        static u8 self[0x308 + 10 * 0x28 + 4];
        int k;
        for (k = 0; k < 10; k++) {
            u8 *it = self + 0x308 + k * 0x28;
            VC_SET_VPTR(it, 0x0, VT_Item);
            it[4] = (u8)k;
        }
        for (k = 0; k < 10; k++) {
            u8 *it = self + 0x308 + k * 0x28;
            CHECK(VCALL0(it, 0x0, 0x1C, s32) == k);
            CHECK(VCALL(it, 0x0, 0x18, s32, (void *, s32, s32), 10, 20) == k * 1000 + 30);
        }
    }
    /* 4. MI (D_00472260 / D_0047227C, ctor at 0x3EE2FC): secondary vptr at obj+4, the
     *    secondary slot is a GAME thunk doing this-=4; the caller passes obj+4. */
    {
        u32 o[3];
        u32 *sub;
        VC_SET_VPTR(o, 0x0, VT_Pool);
        VC_SET_VPTR(o, 0x4, (u8 *)VT_Pool + 0x1C);
        o[2] = 55;
        CHECK(VCALL0(o, 0x0, 0x8, s32) == 55);
        sub = o + 1;                                   /* static_cast<View*>(pool) */
        CHECK(VCALL0(sub, 0x0, 0x8, s32) == 55);
    }
    /* 5. struct return (UnitStatusTestJustAdded_3b0380: `Bits48 v119()`), out first */
    {
        u32 ob[4];
        Bits48 r;
        u8 *o = (u8 *)ob;
        VC_SET_VPTR(o, 0x0, VT_Obj);
        *(u64 *)(o + 8) = 0x0000123456789ABCull;
        r.w = 0;
        VCALL_THIS(o, 0x0, 0x1E4, void, (Bits48 *, void *))(&r, o);
        CHECK(r.w == 0x0000123456789ABCull);
    }
    /* 6. bool virtual: mwcc tests the low byte only */
    {
        u32 ob[2];
        VC_SET_VPTR(ob, 0x0, VT_Obj);
        CHECK(VCALL_BOOL0(ob, 0x0, 0x8) == 0);    /* 0x100 -> false, as on the PS2 */
        CHECK(VCALL_BOOL0(ob, 0x0, 0xC) == 1);    /* 0x101 -> true                  */
    }
    /* 7. HandleRegistryStepAll_314e10: vptr 0xB0, slot 0x8, (H *, f32) args, f32 return */
    {
        static u8 ob[0xB4];
        f32 r;
        *(f32 *)(ob + 0x84) = 1.5f;
        VC_SET_VPTR(ob, 0xB0, VT_Hnd);
        r = VCALL(ob, 0xB0, 0x8, f32, (void *, void *, f32), (void *)0, 4.0f);
        CHECK(r == 6.0f);
    }
#if defined(__GNUC__) || defined(__clang__)
    /* single-evaluation form */
    {
        u32 u[2]; u32 *arr[1]; int n = 0;
        u[0] = (u32)VT_Unit; u[1] = 3; arr[0] = u;
        CHECK(VCALL0_SE(arr[n++], 0x0, 0xC0, s32) == 3);
        CHECK(n == 1);
    }
#endif
    printf("%s (%d failures)\n", g_fail ? "FAIL" : "PASS", g_fail);
    return g_fail != 0;
}
