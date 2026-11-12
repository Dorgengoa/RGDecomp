/* SPDX-License-Identifier: CC0-1.0 */
/* Interpolated presentation, device side (nr_interp.h, docs/NATIVE-RENDER.md "Interpolated
 * presentation"): the retained frame as the device's own command list.
 *
 * A recorder wraps the backend (installed when interpolation is first switched on; until then
 * nothing changes).  While a log records, every command that draws is kept with copies of what
 * it points at: native draws (mesh and immediate: targets, state, constant rows, vertices,
 * the decoded texture's content key), target copies, loads and clears, target creations and
 * destructions.  Not kept: local-memory traffic (transfers, write-backs, CLUT loads, local copies,
 * read-backs): a replay never touches local memory, so the game's view of the device cannot
 * change.  Each target the log writes that existed before it gets a pre-image (a copy taken
 * just before the log's first write), so a replay starts from the target's state at the frame's
 * start (frames that blend over last frame's content draw the same image again).
 *
 * Replay: the current content of every pre-existing target the log wrote is saved (once per
 * dirty period), the pre-images put back, then the commands run on the real backend: textures by
 * their decoded key only (tex_cached_only), targets the log created replaced by temporary ones,
 * mesh draws with constant rows / bones from nr_ip_mesh_cb (interpolated); then the display
 * shows the in-between frame.  Restore: the saved content back (exact). */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <map>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>

#include "gpu_internal.h"
#include "nr_interp.h"

GpuBackend **gpu_ip_backend(gpu_renderer *r);

namespace {

enum CmdKind { C_DRAW, C_COPY, C_LOAD, C_CLEAR, C_CREATE, C_DESTROY, C_RESIZE, C_REINT };

struct Cmd {
    CmdKind k;
    GpuNrDraw g;                 /* C_DRAW (pointers re-pointed into the owned copies at replay) */
    int has_d;
    gpu_nr_draw d;
    std::vector<GpuImVtx> im;
    std::vector<uint32_t> runs;
    std::vector<uint32_t> rgba;
    uint32_t mesh_id;            /* the mesh record drawn (0: immediate / generated) */
    int rt[3];                   /* referenced targets (color, depth, tex / dst, src) */
    int srt[3];                  /* C_DRAW: the targets as frame-stable tokens (a target the log created: its creation ordinal) */
    uint32_t life[3];
    int a, b, c;                 /* C_COPY dx dy; C_CREATE depth w h; C_RESIZE w h */
    GpuRect r;
    uint32_t bp, bw;
    int psm;
    int img;                     /* C_LOAD: the target as the load left it (local memory may differ at replay) */
    int img_rect;                /* C_LOAD: img holds only the loaded rect, at (0, 0) */
    GpuRect r2;                  /* C_REINT: the source rect (r: the destination's); bp bw psm the destination's */
    uint32_t bp2, bw2;
    int psm2;
};

struct Pre { int id; uint32_t life; int img; };

struct Slot {
    int rec;                     /* recorded (complete or recording) */
    int bad;                     /* something not replayable met */
    std::vector<Cmd> cmds;
    std::vector<Pre> pre;        /* pre-existing targets written, their pre-images */
    std::map<int, uint32_t> born;   /* targets created in the log: id -> life at creation */
    std::map<int, int> ord;      /* targets created in the log: id -> creation ordinal (current life) */
    int nborn = 0;
    uint64_t gen = 0;            /* changes whenever the slot is freed (pair_im's cache) */
};

struct Stats {
    uint64_t draws, copies, loads, clears, creates, pre_images, pre_fail;
    uint64_t replays, replay_draws, replay_interp, replay_stale, replay_notex, replay_bad;
    uint64_t saves, restores, put_fail, pre_skipped;
    uint64_t pc_plans, pc_plan_skip, pc_plan_cmds, pc_plan_cuts, pc_passes, pc_skipped, pc_taken, pc_put, pc_fail;
    uint64_t im_draws, im_paired, im_tris, im_tris_lerped, trimmed, zs_strips, zs_groups, zs_groups_all, zs_pose, zs_widened;
    uint64_t oom;                /* logs ended by std::bad_alloc while recording (IpRec::oom) */
};

static uint32_t g_mesh_id;
static int dbg_on()
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_INTERP_DEBUG"); on = e && *e && e[0] != '0'; }
    return on;
}

class IpRec : public GpuBackend {
public:
    GpuBackend *in;
    std::vector<uint32_t> life;  /* per target id: creations + destructions */
    Slot slot[NR_IP_SLOTS];
    int cur = -1;                /* slot recording */
    uint64_t gen_clock = 0;
    /* pair_im of the last (slot, previous slot) pair: the same for every pass between two game
     * frames (the passes of a frame pair differ only in alpha) */
    struct { uint64_t gs, gp; size_t ns, np; std::vector<int> m; } pm_cache = { 0, 0, 0, 0, {} };
    int replaying = 0;
    std::vector<Pre> saved;      /* current content of targets a replay wrote (restore) */
    int dirty = 0;
    Stats st = {};

    explicit IpRec(GpuBackend *b) : in(b) { sync(); }
    ~IpRec() override;
    void sync()
    {
        n_decodes = in->n_decodes;
        n_decode_hits = in->n_decode_hits;
        n_nr_tex = in->n_nr_tex;
        n_nr_mesh = in->n_nr_mesh;
        n_nr_blend_approx = in->n_nr_blend_approx;
        n_nr_mesh_pre = in->n_nr_mesh_pre;
        n_rt_pool_hits = in->n_rt_pool_hits;
    }
    uint32_t life_of(int id) const { return id >= 0 && (size_t)id < life.size() ? life[(size_t)id] : 0; }
    void bump(int id)
    {
        if (id < 0) return;
        if ((size_t)id >= life.size()) life.resize((size_t)id + 1, 0);
        life[(size_t)id]++;
    }
    void free_slot(int i)
    {
        Slot &s = slot[i];
        for (Pre &p : s.pre)
            if (p.img >= 0) in->rt_destroy(p.img);
        for (Cmd &c : s.cmds)
            if (c.img >= 0) in->rt_destroy(c.img);
        s.pre.clear();
        s.cmds.clear();
        s.born.clear();
        s.ord.clear();
        s.nborn = 0;
        s.rec = 0;
        s.bad = 0;
        s.gen = ++gen_clock;
    }
    /* a write to target id is coming: its pre-image first (pre-existing targets, once per log) */
    void writes(int id)
    {
        if (cur < 0 || replaying || id < 0) return;
        Slot &s = slot[cur];
        if (s.born.count(id)) return;
        for (const Pre &p : s.pre)
            if (p.id == id) return;
        Pre p;
        p.id = id;
        p.life = life_of(id);
        p.img = in->rt_clone(id);
        if (p.img < 0) { st.pre_fail++; s.bad = 1; }
        else st.pre_images++;
        s.pre.push_back(p);
    }
    /* Out of memory while recording (gfxperf10): std::bad_alloc from a command's copies (the log's
     * vector growing, vertices, texels, maps) ends this frame's log instead of the process: the
     * slot is freed (its capacity given back) and marked unrecorded, so no pass replays it (the
     * presentation shows the newest frame, as for any frame without a log) and recording stops
     * until the next frame boundary.  Seen when the machine's commit limit was reached
     * (gfxperf9 timing round 1: 51.05 of 51.06 GB committed machine-wide).  $RG_INTERP_OOM_AT=N
     * (measurement, fault injection): every N-th recorded command (run-wide count) throws instead. */
    uint64_t n_added = 0;
    static uint64_t oom_at()
    {
        static long long at = -1;
        if (at < 0) { const char *e = getenv("RG_INTERP_OOM_AT"); at = e ? atoll(e) : 0; if (at < 0) at = 0; }
        return (uint64_t)at;
    }
    void oom()
    {
        st.oom++;
        if (cur < 0) return;
        free_slot(cur);
        std::vector<Cmd>().swap(slot[cur].cmds);
        std::vector<Pre>().swap(slot[cur].pre);
        cur = -1;
        if (dbg_on() || memlog_on()) fprintf(stderr, "interp device: out of memory while recording (%llu): frame not kept\n",
                                             (unsigned long long)st.oom);
    }
    Cmd &add(CmdKind k)
    {
        Slot &s = slot[cur];
        if (++n_added % (oom_at() ? oom_at() : ~0ull) == 0) throw std::bad_alloc();
        s.cmds.emplace_back();
        Cmd &c = s.cmds.back();
        c.k = k;
        c.has_d = 0;
        c.mesh_id = 0;
        c.rt[0] = c.rt[1] = c.rt[2] = -1;
        c.srt[0] = c.srt[1] = c.srt[2] = -1;
        c.life[0] = c.life[1] = c.life[2] = 0;
        c.img = -1;
        c.img_rect = 0;
        return c;
    }
    bool recording() const { return cur >= 0 && !replaying; }
    /* $RG_INTERP_MEMLOG=1 (measurement, gfxperf10): host bytes each slot holds, one stderr line per
     * frame boundary (the slot just recorded + all slots), peaks at exit (gpu_ip_stats) */
    static int memlog_on()
    {
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_INTERP_MEMLOG"); on = e && *e && e[0] != '0'; }
        return on;
    }
    size_t slot_bytes(const Slot &s, size_t *payload) const
    {
        size_t p = 0;
        for (const Cmd &c : s.cmds)
            p += c.im.capacity() * sizeof(GpuImVtx) + (c.runs.capacity() + c.rgba.capacity()) * sizeof(uint32_t);
        if (payload) *payload = p;
        return s.cmds.capacity() * sizeof(Cmd) + p;
    }
    size_t mem_peak_all = 0, mem_peak_slot = 0, mem_peak_cmds = 0, mem_peak_payload = 0;
    void memlog(int next)
    {
        if (!memlog_on()) return;
        size_t all = 0;
        for (int i = 0; i < NR_IP_SLOTS; i++) all += slot_bytes(slot[i], NULL);
        if (all > mem_peak_all) mem_peak_all = all;
        if (cur >= 0) {
            size_t pay = 0, b = slot_bytes(slot[cur], &pay);
            if (b > mem_peak_slot) mem_peak_slot = b;
            if (slot[cur].cmds.size() > mem_peak_cmds) mem_peak_cmds = slot[cur].cmds.size();
            if (pay > mem_peak_payload) mem_peak_payload = pay;
            fprintf(stderr, "interp mem: slot %d cmds %zu cap %zu (%.1f MB) payload %.1f MB pre %zu; all slots %.1f MB; next %d\n",
                    cur, slot[cur].cmds.size(), slot[cur].cmds.capacity(),
                    slot[cur].cmds.capacity() * sizeof(Cmd) / 1048576.0, pay / 1048576.0, slot[cur].pre.size(), all / 1048576.0, next);
        }
    }

