/* SPDX-License-Identifier: CC0-1.0 */
#include "vu_retail.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *rg_retail_elf_path(void)
{
    const char *p = getenv("RG_ELF");
    return (p && *p) ? p : "../work/SCUS_974.90";
}

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static uint16_t rd16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }

int rg_elf_load(rg_elf *e, const char *path)
{
    FILE *f = fopen(path, "rb");
    long n;
    uint32_t phoff, i, phnum;
    memset(e, 0, sizeof *e);
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 0x34) { fclose(f); return -1; }
    e->data = (uint8_t *)malloc((size_t)n);
    e->size = (size_t)n;
    if (!e->data || fread(e->data, 1, (size_t)n, f) != (size_t)n) { fclose(f); rg_elf_free(e); return -1; }
    fclose(f);
    if (memcmp(e->data, "\x7f" "ELF", 4) != 0) { rg_elf_free(e); return -1; }
    phoff = rd32(e->data + 0x1C);
    phnum = rd16(e->data + 0x2C);
    for (i = 0; i < phnum && e->nph < 32; i++) {
        const uint8_t *ph = e->data + phoff + 32 * i;
        if (phoff + 32 * (i + 1) > e->size) break;
        if (rd32(ph) != 1) continue; /* PT_LOAD */
        e->ph[e->nph].off = rd32(ph + 4);
        e->ph[e->nph].vaddr = rd32(ph + 8);
        e->ph[e->nph].filesz = rd32(ph + 16);
        e->nph++;
    }
    return 0;
}

void rg_elf_free(rg_elf *e)
{
    free(e->data);
    memset(e, 0, sizeof *e);
}

const uint8_t *rg_elf_ptr(const rg_elf *e, uint32_t va, uint32_t len)
{
    int i;
    for (i = 0; i < e->nph; i++) {
        uint32_t v = e->ph[i].vaddr, s = e->ph[i].filesz;
        if (va >= v && va + len <= v + s && (size_t)e->ph[i].off + (va - v) + len <= e->size)
            return e->data + e->ph[i].off + (va - v);
    }
    return NULL;
}

const uint32_t *rg_vif_packet(const rg_elf *e, uint32_t va, size_t *nwords)
{
    const uint8_t *t = rg_elf_ptr(e, va, 16), *p;
    uint32_t qwc;
    if (!t) return NULL;
    qwc = rd32(t) & 0xFFFF;
    p = rg_elf_ptr(e, va + 8, 8 + qwc * 16);
    if (!p) return NULL;
    *nwords = 2 + qwc * 4;
    return (const uint32_t *)p;
}

static void field(char **s, char *out, size_t cap)
{
    size_t k = 0;
    while (**s && **s != '\t' && **s != '\n' && **s != '\r') {
        if (k + 1 < cap) out[k++] = **s;
        (*s)++;
    }
    out[k] = 0;
    if (**s == '\t') (*s)++;
}

int vu_census_load(const char *path, vu_census_row **rows)
{
    FILE *f = fopen(path, "rb");
    char line[4096];
    int n = 0, cap = 0, header = 1;
    vu_census_row *r = NULL;
    *rows = NULL;
    if (!f) return -1;
    while (fgets(line, sizeof line, f)) {
        char *s = line, tmp[32];
        vu_census_row *x;
        if (line[0] == '#') continue;
        if (header) { header = 0; continue; }
        if (n == cap) {
            vu_census_row *nr;
            cap = cap ? cap * 2 : 256;
            nr = (vu_census_row *)realloc(r, (size_t)cap * sizeof *r);
            if (!nr) { free(r); fclose(f); return -1; }
            r = nr;
        }
        x = &r[n];
        memset(x, 0, sizeof *x);
        field(&s, x->kind, sizeof x->kind);
        field(&s, x->addr, sizeof x->addr);
        field(&s, x->vu, sizeof x->vu);
        field(&s, tmp, sizeof tmp); x->dest = (uint32_t)strtoul(tmp, NULL, 16);
        field(&s, tmp, sizeof tmp); x->insns = (uint32_t)strtoul(tmp, NULL, 10);
        field(&s, tmp, sizeof tmp); /* bytes */
        field(&s, x->sha1, sizeof x->sha1);
        field(&s, tmp, sizeof tmp); /* tag */
        field(&s, x->used_by, sizeof x->used_by);
        field(&s, x->detail, sizeof x->detail);
        n++;
    }
    fclose(f);
    *rows = r;
    return n;
}
