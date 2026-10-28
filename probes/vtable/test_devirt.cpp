// test_devirt.cpp -- the PROPOSED ingest rewrite (README "Design B"): a decomp dummy class
// is de-virtualised into a plain class with an explicit `vc_u32 __vptr` member placed
// where mwcc placed it, and every virtual becomes an inline thunk that dispatches
// through VCALL with the mwcc slot offset. Call sites stay as they are.
//
// Each class below is what the transform should emit for a real decomp class:
//   VT14     <- src/main/anim/MotionEventBlockAppendEvent_1b2370.cpp
//   Item/Self<- src/main/chara/CharaDeserialize_3a9c50.cpp (embedded polymorphic array)
//   B/O      <- src/main/camera/CameraObjCtor_177430.cpp (vptr 0xC0, derived class)
//   Top      <- `struct Top : Pad88, List` (polymorphic second base at +0x88)
//
//   clang --target=i686-pc-windows-msvc -std=c++14 -O1 test_devirt.cpp -o test_devirt.exe
//   cl /nologo /W3 /EHsc test_devirt.cpp                (MSVC x86)
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "vcall.h"

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

static int g_fail;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); g_fail++; } } while (0)

// ---- generated: VT14 -------------------------------------------------------------
// was:  class VT14 { u8 pad_[0x14]; public: virtual void f8(); };
class VT14 {
    u8 pad_[0x14];
public:
    vc_u32 __vptr;                                           // inserted at 1st virtual
    void f8() { VCALL0(this, 0x14, 0x8, void); }             // virtual #0
};
static_assert(offsetof(VT14, __vptr) == 0x14, "mwcc: vptr after pre-virtual data");

// ---- generated: Item / Self -----------------------------------------------------
// was:  class Item { public: virtual void v008(); ... virtual void v018(s32, s32);
//                    virtual void v01C(); u8 pad4[0x24]; };
class Item {
public:
    vc_u32 __vptr;
    s32 v018(s32 a, s32 b) { return VCALL(this, 0x0, 0x18, s32, (void *, s32, s32), a, b); } // #4
    s32 v01C() { return VCALL0(this, 0x0, 0x1C, s32); }                                       // #5
    u8 pad4[0x24];
};
static_assert(sizeof(Item) == 0x28, "Item stride");
class Self {
public:
    vc_u32 __vptr;
    void v508(s32 p, s32 n) { VCALL(this, 0x0, 0x508, void, (void *, s32, s32), p, n); }    // #320
    u8 pad4[0x304];
    Item items[10];
    s32 m498;
};
static_assert(offsetof(Self, items) == 0x308, "retail lw $25,0x308(...)");

// ---- generated: B177430 / O177430 (single inheritance, override keeps base slot) ----
class B177430 {
public:
    u8 pad0[0xC0];
    vc_u32 __vptr;
    void Init() { VCALL0(this, 0xC0, 0x44, void); }            // #15
    void *Params() { return VCALL0(this, 0xC0, 0x48, void *); } // #16
};
class O177430 : public B177430 {
public:
    // `virtual void Init();` etc. re-declared in the derived class: SAME slot, so the
    // transform simply drops the redeclaration (the base thunk is inherited).
    u8 padC4[0xD0 - 0xC4];
    u8 vD0[0x10];
};
static_assert(offsetof(O177430, padC4) == 0xC4, "derived data after base vptr");

// ---- generated: MI with a pad base -------------------------------------------------
struct Pad88 { u8 pad[0x88]; };
struct List {
    VC_VPTR_MEMBER;
    s32 count() { return VCM0(s32, 0x8); }      // VCM form: compiler supplies VOFF
};
struct Top : Pad88, List { s32 n; };
// Itanium would hoist the polymorphic List to offset 0 as primary base; once
// de-virtualised, clang keeps declaration order, which is what mwcc did.
static_assert(sizeof(Top) == 0x88 + 4 + 4, "Top size");

// ---- implementations + vtables (data2c spelling) --------------------------------------
extern "C" {
static s32 g_init, g_clear;
static void ListNodeClear(u8 *self) { g_clear = *(s32 *)(self + 0x10); }
static s32 Item_v018(u8 *self, s32 a, s32 b) { return self[4] * 1000 + a + b; }
static s32 Item_v01C(u8 *self) { return self[4]; }
static void Self_v508(u8 *self, s32 p, s32 n) { *(s32 *)(self + 0x498) = p + n; }
static void CamBaseInit(u8 *self) { (void)self; g_init = 1; }
static void *CamParams(u8 *self) { return self + 0xD0; }
static s32 TopCount_thunk(u8 *self) { return *(s32 *)(self - 0x88 + 0x8C); } // game thunk (-0x88)
}
#define F(fn) (u32)&fn
static u32 D_VT14[3] = { 0, 0, F(ListNodeClear) };
static u32 D_Item[8] = { 0, 0, 0, 0, 0, 0, F(Item_v018), F(Item_v01C) };
static u32 D_Self[2 + 321];
static u32 D_Base[2 + 16];
static u32 D_Obj[2 + 18];
static u32 D_TopList[3] = { 0, 0, F(TopCount_thunk) };

int main()
{
    D_Self[2 + 320] = F(Self_v508);
    D_Base[2 + 15] = F(CamBaseInit);
    D_Obj[2 + 15] = F(CamBaseInit);
    D_Obj[2 + 16] = F(CamParams);

    {   // VT14: as MotionEventBlockAppendEvent_1b2370 writes it
        static u8 buf[0x18];
        VT14 *nd = (VT14 *)buf;
        *(s32 *)(buf + 0x10) = 77;
        VC_SET_VPTR(nd, 0x14, D_VT14);
        nd->f8();
        CHECK(g_clear == 77);
    }
    {   // Self / items[k]: call sites unchanged from the decomp
        static Self s;
        int k;
        VC_SET_VPTR(&s, 0x0, D_Self);
        for (k = 0; k < 10; k++) { VC_SET_VPTR(&s.items[k], 0x0, D_Item); ((u8 *)&s.items[k])[4] = (u8)k; }
        for (k = 0; k < 10; k++) {
            CHECK(s.items[k].v01C() == k);
            CHECK(s.items[k].v018(1, 2) == k * 1000 + 3);
        }
        s.v508(40, 2);
        CHECK(s.m498 == 42);
    }
    {   // CameraObjCtor_177430 — the ONE real ctor; its override spells the vptr stores
        static O177430 o;
        VC_SET_VPTR(&o, 0xC0, D_Base);   // inlined B177430() { Init(); }
        o.Init();
        VC_SET_VPTR(&o, 0xC0, D_Obj);
        CHECK(g_init == 1);
        CHECK(o.Params() == (void *)o.vD0);
    }
    {   // MI: top->count() converts Top* -> List* (+0x88) exactly like mwcc's this
        static Top t;
        VC_SET_VPTR(static_cast<List *>(&t), 0x0, D_TopList);
        t.n = 9;
        CHECK((u8 *)static_cast<List *>(&t) == (u8 *)&t + 0x88);
        CHECK(t.count() == 9);
    }
    printf("%s (%d failures)\n", g_fail ? "FAIL" : "PASS", g_fail);
    return g_fail != 0;
}
