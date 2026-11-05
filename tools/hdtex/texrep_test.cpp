/* SPDX-License-Identifier: CC0-1.0 */
/* ctest native.texrep (docs/TEXTURES.md "Checks"): nr_texrep.cpp's pieces without the game.
 *   1. names: format (hashes without leading zeros) and parse (1..16 digits, any case);
 *   2. the lazy CPU copy of local memory: transfers recorded per block and made on demand give
 *      the same texture blocks (and data hash) as an eager per-pixel swizzle (nr_px_word), for
 *      CT32 / T8 / T4 / CT16 textures and partly overlapping transfers;
 *   3. the data hash = XXH3-64 of the blocks in raster order, the CLUT hash = XXH3-64 of the
 *      entries as 32-bit words (docs/TEXTURES.md "Names");
 *   4. DDS decode: BC1 (4-colour and 3-colour + transparent), BC3 alpha, BC7 mode 6;
 *   5. live toggles (lane hdtex2): replacement off frees the images (nr_texrep_valid 0) and both
 *      off the CPU copy (a new one from the mirror at the next enable); a pack file added while
 *      off is found at the next enable; dump mode 1 skips textures named while a movie plays
 *      and dumps them at a later draw outside it, mode 2 dumps at once.
 * --control: one transfer byte flipped after the eager copy: must FAIL. */
#define RG_NATIVE_ONLY 1
#include "../../src/native/render/nr_texrep.cpp"

#include <random>

int nr_gs_movie;   /* (nr_gs.c in the game: a movie plays) */
uint32_t nr_gs_fields;

static int g_fail;
#define EXPECT(c, ...) do { if (!(c)) { g_fail++; printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

static std::vector<uint8_t> g_ref(4u << 20);   /* eager reference copy */

static void ref_xfer(const gs_mem_rect &rc, const uint8_t *data, uint32_t npx)
{
    int bpp = nr_psm_bpp(rc.psm);
    for (uint32_t i = 0; i < npx; i++) {
        uint32_t x = rc.x + i % rc.w, y = rc.y + i / rc.w, w, m, sh, v;
        nr_px_word(rc.psm, rc.bp, rc.bw, x, y, &w, &m, &sh);
        if (bpp == 32) memcpy(&v, data + 4 * i, 4);
        else if (bpp == 16) v = data[2 * i] | (data[2 * i + 1] << 8);
        else if (bpp == 8) v = data[i];
        else v = (data[i >> 1] >> ((i & 1) * 4)) & 15;
        uint32_t *p = (uint32_t *)g_ref.data() + w;
        *p = (*p & ~m) | ((v << sh) & m);
    }
}

static uint64_t ref_hash(uint64_t tex0)
{
    int psm = (int)TBITS(tex0, 20, 6);
    uint32_t bp = TBITS(tex0, 0, 14), bw = TBITS(tex0, 14, 6);
    int w = 1 << TBITS(tex0, 26, 4), h = 1 << TBITS(tex0, 30, 4);
    int bwk = psm == CT32 ? 8 : psm == CT16 ? 16 : psm == T8 ? 16 : 32, bhk = psm == CT32 || psm == CT16 ? 8 : 16;
    std::vector<uint8_t> b;
    for (int by = 0; by < (h / bhk > 1 ? h / bhk : 1); by++)
        for (int bx = 0; bx < (w / bwk > 1 ? w / bwk : 1); bx++) {
            uint32_t a = nr_px_addr(psm, bp, bw, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) & ~255u;
            b.insert(b.end(), g_ref.begin() + a, g_ref.begin() + a + 256);
        }
    return XXH3_64bits(b.data(), b.size());
}

