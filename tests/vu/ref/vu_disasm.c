/* SPDX-License-Identifier: CC0-1.0 */
/* VU lower-op register use + disassembler (docs/VU.md). */
#include "vu_decode.h"

#include <stdio.h>
#include <string.h>

void vu_use_add_read(vu_use *o, unsigned reg, unsigned mask);
#define add_r vu_use_add_read

static unsigned fbit(unsigned f) { return 8u >> f; }

void vu_lower_use(const vu_lower *l, vu_use *o)
{
    memset(o, 0, sizeof *o);
    o->vi_w = o->vi_r0 = o->vi_r1 = -1;
    switch (l->op) {
    case VU_L_LQ: o->vi_r0 = l->fs; o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_LQI: case VU_L_LQD:
        o->vi_r0 = l->fs; o->vi_w = l->fs; o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_SQ: add_r(o, l->fs, l->dest); o->vi_r0 = l->ft; break;
    case VU_L_SQI: case VU_L_SQD:
        add_r(o, l->fs, l->dest); o->vi_r0 = l->ft; o->vi_w = l->ft; break;
    case VU_L_ILW: case VU_L_ILWR: o->vi_r0 = l->fs; o->vi_w = l->ft; break;
    case VU_L_ISW: case VU_L_ISWR: o->vi_r0 = l->fs; o->vi_r1 = l->ft; break;
    case VU_L_IADDIU: case VU_L_ISUBIU: case VU_L_IADDI:
        o->vi_r0 = l->fs; o->vi_w = l->ft; break;
    case VU_L_IADD: case VU_L_ISUB: case VU_L_IAND: case VU_L_IOR:
        o->vi_r0 = l->fs; o->vi_r1 = l->ft; o->vi_w = l->fd; break;
    case VU_L_FCEQ: case VU_L_FCAND: case VU_L_FCOR: o->vi_w = 1; break;
    case VU_L_FSEQ: case VU_L_FSAND: case VU_L_FSOR: case VU_L_FCGET: o->vi_w = l->ft; break;
    case VU_L_FMEQ: case VU_L_FMAND: case VU_L_FMOR: o->vi_r0 = l->fs; o->vi_w = l->ft; break;
    case VU_L_B: o->is_branch = 1; break;
    case VU_L_BAL: o->is_branch = 1; o->vi_w = l->ft; break;
    case VU_L_JR: o->is_branch = 1; o->vi_r0 = l->fs; break;
    case VU_L_JALR: o->is_branch = 1; o->vi_r0 = l->fs; o->vi_w = l->ft; break;
    case VU_L_IBEQ: case VU_L_IBNE:
        o->is_branch = o->is_cond_branch = 1; o->vi_r0 = l->fs; o->vi_r1 = l->ft; break;
    case VU_L_IBLTZ: case VU_L_IBGTZ: case VU_L_IBLEZ: case VU_L_IBGEZ:
        o->is_branch = o->is_cond_branch = 1; o->vi_r0 = l->fs; break;
    case VU_L_MOVE: add_r(o, l->fs, l->dest); o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_MR32: {
        /* x <- y, y <- z, z <- w, w <- x */
        unsigned src = 0;
        if (l->dest & 8) src |= 4;
        if (l->dest & 4) src |= 2;
        if (l->dest & 2) src |= 1;
        if (l->dest & 1) src |= 8;
        add_r(o, l->fs, src); o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    }
    case VU_L_DIV: case VU_L_RSQRT:
        add_r(o, l->fs, fbit(l->fsf)); add_r(o, l->ft, fbit(l->ftf)); o->writes_q = 1; break;
    case VU_L_SQRT: add_r(o, l->ft, fbit(l->ftf)); o->writes_q = 1; break;
    case VU_L_WAITQ: o->writes_q = 1; break;
    case VU_L_MTIR: add_r(o, l->fs, fbit(l->fsf)); o->vi_w = l->ft; break;
    case VU_L_MFIR: o->vi_r0 = l->fs; o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_RNEXT: case VU_L_RGET: o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_RINIT: case VU_L_RXOR: add_r(o, l->fs, fbit(l->fsf)); break;
    case VU_L_MFP: o->uses_p = 1; o->vf_w = l->ft; o->vf_w_mask = l->dest; break;
    case VU_L_XTOP: case VU_L_XITOP: o->vi_w = l->ft; break;
    case VU_L_XGKICK: o->vi_r0 = l->fs; break;
    case VU_L_ESADD: case VU_L_ERSADD: case VU_L_ELENG: case VU_L_ERLENG:
        add_r(o, l->fs, 0xE); o->writes_p = 1; break;
    case VU_L_EATANxy: add_r(o, l->fs, 0xC); o->writes_p = 1; break;
    case VU_L_EATANxz: add_r(o, l->fs, 0xA); o->writes_p = 1; break;
    case VU_L_ESUM: add_r(o, l->fs, 0xF); o->writes_p = 1; break;
    case VU_L_ESQRT: case VU_L_ERSQRT: case VU_L_ERCPR: case VU_L_ESIN:
    case VU_L_EATAN: case VU_L_EEXP:
        add_r(o, l->fs, fbit(l->fsf)); o->writes_p = 1; break;
    case VU_L_WAITP: o->writes_p = 1; break;
    default: break;
    }
    if (o->vf_w == 0) o->vf_w_mask = 0;
    if (o->vi_w == 0) o->vi_w = -1;
}

