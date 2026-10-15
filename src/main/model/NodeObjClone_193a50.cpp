#define KV 9
#define KD 1
#define KL 1
#define KE 1
#include "types.h"
#ifndef KV
#define KV 1
#endif
#ifndef KC
#define KC 0
#endif
#ifndef KH
#define KH 0
#endif
#ifndef KD
#define KD 0
#endif
#ifndef KE
#define KE 0
#endif
#ifndef KL
#define KL 0
#endif
#if KO == 3
#pragma optimization_level 3
#endif
#if KR
#pragma opt_repositioncode on
#endif

extern "C" {
void *MemStackNew_14e230(s32 size, s32 heap);
void NodeRelated_185f50(void *);
void Copy20Bytes_18b5c0(void *, void *);
static inline void cpy20(u8 *a, u8 *b) { Copy20Bytes_18b5c0(a, b); }
void FuncDataTableClone_18fc10(void *, void *, s32);
s32 FuncDataTableIterNext_1908b0(void *);
void FuncDataTableIterBegin_1908e0(void *, s32);
void FuncAnimeBind_190fc0(void *, s32, void *);
void NodeAssign_193f60(void *, void *);
void NodeObjBasicInit_196880(void *);
void NodeObjBasicCopy_1968d0(void *, void *);
extern u8 D_00470410[];
extern u8 D_00470548[];
extern u8 D_00470610[];
extern u8 D_00470620[];
}

struct Vec4 { f32 x, y, z, w; };
struct Vec2 { f32 x, y; };

class Link {
public:
    Link *next;
    Link *prev;
    u8 pad8[8];
    void *obj;
    virtual void init();
};

class Item {
public:
    Item *next;
    Item *prev;
    u8 pad8[8];
    s32 f10, f14, f18, f1c, f20, f24;
    u8 pad28[0x28];
    virtual void init();
};

struct Src {
    Src *next;
    u8 pad4[0xC];
    void *obj;
};

#if KV == 9
class B6C { public: u8 d[0x6C]; B6C &operator=(const B6C &o) { NodeAssign_193f60(this, (void *)&o); return *this; } };
class S20 { public: u8 d[0x20]; S20 &operator=(const S20 &o) { Copy20Bytes_18b5c0(this, (void *)&o); return *this; } };
struct Obj : public B6C {
#define sb0T S20
#else
#define sb0T S20
struct S20 { u8 d[0x20]; };
struct Obj {
    u8 base[0x6C];
#endif
    s8 name[0x20];
    s32 w8c;
    s32 w90;
    void *list;
    s32 w98, w9c, wa0, wa4, wa8, wac;
    sb0T sb0;
    Vec4 vd0;
    sb0T se0;
    Vec4 v100;
    s32 w110;
    Vec4 v114;
    s32 w124, w128, w12c, w130, w134, w138;
    Item *items;
    s32 w140, w144;
    Vec2 v148;
};

#if KV == 0
#define VC(d, s) (d) = (s);
#define V2C(d, s) (d) = (s);
#elif KV == 1
#define VC(d, s) { f32 x_ = (s).x; f32 y_ = (s).y; f32 z_ = (s).z; f32 w_ = (s).w; (d).x = x_; (d).y = y_; (d).z = z_; (d).w = w_; }
#define V2C(d, s) { f32 x_ = (s).x; f32 y_ = (s).y; (d).x = x_; (d).y = y_; }
#elif KV == 2
#define VC(d, s) { Vec4 t_ = (s); (d) = t_; }
#define V2C(d, s) { Vec2 t_ = (s); (d) = t_; }
#elif KV == 4
#define VC(d, s) { f32 x_ = (s).x; f32 y_ = (s).y; f32 z_ = (s).z; f32 w_ = (s).w; (d).w = w_; (d).z = z_; (d).y = y_; (d).x = x_; }
#define V2C(d, s) { f32 x_ = (s).x; f32 y_ = (s).y; (d).y = y_; (d).x = x_; }
#elif KV == 5
#define VC(d, s) { const Vec4 *s_ = &(s); Vec4 *d_ = &(d); f32 x_, y_, z_, w_; x_ = s_->x; y_ = s_->y; z_ = s_->z; w_ = s_->w; d_->x = x_; d_->y = y_; d_->z = z_; d_->w = w_; }
#define V2C(d, s) { const Vec2 *s_ = &(s); Vec2 *d_ = &(d); f32 x_, y_; x_ = s_->x; y_ = s_->y; d_->x = x_; d_->y = y_; }
#else
#define VC(d, s) { f32 w_ = (s).w; f32 z_ = (s).z; f32 y_ = (s).y; f32 x_ = (s).x; (d).x = x_; (d).y = y_; (d).z = z_; (d).w = w_; }
#define V2C(d, s) { f32 y_ = (s).y; f32 x_ = (s).x; (d).x = x_; (d).y = y_; }
#endif

#if KC == 0
#define CC(d, s) { s8 *sp_ = (s)->name; s8 *dp_ = (d)->name; s32 n_ = 16; \
    do { s8 a_ = sp_[0]; n_--; { s8 b_ = sp_[1]; dp_[0] = a_; sp_ += 2; dp_[1] = b_; dp_ += 2; } } while (n_ > 0); }