    /* ---- the backend, forwarded ---- */
    const char *name() const override { return in->name(); }
    bool exact() const override { return in->exact(); }
    bool rov() const override { return in->rov(); }
    bool zrov() const override { return in->zrov(); }
    void mirror_upload(uint32_t off, uint32_t len, const uint8_t *src) override { in->mirror_upload(off, len, src); }
    void mirror_download(const uint32_t *runs, int nruns, uint8_t *vram) override { in->mirror_download(runs, nruns, vram); }
    bool can_merge() const override { return in->can_merge(); }
    void mirror_merge(uint32_t w0, uint32_t n, const uint32_t *dm) override { in->mirror_merge(w0, n, dm); }
    int rt_create(int depth, int w, int h) override
    {
        int id = in->rt_create(depth, w, h);
        if (id >= 0) {
            bump(id);
            if (recording()) {
                try {
                    Cmd &c = add(C_CREATE);
                    c.rt[0] = id;
                    c.life[0] = life_of(id);
                    c.a = depth; c.b = w; c.c = h;
                    slot[cur].born[id] = life_of(id);
                    slot[cur].ord[id] = slot[cur].nborn++;
                    st.creates++;
                } catch (const std::bad_alloc &) { oom(); }
            }
        }
        sync();
        return id;
    }
    void rt_resize(int id, int w, int h) override
    {
        if (recording()) {
            try {
                writes(id);
                Cmd &c = add(C_RESIZE);
                c.rt[0] = id;
                c.life[0] = life_of(id);
                c.a = w; c.b = h;
            } catch (const std::bad_alloc &) { oom(); }
        }
        in->rt_resize(id, w, h);
    }
    void rt_destroy(int id) override
    {
        if (recording() && id >= 0) {
            try {
                Cmd &c = add(C_DESTROY);
                c.rt[0] = id;
                c.life[0] = life_of(id);
                slot[cur].ord.erase(id);
            } catch (const std::bad_alloc &) { oom(); }
        }
        in->rt_destroy(id);
        bump(id);
    }
    void rt_clear(int id) override
    {
        if (recording()) {
            try {
                writes(id);
                Cmd &c = add(C_CLEAR);
                c.rt[0] = id;
                c.life[0] = life_of(id);
                st.clears++;
            } catch (const std::bad_alloc &) { oom(); }
        }
        in->rt_clear(id);
    }
    void rt_load(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        if (recording()) {
            try {
                writes(id);
                Cmd &c = add(C_LOAD);
                c.rt[0] = id;
                c.life[0] = life_of(id);
                c.bp = bp; c.bw = bw; c.psm = psm; c.r = r;
                st.loads++;
            } catch (const std::bad_alloc &) {
                oom();
                in->rt_load(id, bp, bw, psm, r);
                return;
            }
            in->rt_load(id, bp, bw, psm, r);
            /* the target after the load: the replay puts it back (local memory is not the same
             * then: the core makes it current from live targets before a load) */
            {
                /* ($RG_INTERP_LOADRECT, default on) only the loaded rect: the replay copies just it */
                Cmd &cl = slot[cur].cmds.back();
                cl.img = loadrect_on() ? in->rt_clone_rect(id, r) : -1;
                cl.img_rect = cl.img >= 0;
                if (cl.img < 0) cl.img = in->rt_clone(id);
            }
            return;
        }
        in->rt_load(id, bp, bw, psm, r);
    }
    void rt_writeback(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override { in->rt_writeback(id, bp, bw, psm, r); }
    bool rt_copy(int dst, int dx, int dy, int src, const GpuRect &sr) override
    {
        if (recording()) {
            try {
                writes(dst);
                writes(src);
                Cmd &c = add(C_COPY);
                c.rt[0] = dst; c.life[0] = life_of(dst);
                c.rt[1] = src; c.life[1] = life_of(src);
                c.a = dx; c.b = dy; c.r = sr;
                st.copies++;
            } catch (const std::bad_alloc &) { oom(); }
        }
        return in->rt_copy(dst, dx, dy, src, sr);
    }
    bool rt_reinterpret(int dst, uint32_t dbp, uint32_t dbw, int dpsm, const GpuRect &dr, int src, uint32_t sbp, uint32_t sbw,
                        int spsm, const GpuRect &sr) override
    {
        if (recording()) {
            try {
                writes(dst);
                writes(src);
                Cmd &c = add(C_REINT);
                c.rt[0] = dst; c.life[0] = life_of(dst);
                c.rt[1] = src; c.life[1] = life_of(src);
                c.bp = dbp; c.bw = dbw; c.psm = dpsm; c.r = dr;
                c.bp2 = sbp; c.bw2 = sbw; c.psm2 = spsm; c.r2 = sr;
            } catch (const std::bad_alloc &) { oom(); }
        }
        return in->rt_reinterpret(dst, dbp, dbw, dpsm, dr, src, sbp, sbw, spsm, sr);
    }
    int rt_read(int id, const GpuRect &r, uint32_t *out) override { return in->rt_read(id, r, out); }
    void set_clut(const GpuClutCB &c) override { in->set_clut(c); }
    void set_clut_part(const GpuClutCB &c, const uint8_t *own) override { in->set_clut_part(c, own); }
    bool clut_load_gpu(const uint32_t u[3][4]) override { return in->clut_load_gpu(u); }
    bool clut_read(GpuClutCB *out) override { return in->clut_read(out); }
    bool mem_copy(const uint32_t u[3][4]) override { return in->mem_copy(u); }
    bool mem_xfer_batch(const uint8_t *bytes, uint32_t nbytes, const uint32_t *desc, uint32_t ndesc, uint32_t npx) override
    {
        return in->mem_xfer_batch(bytes, nbytes, desc, ndesc, npx);
    }
    void draw(const GpuDraw &d) override
    {
        if (recording()) slot[cur].bad = 1;   /* (the GS-exact path: not in the native-only device) */
        in->draw(d);
    }
    void kick() override { in->kick(); sync(); }
    int snap_copy(const uint32_t *runs, int nruns) override { return in->snap_copy(runs, nruns); }
    const uint8_t *snap_map(int s) override { return in->snap_map(s); }
    void snap_unmap(int s) override { in->snap_unmap(s); }
    int disp_rt[2] = { -1, -1 };   /* the targets the last display read (circuits) */
    /* redirected replay ($RG_INTERP_REDIRECT, default 1; docs/NATIVE-RENDER.md "Interpolation at
     * 5x"): a pass writes no pre-existing target; each one it touches is a temporary made from
     * its pre-image (pre-existing id -> temporary), the compose reads the temporaries of the
     * displayed targets, the restore only frees them.  (Was: the targets' content saved, the
     * pre-images put in, the content put back after the compose: three whole-target copies per
     * target instead of one.) */
    std::map<int, int> redir;
    static int redirect_on()
    {
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_INTERP_REDIRECT"); on = !(e && e[0] == '0'); }
        return on;
    }
    const GpuDisplay &redir_display(const GpuDisplay &d, GpuDisplay &d2)
    {
        if (redir.empty()) return d;
        d2 = d;
        for (int i = 0; i < 2; i++) {
            if (!d2.c[i].en || d2.c[i].rt < 0) continue;
            auto it = redir.find(d2.c[i].rt);
            if (it != redir.end()) d2.c[i].rt = it->second;
        }
        return d2;
    }
    void drop_redir()
    {
        for (auto &kv : redir) {
            in->rt_destroy(kv.second);
            bump(kv.second);
        }
        redir.clear();
    }
    void note_display(const GpuDisplay &d)
    {
        for (int i = 0; i < 2; i++) disp_rt[i] = d.c[i].en ? d.c[i].rt : -1;
    }
    int display(const GpuDisplay &d, uint32_t *out) override
    {
        note_display(d);
        in->prof_tag(dirty ? GPT_COMPOSE_PASS : GPT_COMPOSE);
        GpuDisplay d2;
        int rc = in->display(redir_display(d, d2), out);
        in->prof_tag(GPT_GAME);
        sync();
        return rc;
    }
    int display_post(const GpuDisplay &d, const GpuPost &p, uint32_t *out) override
    {
        note_display(d);
        in->prof_tag(dirty ? GPT_COMPOSE_PASS : GPT_COMPOSE);
        GpuDisplay d2;
        int rc = in->display_post(redir_display(d, d2), p, out);
        in->prof_tag(GPT_GAME);
        sync();
        return rc;
    }
    void *shared_out() override { return in->shared_out(); }
    bool vk_present_device(gpu_vk_device *o) override { return in->vk_present_device(o); }
    void set_scale(int s) override
    {
        pc_drop();
        for (int i = 0; i < NR_IP_SLOTS; i++) free_slot(i);
        drop_saved();
        in->set_scale(s);
    }
    bool nr_draw(const GpuNrDraw &g) override
    {
        if (recording()) {
            try {
                /* pre-images of what the draw writes and reads (a target read may be gone at replay) */
                writes(g.color_rt);
                writes(g.depth_rt);
                writes(g.tex_rt);
                Cmd &c = add(C_DRAW);
                c.g = g;
                if (g.d) { c.d = *g.d; c.has_d = 1; }
                if (g.im && g.nim) c.im.assign(g.im, g.im + g.nim);
                if (g.runs && g.nruns > 0) c.runs.assign(g.runs, g.runs + 2 * g.nruns);
                if (g.dec_rgba) {
                    size_t n = (size_t)(g.dec_rect.x1 - g.dec_rect.x0) * (size_t)(g.dec_rect.y1 - g.dec_rect.y0);
                    c.rgba.assign(g.dec_rgba, g.dec_rgba + n);
                }
                c.mesh_id = g.im ? 0 : g_mesh_id;
                c.rt[0] = g.color_rt; c.life[0] = life_of(g.color_rt);
                c.rt[1] = g.depth_rt; c.life[1] = life_of(g.depth_rt);
                c.rt[2] = g.tex_rt; c.life[2] = life_of(g.tex_rt);
                for (int k = 0; k < 3; k++) {
                    auto o = slot[cur].ord.find(c.rt[k]);
                    c.srt[k] = o != slot[cur].ord.end() ? 0x40000000 + o->second : c.rt[k];
                }
                st.draws++;
            } catch (const std::bad_alloc &) { oom(); }
        }
        bool ok = in->nr_draw(g);
        sync();
        return ok;
    }
    bool nr_tex_cached(const uint32_t *key, const GpuRect &rc) override { return in->nr_tex_cached(key, rc); }
    void nr_mesh_prewarm(const gpu_nr_mesh &m) override { in->nr_mesh_prewarm(m); }
    int rt_clone(int src) override { return in->rt_clone(src); }
    bool rt_put(int dst, int src) override { return in->rt_put(dst, src); }
    void prof_tag(int cat) override { in->prof_tag(cat); }
    int rt_clone_rect(int src, const GpuRect &r) override { return in->rt_clone_rect(src, r); }

    /* ---- interpolated presentation ---- */
    void drop_saved()
    {
        for (Pre &p : saved)
            if (p.img >= 0) in->rt_destroy(p.img);
        saved.clear();
        drop_redir();
        dirty = 0;
    }
    void restore()
    {
        if (!dirty) return;
        in->prof_tag(GPT_RESTORE);
        drop_redir();
        for (Pre &p : saved) {
            if (p.img < 0) continue;
            if (life_of(p.id) != p.life || !in->rt_put(p.id, p.img)) st.put_fail++;
            in->rt_destroy(p.img);
        }
        saved.clear();
        dirty = 0;
        st.restores++;
        in->prof_tag(GPT_GAME);
    }
    /* map a recorded target to the one the replay uses (-1 stays -1); false: stale */
    bool map_rt(const Slot &s, std::map<int, int> &tmp, int id, uint32_t lf, int *out)
    {
        if (id < 0) { *out = -1; return true; }
        auto t = tmp.find(id);
        if (t != tmp.end()) { *out = t->second; return true; }
        if (life_of(id) != lf) return false;
        (void)s;
        *out = id;
        return true;
    }
    /* the slots sl[0..n) (oldest first) run again in order; interp_at: the one whose mesh draws
     * are interpolated (-1: none) */
    int replay(const int *sl, int n, int interp_at, int prev, float alpha)
    {
        for (int i = 0; i < n; i++)
            if (!slot[sl[i]].rec || slot[sl[i]].bad) { st.replay_bad++; return -1; }
        /* the targets' current content, once per dirty period (redirected: nothing to save; the
         * previous pass's temporaries go) */
        const int rd = redirect_on();
        if (rd) drop_redir();
        in->prof_tag(GPT_SAVE);
        for (int i = 0; i < n && !rd; i++)
            for (const Pre &p : slot[sl[i]].pre) {
                bool have = false;
                for (const Pre &q : saved)
                    if (q.id == p.id) have = true;
                if (have || p.img < 0) continue;
                if (life_of(p.id) != p.life) continue;   /* (destroyed since: nothing to keep) */
                Pre q;
                q.id = p.id;
                q.life = p.life;
                q.img = in->rt_clone(p.id);
                if (q.img < 0) { st.put_fail++; dirty = !saved.empty(); return -1; }
                saved.push_back(q);
                st.saves++;
            }
        dirty = 1;
        replaying = 1;
        std::map<int, int> tmp;   /* targets the slots created or that are gone -> temporary ones */
        /* every target at its state when the sequence began: the first pre-image of it in the
         * sequence (targets an earlier slot created are its temporaries, already right) */
        std::vector<size_t> lims((size_t)n);
        for (int i = 0; i < n; i++) {
            /* after the interpolated frame only what reaches the displayed target matters (this
             * game: the copy of the frame into the display buffer at the next frame's start);
             * the rest of the later frames is drawn into targets the restore puts back anyway */
            size_t lim = slot[sl[i]].cmds.size();
            if (interp_at >= 0 && i > interp_at && trim_on() && (disp_rt[0] >= 0 || disp_rt[1] >= 0)) {
                lim = 0;
                for (size_t ci = 0; ci < slot[sl[i]].cmds.size(); ci++) {
                    const Cmd &c = slot[sl[i]].cmds[ci];
                    if (c.k != C_CREATE && c.k != C_DESTROY && c.rt[0] >= 0 && (c.rt[0] == disp_rt[0] || c.rt[0] == disp_rt[1]))
                        lim = ci + 1;
                }
                st.trimmed += slot[sl[i]].cmds.size() - lim;
            }
            lims[(size_t)i] = lim;
        }
        const std::vector<std::vector<char>> *need = live_cmds(sl, n, lims);
        /* (redirected) the pre-existing targets the replayed commands touch: only they need a
         * temporary (the others' pre-images would be copied for nothing) */
        std::vector<char> touched;
        if (rd) {
            auto tch = [&touched](int id) {
                if (id < 0) return;
                if ((size_t)id >= touched.size()) touched.resize((size_t)id + 1, 0);
                touched[(size_t)id] = 1;
            };
            for (int i = 0; i < n; i++) {
                const Slot &s = slot[sl[i]];
                for (size_t ci = 0; ci < lims[(size_t)i] && ci < s.cmds.size(); ci++) {
                    if (need && !(*need)[(size_t)i][ci]) continue;
                    for (int k = 0; k < 3; k++) tch(s.cmds[ci].rt[k]);
                }
            }
            tch(disp_rt[0]);
            tch(disp_rt[1]);
        }
        in->prof_tag(GPT_PRE);
        {
            std::vector<int> done;
            std::map<int, uint32_t> born;
            for (int i = 0; i < n; i++) {
                for (const Pre &p : slot[sl[i]].pre) {
                    bool skip = p.img < 0 || born.count(p.id);
                    for (int d : done)
                        if (d == p.id) skip = true;
                    if (skip) continue;
                    done.push_back(p.id);
                    if (rd && !((size_t)p.id < touched.size() && touched[(size_t)p.id])) {
                        st.pre_skipped++;
                    } else if (rd) {
                        /* a temporary from its pre-image; the compose reads it when displayed */
                        int t = in->rt_clone(p.img);
                        if (t >= 0) {
                            bump(t);
                            tmp[p.id] = t;
                            if (life_of(p.id) == p.life) redir[p.id] = t;
                        } else
                            st.put_fail++;
                    } else if (life_of(p.id) != p.life) {
                        /* destroyed (or re-made) since: a temporary target from its pre-image */
                        int t = in->rt_clone(p.img);
                        if (t >= 0) tmp[p.id] = t;
                        else st.put_fail++;
                    } else if (!in->rt_put(p.id, p.img)) {
                        st.put_fail++;
                    }
                }
                for (auto &kv : slot[sl[i]].born) born[kv.first] = kv.second;
            }
        }
        /* the pair cache (pc_plan): the first pass of a frame pair takes the copies, the later
         * ones skip what is the same in all of them */
        const Slot *pslot = interp_at >= 0 && prev >= 0 && prev != sl[interp_at] && slot[prev].rec && !slot[prev].bad ? &slot[prev] : NULL;
        int pcmode = 0;   /* 0 off, 1 capture, 2 use */
        if (paircache_on() && rd && interp_at >= 0 && need) {
            std::vector<uint64_t> key = dce.key;
            key.push_back((uint64_t)(uint32_t)interp_at << 32 | (uint32_t)(pslot ? prev : -1));
            key.push_back(pslot ? pslot->gen : 0);
            if (key != pc.key) {
                pc_drop();
                pc.key = key;
                pc.state = pc_plan(sl, n, interp_at, pslot, lims, need) ? 0 : -1;
            }
            pcmode = pc.state == 0 ? 1 : pc.state == 1 ? 2 : 0;
        }
        /* ray tracing (RT2d): the interpolated frame's mesh draws at this present's rows as the
         * present's casters, before it draws (the backend builds its TLAS; nothing drawn) */
        const bool rtp = interp_at >= 0 && in->rt_pass(0);
        if (rtp) {
            rt_precast(slot[sl[interp_at]], lims[(size_t)interp_at]);
            in->rt_pass(1);
        }
        for (int i = 0; i < n; i++)
            replay_cmds(slot[sl[i]], tmp, i == interp_at, i == interp_at ? pslot : NULL, alpha,
                        lims[(size_t)i], need ? (*need)[(size_t)i].data() : NULL,
                        pcmode == 2 ? pc.skip[(size_t)i].data() : NULL, pcmode ? pc.cutf[(size_t)i].data() : NULL, pcmode == 1);
        if (rtp) in->rt_pass(2);
        if (pcmode == 1 && pc.state == 0) pc.state = 1;
        if (pcmode == 2) st.pc_passes++;
        in->prof_tag(GPT_CREATE);
        for (auto &kv : tmp) {
            auto r = redir.find(kv.first);
            if (r != redir.end() && r->second == kv.second) continue;   /* (kept for the compose) */
            in->rt_destroy(kv.second);
            bump(kv.second);
        }
        replaying = 0;
        in->kick();
        sync();
        st.replays++;
        return 0;
    }
    /* does what slot sl[0]'s mesh draws drew reach the displayed target by the end of the
     * sequence (through draws sampling a target and target copies)?  1 yes, 0 no, -1 unknown
     * (no display seen yet) */
    int flows(const int *sl, int n)
    {
        if (disp_rt[0] < 0 && disp_rt[1] < 0) return -1;
        std::map<int, int> t;
        for (int i = 0; i < n; i++)
            for (const Cmd &c : slot[sl[i]].cmds) {
                switch (c.k) {
                case C_DRAW:
                    if (c.rt[0] < 0) break;
                    if ((i == 0 && c.mesh_id) || (c.rt[2] >= 0 && t[c.rt[2]])) t[c.rt[0]] = 1;
                    break;
                case C_COPY:
                case C_REINT:
                    if (t[c.rt[1]]) t[c.rt[0]] = 1;
                    break;
                case C_CREATE:
                case C_DESTROY:
                    t[c.rt[0]] = 0;
                    break;
                default:
                    break;
                }
            }
        return (disp_rt[0] >= 0 && t[disp_rt[0]]) || (disp_rt[1] >= 0 && t[disp_rt[1]]) ? 1 : 0;
    }
    /* immediate draws of a frame paired with the previous frame's: the same state and vertex
     * count, in order (the k-th draw of a key with the k-th of the previous frame) */
    static int im_key_drop()
    {
        static int m = -1;   /* $RG_INTERP_IMKEY=bits (measurement): 1 no targets, 2 no texture key, 4 no vertex count */
        if (m < 0) { const char *e = getenv("RG_INTERP_IMKEY"); m = e && *e ? atoi(e) : 0; }
        return m;
    }
    static uint64_t im_key(const Cmd &c)
    {
        uint64_t h = 1469598103934665603ull;
        int drop = im_key_drop();
        auto mix = [&h](const void *p, size_t n) {
            const unsigned char *b = (const unsigned char *)p;
            for (size_t i = 0; i < n; i++) h = (h ^ b[i]) * 1099511628211ull;
        };
        const GpuNrDraw &g = c.g;
        if (!(drop & 1)) mix(&c.srt[0], sizeof c.srt);
        mix(&g.tme, sizeof g.tme);
        if (!(drop & 2)) mix(g.dec_key, sizeof g.dec_key);
        mix(&g.alpha_abcd, sizeof g.alpha_abcd);
        mix(&g.abe, sizeof g.abe);
        mix(&g.zfunc, sizeof g.zfunc);
        mix(&g.zwrite, sizeof g.zwrite);
        mix(&g.cmask, sizeof g.cmask);
        mix(&g.tex_snap, sizeof g.tex_snap);
        mix(&g.crov, sizeof g.crov);
        size_t nv = c.im.size(), nr = c.runs.size();
        if (!(drop & 4)) mix(&nv, sizeof nv);
        mix(&nr, sizeof nr);
        return h;
    }
    std::vector<int> pair_im(const Slot &s, const Slot &p)
    {
        std::vector<int> m(s.cmds.size(), -1);
        std::unordered_map<uint64_t, std::deque<int>> q;
        for (size_t i = 0; i < p.cmds.size(); i++)
            if (p.cmds[i].k == C_DRAW && !p.cmds[i].im.empty()) q[im_key(p.cmds[i])].push_back((int)i);
        for (size_t i = 0; i < s.cmds.size(); i++) {
            if (s.cmds[i].k != C_DRAW || s.cmds[i].im.empty()) continue;
            auto it = q.find(im_key(s.cmds[i]));
            if (it == q.end() || it->second.empty()) continue;
            m[i] = it->second.front();
            it->second.pop_front();
        }
        return m;
    }
    /* the triangles of a paired draw that moved (same texture coordinates, a bounded step on
     * screen) lerped from the previous frame's toward the recorded ones; the rest as recorded */
    std::vector<GpuImVtx> im_tmp;
    const GpuImVtx *im_lerp(const Cmd &c, const Cmd &pc, float alpha)
    {
        size_t n = c.im.size();
        float lim = 0.15f * (float)(c.g.vp_w > c.g.vp_h ? c.g.vp_w : c.g.vp_h);
        int changed = 0;
        im_tmp.assign(c.im.begin(), c.im.end());
        for (size_t t = 0; t + 2 < n; t += 3) {
            if (t + 2 >= pc.im.size()) break;
            const GpuImVtx *a = &pc.im[t], *b = &c.im[t];
            bool ok = true, moved = false;
            for (int k = 0; k < 3 && ok; k++) {
                if (memcmp(&a[k].s, &b[k].s, 3 * sizeof(float))) ok = false;
                float dx = b[k].x - a[k].x, dy = b[k].y - a[k].y;
                if (!(dx * dx + dy * dy <= lim * lim)) ok = false;
                if (dx != 0.0f || dy != 0.0f || a[k].z != b[k].z || a[k].rgba != b[k].rgba) moved = true;
            }
            st.im_tris++;
            if (!ok || !moved) continue;
            for (int k = 0; k < 3; k++) {
                GpuImVtx &o = im_tmp[t + (size_t)k];
                uint32_t rc = 0;
                o.x = a[k].x + (b[k].x - a[k].x) * alpha;
                o.y = a[k].y + (b[k].y - a[k].y) * alpha;
                o.z = (uint32_t)((double)a[k].z + ((double)b[k].z - (double)a[k].z) * alpha + 0.5);
                for (int j = 0; j < 32; j += 8) {
                    float ca = (float)((a[k].rgba >> j) & 0xFF), cb = (float)((b[k].rgba >> j) & 0xFF);
                    rc |= (uint32_t)(ca + (cb - ca) * alpha + 0.5f) << j;
                }
                o.rgba = rc;
            }
            st.im_tris_lerped++;
            changed = 1;
        }
        return changed ? im_tmp.data() : c.im.data();
    }
    static int trim_on()
    {
        static int t = -1;   /* $RG_INTERP_TRIM=0 (control): later frames replayed whole */
        if (t < 0) { const char *e = getenv("RG_INTERP_TRIM"); t = !(e && e[0] == '0'); }
        return t;
    }
    /* ---- composite placement and composite poses ($RG_INTERP_ZSCALE, default 4; nr_interp.c) ----
     * A strip group: the immediate draws that read a work target W into another target right
     * after mesh draws into W (the offscreen composite: a character part drawn into a work
     * buffer, copied into the frame by sprite strips cut for its screen box), until W is written
     * again.  The battle renderer draws each character through its own view of the work buffer,
     * so the groups of one key (W, destination, as frame-stable tokens) are one character: their
     * union rectangle is paired with the previous frame's of the same key, and every group of it
     * moves by the lerp of the two rectangles' centres: the character, drawn as recorded, travels
     * with the scene in one piece (per part, the parts' boxes change with the pose and drift
     * apart).  The parts' own constants cannot be interpolated: they also place each part in the
     * work buffer.
     * Composite poses (mode 4, default; docs/NATIVE-RENDER.md "Checkpoint 13"): one group is one
     * composite call (ModelDrawOffscreenCompositeMaybe_16aac0: an RGBA-0 clear of the call's box
     * in W, its parts, the copy strips); a group paired with the previous frame's draws its parts
     * with the bones interpolated (camera / object rows as recorded, so the part stays where the
     * frame put it in W), its copy moves by the pair's centres and is widened, with the clear, to
     * cover the pose between the two frames: nothing is cut (place_plan, zs_widen). */
    struct Grp {
        int key_w, key_f;
        float x0, y0, x1, y1;
        int vp;
        int clear;     /* the work target's clear before the parts (an untextured, unblended immediate draw), -1 none */
        int own;       /* the parts drawn into W since the last group feed this one (else it re-reads W: clear inherited) */
        int zs;        /* every part fed to it is a Z-scale composite mesh (nr_ip_zs_item; only in a pass) */
        uint64_t sig;  /* its parts' meshes (device mesh id, index count; order-free), 0 none: the call's identity across frames */
    };
    static int place_on()
    {
        int m = nr_ip_zs_mode();
        return m == 2 || m == 3 || m == 4;
    }
    /* cmd index -> group index (-1), and the groups; feed (optional): mesh draw cmd index -> the
     * group its part goes to (the first group reading its work target after it) */
    static void groups_of(const Slot &s, std::vector<int> &of, std::vector<Grp> &gs, std::vector<int> *feed = NULL)
    {
        of.assign(s.cmds.size(), -1);
        if (feed) feed->assign(s.cmds.size(), -1);
        gs.clear();
        std::map<int, int> lastw;   /* target id -> 1: last written by a mesh draw, 2 otherwise */
        std::map<int, int> open;    /* work target id -> its open group */
        std::map<int, std::vector<int>> pend;   /* target id -> mesh draws and clears into it since its last group */
        std::map<int, int> lastclear;           /* work target id -> the clear of its latest group with parts */
        auto wrote = [&](int id, int kind) {
            if (id < 0) return;
            lastw[id] = kind;
            open.erase(id);
        };
        for (size_t i = 0; i < s.cmds.size(); i++) {
            const Cmd &c = s.cmds[i];
            switch (c.k) {
            case C_DRAW:
                if (c.im.empty()) {
                    wrote(c.rt[0], c.mesh_id ? 1 : 2);
                    if (c.mesh_id && c.rt[0] >= 0) pend[c.rt[0]].push_back((int)i);
                    break;
                }
                if (c.rt[2] >= 0 && c.rt[2] != c.rt[0] && c.rt[0] >= 0) {
                    auto o = open.find(c.rt[2]);
                    int gi = -1;
                    if (o != open.end() && gs[(size_t)o->second].key_f == c.srt[0]) gi = o->second;
                    else if (lastw[c.rt[2]] == 1) {
                        Grp g;
                        g.key_w = c.srt[2];
                        g.key_f = c.srt[0];
                        g.x0 = g.y0 = 1e30f;
                        g.x1 = g.y1 = -1e30f;
                        g.vp = c.g.vp_w > c.g.vp_h ? c.g.vp_w : c.g.vp_h;
                        g.clear = -1;
                        g.own = 0;
                        g.zs = 0;
                        g.sig = 0;
                        gi = (int)gs.size();
                        /* the parts since W's last group, and the clear before the first of them */
                        std::vector<int> &pv = pend[c.rt[2]];
                        int clr = -1, meshes = 0, zsn = 0;
                        for (int idx : pv) {
                            const Cmd &m = s.cmds[(size_t)idx];
                            if (m.im.empty()) {
                                meshes++;
                                if (feed) (*feed)[(size_t)idx] = gi;
                                zsn += nr_ip_zs_item(m.mesh_id);
                                if (m.has_d) {
                                    uint64_t h = ((uint64_t)m.d.mesh.id << 32 | m.d.mesh.nidx) * 0x9E3779B97F4A7C15ull;
                                    g.sig += (h ^ (h >> 29)) | 1;   /* (a sum: the parts come in any order) */
                                }
                            } else if (!meshes)
                                clr = idx;   /* (the last one before the parts) */
                        }
                        g.zs = meshes && zsn == meshes;   /* (all its parts composites: not a screen grab) */
                        if (meshes) {
                            g.own = 1;
                            g.clear = clr;
                            lastclear[c.rt[2]] = clr;
                        } else {
                            auto lc = lastclear.find(c.rt[2]);
                            g.clear = lc != lastclear.end() ? lc->second : -1;
                        }
                        pv.clear();
                        gs.push_back(g);
                        open[c.rt[2]] = gi;
                    }
                    if (gi >= 0) {
                        Grp &g = gs[(size_t)gi];
                        for (const GpuImVtx &v : c.im) {
                            if (v.x < g.x0) g.x0 = v.x;
                            if (v.y < g.y0) g.y0 = v.y;
                            if (v.x > g.x1) g.x1 = v.x;
                            if (v.y > g.y1) g.y1 = v.y;
                        }
                        of[i] = gi;
                        lastw[c.rt[2]] = 1;   /* (W stays the part's until written again) */
                        lastw[c.rt[0]] = 2;
                        open.erase(c.rt[0]);
                        break;
                    }
                }
                wrote(c.rt[0], 2);
                /* an untextured, unblended immediate draw: a clear of the work buffer when parts follow */
                if (c.rt[0] >= 0 && !c.g.tme && !c.g.abe && c.rt[2] < 0) pend[c.rt[0]].push_back((int)i);
                break;
            case C_COPY:
            case C_LOAD:
            case C_CLEAR:
            case C_REINT:
            case C_RESIZE:
                wrote(c.rt[0], 2);
                pend.erase(c.rt[0]);
                lastclear.erase(c.rt[0]);
                break;
            case C_CREATE:
            case C_DESTROY:
                lastw.erase(c.rt[0]);
                open.erase(c.rt[0]);
                pend.erase(c.rt[0]);
                lastclear.erase(c.rt[0]);
                break;
            }
        }
    }
    /* per group of s: the shift its draws take at alpha (0 when unpaired or not plausible); pose
     * (mode 4): per group ex[4] = how far its copy strips (and, for the group owning the parts,
     * the work buffer's clear) are widened left / top / right / bottom, pose[g] = 1 when its parts
     * are interpolated (then no shift), 2 when it re-reads a work buffer whose parts are (drawn as
     * recorded), 0 placement as in mode 2 */
    struct Plan {
        std::vector<int> of, feed, clear_of;   /* cmd -> group (strips), cmd -> group (parts), cmd -> group (its clear) */
        std::vector<Grp> gs;
        std::vector<float> sh, ex, er;   /* er: (pose) the rectangle the group's copy covers, x0 y0 x1 y1 */
        std::vector<int> pose;
    };
    void place_plan(const Slot &s, const Slot &p, float alpha, Plan &pl)
    {
        std::vector<Grp> gp;
        std::vector<int> ofp;
        const int pose_mode = nr_ip_zs_mode() == 4;
        std::vector<Grp> &gs = pl.gs;
        groups_of(s, pl.of, gs, pose_mode ? &pl.feed : NULL);
        groups_of(p, ofp, gp);
        std::vector<float> &sh = pl.sh;
        sh.assign(gs.size() * 2, 0.0f);
        pl.ex.assign(gs.size() * 4, 0.0f);
        pl.er.assign(gs.size() * 4, 0.0f);
        pl.pose.assign(gs.size(), 0);
        pl.clear_of.assign(s.cmds.size(), -1);
        /* union rectangles per key */
        typedef std::pair<int, int> K;
        auto unite = [](std::map<K, Grp> &m, const Grp &g) {
            auto it = m.find(K(g.key_w, g.key_f));
            if (it == m.end()) { m[K(g.key_w, g.key_f)] = g; return; }
            Grp &u = it->second;
            if (g.x0 < u.x0) u.x0 = g.x0;
            if (g.y0 < u.y0) u.y0 = g.y0;
            if (g.x1 > u.x1) u.x1 = g.x1;
            if (g.y1 > u.y1) u.y1 = g.y1;
        };
        std::map<K, Grp> us, up;
        for (const Grp &g : gs) unite(us, g);
        for (const Grp &g : gp) unite(up, g);
        std::map<K, std::pair<float, float>> d;
        for (auto &kv : us) {
            auto it = up.find(kv.first);
            if (it == up.end()) continue;
            const Grp &a = it->second, &b = kv.second;
            float wa = a.x1 - a.x0, ha = a.y1 - a.y0, wb = b.x1 - b.x0, hb = b.y1 - b.y0;
            float dx = 0.5f * (a.x0 + a.x1 - b.x0 - b.x1), dy = 0.5f * (a.y0 + a.y1 - b.y0 - b.y1);
            float lim = 0.15f * (float)b.vp;
            /* (parts' boxes, not a screen pass; a similar box; a bounded step) */
            if (!(wb > 0 && hb > 0) || wb > 0.5f * (float)b.vp || hb > 0.5f * (float)b.vp) continue;
            if (wa > 1.5f * wb + 16.0f || wb > 1.5f * wa + 16.0f || ha > 1.5f * hb + 16.0f || hb > 1.5f * ha + 16.0f) continue;
            if (!(dx * dx + dy * dy <= lim * lim)) continue;
            d[kv.first] = std::make_pair(dx * (1.0f - alpha), dy * (1.0f - alpha));
        }
        /* pose, per group (one composite call: the clear of its work buffer, its parts, the copy
         * strips; several calls and several characters can share one work buffer key): it owns
         * parts that are all Z-scale meshes, its clear (RGBA 0, not a full-target clear) overlaps
         * its box, and it pairs with the previous frame's group of the key nearest in box (greedy:
         * the calls can come in another order) with a bounded step; why codes in the debug line:
         * 1 parts / clear, 2 clear not RGBA 0, 3 clear apart, 4 clear too large, 5-7 the pair.
         * Its copy is moved by the pair's centres (as placement) and widened, and its clear grown,
         * to the union of its box and the previous box moved onto it, + a margin (GS window
         * pixels: the work buffer and the frame share the window) */
        std::vector<int> gok(gs.size(), 0), gpair(gs.size(), -1), gwhy(gs.size(), 0), gks(gs.size(), 0), gkp(gs.size(), 0);
        std::vector<float> gsh(gs.size() * 2, 0.0f);
        std::vector<std::vector<float>> eg(gs.size());
        if (pose_mode) {
            std::map<K, std::vector<int>> ks, kp;
            for (size_t i = 0; i < gs.size(); i++) ks[K(gs[i].key_w, gs[i].key_f)].push_back((int)i);
            for (size_t i = 0; i < gp.size(); i++) kp[K(gp[i].key_w, gp[i].key_f)].push_back((int)i);
            const float m = 8.0f;
            /* each group with a previous frame's group, greedily by box distance (centre and size;
             * the calls can come in another order): first the groups drawing the same parts (part
             * signature, any work-buffer key: a character's view of the work buffer is a target the
             * frame creates, keyed by its creation ordinal, which shifts when another character's
             * view comes or goes), then the rest within their key ($RG_INTERP_ZSPAIR=0: by key only,
             * checkpoint 13) */
            static int bysig = -1;
            if (bysig < 0) { const char *e = getenv("RG_INTERP_ZSPAIR"); bysig = !(e && e[0] == '0'); }
            std::vector<int> gall(gs.size(), -1);
            {
                std::vector<std::pair<std::pair<int, float>, std::pair<int, int>>> cand;
                for (size_t i = 0; i < gs.size(); i++)
                    for (size_t j = 0; j < gp.size(); j++) {
                        const Grp &g = gs[i], &q = gp[j];
                        int tier;
                        if (bysig && g.sig && g.sig == q.sig && g.key_f == q.key_f) tier = 0;
                        else if (g.key_w == q.key_w && g.key_f == q.key_f) tier = 1;
                        else continue;
                        float c = fabsf(q.x0 - g.x0) + fabsf(q.x1 - g.x1) + fabsf(q.y0 - g.y0) + fabsf(q.y1 - g.y1);
                        cand.push_back(std::make_pair(std::make_pair(tier, c), std::make_pair((int)i, (int)j)));
                    }
                std::sort(cand.begin(), cand.end());
                std::vector<char> used(gp.size(), 0);
                for (auto &c : cand)
                    if (gall[(size_t)c.second.first] < 0 && !used[(size_t)c.second.second]) {
                        gall[(size_t)c.second.first] = c.second.second;
                        used[(size_t)c.second.second] = 1;
                    }
            }
            for (auto &kv : ks) {
                const std::vector<int> &vs = kv.second, &vq = kp[kv.first];
                std::vector<int> pair(vs.size(), -1);
                for (int v : vs) { gks[(size_t)v] = (int)vs.size(); gkp[(size_t)v] = (int)vq.size(); }   /* (debug: interp_groups.py) */
                for (size_t n = 0; n < vs.size(); n++) pair[n] = gall[(size_t)vs[n]];
                for (size_t n = 0; n < vs.size(); n++) {
                    if (pair[n] < 0) continue;
                    const Grp &g = gs[(size_t)vs[n]], &q = gp[(size_t)pair[n]];
                    gpair[(size_t)vs[n]] = pair[n];
                    if (!g.own || g.clear < 0 || !g.zs) { gwhy[(size_t)vs[n]] = 1; continue; }
                    float cx0 = 1e30f, cy0 = 1e30f, cx1 = -1e30f, cy1 = -1e30f;
                    int zero = 1;
                    for (const GpuImVtx &v : s.cmds[(size_t)g.clear].im) {
                        if (v.rgba) zero = 0;
                        cx0 = v.x < cx0 ? v.x : cx0; cx1 = v.x > cx1 ? v.x : cx1;
                        cy0 = v.y < cy0 ? v.y : cy0; cy1 = v.y > cy1 ? v.y : cy1;
                    }
                    if (!zero) { gwhy[(size_t)vs[n]] = 2; continue; }   /* (the composite clears to RGBA 0) */
                    if (!(cx1 > g.x0 && cx0 < g.x1 && cy1 > g.y0 && cy0 < g.y1)) { gwhy[(size_t)vs[n]] = 3; continue; }
                    if (cx1 - cx0 > 0.5f * (float)g.vp || cy1 - cy0 > 0.5f * (float)g.vp) { gwhy[(size_t)vs[n]] = 4; continue; }
                    float wa = q.x1 - q.x0, ha = q.y1 - q.y0, wb = g.x1 - g.x0, hb = g.y1 - g.y0;
                    float dx = 0.5f * (q.x0 + q.x1 - g.x0 - g.x1), dy = 0.5f * (q.y0 + q.y1 - g.y0 - g.y1);
                    float lim = 0.15f * (float)g.vp;
                    if (!(wb >= 0 && hb >= 0 && wa >= 0 && ha >= 0)) { gwhy[(size_t)vs[n]] = 5; continue; }
                    if (wa > 3.0f * wb + 64.0f || wb > 3.0f * wa + 64.0f || ha > 3.0f * hb + 64.0f || hb > 3.0f * ha + 64.0f) { gwhy[(size_t)vs[n]] = 6; continue; }
                    if (!(dx * dx + dy * dy <= lim * lim)) { gwhy[(size_t)vs[n]] = 7; continue; }
                    /* the parts stay where this frame drew them in the work buffer (their camera and
                     * object rows as recorded, the bones interpolated: nr_interp.c), the copy moves
                     * with the pair's centres as in placement; the pose then lies about within the
                     * union of this box and the previous one moved onto it */
                    float qx0 = q.x0 - dx, qy0 = q.y0 - dy, qx1 = q.x1 - dx, qy1 = q.y1 - dy;
                    std::vector<float> e(4);
                    e[0] = g.x0 - ((qx0 < g.x0 ? qx0 : g.x0) - m);
                    e[1] = g.y0 - ((qy0 < g.y0 ? qy0 : g.y0) - m);
                    e[2] = ((qx1 > g.x1 ? qx1 : g.x1) + m) - g.x1;
                    e[3] = ((qy1 > g.y1 ? qy1 : g.y1) + m) - g.y1;
                    gsh[2 * (size_t)vs[n]] = dx * (1.0f - alpha);
                    gsh[2 * (size_t)vs[n] + 1] = dy * (1.0f - alpha);
                    eg[(size_t)vs[n]] = e;
                    pl.er[4 * (size_t)vs[n] + 0] = g.x0 - e[0];
                    pl.er[4 * (size_t)vs[n] + 1] = g.y0 - e[1];
                    pl.er[4 * (size_t)vs[n] + 2] = g.x1 + e[2];
                    pl.er[4 * (size_t)vs[n] + 3] = g.y1 + e[3];
                    gok[(size_t)vs[n]] = 1;
                }
            }
        }
        for (size_t i = 0; i < gs.size(); i++) {
            K k(gs[i].key_w, gs[i].key_f);
            if (gok[i]) {
                const std::vector<float> &e = eg[i];
                for (int j = 0; j < 4; j++) pl.ex[4 * i + (size_t)j] = e[(size_t)j];
                pl.pose[i] = 1;
                sh[2 * i] = gsh[2 * i];
                sh[2 * i + 1] = gsh[2 * i + 1];
                pl.clear_of[(size_t)gs[i].clear] = (int)i;
                st.zs_pose++;
                continue;
            }
            if (pose_mode && gpair[i] >= 0) {
                /* (mode 4) a group drawn as recorded moves with its own pair, not the character's
                 * union: its neighbours are posed, not placed */
                const Grp &q = gp[(size_t)gpair[i]], &g = gs[i];
                float dx = 0.5f * (q.x0 + q.x1 - g.x0 - g.x1), dy = 0.5f * (q.y0 + q.y1 - g.y0 - g.y1);
                float lim = 0.15f * (float)g.vp;
                if (dx * dx + dy * dy <= lim * lim) {
                    sh[2 * i] = dx * (1.0f - alpha);
                    sh[2 * i + 1] = dy * (1.0f - alpha);
                    st.zs_groups++;
                }
                continue;
            }
            auto it = d.find(k);
            if (it == d.end()) continue;
            sh[2 * i] = it->second.first;
            sh[2 * i + 1] = it->second.second;
            st.zs_groups++;
        }
        if (pose_mode)
            /* a group re-reading a work buffer whose parts moved (e.g. the motion-blur copy): as
             * recorded, not shifted (the parts are where the interpolation put them) */
            for (size_t i = 0; i < gs.size(); i++) {
                if (gs[i].own || gs[i].clear < 0 || pl.pose[i]) continue;
                int owner = pl.clear_of[(size_t)gs[i].clear];
                if (owner >= 0 && pl.pose[(size_t)owner] == 1) {
                    pl.pose[i] = 2;
                    sh[2 * i] = sh[2 * i + 1] = 0.0f;
                }
            }
        st.zs_groups_all += gs.size();
        if (dbg_on()) {
            static int nd;
            for (size_t i = 0; i < gs.size() && nd < 4000000; i++, nd++)
                fprintf(stderr, "interp group %zu: key %d/%d box %.0f,%.0f-%.0f,%.0f own %d clear %d zs %d pose %d why %d pair %d ex %.0f %.0f %.0f %.0f sh %.1f %.1f ks %d kp %d\n", i,
                        gs[i].key_w, gs[i].key_f, gs[i].x0, gs[i].y0, gs[i].x1, gs[i].y1, gs[i].own, gs[i].clear, gs[i].zs, pl.pose[i], gwhy[i], gpair[i],
                        pl.ex[4 * i], pl.ex[4 * i + 1], pl.ex[4 * i + 2], pl.ex[4 * i + 3], sh[2 * i], sh[2 * i + 1], gks[i], gkp[i]);
        }
    }
    /* the draw's vertices on its outer edges moved out by ex (left, top, right, bottom), texture
     * coordinates along (the draw's own pixel -> texel mapping, from its extreme vertices): copy
     * strips cut for the recorded box cover the widened one; a clear (untextured) just grows */
    std::vector<GpuImVtx> ex_tmp;
    const GpuImVtx *zs_widen(const Cmd &c, const GpuImVtx *v, const float *ex)
    {
        size_t n = c.im.size();
        if (!n || (ex[0] <= 0.0f && ex[1] <= 0.0f && ex[2] <= 0.0f && ex[3] <= 0.0f)) return v;
        float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;
        size_t ix0 = 0, iy0 = 0, ix1 = 0, iy1 = 0;
        for (size_t i = 0; i < n; i++) {
            if (v[i].x < x0) { x0 = v[i].x; ix0 = i; }
            if (v[i].x > x1) { x1 = v[i].x; ix1 = i; }
            if (v[i].y < y0) { y0 = v[i].y; iy0 = i; }
            if (v[i].y > y1) { y1 = v[i].y; iy1 = i; }
        }
        if (!(x1 > x0) || !(y1 > y0)) return v;
        float su = 0.0f, sv = 0.0f;   /* texels per pixel (u = s / q) */
        if (c.g.tme) {
            float qa = v[ix0].q != 0.0f ? v[ix0].q : 1.0f, qb = v[ix1].q != 0.0f ? v[ix1].q : 1.0f;
            float qc = v[iy0].q != 0.0f ? v[iy0].q : 1.0f, qd = v[iy1].q != 0.0f ? v[iy1].q : 1.0f;
            su = (v[ix1].s / qb - v[ix0].s / qa) / (x1 - x0);
            sv = (v[iy1].t / qd - v[iy0].t / qc) / (y1 - y0);
            if (!(su != 0.0f) || !(sv != 0.0f) || !std::isfinite(su) || !std::isfinite(sv)) return v;
        }
        ex_tmp.assign(v, v + n);
        for (GpuImVtx &o : ex_tmp) {
            float q = o.q != 0.0f ? o.q : 1.0f, dx = 0.0f, dy = 0.0f;
            if (o.x == x0) dx = -ex[0];
            else if (o.x == x1) dx = ex[2];
            if (o.y == y0) dy = -ex[1];
            else if (o.y == y1) dy = ex[3];
            o.x += dx;
            o.y += dy;
            if (c.g.tme) {
                o.s = (o.s / q + dx * su) * q;
                o.t = (o.t / q + dy * sv) * q;
            }
        }
        st.zs_widened++;
        return ex_tmp.data();
    }
    std::vector<GpuImVtx> zs_tmp;
    const GpuImVtx *zs_move(const Cmd &c, const GpuImVtx *v, float dx, float dy)
    {
        zs_tmp.assign(v, v + c.im.size());
        for (GpuImVtx &o : zs_tmp) { o.x += dx; o.y += dy; }
        return zs_tmp.data();
    }
    /* Dead commands of a pass (docs/NATIVE-RENDER.md "Interpolation throughput (2026-10-30)", "Replay
     * only what the image needs"): backward over the replayed sequence from the displayed targets,
     * a command is needed when it writes a live target (a draw: its colour or depth target; a copy,
     * load, clear, reinterpretation: its destination); a needed command makes the targets it reads
     * live (a draw: texture, colour and depth: blending and the depth test read them; a copy: its
     * source); a creation ends a target's life (before it, the id is another target).  Commands no
     * displayed pixel depends on are skipped: their targets are put back by the restore anyway.
     * Cached per sequence (the passes of a frame pair replay the same commands).  NULL: replay all
     * ($RG_INTERP_DCE=0, or no display seen yet). */
    struct { std::vector<uint64_t> key; std::vector<std::vector<char>> need; } dce;
    uint64_t dce_skipped = 0, dce_cmds = 0;
    const std::vector<std::vector<char>> *live_cmds(const int *sl, int n, const std::vector<size_t> &lims)
    {
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_INTERP_DCE"); on = !(e && e[0] == '0'); }
        if (!on || (disp_rt[0] < 0 && disp_rt[1] < 0)) return NULL;
        std::vector<uint64_t> key;
        key.push_back((uint64_t)(uint32_t)disp_rt[0] << 32 | (uint32_t)disp_rt[1]);
        for (int i = 0; i < n; i++) {
            key.push_back(slot[sl[i]].gen);
            key.push_back(lims[(size_t)i]);
        }
        if (key == dce.key) return &dce.need;
        dce.key = key;
        dce.need.assign((size_t)n, std::vector<char>());
        std::vector<char> live;
        auto is = [&live](int id) { return id >= 0 && (size_t)id < live.size() && live[(size_t)id]; };
        auto mk = [&live](int id) {
            if (id < 0) return;
            if ((size_t)id >= live.size()) live.resize((size_t)id + 1, 0);
            live[(size_t)id] = 1;
        };
        auto kill = [&live](int id) { if (id >= 0 && (size_t)id < live.size()) live[(size_t)id] = 0; };
        mk(disp_rt[0]);
        mk(disp_rt[1]);
        for (int i = n - 1; i >= 0; i--) {
            const Slot &s = slot[sl[i]];
            size_t lim = lims[(size_t)i] < s.cmds.size() ? lims[(size_t)i] : s.cmds.size();
            std::vector<char> &nd = dce.need[(size_t)i];
            nd.assign(s.cmds.size(), 0);
            for (size_t ci = lim; ci-- > 0;) {
                const Cmd &c = s.cmds[ci];
                switch (c.k) {
                case C_CREATE:
                    nd[ci] = 1;
                    kill(c.rt[0]);
                    break;
                case C_DESTROY:
                    nd[ci] = 1;
                    break;
                case C_DRAW:
                    if (is(c.rt[0]) || is(c.rt[1])) {
                        nd[ci] = 1;
                        mk(c.rt[0]);
                        mk(c.rt[1]);
                        mk(c.rt[2]);
                    }
                    break;
                case C_COPY:
                case C_REINT:
                    if (is(c.rt[0])) { nd[ci] = 1; mk(c.rt[1]); }
                    break;
                case C_CLEAR:   /* (the whole target: what it held before is dead) */
                    if (is(c.rt[0])) { nd[ci] = 1; kill(c.rt[0]); }
                    break;
                default:   /* C_LOAD (a rectangle), C_RESIZE */
                    if (is(c.rt[0])) nd[ci] = 1;
                    break;
                }
                dce_cmds++;
                if (!nd[ci]) dce_skipped++;
            }
        }
        return &dce.need;
    }
    /* $RG_INTERP_IMPROF=1 with $RG_GPU_PROFILE=4 (measurement): the pass's draws timed per kind
     * (target, texture target, colour view, blending, size), printed at exit (gpu_ip_stats) */
    static int improf_on()
    {
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_INTERP_IMPROF"); on = e && e[0] == '1'; }
        return on;
    }
    std::map<std::string, int> ip_keys;
    std::vector<std::string> ip_names;
    int improf_key(const Cmd &c)
    {
        char b[160];
        if (c.im.empty())
            snprintf(b, sizeof b, "mesh  rt %d z %d tex %d", c.srt[0], c.srt[1] >= 0, c.srt[2]);
        else {
            float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;
            for (const GpuImVtx &v : c.im) {
                x0 = v.x < x0 ? v.x : x0; x1 = v.x > x1 ? v.x : x1;
                y0 = v.y < y0 ? v.y : y0; y1 = v.y > y1 ? v.y : y1;
            }
            double ar = (double)(x1 - x0) * (double)(y1 - y0);
            int lb = 0;
            while (lb < 24 && ar >= (double)(1 << (lb + 1))) lb++;
            snprintf(b, sizeof b, "im    rt %d z %d tex %d crov %d tme %d abe %d tris %zu area 2^%d", c.srt[0], c.srt[1] >= 0, c.srt[2],
                     c.g.crov, c.g.tme, c.g.abe, c.im.size() / 3 >= 64 ? (size_t)64 : c.im.size() / 3, lb);
        }
        auto it = ip_keys.find(b);
        if (it != ip_keys.end()) return it->second;
        int k = GPT_N + (int)ip_names.size();
        if (k >= 4095) return GPT_IM;
        ip_keys[b] = k;
        ip_names.push_back(b);
        return k;
    }
    void improf_print(FILE *f)
    {
        std::vector<std::pair<double, int>> v;
        double tot = 0;
        for (size_t i = 0; i < ip_names.size(); i++) {
            double ms = 0, n = 0;
            if (!in->prof_get(GPT_N + (int)i, &ms, &n)) return;
            v.push_back(std::make_pair(ms, (int)i));
            tot += ms;
        }
        std::sort(v.rbegin(), v.rend());
        fprintf(f, "interp device: pass draws by kind (RG_INTERP_IMPROF, GPU ms, %.1f in all):\n", tot);
        for (size_t i = 0; i < v.size() && i < 60; i++) {
            double ms = 0, n = 0;
            in->prof_get(GPT_N + v[i].second, &ms, &n);
            fprintf(f, "  %9.1f ms %5.1f%% %8.0f segs  %s\n", ms, tot > 0 ? 100.0 * ms / tot : 0.0, n, ip_names[(size_t)v[i].second].c_str());
        }
    }
    /* ---- pair cache ($RG_INTERP_PAIRCACHE, measurement, default off; docs/NATIVE-RENDER.md "Interpolation at 5x") ----
     * The passes of one frame pair replay the same commands; only alpha differs.  A command is
     * the same in every one of them (invariant) when nothing it reads or writes depends on alpha:
     * not a mesh draw of the interpolated frame (its constants are interpolated), not an
     * immediate draw of it that is paired and moves (lerped) or belongs to a composite group
     * (moved / widened), and no target it reads or writes was written by a varying command
     * before (taint, from the pre-images on: they are the same in every pass).  For each target
     * life the invariant writes before its first varying use end at a cut: the first pass of the
     * pair runs everything and takes a copy of the target after the cut (only where a command
     * that still runs uses it later, or it is displayed); the later passes skip the invariant
     * draws, copies, reinterpretations and loads and put the copy at the cut.  Creations,
     * destructions, clears and resizes always run. */
    struct PcCut { int rtk; int snap; int next; };
    struct {
        std::vector<uint64_t> key;
        std::vector<std::vector<char>> skip;
        std::vector<std::vector<int>> cutf;
        std::vector<PcCut> cuts;
        std::vector<int> snaps;    /* target ids of the copies (-1: not taken) */
        int state = 0;             /* 0: take the copies in the next pass, 1: valid, -1: off for this key */
    } pc;
    /* $RG_INTERP_PAIRCACHE (measurement, default 0 = off): 1 exact (the same images: 74 of 74
     * pass dumps identical), 2 effect layers taken from the pair's first pass (see pc_plan; may
     * change in-between images).  Measured not worth it (docs/NATIVE-RENDER.md "Interpolation at
     * 5x"): 7.6 % (exact) / 9.3 % (2) of the replayed commands could be skipped, for ~16 target
     * copies per pass. */
    static int paircache_on()
    {
        static int m = -1;
        if (m < 0) { const char *e = getenv("RG_INTERP_PAIRCACHE"); m = e && *e ? atoi(e) : 0; }
        return m;
    }
    void pc_drop()
    {
        for (int &id : pc.snaps)
            if (id >= 0) { in->rt_destroy(id); id = -1; }
        pc.snaps.clear();
        pc.key.clear();
        pc.skip.clear();
        pc.cutf.clear();
        pc.cuts.clear();
        pc.state = 0;
    }
    void pc_cut(const Slot &s, std::map<int, int> &tmp, const Cmd &c, int ci0, int capture)
    {
        for (int k = ci0; k >= 0; k = pc.cuts[(size_t)k].next) {
            const PcCut &u = pc.cuts[(size_t)k];
            int a = -1;
            if (!map_rt(s, tmp, c.rt[u.rtk], c.life[u.rtk], &a) || a < 0) { st.pc_fail++; pc.state = -1; continue; }
            int &sn = pc.snaps[(size_t)u.snap];
            if (capture) {
                if (sn >= 0) in->rt_destroy(sn);
                sn = in->rt_clone(a);
                if (sn < 0) { st.pc_fail++; pc.state = -1; }
                else st.pc_taken++;
            } else if (sn < 0 || !in->rt_put(a, sn)) {
                st.pc_fail++;
                pc.state = -1;
            } else
                st.pc_put++;
        }
    }
    /* does immediate draw c (paired with pc_) have a triangle im_lerp would move? */
    static bool im_moves(const Cmd &c, const Cmd &pcm)
    {
        size_t n = c.im.size();
        float lim = 0.15f * (float)(c.g.vp_w > c.g.vp_h ? c.g.vp_w : c.g.vp_h);
        for (size_t t = 0; t + 2 < n; t += 3) {
            if (t + 2 >= pcm.im.size()) break;
            const GpuImVtx *a = &pcm.im[t], *b = &c.im[t];
            bool ok = true, moved = false;
            for (int k = 0; k < 3 && ok; k++) {
                if (memcmp(&a[k].s, &b[k].s, 3 * sizeof(float))) ok = false;
                float dx = b[k].x - a[k].x, dy = b[k].y - a[k].y;
                if (!(dx * dx + dy * dy <= lim * lim)) ok = false;
                if (dx != 0.0f || dy != 0.0f || a[k].z != b[k].z || a[k].rgba != b[k].rgba) moved = true;
            }
            if (ok && moved) return true;
        }
        return false;
    }
    /* plan the pair cache for the sequence (returns false: none) */
    bool pc_plan(const int *sl, int n, int interp_at, const Slot *prev, const std::vector<size_t> &lims,
                 const std::vector<std::vector<char>> *need)
    {
        pc.skip.assign((size_t)n, std::vector<char>());
        pc.cutf.assign((size_t)n, std::vector<int>());
        pc.cuts.clear();
        pc.snaps.clear();
        /* what varies in the interpolated frame */
        std::vector<char> varies;
        if (interp_at >= 0) {
            const Slot &s = slot[sl[interp_at]];
            varies.assign(s.cmds.size(), 0);
            std::vector<int> pm;
            Plan zp;
            if (prev) {
                if (pm_cache.gs != s.gen || pm_cache.gp != prev->gen || pm_cache.ns != s.cmds.size() ||
                    pm_cache.np != prev->cmds.size() || !s.gen) {
                    pm_cache.m = pair_im(s, *prev);
                    pm_cache.gs = s.gen;
                    pm_cache.gp = prev->gen;
                    pm_cache.ns = s.cmds.size();
                    pm_cache.np = prev->cmds.size();
                }
                pm = pm_cache.m;
                /* (the groups that move or are posed at some alpha: their shift is d x (1 - alpha)) */
                if (place_on()) place_plan(s, *prev, 0.5f, zp);
            }
            for (size_t ci = 0; ci < s.cmds.size(); ci++) {
                const Cmd &c = s.cmds[ci];
                if (c.k != C_DRAW) continue;
                if (c.im.empty()) varies[ci] = c.mesh_id && c.has_d;
                else if (prev) {
                    int zg = !zp.of.empty() ? zp.of[ci] : -1;
                    if (zg >= 0 && (zp.pose[(size_t)zg] == 1 || zp.sh[2 * (size_t)zg] != 0.0f || zp.sh[2 * (size_t)zg + 1] != 0.0f))
                        varies[ci] = 1;
                    else if (!zp.clear_of.empty() && zp.clear_of[ci] >= 0) varies[ci] = 1;
                    else if (zg < 0 && !pm.empty() && pm[ci] >= 0 && im_moves(c, prev->cmds[(size_t)pm[ci]])) varies[ci] = 1;
                }
            }
        }
        /* (mode 2, effect layers reused) the final targets: the displayed ones, what is drawn or
         * copied into them, and the depth of draws into those; a command that varies with alpha
         * never runs from the cache, and one that writes a final target only when exact; any
         * other one (an effect layer: blur, glow, afterimage buffers) is taken as it was in the
         * pair's first pass even when it reads the moving scene */
        const int approx = paircache_on() == 2;
        std::vector<char> fin;
        auto isfin = [&fin](int id) { return id >= 0 && (size_t)id < fin.size() && fin[(size_t)id]; };
        auto mkfin = [&fin](int id) {
            if (id < 0) return;
            if ((size_t)id >= fin.size()) fin.resize((size_t)id + 1, 0);
            fin[(size_t)id] = 1;
        };
        if (approx) {
            mkfin(disp_rt[0]);
            mkfin(disp_rt[1]);
            for (int pass = 0; pass < 2; pass++)
                for (int i = 0; i < n; i++) {
                    const Slot &s = slot[sl[i]];
                    size_t lim = lims[(size_t)i] < s.cmds.size() ? lims[(size_t)i] : s.cmds.size();
                    for (size_t ci = 0; ci < lim; ci++) {
                        const Cmd &c = s.cmds[ci];
                        if (!isfin(c.rt[0])) continue;
                        if (c.k == C_COPY || c.k == C_REINT) { if (pass == 0) mkfin(c.rt[1]); }
                        else if (c.k == C_DRAW) {
                            if (pass == 0 && c.rt[0] != c.rt[2]) mkfin(c.rt[2]);
                            mkfin(c.rt[1]);
                        }
                    }
                }
        }
        /* the sequence; taint; target lives */
        struct Touch { size_t g; int w; };
        struct Life { int id; int cut = -1, cut_rtk = 0; int tainted = 0; std::vector<Touch> t; int open = 1; };
        std::vector<std::pair<int, size_t>> seq;
        std::vector<char> inv, skippable;
        std::vector<Life> lives;
        std::map<int, int> cur;   /* id -> its open life */
        std::vector<char> T;
        auto tt = [&T](int id) { return id >= 0 && (size_t)id < T.size() && T[(size_t)id]; };
        auto ts = [&T](int id, char v) {
            if (id < 0) return;
            if ((size_t)id >= T.size()) T.resize((size_t)id + 1, 0);
            T[(size_t)id] = v;
        };
        auto life = [&](int id) -> Life & {
            auto it = cur.find(id);
            if (it == cur.end()) {
                Life L;
                L.id = id;
                lives.push_back(L);
                it = cur.insert(std::make_pair(id, (int)lives.size() - 1)).first;
            }
            return lives[(size_t)it->second];
        };
        for (int i = 0; i < n; i++) {
            const Slot &s = slot[sl[i]];
            size_t lim = lims[(size_t)i] < s.cmds.size() ? lims[(size_t)i] : s.cmds.size();
            pc.skip[(size_t)i].assign(s.cmds.size(), 0);
            pc.cutf[(size_t)i].assign(s.cmds.size(), -1);
            for (size_t ci = 0; ci < lim; ci++) {
                if (need && !(*need)[(size_t)i][ci]) continue;
                const Cmd &c = s.cmds[ci];
                size_t g = seq.size();
                seq.push_back(std::make_pair(i, ci));
                int iv = 1, sk = 0;
                int rd[3] = { -1, -1, -1 }, wr[2] = { -1, -1 };
                switch (c.k) {
                case C_CREATE:
                    if (cur.count(c.rt[0])) lives[(size_t)cur[c.rt[0]]].open = 0;
                    cur.erase(c.rt[0]);
                    ts(c.rt[0], 0);
                    wr[0] = c.rt[0];
                    break;
                case C_DESTROY:
                    if (cur.count(c.rt[0])) lives[(size_t)cur[c.rt[0]]].open = 0;
                    cur.erase(c.rt[0]);
                    break;
                case C_CLEAR:
                    ts(c.rt[0], 0);
                    sk = 1;
                    wr[0] = c.rt[0];
                    break;
                case C_RESIZE:
                    iv = !tt(c.rt[0]);
                    rd[0] = wr[0] = c.rt[0];
                    break;
                case C_LOAD:
                    iv = !tt(c.rt[0]);
                    sk = 1;
                    rd[0] = wr[0] = c.rt[0];
                    break;
                case C_COPY:
                case C_REINT:
                    iv = !tt(c.rt[0]) && !tt(c.rt[1]);
                    if (approx && !isfin(c.rt[0])) iv = 1;
                    if (!iv) ts(c.rt[0], 1);
                    sk = 1;
                    rd[0] = wr[0] = c.rt[0];
                    rd[1] = c.rt[1];
                    break;
                case C_DRAW:
                    iv = !(i == interp_at && !varies.empty() && varies[ci]) && !tt(c.rt[0]) && !tt(c.rt[1]) && !tt(c.rt[2]);
                    if (approx && !(i == interp_at && !varies.empty() && varies[ci]) && !isfin(c.rt[0]) && !isfin(c.rt[1])) iv = 1;
                    if (!iv) { ts(c.rt[0], 1); ts(c.rt[1], 1); }
                    sk = 1;
                    rd[0] = wr[0] = c.rt[0];
                    rd[1] = wr[1] = c.rt[1];
                    rd[2] = c.rt[2];
                    break;
                }
                inv.push_back((char)iv);
                skippable.push_back((char)(iv && sk));
                if (c.k == C_CREATE || c.k == C_DESTROY) continue;
                /* touches, in order; the cut moves along the invariant writes until the first
                 * varying touch */
                int seen[5] = { -2, -2, -2, -2, -2 }, ns = 0;
                for (int k = 0; k < 3; k++) {
                    int id = rd[k];
                    bool w = k < 2 && wr[k] == id && id >= 0;
                    if (id < 0) continue;
                    bool dup = false;
                    for (int q = 0; q < ns; q++) if (seen[q] == id) dup = true;
                    if (dup) continue;
                    seen[ns++] = id;
                    Life &L = life(id);
                    L.t.push_back(Touch{ g, w ? 1 : 0 });
                    if (!iv) L.tainted = 1;
                    else if (!L.tainted && w && sk) { L.cut = (int)g; L.cut_rtk = k; }
                }
                for (int k = 0; k < 2; k++) {
                    int id = wr[k];
                    if (id < 0) continue;
                    bool dup = false;
                    for (int q = 0; q < ns; q++) if (seen[q] == id) dup = true;
                    if (dup) continue;
                    seen[ns++] = id;
                    Life &L = life(id);
                    L.t.push_back(Touch{ g, 1 });
                    if (!iv) L.tainted = 1;
                    else if (!L.tainted && sk) { L.cut = (int)g; L.cut_rtk = k; }
                }
            }
        }
        /* skipped: invariant draws / copies / reinterpretations / loads at or before the cut of
         * every target they write; a target's cut: its last skipped write before the first
         * command that runs and touches it (until nothing changes: a command left to run ends
         * the runs of what it touches) */
        std::vector<char> skip(seq.size(), 0);
        for (size_t g = 0; g < seq.size(); g++) skip[g] = skippable[g];
        for (int it = 0; it < 64; it++) {
            for (Life &L : lives) {
                L.cut = -1;
                for (const Touch &t : L.t) {
                    if (!skip[t.g]) break;
                    if (t.w) L.cut = (int)t.g;
                }
            }
            bool changed = false;
            for (const Life &L : lives)
                for (const Touch &t : L.t)
                    if (t.w && skip[t.g] && (int)t.g > L.cut) { skip[t.g] = 0; changed = true; }
            if (!changed) break;
            if (it == 63) return false;
        }
        for (Life &L : lives) {
            /* (the write at the cut: which of the command's targets) */
            if (L.cut < 0) continue;
            const Cmd &c = slot[sl[seq[(size_t)L.cut].first]].cmds[seq[(size_t)L.cut].second];
            L.cut_rtk = c.rt[0] == L.id ? 0 : 1;
        }
        /* the cuts that need a copy: a command that still runs touches the target after it, or
         * it is displayed at the end */
        size_t nskip = 0;
        for (size_t g = 0; g < seq.size(); g++) nskip += skip[g];
        if (!nskip) return false;
        for (const Life &L : lives) {
            if (L.cut < 0) continue;
            bool needed = L.open && (L.id == disp_rt[0] || L.id == disp_rt[1]);
            for (const Touch &t : L.t)
                if ((int)t.g > L.cut && !skip[t.g]) needed = true;
            if (!needed) continue;
            const std::pair<int, size_t> &q = seq[(size_t)L.cut];
            PcCut u;
            u.rtk = L.cut_rtk;
            u.snap = (int)pc.snaps.size();
            u.next = pc.cutf[(size_t)q.first][q.second];
            pc.snaps.push_back(-1);
            pc.cutf[(size_t)q.first][q.second] = (int)pc.cuts.size();
            pc.cuts.push_back(u);
        }
        for (size_t g = 0; g < seq.size(); g++)
            if (skip[g]) pc.skip[(size_t)seq[g].first][seq[g].second] = 1;
        st.pc_plans++;
        st.pc_plan_skip += nskip;
        st.pc_plan_cmds += seq.size();
        st.pc_plan_cuts += pc.cuts.size();
        return true;
    }
    static int loadrect_on()
    {
        static int on = -1;
        if (on < 0) { const char *e = getenv("RG_INTERP_LOADRECT"); on = !(e && e[0] == '0'); }
        return on;
    }
    void unredir(int id, int t)
    {
        auto r = redir.find(id);
        if (r != redir.end() && r->second == t) redir.erase(r);
    }
    /* RT2d: the slot's mesh draws with the present's interpolated rows (composite parts: their
     * pose, as mode 3) to the backend's caster collection only */
    void rt_precast(const Slot &s, size_t lim)
    {
        gpu_nr_draw dd;
        for (size_t ci = 0; ci < lim && ci < s.cmds.size(); ci++) {
            const Cmd &c = s.cmds[ci];
            if (c.k != C_DRAW || !c.mesh_id || !c.has_d || !c.im.empty()) continue;
            GpuNrDraw g = c.g;
            memcpy(&dd, &c.d, offsetof(gpu_nr_draw, bones));
            if (c.d.nbones_rows > 0)
                memcpy(dd.bones, c.d.bones, sizeof dd.bones[0] * (size_t)(c.d.nbones_rows < 256 ? c.d.nbones_rows : 256));
            dd.nbones_rows = c.d.nbones_rows;
            nr_ip_zs_allow(1);
            nr_ip_mesh_cb(c.mesh_id, &dd);
            nr_ip_zs_allow(0);
            g.im = NULL;
            g.d = &dd;
            g.dec_rgba = c.rgba.empty() ? NULL : c.rgba.data();
            g.tex_cached_only = 1;
            in->rt_pass_cast(g);
        }
    }
    void replay_cmds(Slot &s, std::map<int, int> &tmp, int interp, const Slot *prev, float alpha, size_t lim,
                     const char *need = NULL, const char *pcs = NULL, const int *pcc = NULL, int capture = 0)
    {
        std::vector<int> pm;
        Plan pl;
        if (prev) {
            if (pm_cache.gs != s.gen || pm_cache.gp != prev->gen || pm_cache.ns != s.cmds.size() ||
                pm_cache.np != prev->cmds.size() || !s.gen) {
                pm_cache.m = pair_im(s, *prev);
                pm_cache.gs = s.gen;
                pm_cache.gp = prev->gen;
                pm_cache.ns = s.cmds.size();
                pm_cache.np = prev->cmds.size();
            }
            pm = pm_cache.m;
        }
        if (prev && place_on()) place_plan(s, *prev, alpha, pl);
        const std::vector<int> &zof = pl.of;
        const std::vector<float> &zsh = pl.sh;
        /* $RG_INTERP_ISOLATE=1 (measurement, tools/native/interp_pose.py): the interpolated frame's
         * composite characters alone: every other draw into the targets their strips copy into
         * writes no colour (depth as recorded) and those targets start cleared (the pose and
         * placement without the scene) */
        static int isolate = -1;
        if (isolate < 0) { const char *e = getenv("RG_INTERP_ISOLATE"); isolate = e && e[0] == '1'; }
        std::vector<int> iso_of;
        std::map<int, int> iso_dst;   /* destination target -> cleared yet */
        if (interp && isolate) {
            if (pl.of.empty()) {
                std::vector<Grp> ig;
                groups_of(s, iso_of, ig);
            } else
                iso_of = pl.of;
            for (size_t i = 0; i < s.cmds.size(); i++)
                if (iso_of[i] >= 0) iso_dst[s.cmds[i].rt[0]] = 0;
        }
        for (size_t ci = 0; ci < lim && ci < s.cmds.size(); ci++) {
            Cmd &c = s.cmds[ci];
            int a = -1, b = -1, t = -1;
            if (need && !need[ci]) continue;   /* (no displayed pixel depends on it: live_cmds) */
            if (pcs && pcs[ci]) {
                /* (pair cache) the same in every pass of this frame pair: its result comes from the
                 * snapshot put at the cut below */
                st.pc_skipped++;
            } else {
            in->prof_tag(c.k == C_DRAW ? (improf_on() ? improf_key(c) : c.im.empty() ? GPT_MESH : GPT_IM) : c.k == C_COPY ? GPT_COPY
                         : c.k == C_LOAD ? GPT_LOAD : c.k == C_CLEAR ? GPT_CLEAR : c.k == C_REINT ? GPT_REINT : GPT_CREATE);
            switch (c.k) {
            case C_CREATE: {
                auto old = tmp.find(c.rt[0]);
                if (old != tmp.end()) {   /* (a temporary for the id's earlier life) */
                    unredir(c.rt[0], old->second);
                    in->rt_destroy(old->second);
                    bump(old->second);
                    tmp.erase(old);
                }
                int id = in->rt_create(c.a, c.b, c.c);
                if (id >= 0) {
                    bump(id);
                    tmp[c.rt[0]] = id;
                }
                break;
            }
            case C_DESTROY: {
                auto it = tmp.find(c.rt[0]);
                if (it != tmp.end()) {
                    unredir(c.rt[0], it->second);
                    in->rt_destroy(it->second);
                    bump(it->second);
                    tmp.erase(it);
                }
                break;
            }
            case C_RESIZE:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0) in->rt_resize(a, c.a, c.b);
                break;
            case C_CLEAR:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0) in->rt_clear(a);
                break;
            case C_LOAD:
                /* the loaded rectangle from the target as the load left it ($RG_INTERP_LOADRECT=0:
                 * the whole target, as before: a whole-target copy per load, and what the pass drew
                 * into the target outside the rectangle replaced by the recorded frame's) */
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0) {
                    bool done = false;
                    if (c.img >= 0 && c.img_rect) {
                        GpuRect r0 = { 0, 0, c.r.x1 - c.r.x0, c.r.y1 - c.r.y0 };
                        done = in->rt_copy(a, c.r.x0, c.r.y0, c.img, r0);
                    } else if (c.img >= 0)
                        done = (loadrect_on() && in->rt_copy(a, c.r.x0, c.r.y0, c.img, c.r)) || in->rt_put(a, c.img);
                    if (!done) in->rt_load(a, c.bp, c.bw, c.psm, c.r);
                }
                break;
            case C_REINT:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && map_rt(s, tmp, c.rt[1], c.life[1], &b) && a >= 0 && b >= 0)
                    in->rt_reinterpret(a, c.bp, c.bw, c.psm, c.r, b, c.bp2, c.bw2, c.psm2, c.r2);
                else
                    st.replay_stale++;
                break;
            case C_COPY:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && map_rt(s, tmp, c.rt[1], c.life[1], &b) && a >= 0 && b >= 0) {
                    in->rt_copy(a, c.a, c.b, b, c.r);
                } else
                    st.replay_stale++;
                break;
            case C_DRAW: {
                int iso_mask = 0;
                if (!iso_dst.empty()) {
                    auto it = iso_dst.find(c.rt[0]);
                    if (it != iso_dst.end()) {
                        int t0 = -1;
                        if (!it->second && map_rt(s, tmp, c.rt[0], c.life[0], &t0) && t0 >= 0) in->rt_clear(t0);
                        it->second = 1;
                        if (iso_of[ci] < 0) iso_mask = 1;   /* (depth still written: what hides the characters) */
                    }
                }
                if (!map_rt(s, tmp, c.rt[0], c.life[0], &a) || !map_rt(s, tmp, c.rt[1], c.life[1], &b) ||
                    !map_rt(s, tmp, c.rt[2], c.life[2], &t)) {
                    st.replay_stale++;
                    if (dbg_on() && st.replay_stale < 40)
                        fprintf(stderr, "interp replay: stale draw rt %d/%u %d/%u %d/%u now %u %u %u\n", c.rt[0], c.life[0], c.rt[1],
                                c.life[1], c.rt[2], c.life[2], life_of(c.rt[0]), life_of(c.rt[1]), life_of(c.rt[2]));
                    break;
                }
                GpuNrDraw g = c.g;
                gpu_nr_draw dd;
                g.color_rt = a;
                g.depth_rt = b;
                g.tex_rt = t;
                g.im = c.im.empty() ? NULL : c.im.data();
                {
                    /* a composite strip: moved with its group (not lerped) */
                    int zg = g.im && !zof.empty() ? zof[ci] : -1;
                    int zc = g.im && !pl.clear_of.empty() ? pl.clear_of[ci] : -1;
                    if (zg >= 0) {
                        float dx = zsh[2 * (size_t)zg], dy = zsh[2 * (size_t)zg + 1];
                        st.im_draws++;
                        if (pl.pose[(size_t)zg] == 1) g.im = zs_widen(c, g.im, &pl.ex[4 * (size_t)zg]);
                        if (dx != 0.0f || dy != 0.0f) { g.im = zs_move(c, g.im, dx, dy); st.zs_strips++; }
                    } else if (zc >= 0) {
                        /* the work buffer's clear before a composite's parts: over all its copy covers */
                        float b[4] = { 1e30f, 1e30f, -1e30f, -1e30f }, e[4];
                        const float *r = &pl.er[4 * (size_t)zc];
                        for (const GpuImVtx &v : c.im) {
                            b[0] = v.x < b[0] ? v.x : b[0]; b[1] = v.y < b[1] ? v.y : b[1];
                            b[2] = v.x > b[2] ? v.x : b[2]; b[3] = v.y > b[3] ? v.y : b[3];
                        }
                        e[0] = b[0] - (r[0] - 2.0f); e[1] = b[1] - (r[1] - 2.0f);
                        e[2] = (r[2] + 2.0f) - b[2]; e[3] = (r[3] + 2.0f) - b[3];
                        for (int j = 0; j < 4; j++)
                            if (!(e[j] > 0.0f)) e[j] = 0.0f;
                        st.im_draws++;
                        g.im = zs_widen(c, g.im, e);
                    } else if (prev && g.im) {
                        st.im_draws++;
                        if (pm[ci] >= 0) {
                            st.im_paired++;
                            g.im = im_lerp(c, prev->cmds[(size_t)pm[ci]], alpha);
                        }
                    }
                }
                g.runs = c.runs.empty() ? NULL : c.runs.data();
                g.dec_rgba = c.rgba.empty() ? NULL : c.rgba.data();
                g.d = c.has_d ? &c.d : NULL;
                if (iso_mask) g.cmask = 0;
                if (g.tme && g.tex_rt < 0 && !g.dec_rgba) g.tex_cached_only = 1;   /* by its content key */
                if (interp && c.mesh_id && c.has_d) {
                    /* (the header and constant rows; bone rows only as far as the draw uploads them:
                     * a whole gpu_nr_draw is 4.5 KB per mesh draw per pass) */
                    memcpy(&dd, &c.d, offsetof(gpu_nr_draw, bones));
                    if (c.d.nbones_rows > 0)
                        memcpy(dd.bones, c.d.bones, sizeof dd.bones[0] * (size_t)(c.d.nbones_rows < 256 ? c.d.nbones_rows : 256));
                    dd.nbones_rows = c.d.nbones_rows;
                    dd.cull = c.d.cull;
                    dd.cull_sign = c.d.cull_sign;
                    dd.has_box = c.d.has_box;
                    memcpy(dd.box, c.d.box, sizeof dd.box);
                    /* (mode 4) a composite part moves only when its copy was widened */
                    nr_ip_zs_allow(!pl.feed.empty() && pl.feed[ci] >= 0 && pl.pose[(size_t)pl.feed[ci]] == 1);
                    if (nr_ip_mesh_cb(c.mesh_id, &dd)) {
                        if (dbg_on() > 0) {
                            static int nprint;
                            for (int k = 0; k < (int)(sizeof g.cb / sizeof g.cb[0]) && nprint < 60; k++) {
                                if (k == 11 || k == 23) continue;
                                float m = 0;
                                for (int j = 0; j < 4; j++) {
                                    float d = g.cb[k][j] - dd.cb[k][j];
                                    if (d < 0) d = -d;
                                    if (d > m) m = d;
                                }
                                if (m > 1e-3f) {
                                    nprint++;
                                    fprintf(stderr, "interp cb: mesh %u row %d recorded %g %g %g %g new %g %g %g %g\n", c.mesh_id, k,
                                            g.cb[k][0], g.cb[k][1], g.cb[k][2], g.cb[k][3], dd.cb[k][0], dd.cb[k][1], dd.cb[k][2],
                                            dd.cb[k][3]);
                                }
                            }
                        }
                        /* only the components the interpolated constants changed (the
                         * recorded source c.d vs the new dd): what the device derived at
                         * submit (row 10.z the depth format's largest Z, row 11 the
                         * viewport, 22-23 pixel state, 12-13 for target textures) stays; rows 24-25
                         * (the VU clipper's clip-space mapping, per camera) move with the camera */
                        static int nrows = -1;   /* $RG_INTERP_CLIPROWS=0: rows 0-23 only (before) */
                        if (nrows < 0) {
                            const char *e = getenv("RG_INTERP_CLIPROWS");
                            nrows = e && e[0] == '0' ? 24 : (int)(sizeof g.cb / sizeof g.cb[0]);
                        }
                        for (int k = 0; k < nrows; k++)
                            for (int j = 0; j < 4; j++)
                                if (memcmp(&c.d.cb[k][j], &dd.cb[k][j], 4)) g.cb[k][j] = dd.cb[k][j];
                        g.d = &dd;
                        st.replay_interp++;
                    }
                }
                {
                    static int nodraw = -1;   /* $RG_INTERP_NODRAW=1: control, the replay draws nothing */
                    if (nodraw < 0) { const char *e = getenv("RG_INTERP_NODRAW"); nodraw = e && e[0] == '1'; }
                    if (nodraw) break;
                    /* $RG_INTERP_SKIPDRAW=bits (measurement; the picture is wrong): the pass skips
                     * 1 mesh draws, 2 immediate draws through the output merger, 4 immediate draws
                     * through the colour view, 8 draws sampling a target, 16 draws into a target
                     * other than the displayed ones' sources (work buffers) */
                    static int skipm = -1;
                    if (skipm < 0) { const char *e = getenv("RG_INTERP_SKIPDRAW"); skipm = e && *e ? atoi(e) : 0; }
                    if (skipm) {
                        int k = !g.im ? 1 : g.crov ? 4 : 2;
                        if ((skipm & k) || ((skipm & 8) && g.tex_rt >= 0) || ((skipm & 16) && c.rt[0] != 1)) break;
                    }
                }
                nr_ip_zs_allow(0);
                if (!in->nr_draw(g)) st.replay_notex++;
                st.replay_draws++;
                break;
            }
            }
            }
            if (pcc && pcc[ci] >= 0) pc_cut(s, tmp, c, pcc[ci], capture);
        }
    }
};