/* ------------------------------------------------------------- disassembly */

static void destsfx(unsigned d, char *s)
{
    if (!d) { *s = 0; return; }
    *s++ = '.';
    if (d & 8) *s++ = 'x';
    if (d & 4) *s++ = 'y';
    if (d & 2) *s++ = 'z';
    if (d & 1) *s++ = 'w';
    *s = 0;
}

static const char fld[4] = {'x', 'y', 'z', 'w'};

static void lower_case(char *d, const char *s)
{
    while (*s) {
        char c = *s++;
        *d++ = (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
    }
    *d = 0;
}

static void dis_upper(const vu_upper *u, char *b, unsigned n)
{
    char ds[6], mn[32], nm[24];
    destsfx(u->dest, ds);
    lower_case(nm, vu_upper_name(u));
    if (u->src == VU_SRC_BC && u->kind <= VU_U_MINI) {
        size_t L = strlen(nm);
        nm[L - 2] = fld[u->bc];
        nm[L - 1] = 0;
    }
    snprintf(mn, sizeof mn, "%s%s", nm, ds);
    switch (u->kind) {
    case VU_U_NOP: snprintf(b, n, "nop"); break;
    case VU_U_INVALID: snprintf(b, n, "upper?"); break;
    case VU_U_CLIP: snprintf(b, n, "clipw.xyz vf%02d, vf%02dw", u->fs, u->ft); break;
    case VU_U_ITOF: case VU_U_FTOI: case VU_U_ABS:
        snprintf(b, n, "%s vf%02d, vf%02d", mn, u->ft, u->fs); break;
    case VU_U_OPMULA: snprintf(b, n, "opmula.xyz acc, vf%02d, vf%02d", u->fs, u->ft); break;
    case VU_U_OPMSUB: snprintf(b, n, "opmsub.xyz vf%02d, vf%02d, vf%02d", u->fd, u->fs, u->ft); break;
    default: {
        char d[8], t[12];
        if (u->to_acc) snprintf(d, sizeof d, "acc");
        else snprintf(d, sizeof d, "vf%02d", u->fd);
        if (u->src == VU_SRC_VF) snprintf(t, sizeof t, "vf%02d", u->ft);
        else if (u->src == VU_SRC_BC) snprintf(t, sizeof t, "vf%02d%c", u->ft, fld[u->bc]);
        else snprintf(t, sizeof t, "%s", u->src == VU_SRC_Q ? "Q" : "I");
        snprintf(b, n, "%s %s, vf%02d, %s", mn, d, u->fs, t);
    }
    }
}

static unsigned btarget(uint32_t pc, int32_t imm) { return (unsigned)(pc + 8 + imm * 8) & 0xFFFF; }

static void dis_lower(const vu_lower *l, uint32_t pc, char *b, unsigned n)
{
    char ds[6], nm[16];
    destsfx(l->dest, ds);
    lower_case(nm, vu_lower_name(l->op));
    switch (l->op) {
    case VU_L_NOP: snprintf(b, n, "nop"); break;
    case VU_L_INVALID: snprintf(b, n, "lower?"); break;
    case VU_L_LOI: {
        union { uint32_t u; float f; } c;
        c.u = (uint32_t)l->imm;
        snprintf(b, n, "loi 0x%08x (%g)", c.u, (double)c.f);
        break;
    }
    case VU_L_LQ: snprintf(b, n, "lq%s vf%02d, %d(vi%02d)", ds, l->ft, l->imm, l->fs); break;
    case VU_L_SQ: snprintf(b, n, "sq%s vf%02d, %d(vi%02d)", ds, l->fs, l->imm, l->ft); break;
    case VU_L_ILW: snprintf(b, n, "ilw%s vi%02d, %d(vi%02d)", ds, l->ft, l->imm, l->fs); break;
    case VU_L_ISW: snprintf(b, n, "isw%s vi%02d, %d(vi%02d)", ds, l->ft, l->imm, l->fs); break;
    case VU_L_ILWR: snprintf(b, n, "ilwr%s vi%02d, (vi%02d)", ds, l->ft, l->fs); break;
    case VU_L_ISWR: snprintf(b, n, "iswr%s vi%02d, (vi%02d)", ds, l->ft, l->fs); break;
    case VU_L_LQI: snprintf(b, n, "lqi%s vf%02d, (vi%02d++)", ds, l->ft, l->fs); break;
    case VU_L_LQD: snprintf(b, n, "lqd%s vf%02d, (--vi%02d)", ds, l->ft, l->fs); break;
    case VU_L_SQI: snprintf(b, n, "sqi%s vf%02d, (vi%02d++)", ds, l->fs, l->ft); break;
    case VU_L_SQD: snprintf(b, n, "sqd%s vf%02d, (--vi%02d)", ds, l->fs, l->ft); break;
    case VU_L_IADDIU: case VU_L_ISUBIU:
        snprintf(b, n, "%s vi%02d, vi%02d, 0x%x", nm, l->ft, l->fs, (unsigned)l->imm); break;
    case VU_L_IADDI: snprintf(b, n, "iaddi vi%02d, vi%02d, %d", l->ft, l->fs, l->imm); break;
    case VU_L_IADD: case VU_L_ISUB: case VU_L_IAND: case VU_L_IOR:
        snprintf(b, n, "%s vi%02d, vi%02d, vi%02d", nm, l->fd, l->fs, l->ft); break;
    case VU_L_FCEQ: case VU_L_FCAND: case VU_L_FCOR:
        snprintf(b, n, "%s vi01, 0x%06x", nm, (unsigned)l->imm); break;
    case VU_L_FCSET: snprintf(b, n, "fcset 0x%06x", (unsigned)l->imm); break;
    case VU_L_FSSET: snprintf(b, n, "fsset 0x%03x", (unsigned)l->imm); break;
    case VU_L_FSEQ: case VU_L_FSAND: case VU_L_FSOR:
        snprintf(b, n, "%s vi%02d, 0x%03x", nm, l->ft, (unsigned)l->imm); break;
    case VU_L_FMEQ: case VU_L_FMAND: case VU_L_FMOR:
        snprintf(b, n, "%s vi%02d, vi%02d", nm, l->ft, l->fs); break;
    case VU_L_FCGET: snprintf(b, n, "fcget vi%02d", l->ft); break;
    case VU_L_B: snprintf(b, n, "b 0x%04x", btarget(pc, l->imm)); break;
    case VU_L_BAL: snprintf(b, n, "bal vi%02d, 0x%04x", l->ft, btarget(pc, l->imm)); break;
    case VU_L_JR: snprintf(b, n, "jr vi%02d", l->fs); break;
    case VU_L_JALR: snprintf(b, n, "jalr vi%02d, vi%02d", l->ft, l->fs); break;
    case VU_L_IBEQ: case VU_L_IBNE:
        snprintf(b, n, "%s vi%02d, vi%02d, 0x%04x", nm, l->ft, l->fs, btarget(pc, l->imm)); break;
    case VU_L_IBLTZ: case VU_L_IBGTZ: case VU_L_IBLEZ: case VU_L_IBGEZ:
        snprintf(b, n, "%s vi%02d, 0x%04x", nm, l->fs, btarget(pc, l->imm)); break;
    case VU_L_MOVE: case VU_L_MR32:
        snprintf(b, n, "%s%s vf%02d, vf%02d", nm, ds, l->ft, l->fs); break;
    case VU_L_DIV: snprintf(b, n, "div Q, vf%02d%c, vf%02d%c", l->fs, fld[l->fsf], l->ft, fld[l->ftf]); break;
    case VU_L_RSQRT: snprintf(b, n, "rsqrt Q, vf%02d%c, vf%02d%c", l->fs, fld[l->fsf], l->ft, fld[l->ftf]); break;
    case VU_L_SQRT: snprintf(b, n, "sqrt Q, vf%02d%c", l->ft, fld[l->ftf]); break;
    case VU_L_WAITQ: case VU_L_WAITP: snprintf(b, n, "%s", nm); break;
    case VU_L_MTIR: snprintf(b, n, "mtir vi%02d, vf%02d%c", l->ft, l->fs, fld[l->fsf]); break;
    case VU_L_MFIR: snprintf(b, n, "mfir%s vf%02d, vi%02d", ds, l->ft, l->fs); break;
    case VU_L_RNEXT: case VU_L_RGET: snprintf(b, n, "%s%s vf%02d, R", nm, ds, l->ft); break;
    case VU_L_RINIT: case VU_L_RXOR: snprintf(b, n, "%s R, vf%02d%c", nm, l->fs, fld[l->fsf]); break;
    case VU_L_MFP: snprintf(b, n, "mfp%s vf%02d, P", ds, l->ft); break;
    case VU_L_XTOP: case VU_L_XITOP: snprintf(b, n, "%s vi%02d", nm, l->ft); break;
    case VU_L_XGKICK: snprintf(b, n, "xgkick vi%02d", l->fs); break;
    case VU_L_ESADD: case VU_L_ERSADD: case VU_L_ELENG: case VU_L_ERLENG:
    case VU_L_EATANxy: case VU_L_EATANxz: case VU_L_ESUM:
        snprintf(b, n, "%s P, vf%02d", nm, l->fs); break;
    default: snprintf(b, n, "%s P, vf%02d%c", nm, l->fs, fld[l->fsf]); break;
    }
}

void vu_disasm_pair(const vu_pair *p, uint32_t pc, char *buf, unsigned bufsz)
{
    char u[64], l[64], fl[8], t[80];
    unsigned k = 0;
    dis_upper(&p->up, u, sizeof u);
    dis_lower(&p->lo, pc, l, sizeof l);
    if (p->up.bits & VU_B_I) fl[k++] = 'i';
    if (p->up.bits & VU_B_E) fl[k++] = 'e';
    if (p->up.bits & VU_B_M) fl[k++] = 'm';
    if (p->up.bits & VU_B_D) fl[k++] = 'd';
    if (p->up.bits & VU_B_T) fl[k++] = 't';
    fl[k] = 0;
    if (k) snprintf(t, sizeof t, "%s[%s]", u, fl);
    else snprintf(t, sizeof t, "%s", u);
    snprintf(buf, bufsz, "%-44s %s", t, l);
}
