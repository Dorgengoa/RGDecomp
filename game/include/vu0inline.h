/* Inline VU0 macro-mode helpers used by game code (same register conventions as
   Sony libvu0).  The ONLY asm in these units lives here; callers are plain C. */
#ifndef VU0INLINE_H
#define VU0INLINE_H

/* d.xyz = s.xyz (d.w kept) */
static inline void Vu0CopyVectorXYZ(void *d, void *s)
{
    asm volatile {
        lqc2      vf1, 0(d)
        lqc2      vf2, 0(s)
        vaddx.xyz vf1, vf2, vf0x
        sqc2      vf1, 0(d)
    }
}

/* d = (0,0,0,1) */
static inline void Vu0UnitVector(void *d)
{
    asm volatile {
        sqc2      vf0, 0(d)
    }
}

/* d = (s.x, s.y, s.z, 1) */
static inline void Vu0CopyVectorW1(void *d, void *s)
{
    asm volatile {
        lqc2      vf4, 0(s)
        vmul.w    vf4, vf0, vf0
        sqc2      vf4, 0(d)
    }
}

/* return v.x*v.x + v.y*v.y + v.z*v.z  (clobbers $a1, as the original did) */
static inline f32 Vu0SquareLength(void *v)
{
    f32 r;
    asm volatile {
        lqc2      vf4, 0(v)
        vmul.xyz  vf4, vf4, vf4
        vaddy.x   vf4, vf4, vf4y
        vaddz.x   vf4, vf4, vf4z
        qmfc2.ni  a1, vf4
        mtc1      a1, r
    }
    return r;
}

/* dst = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector) */
static inline void Vu0InterVector(void *dst, void *p1, void *p2, f32 t)
{
    asm volatile {
        lqc2        vf4, 0(p2)
        lqc2        vf5, 0(p1)
        mfc1        t0, t
        nop
        qmtc2.ni    t0, vf6
        vsub.xyzw   vf7, vf5, vf4
        vmulaw.xyzw ACC, vf4, vf0w
        vmaddx.xyzw vf8, vf7, vf6x
        sqc2        vf8, 0(dst)
    }
}

/* d = s with rows 0..2 scaled by v.x, v.y, v.z (row 3 copied) */
static inline void Vu0ScaleMatrix(void *d, void *v, void *s)
{
    asm volatile {
        lqc2       vf10, 0(v)
        lqc2       vf1, 0(s)
        lqc2       vf2, 0x10(s)
        lqc2       vf3, 0x20(s)
        lqc2       vf4, 0x30(s)
        vmulx.xyzw vf1, vf1, vf10x
        vmuly.xyzw vf2, vf2, vf10y
        vmulz.xyzw vf3, vf3, vf10z
        sqc2       vf1, 0(d)
        sqc2       vf2, 0x10(d)
        sqc2       vf3, 0x20(d)
        sqc2       vf4, 0x30(d)
    }
}

/* d = s with rows 0..2 divided by v.x, v.y, v.z (row 3 copied) */
static inline void Vu0InvScaleMatrix(void *d, void *v, void *s)
{
    asm volatile {
        lqc2       vf10, 0(v)
        lqc2       vf1, 0(s)
        lqc2       vf2, 0x10(s)
        lqc2       vf3, 0x20(s)
        lqc2       vf4, 0x30(s)
        vdiv       Q, vf0w, vf10x
        vwaitq
        vmulq.xyzw vf1, vf1, Q
        vdiv       Q, vf0w, vf10y
        vwaitq
        vmulq.xyzw vf2, vf2, Q
        vdiv       Q, vf0w, vf10z
        vwaitq
        vmulq.xyzw vf3, vf3, Q
        sqc2       vf1, 0(d)
        sqc2       vf2, 0x10(d)
        sqc2       vf3, 0x20(d)
        sqc2       vf4, 0x30(d)
    }
}

#endif