#elif KC == 1
#define CC(d, s) { s32 i_; for (i_ = 0; i_ < 32; i_++) (d)->name[i_] = (s)->name[i_]; }
#elif KC == 2
#define CC(d, s) { s8 *sp_ = (s)->name; s8 *dp_ = (d)->name; s32 n_ = 16; \
    do { n_--; dp_[0] = sp_[0]; dp_[1] = sp_[1]; sp_ += 2; dp_ += 2; } while (n_ > 0); }
#elif KC == 3
#define CC(d, s) { s8 *sp_ = (s)->name; s8 *dp_ = (d)->name; s32 n_ = 16; \
    do { s8 b_ = sp_[1]; n_--; { s8 a_ = sp_[0]; dp_[0] = a_; sp_ += 2; dp_[1] = b_; dp_ += 2; } } while (n_ > 0); }
#elif KC == 5
struct N32 { s8 c[32]; };
#define CC(d, s) *(N32 *)(d)->name = *(N32 *)(s)->name;
#else
#define CC(d, s) { s32 i_; for (i_ = 0; i_ < 32; i_ += 2) { (d)->name[i_] = (s)->name[i_]; (d)->name[i_ + 1] = (s)->name[i_ + 1]; } }
#endif

#if KV == 9
#define COPY(d, s) (*(d) = *(s))
#else
#define COPY(d, s) do { \
    NodeAssign_193f60((d), (s)); \
    CC(d, s) \
    (d)->w8c = (s)->w8c; (d)->w90 = (s)->w90; (d)->list = (s)->list; \
    (d)->w98 = (s)->w98; (d)->w9c = (s)->w9c; (d)->wa0 = (s)->wa0; \
    (d)->wa4 = (s)->wa4; (d)->wa8 = (s)->wa8; (d)->wac = (s)->wac; \
    Copy20Bytes_18b5c0((void *)&(d)->sb0, (void *)&(s)->sb0); \
    VC((d)->vd0, (s)->vd0) \
    Copy20Bytes_18b5c0((void *)&(d)->se0, (void *)&(s)->se0); \
    VC((d)->v100, (s)->v100) \
    (d)->w110 = (s)->w110; \
    VC((d)->v114, (s)->v114) \
    (d)->w124 = (s)->w124; (d)->w128 = (s)->w128; (d)->w12c = (s)->w12c; \
    (d)->w130 = (s)->w130; (d)->w134 = (s)->w134; (d)->w138 = (s)->w138; \
    (d)->items = (s)->items; (d)->w140 = (s)->w140; (d)->w144 = (s)->w144; \
    V2C((d)->v148, (s)->v148) \
} while (0)
#endif

#if KL == 0
#define APPEND(T, headexpr, n) \
    if ((headexpr) == 0) { (headexpr) = (n); } else { \
        T *p_ = (headexpr); \
        while (p_ != 0) { if (p_->next == 0) break; p_ = p_->next; } \
        p_->next = (n); if ((n) != 0) (n)->prev = p_; }
#elif KL == 1
#define APPEND(T, headexpr, n) \
    if ((headexpr) != 0) { \
        T *p_ = (headexpr); \
        while (p_ != 0) { if (p_->next == 0) break; p_ = p_->next; } \
        p_->next = (n); if ((n) != 0) (n)->prev = p_; } else { (headexpr) = (n); }