/* the one recorder (one device per process); valid while the renderer's backend is it */
static IpRec *g_inst;
static gpu_renderer *g_inst_r;
static IpRec *rec_of(gpu_renderer *r)
{
    GpuBackend **b = r ? gpu_ip_backend(r) : NULL;
    return b && g_inst && r == g_inst_r && *b == (GpuBackend *)g_inst ? g_inst : NULL;
}

IpRec::~IpRec()
{
    for (int i = 0; i < NR_IP_SLOTS; i++) free_slot(i);
    drop_saved();
    delete in;
    if (g_inst == this) { g_inst = NULL; g_inst_r = NULL; }
}

} // namespace

extern "C" {

void gpu_ip_install(gpu_renderer *r)
{
    GpuBackend **b = r ? gpu_ip_backend(r) : NULL;
    if (!b || !*b || rec_of(r)) return;
    g_inst = new IpRec(*b);
    g_inst_r = r;
    *b = g_inst;
}

void gpu_ip_set_mesh(uint32_t id) { g_mesh_id = id; }

void gpu_ip_rec_slot(gpu_renderer *r, int s)
{
    IpRec *p = rec_of(r);
    if (!p) return;
    p->memlog(s);
    p->restore();
    if (s >= 0 && s < NR_IP_SLOTS) {
        p->free_slot(s);
        p->slot[s].rec = 1;
        p->cur = s;
    } else {
        p->cur = -1;
    }
}

void gpu_ip_slot_free(gpu_renderer *r, int s)
{
    IpRec *p = rec_of(r);
    if (!p || s < 0 || s >= NR_IP_SLOTS) return;
    if (p->cur == s) p->cur = -1;
    p->free_slot(s);
}

int gpu_ip_replay(gpu_renderer *r, const int *slots, int n, int interp_at, int prev, float alpha)
{
    IpRec *p = rec_of(r);
    if (!p || n <= 0 || n > NR_IP_SLOTS) return -1;
    for (int i = 0; i < n; i++)
        if (slots[i] < 0 || slots[i] >= NR_IP_SLOTS) return -1;
    if (prev >= NR_IP_SLOTS) prev = -1;
    return p->replay(slots, n, interp_at, prev, alpha);
}

void gpu_ip_restore(gpu_renderer *r)
{
    IpRec *p = rec_of(r);
    if (p) p->restore();
}

int gpu_ip_flows(gpu_renderer *r, const int *slots, int n)
{
    IpRec *p = rec_of(r);
    if (!p || n <= 0 || n > NR_IP_SLOTS) return -1;
    return p->flows(slots, n);
}

int gpu_ip_dirty(gpu_renderer *r)
{
    IpRec *p = rec_of(r);
    return p ? p->dirty : 0;
}

void gpu_ip_slot_info(gpu_renderer *r, int s, uint32_t out[4])
{
    IpRec *p = rec_of(r);
    out[0] = out[1] = out[2] = out[3] = 0;
    if (!p || s < 0 || s >= NR_IP_SLOTS) return;
    out[0] = (uint32_t)p->slot[s].cmds.size();
    out[1] = (uint32_t)p->slot[s].pre.size();
    out[2] = (uint32_t)p->slot[s].born.size();
    out[3] = (uint32_t)p->slot[s].bad;
}

void gpu_ip_dump(gpu_renderer *r, int si, FILE *f)
{
    IpRec *p = rec_of(r);
    if (!p || si < 0 || si >= NR_IP_SLOTS || !f) return;
    const Slot &s = p->slot[si];
    static const char *kn[] = { "draw", "copy", "load", "clear", "create", "destroy", "resize", "reint" };
    fprintf(f, "interp device log: %zu commands, %zu pre-images:", s.cmds.size(), s.pre.size());
    for (const Pre &q : s.pre) fprintf(f, " %d", q.id);
    fprintf(f, "\n");
    for (const Cmd &c : s.cmds) {
        fprintf(f, "  %-7s rt %d %d %d", kn[c.k], c.rt[0], c.rt[1], c.rt[2]);
        if (c.k == C_DRAW) {
            fprintf(f, " mesh %u im %zu tme %d tex_rt %d abe %d rt %dx%d", c.mesh_id, c.im.size(), c.g.tme, c.g.tex_rt, c.g.abe,
                    c.g.rt_w, c.g.rt_h);
            if (!c.im.empty()) {
                float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f, s0 = 1e30f, s1 = -1e30f;
                for (const GpuImVtx &v : c.im) {
                    x0 = v.x < x0 ? v.x : x0; x1 = v.x > x1 ? v.x : x1;
                    y0 = v.y < y0 ? v.y : y0; y1 = v.y > y1 ? v.y : y1;
                    s0 = v.s < s0 ? v.s : s0; s1 = v.s > s1 ? v.s : s1;
                }
                fprintf(f, " box %.1f,%.1f-%.1f,%.1f s %g-%g", x0, y0, x1, y1, s0, s1);
            }
        }
        else if (c.k == C_LOAD)
            fprintf(f, " bp %u bw %u psm %d rect %d,%d-%d,%d", c.bp, c.bw, c.psm, c.r.x0, c.r.y0, c.r.x1, c.r.y1);
        else if (c.k == C_COPY)
            fprintf(f, " to %d,%d from %d,%d-%d,%d", c.a, c.b, c.r.x0, c.r.y0, c.r.x1, c.r.y1);
        else if (c.k == C_CREATE)
            fprintf(f, " depth %d %dx%d", c.a, c.b, c.c);
        fprintf(f, "\n");
    }
}

void gpu_ip_stats(gpu_renderer *r, FILE *f)
{
    IpRec *p = rec_of(r);
    if (!p || !f) return;
    const Stats &s = p->st;
    fprintf(f, "interp device: recorded draws %llu, target copies %llu, loads %llu, clears %llu, targets created %llu, "
               "pre-images %llu (failed %llu); replays %llu (%llu draws, %llu interpolated, %llu stale, %llu without "
               "texture, %llu refused), saves %llu, restores %llu (copy failures %llu); immediate draws in passes %llu, "
               "paired %.1f %%, triangles lerped %llu of %llu; composite strip groups placed %llu of %llu (draws moved %llu), "
               "posed %llu (draws widened %llu); commands trimmed %llu\n",
            (unsigned long long)s.draws, (unsigned long long)s.copies, (unsigned long long)s.loads,
            (unsigned long long)s.clears, (unsigned long long)s.creates, (unsigned long long)s.pre_images,
            (unsigned long long)s.pre_fail, (unsigned long long)s.replays, (unsigned long long)s.replay_draws,
            (unsigned long long)s.replay_interp, (unsigned long long)s.replay_stale, (unsigned long long)s.replay_notex,
            (unsigned long long)s.replay_bad, (unsigned long long)s.saves, (unsigned long long)s.restores,
            (unsigned long long)s.put_fail, (unsigned long long)s.im_draws,
            s.im_draws ? 100.0 * (double)s.im_paired / (double)s.im_draws : 0.0, (unsigned long long)s.im_tris_lerped,
            (unsigned long long)s.im_tris, (unsigned long long)s.zs_groups, (unsigned long long)s.zs_groups_all,
            (unsigned long long)s.zs_strips, (unsigned long long)s.zs_pose, (unsigned long long)s.zs_widened,
            (unsigned long long)s.trimmed);
    if (s.oom)
        fprintf(f, "interp device: logs ended by out of memory %llu (frames shown without passes)\n", (unsigned long long)s.oom);
    if (IpRec::memlog_on())
        fprintf(f, "interp mem peaks: all slots %.1f MB, one slot %.1f MB (payload %.1f MB), commands in a slot %zu (Cmd %zu bytes)\n",
                p->mem_peak_all / 1048576.0, p->mem_peak_slot / 1048576.0, p->mem_peak_payload / 1048576.0, p->mem_peak_cmds,
                sizeof(Cmd));
    fprintf(f, "interp device: dead commands (live_cmds) %llu of %llu sequence commands analysed; redirected %s, "
               "pre-images not needed %llu\n",
            (unsigned long long)p->dce_skipped, (unsigned long long)p->dce_cmds, p->redirect_on() ? "on" : "off",
            (unsigned long long)s.pre_skipped);
    fprintf(f, "interp device: pair cache %s: plans %llu (commands %llu, skippable %llu, cuts %llu), passes using it %llu "
               "(commands skipped %llu, copies taken %llu, put %llu, failed %llu)\n",
            p->paircache_on() ? "on" : "off", (unsigned long long)s.pc_plans, (unsigned long long)s.pc_plan_cmds,
            (unsigned long long)s.pc_plan_skip, (unsigned long long)s.pc_plan_cuts, (unsigned long long)s.pc_passes,
            (unsigned long long)s.pc_skipped, (unsigned long long)s.pc_taken, (unsigned long long)s.pc_put,
            (unsigned long long)s.pc_fail);
    if (p->improf_on()) p->improf_print(f);
}

} /* extern "C" */

