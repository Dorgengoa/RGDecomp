/* Synthetic devirt fixture (mwcc-style dummy classes), one class per rule of
 * tools/stages/devirt.py.  test_layout.cpp includes the stage's OUTPUT for this
 * file and checks layout (static_assert) and dispatch (fake vtables). */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;
struct Bits48 { u8 b[6]; };

/* vptr after the pre-virtual data; `class` default access is private */
class VT14 {
    u8 pad_[0x14];
public:
    virtual void f8();
};

/* root: slots in declaration order; bool / struct return / variadic; data after
 * the virtuals stays after the vptr */
class Root {
public:
    u8 pad[0x10];
    virtual void v0();
    virtual s32 get(s32 a);
    virtual bool busy();
    virtual Bits48 bits(s32 k);
    virtual s32 vf(...);
    virtual void unused_placeholder();
    s32 tail;
};

/* derived: an override keeps its base slot (and is dropped), a new virtual
 * gets base_count + i */
class Derived : public Root {
public:
    virtual s32 get(s32 a);
    virtual s32 extra(s32 a, f32 b);
    s32 d0;
};

/* polymorphic second base behind a pad base: declaration order is kept */
struct Pad88 { u8 pad[0x88]; };
struct List {
    virtual s32 count();
};
struct Top : Pad88, List { s32 n; };

/* virtuals declared through a macro */
#define V1(n) virtual void v##n();
class Mac {
public:
    V1(0) V1(1)
    virtual s32 two();
};

/* a variadic virtual inside an extern "C" block (member templates need C++ linkage) */
extern "C" {
class InC {
public:
    u8 pad[4];
    virtual s32 f(...);
};
}

/* linkage: data declarations and game-symbol definitions become extern "C" */
extern s32 D_00123456;
extern struct rgp_anon_D_00123460 { s32 a; s32 b; } D_00123460;

s32 GameFnSynthetic_123456(Root *r, Derived *d, Top *t, Mac *m, InC *c)
{
    extern s32 D_00123470;
    s32 acc = 0;
    Bits48 x;
    r->v0();
    acc += r->get(1);
    acc += r->busy() ? 1000 : 0;
    x = r->bits(2);
    acc += x.b[5];
    acc += r->vf(3, 4.0f);
    acc += d->get(5);
    acc += d->extra(6, 0.5f);
    acc += t->count();
    acc += m->two();
    acc += c->f(7);
    return acc + D_00123456 + D_00123460.b + D_00123470;
}