int main(int argc, char **argv)
{
    bool control = argc > 1 && !strcmp(argv[1], "--control");
    /* the texture root of test 5: a folder of its own in the working directory */
    const std::string troot = std::string("rg-texrep-test-") + (control ? "c" : "t");
#ifdef _WIN32
    _putenv_s("RG_TEXTURES", troot.c_str());
#else
    setenv("RG_TEXTURES", troot.c_str(), 1);
#endif
    {
        std::vector<std::string> old;   /* (an earlier run's pack file) */
        list_files(troot + "/SCUS-97490/replacements", "", old);
        for (const std::string &f : old) remove((troot + "/SCUS-97490/replacements/" + f).c_str());
    }
    /* 1. names */
    {
        Name n = { 0x042f157c3545a5aeull, 0x015f23a3430ff50full, 0x2213, true };
        EXPECT(name_str(n) == "42f157c3545a5ae-15f23a3430ff50f-00002213", "format %s", name_str(n).c_str());
        Name m;
        EXPECT(parse_name("42F157C3545A5AE-15f23a3430ff50f-00002213", &m) && m == n, "parse unpadded / upper case");
        EXPECT(parse_name("042f157c3545a5ae-015f23a3430ff50f-00002213", &m) && m == n, "parse padded");
        EXPECT(parse_name("b7a26ac4cf10048e-00002640", &m) && !m.has_clut && m.bits == 0x2640, "parse without CLUT");
        EXPECT(!parse_name("b7a26ac4cf10048e-2640", &m) && !parse_name("xyz-00002640", &m), "reject bad names");
    }
    /* 2. + 3. the lazy copy vs an eager one */
    nr_texrep_config(0, 1);   /* (replace mode: no dump folder made) */
    std::mt19937 rng(7);
    struct T { int psm; uint32_t bp, bw, w, h; } tex[] = {
        { CT32, 1024, 4, 256, 128 }, { T8, 3000, 4, 256, 256 }, { T4, 5000, 8, 512, 128 }, { CT16, 7000, 2, 128, 64 },
        { CT32, 9000, 1, 8, 8 },
    };
    for (const T &t : tex) {
        /* the texture written by two transfers: the whole rectangle, then a part not aligned to
         * blocks over it (partly covered blocks: made at once) */
        int bpp = nr_psm_bpp(t.psm);
        for (int pass = 0; pass < 2; pass++) {
            gs_mem_rect rc = { t.bp, t.bw, t.psm, pass ? 3u : 0u, pass ? 5u : 0u, pass ? t.w / 2 + 1 : t.w, pass ? t.h / 2 + 3 : t.h };
            uint32_t npx = rc.w * rc.h;
            std::vector<uint8_t> d(((size_t)npx * bpp + 7) / 8);
            for (auto &c : d) c = (uint8_t)rng();
            nr_texrep_xfer(&rc, d.data(), npx);
            if (control && pass == 1) d[d.size() / 2] ^= 0x10;
            ref_xfer(rc, d.data(), npx);
        }
        int tw = 0, th = 0;
        while ((1u << tw) < t.w) tw++;
        while ((1u << th) < t.h) th++;
        uint64_t tex0 = t.bp | ((uint64_t)t.bw << 14) | ((uint64_t)t.psm << 20) | ((uint64_t)tw << 26) | ((uint64_t)th << 30);
        uint16_t clut[512];
        for (int i = 0; i < 512; i++) clut[i] = (uint16_t)(i * 2654435761u >> 7);
        char nm[80];
        EXPECT(nr_texrep_name(tex0, 0, clut, nm, sizeof nm), "psm %02x: not nameable", t.psm);
        Name n;
        EXPECT(parse_name(nm, &n), "name %s", nm);
        EXPECT(n.th == ref_hash(tex0), "psm %02x %ux%u: data hash %llx vs eager %llx", t.psm, t.w, t.h,
               (unsigned long long)n.th, (unsigned long long)ref_hash(tex0));
        if (indexed(t.psm)) {
            uint32_t e[256];
            int k = t.psm == T8 ? 256 : 16;
            for (int i = 0; i < k; i++) e[i] = clut[i] | ((uint32_t)clut[i + 256] << 16);
            EXPECT(n.ch == XXH3_64bits(e, (size_t)k * 4), "psm %02x: CLUT hash", t.psm);
        }
        EXPECT(n.bits == ((uint32_t)t.psm | (uint32_t)tw << 6 | (uint32_t)th << 10), "bits %x", n.bits);
    }
    /* 4. block decoders */
    {
        uint8_t b1[8] = { 0x00, 0xF8, 0x1F, 0x00, 0xE4, 0xE4, 0xE4, 0xE4 };   /* red, blue; indices 0 1 2 3 per row */
        uint32_t px[16];
        bc_color(b1, px, true);
        EXPECT(px[0] == 0xFF0000FFu && px[1] == 0xFFFF0000u, "bc1 endpoints %08x %08x", px[0], px[1]);
        EXPECT(px[2] == 0xFF5500AAu && px[3] == 0xFFAA0055u, "bc1 thirds %08x %08x", px[2], px[3]);
        uint8_t b3c[8] = { 0x1F, 0x00, 0x00, 0xF8, 0xE4, 0xE4, 0xE4, 0xE4 };  /* c0 < c1: 3 colours + transparent */
        bc_color(b3c, px, true);
        EXPECT(px[3] == 0 && px[2] == 0xFF7F007Fu, "bc1 3-colour %08x %08x", px[2], px[3]);
        uint8_t a[8] = { 255, 0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88 };      /* indices 0,1,2,... pattern */
        uint8_t al[16];
        bc3_alpha(a, al);
        EXPECT(al[0] == 255 && al[1] == 0x0, "bc3 alpha %u %u", al[0], al[1]);
        /* BC7 mode 6: endpoints all 0x7F with p-bit 1 -> 255; indices 0 -> colour 255 everywhere */
        uint8_t b7[16] = {};
        {
            int pos = 0;
            auto put = [&](uint32_t v, int nbits) { for (int i = 0; i < nbits; i++, pos++) if ((v >> i) & 1) b7[pos >> 3] |= (uint8_t)(1 << (pos & 7)); };
            put(1u << 6, 7);                         /* mode 6 */
            for (int i = 0; i < 8; i++) put(0x40, 7);  /* R0 R1 G0 G1 B0 B1 A0 A1 = 0x40 */
            put(1, 1); put(0, 1);                    /* p-bits: endpoint 0 -> 0x81, endpoint 1 -> 0x80 */
            put(0, 3);                               /* anchor index */
            for (int i = 1; i < 16; i++) put(15, 4); /* the rest at endpoint 1 */
        }
        bc7_block(b7, px);
        EXPECT(px[0] == 0x81818181u && px[1] == 0x80808080u, "bc7 mode 6 %08x %08x", px[0], px[1]);
    }
    /* 5. live toggles (the settings menu: gpu_set_enhance -> nr_texrep_config) */
    {
        uint64_t tex0 = 1024 | (4ull << 14) | ((uint64_t)CT32 << 20) | (8ull << 26) | (7ull << 30);   /* tex[0] */
        char nm[80], nm2[80];
        EXPECT(nr_texrep_name(tex0, 0, NULL, nm, sizeof nm), "toggle: tex[0] not nameable");
        const std::string rdir = troot + "/SCUS-97490/replacements";
        mkdir_p(rdir);
        {
            std::vector<std::string> old;   /* (an earlier run's dumps) */
            list_files(troot + "/SCUS-97490/dumps", "", old);
            for (const std::string &f : old) remove((troot + "/SCUS-97490/dumps/" + f).c_str());
        }
        uint32_t px4[16];
        for (int i = 0; i < 16; i++) px4[i] = 0x80123456u + (uint32_t)i;
        EXPECT(stbi_write_png((rdir + "/" + nm + ".png").c_str(), 4, 4, 4, px4, 16), "toggle: write pack file");
        nr_texrep_config(0, 0);
        EXPECT(S->mem.empty() && !nr_texrep_on() && !nr_texrep_name(tex0, 0, NULL, nm2, sizeof nm2), "both off: CPU copy kept");
        EXPECT(nr_texrep_config(0, 1) == 1, "replace on again: no new CPU copy");
        nr_texrep_load_all(g_ref.data());   /* (the device fills it from its mirror) */
        EXPECT(nr_texrep_name(tex0, 0, NULL, nm2, sizeof nm2) && !strcmp(nm, nm2), "after the reload: %s vs %s", nm2, nm);
        EXPECT(S->pack.size() == 1, "pack file added while off not indexed (%zu)", S->pack.size());
        uint32_t key[8] = { 0x1234, 1, 2, 3, 4, 5, 6, 7 };
        const NrRepImg *im = NULL;
        for (int i = 0; i < 500 && !im; i++) {
            im = nr_texrep_draw(key, tex0, 0, NULL, 1);
            if (!im) std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        EXPECT(im && im->w == 4 && im->h == 4 && im->px[0] == 0x80123456u && nr_texrep_valid(im), "replacement not loaded");
        nr_texrep_config(0, 0);
        EXPECT(!nr_texrep_valid(im) && S->live.empty() && S->reps.empty() && S->img_bytes == 0, "replace off: images kept");
        /* dumps and movies */
        nr_texrep_config(1, 0);
        nr_texrep_load_all(g_ref.data());
        uint64_t d0 = S->n_dumped;
        uint32_t k2[8] = { 0x5678, 1, 2, 3, 4, 5, 6, 7 };
        nr_gs_movie = 1;
        nr_texrep_draw(k2, tex0, 0, NULL, 1);
        EXPECT(S->n_dumped == d0 && S->n_movie_skip == 1, "dumped during a movie (%llu)", (unsigned long long)(S->n_dumped - d0));
        nr_gs_movie = 0;
        nr_texrep_draw(k2, tex0, 0, NULL, 1);
        EXPECT(S->n_dumped == d0 + 1, "not dumped after the movie");
        uint64_t tex1 = 3000 | (4ull << 14) | ((uint64_t)T8 << 20) | (8ull << 26) | (8ull << 30);   /* tex[1] */
        uint16_t clut[512] = {};
        uint32_t k3[8] = { 0x9abc, 1, 2, 3, 4, 5, 6, 7 };
        nr_texrep_config(2, 0);
        nr_gs_movie = 1;
        nr_texrep_draw(k3, tex1, 0, clut, 1);
        nr_gs_movie = 0;
        EXPECT(S->n_dumped == d0 + 2, "mode 2: movie-time texture not dumped");
        nr_texrep_config(0, 0);
        nr_texrep_stats(stdout);   /* (waits for the dump files) */
        struct stat st;
        EXPECT(stat((troot + "/SCUS-97490/dumps/" + nm + ".png").c_str(), &st) == 0, "dump file %s missing", nm);
    }
    printf("%s (%d failures)\n", g_fail ? "FAIL" : "PASS", g_fail);
    return g_fail ? 1 : 0;
}
