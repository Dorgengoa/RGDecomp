// SPDX-License-Identifier: CC0-1.0
// devirt stage, end to end: the stage's OUTPUT for fixtures/synthetic.cpp is
// included here (generated at build time by tools/stages/devirt.py), then its
// layout is pinned with static_asserts (the mwcc rule, probes/vtable/README.md)
// and its dispatch is run against fake vtables in data2c spelling
// (u32 words: {RTTI 0, offset 0, slot0, slot1, ...}).
//
//   rg-devirt-layout            all checks must pass
//   rg-devirt-layout control    every vtable is built one slot too far (8+4(k+1)):
//                               dispatch must FAIL (ctest WILL_FAIL)
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "synthetic.devirt.cpp"

// ---- layout: vptr where mwcc put it, data in declaration order
static_assert(offsetof(VT14, __vptr) == 0x14, "vptr after pre-virtual data");
static_assert(sizeof(VT14) == 0x18, "VT14 size");
static_assert(offsetof(Root, __vptr) == 0x10, "Root vptr");
static_assert(offsetof(Root, tail) == 0x14, "data after the virtuals follows the vptr");
static_assert(offsetof(Derived, d0) == 0x18, "derived data after the base");
static_assert(sizeof(Top) == 0x88 + 4 + 4, "Top: Pad88 first, then List");
static_assert(offsetof(Mac, __vptr) == 0, "Mac vptr at 0");
static_assert(offsetof(InC, __vptr) == 4, "InC vptr after pad");

static int g_fail;
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); g_fail++; } } while (0)

extern "C" {
s32 D_00123456 = 100;
struct rgp_anon_D_00123460 D_00123460 = {0, 200};
s32 D_00123470 = 300;
// a C-linkage redeclaration compiles only if the stage gave the definition C linkage
s32 GameFnSynthetic_123456(Root *r, Derived *d, Top *t, Mac *m, InC *c);

static int g_v0;
static void VC_CC Root_v0(void *self) { (void)self; g_v0++; }
static s32 VC_CC Root_get(void *self, s32 a) { return ((Root *)self)->tail + a; }
static u32 VC_CC Root_busy(void *self) { (void)self; return 0x100; }      // low byte 0 -> false
static void VC_CC Root_bits(Bits48 *out, void *self, s32 k)               // sret: out first
{ memset(out, 0, sizeof *out); out->b[5] = (u8)(k * 10); (void)self; }
static s32 VC_CC Root_vf(void *self, s32 a, double f) { (void)self; return a + (s32)f; }  // promoted
static s32 VC_CC Derived_get(void *self, s32 a) { return ((Derived *)self)->d0 * a; }
static s32 VC_CC Derived_extra(void *self, s32 a, f32 b) { (void)self; return a * (s32)(b * 4); }
static s32 VC_CC List_count_thunk(u8 *self) { return *(s32 *)(self - 0x88 + 0x8C); } // game thunk
static s32 VC_CC Mac_two(void *self) { (void)self; return 2; }
static s32 VC_CC InC_f(void *self, s32 a) { (void)self; return a * 3; }
static s32 VC_CC Nop(void *self) { (void)self; return -1; }
}
#define F(fn) (u32)(size_t)&fn

int main(int argc, char **argv)
{
    int shift = (argc > 1 && strcmp(argv[1], "control") == 0) ? 1 : 0;   // control: off by one slot
    static u32 vt_root[2 + 8], vt_der[2 + 8], vt_list[2 + 2], vt_mac[2 + 4], vt_inc[2 + 2];
    u32 *slots_root = vt_root + 2 + shift, *slots_der = vt_der + 2 + shift;
    slots_root[0] = F(Root_v0); slots_root[1] = F(Root_get); slots_root[2] = F(Root_busy);
    slots_root[3] = F(Root_bits); slots_root[4] = F(Root_vf);
    memcpy(slots_der, slots_root, 5 * sizeof(u32));
    slots_der[1] = F(Derived_get);
    slots_der[6] = F(Derived_extra);
    vt_list[2 + shift] = F(List_count_thunk);
    vt_mac[2 + 2 + shift] = F(Mac_two);
    vt_inc[2 + shift] = F(InC_f);
    if (shift) {                     // keep every shifted slot callable: a wrong slot
        u32 *tabs[] = {vt_root, vt_der, vt_list, vt_mac, vt_inc};   // must show up as a
        size_t lens[] = {10, 10, 4, 6, 4};                          // wrong RESULT, not a crash
        for (int i = 0; i < 5; i++)
            for (size_t k = 2; k < lens[i]; k++)
                if (!tabs[i][k]) tabs[i][k] = F(Nop);
    }

    static Root r;
    static Derived d;
    static Top t;
    static Mac m;
    static InC c;
    VC_SET_VPTR(&r, 0x10, vt_root);
    VC_SET_VPTR(&d, 0x10, vt_der);
    VC_SET_VPTR(static_cast<List *>(&t), 0, vt_list);
    VC_SET_VPTR(&m, 0, vt_mac);
    VC_SET_VPTR(&c, 4, vt_inc);
    r.tail = 40;
    d.tail = 1;
    d.d0 = 7;
    t.n = 9;

    CHECK(r.get(2) == 42);
    CHECK(r.busy() == false);              // bool narrows the low byte
    CHECK(r.bits(3).b[5] == 30);           // struct return through the out pointer
    CHECK(r.vf(3, 4.0f) == 7);             // variadic: f32 promoted to double
    CHECK(d.get(5) == 35);                 // override keeps the base slot
    CHECK(d.extra(6, 0.5f) == 12);         // new virtual = base_count + i
    CHECK(t.count() == 9);                 // MI: this converted to the List sub-object
    CHECK(m.two() == 2);                   // macro-declared virtuals counted
    CHECK(c.f(7) == 21);                   // variadic in an extern "C" block
    g_v0 = 0;
    s32 acc = GameFnSynthetic_123456(&r, &d, &t, &m, &c);
    CHECK(g_v0 == 1);
    CHECK(acc == 41 + 0 + 20 + 7 + 5 * 7 + 12 + 9 + 2 + 21 + 100 + 200 + 300);
    printf("%s (%d failures)%s\n", g_fail ? "FAIL" : "PASS", g_fail, shift ? " [control]" : "");
    return g_fail != 0;
}