#else /* the default build (GS model): nothing recorded */

#include <stdint.h>
#include <stdio.h>

#include "nr_interp.h"

extern "C" {
void gpu_ip_install(struct gpu_renderer *r) { (void)r; }
void gpu_ip_set_mesh(uint32_t id) { (void)id; }
void gpu_ip_rec_slot(struct gpu_renderer *r, int s) { (void)r; (void)s; }
void gpu_ip_slot_free(struct gpu_renderer *r, int s) { (void)r; (void)s; }
int gpu_ip_replay(struct gpu_renderer *r, const int *slots, int n, int interp_at, int prev, float alpha) { (void)r; (void)slots; (void)n; (void)interp_at; (void)prev; (void)alpha; return -1; }
void gpu_ip_restore(struct gpu_renderer *r) { (void)r; }
int gpu_ip_dirty(struct gpu_renderer *r) { (void)r; return 0; }
int gpu_ip_flows(struct gpu_renderer *r, const int *slots, int n) { (void)r; (void)slots; (void)n; return -1; }
void gpu_ip_slot_info(struct gpu_renderer *r, int s, uint32_t out[4]) { (void)r; (void)s; out[0] = out[1] = out[2] = out[3] = 0; }
void gpu_ip_stats(struct gpu_renderer *r, FILE *f) { (void)r; (void)f; }
void gpu_ip_dump(struct gpu_renderer *r, int slot, FILE *f) { (void)r; (void)slot; (void)f; }
}

#endif /* RG_NATIVE_ONLY */