#elif KL == 2
#define APPEND(T, headexpr, n) \
    if ((headexpr) == 0) { (headexpr) = (n); } else { \
        T *p_ = (headexpr); \
        for (; p_ != 0; p_ = p_->next) { if (p_->next == 0) break; } \
        p_->next = (n); if ((n) != 0) (n)->prev = p_; }
#elif KL == 4
#define APPEND(T, headexpr, n) \
    if ((headexpr) == 0) goto set_; { \
        T *p_ = (headexpr); \
        while (p_ != 0) { if (p_->next == 0) break; p_ = p_->next; } \
        p_->next = (n); if ((n) != 0) (n)->prev = p_; } goto next_; set_: (headexpr) = (n); next_:;
#elif KL == 5
#define APPEND(T, headexpr, n) \
    if ((headexpr) != 0) { \
        T *p_ = (headexpr); \
        while (p_ != 0) { if (p_->next == 0) break; p_ = p_->next; } \
        p_->next = (n); if ((n) == 0) continue; (n)->prev = p_; continue; } (headexpr) = (n);
#else
#define APPEND(T, headexpr, n) \
    if ((headexpr) == 0) { (headexpr) = (n); } else { \
        T *p_ = (headexpr); T *q_; \
        while (p_ != 0) { q_ = p_->next; if (q_ == 0) break; p_ = q_; } \
        p_->next = (n); if ((n) != 0) (n)->prev = p_; }
#endif
#define APPEND0(T, headexpr, n) \
    if ((headexpr) == 0) { (headexpr) = (n); } else {         T *p_ = (headexpr);         while (p_ != 0) { if (p_->next == 0) break; p_ = p_->next; }         p_->next = (n); if ((n) != 0) (n)->prev = p_; }

extern "C" void NodeObjClone_193a50(Obj *src, Obj *dst, s32 heap)
{
    if (heap != 0) {
#if KD
        Link *head;
        Src *it;
#else
        Src *it;
        Link *head;
#endif
        Link *l;
        Item *t2;
        void *t;
        s32 e;

        COPY(dst, src);
        head = 0;
        for (it = (Src *)src->list; it != 0; it = it->next) {
            l = (Link *)MemStackNew_14e230(0x18, heap);
            if (l != 0) {
                *(void **)((u8 *)l + 0x14) = D_00470548;
                l->init();
            }
            t = MemStackNew_14e230(0x90, heap);
            if (t != 0) {
                *(void **)((u8 *)t + 0x68) = D_00470410;
                *(void **)((u8 *)t + 0x68) = D_00470620;
                NodeObjBasicInit_196880(t);
            }
#if KE == 0
            if (l == 0) return;
            if (t == 0) return;
            l->obj = t;
#elif KE == 1
            if (l == 0 || t == 0) return;
            l->obj = t;
#elif KE == 3
            if (l == 0) return;
            if (t != 0) { l->obj = t; } else { return; }
#else
            if (l == 0) return;
            if (t != 0) goto ok;
            return;
        ok:
            l->obj = t;
#endif
            if (it->obj != 0) NodeObjBasicCopy_1968d0(it->obj, t);
#if KH
            APPEND(Link, head, l)
#else
            APPEND(Link, head, l)
#endif
        }
        dst->list = head;
        FuncDataTableClone_18fc10(&src->v114, &dst->v114, heap);
        FuncDataTableIterBegin_1908e0(&dst->v114, 5);
        while ((e = FuncDataTableIterNext_1908b0(&dst->v114)) != 0) {
            t2 = (Item *)MemStackNew_14e230(0x60, heap);
            if (t2 != 0) {
                *(void **)((u8 *)t2 + 0x50) = D_00470610;
                t2->f14 = 0;
                t2->f18 = 0;
                t2->f1c = 0;
                t2->f10 = 0;
                t2->f24 = 0;
                t2->f20 = 0;
                t2->init();
            }
            if (t2 == 0) break;
            t2->init();
            APPEND0(Item, dst->items, t2)
            FuncAnimeBind_190fc0(&t2->f10, e, dst);
        }
    } else {
        COPY(dst, src);
    }
    NodeRelated_185f50(dst);
}
