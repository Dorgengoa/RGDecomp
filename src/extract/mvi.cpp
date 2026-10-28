// SPDX-License-Identifier: CC0-1.0
// MVI movie conversion. Written from the format description in docs/MVI.md.
//
// An MVI file is an MPEG-2 program stream (16 KiB packs) whose every 2048-byte sector is
// XORed with one fixed keystream. Video is stream 0xE0 (MPEG-2 MP@ML). Audio is private
// stream 1 (0xBD): each payload starts with 4 framing bytes (FF A0 00 00), and the
// concatenated payloads form a Sony "SShd"/"SSbd" block-interleaved 16-bit PCM stream.
//
// Output: the descrambled program stream with every audio packet turned into a padding
// packet of the same size (so the video bytes, the pack layout and the SCRs are unchanged),
// plus a canonical WAV whose sample 0 is presented at the first video PTS.
#include "mvi.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

namespace rgx::mvi {

namespace {

struct Keystream {
    std::array<uint8_t, kSector> b{};
    Keystream() {
        uint32_t k = kSeed;
        for (size_t i = 0; i < kSector; i += 4) {
            b[i + 0] = uint8_t(k);
            b[i + 1] = uint8_t(k >> 8);
            b[i + 2] = uint8_t(k >> 16);
            b[i + 3] = uint8_t(k >> 24);
            k *= kMul;
        }
    }
};
const Keystream& ks() {
    static const Keystream k;
    return k;
}

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

std::string hex_off(uint64_t v) {
    char b[32];
    std::snprintf(b, sizeof b, "0x%llx", (unsigned long long)v);
    return b;
}

// ---- input ------------------------------------------------------------------------------

class Source {
public:
    virtual ~Source() = default;
    // Reads up to n bytes at the current position; returns the count (0 at end).
    virtual size_t read(uint8_t* dst, size_t n) = 0;
};

class FileSource : public Source {
public:
    explicit FileSource(const fs::path& p) {
#ifdef _WIN32
        f_ = _wfopen(p.c_str(), L"rb");
#else
        f_ = std::fopen(p.c_str(), "rb");
#endif
        if (!f_) throw Error("cannot open '" + p.u8string() + "'");
    }
    ~FileSource() override {
        if (f_) std::fclose(f_);
    }
    size_t read(uint8_t* dst, size_t n) override {
        size_t got = std::fread(dst, 1, n, f_);
        if (got < n && std::ferror(f_)) throw Error("read error");
        return got;
    }

private:
    std::FILE* f_ = nullptr;
};

class MemSource : public Source {
public:
    MemSource(const uint8_t* d, size_t n) : d_(d), n_(n) {}
    size_t read(uint8_t* dst, size_t n) override {
        size_t c = std::min(n, n_ - pos_);
        if (c) std::memcpy(dst, d_ + pos_, c);
        pos_ += c;
        return c;
    }

private:
    const uint8_t* d_;
    size_t n_, pos_ = 0;
};

// Descrambling window over a Source: ensure(n) makes n bytes at the cursor contiguous.
class Window {
public:
    explicit Window(Source& s) : src_(s) {}
    // Returns false if fewer than n bytes remain in the file.
    bool ensure(size_t n) {
        if (len_ - pos_ >= n) return true;
        if (pos_ > 0) {
            std::memmove(buf_.data(), buf_.data() + pos_, len_ - pos_);
            len_ -= pos_;
            base_ += pos_;
            pos_ = 0;
        }
        if (buf_.size() < n + kChunk) buf_.resize(n + kChunk);
        while (len_ < n && !eof_) {
            size_t want = buf_.size() - len_;
            size_t got = src_.read(buf_.data() + len_, want);
            if (got == 0) {
                eof_ = true;
                break;
            }
            descramble(buf_.data() + len_, got, base_ + len_);
            len_ += got;
        }
        return len_ - pos_ >= n;
    }
    bool at_end() { return !ensure(1); }
    const uint8_t* p() const { return buf_.data() + pos_; }
    void skip(size_t n) { pos_ += n; }
    uint64_t offset() const { return base_ + pos_; }

private:
    static constexpr size_t kChunk = 1 << 20;
    Source& src_;
    std::vector<uint8_t> buf_;
    size_t pos_ = 0, len_ = 0;
    uint64_t base_ = 0;  // file offset of buf_[0]
    bool eof_ = false;
};

// ---- output -----------------------------------------------------------------------------

class Sink {
public:
    virtual ~Sink() = default;
    virtual void write(const void* d, size_t n) = 0;
    virtual void write_at(uint64_t off, const void* d, size_t n) = 0;
    virtual void finish() {}
};

class FileSink : public Sink {
public:
    explicit FileSink(const fs::path& p) : path_(p) {
#ifdef _WIN32
        f_ = _wfopen(p.c_str(), L"wb");
#else
        f_ = std::fopen(p.c_str(), "wb");
#endif
        if (!f_) throw Error("cannot create '" + p.u8string() + "'");
        buf_.reserve(kBuf);
    }
    ~FileSink() override {
        if (f_) std::fclose(f_);
    }
    void write(const void* d, size_t n) override {
        const uint8_t* s = static_cast<const uint8_t*>(d);
        if (buf_.size() + n > kBuf) flush();
        if (n >= kBuf) {
            put(s, n);
            return;
        }
        buf_.insert(buf_.end(), s, s + n);
    }
    void write_at(uint64_t off, const void* d, size_t n) override {
        flush();
#ifdef _WIN32
        bool ok = _fseeki64(f_, (long long)off, SEEK_SET) == 0;
#else
        bool ok = fseeko(f_, (off_t)off, SEEK_SET) == 0;
#endif
        if (!ok) fail();
        put(static_cast<const uint8_t*>(d), n);
#ifdef _WIN32
        ok = _fseeki64(f_, 0, SEEK_END) == 0;
#else
        ok = fseeko(f_, 0, SEEK_END) == 0;
#endif
        if (!ok) fail();
    }
    void finish() override {
        flush();
        int r = std::fclose(f_);
        f_ = nullptr;
        if (r != 0) fail();
    }

private:
    static constexpr size_t kBuf = 1 << 20;
    void flush() {
        if (!buf_.empty()) put(buf_.data(), buf_.size());
        buf_.clear();
    }
    void put(const uint8_t* d, size_t n) {
        if (std::fwrite(d, 1, n, f_) != n) fail();
    }
    [[noreturn]] void fail() { throw Error("write to '" + path_.u8string() + "' failed (disk full?)"); }
    fs::path path_;
    std::FILE* f_ = nullptr;
    std::vector<uint8_t> buf_;
};

class StringSink : public Sink {
public:
    explicit StringSink(std::string* s) : s_(s) { s_->clear(); }
    void write(const void* d, size_t n) override { s_->append(static_cast<const char*>(d), n); }
    void write_at(uint64_t off, const void* d, size_t n) override {
        std::memcpy(&(*s_)[size_t(off)], d, n);
    }

private:
    std::string* s_;
};

void le16(uint8_t* p, uint32_t v) {
    p[0] = uint8_t(v);
    p[1] = uint8_t(v >> 8);
}
void le32(uint8_t* p, uint32_t v) {
    le16(p, v & 0xFFFF);
    le16(p + 2, v >> 16);
}
uint32_t rd_le32(const uint8_t* p) {
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}

// 33-bit PES timestamp from its 5-byte field.
int64_t pes_ts(const uint8_t* b) {
    return int64_t((b[0] >> 1) & 7) << 30 | int64_t((b[1] << 7) | (b[2] >> 1)) << 15 |
           int64_t((b[3] << 7) | (b[4] >> 1));
}

// ---- conversion -------------------------------------------------------------------------

class Converter {
public:
    Converter(Source& src, Sink& mpg, Sink& wav, MovieInfo& info) : w_(src), mpg_(mpg), wav_(wav), info_(info) {}

    void run() {
        if (!w_.ensure(4) || std::memcmp(w_.p(), "\0\0\1\xBA", 4) != 0)
            throw Error("not an MVI movie: the first sector does not descramble to an MPEG pack header");
        uint8_t hdr[44] = {};
        wav_.write(hdr, sizeof hdr);  // placeholder, patched in finish_wav()
        bool ended = false;
        while (!w_.at_end()) {
            if (ended) throw Error("data after the program end code at " + hex_off(w_.offset()));
            if (!w_.ensure(4)) throw Error("truncated start code at " + hex_off(w_.offset()));
            const uint8_t* p = w_.p();
            if (p[0] != 0 || p[1] != 0 || p[2] != 1)
                throw Error("lost MPEG-PS sync at " + hex_off(w_.offset()));
            switch (p[3]) {
            case 0xBA: pack_header(); break;
            case 0xB9:
                mpg_.write(p, 4);
                w_.skip(4);
                ended = true;
                break;
            case 0xBB:  // system header
            case 0xBE:  // padding
                copy_packet(nullptr);
                break;
            case 0xE0: copy_packet(&Converter::video_payload); break;
            case 0xBD: audio_packet(); break;
            default: throw Error("unexpected stream id " + hex_off(p[3]) + " at " + hex_off(w_.offset()));
            }
        }
        if (info_.packs == 0) throw Error("no MPEG packs");
        parse_sequence_header();
        finish_audio();
        mpg_.finish();
        wav_.finish();
    }

private:
    void pack_header() {
        if (!w_.ensure(14)) throw Error("truncated pack header at " + hex_off(w_.offset()));
        const uint8_t* p = w_.p();
        if ((p[4] & 0xC0) != 0x40) throw Error("not an MPEG-2 pack header at " + hex_off(w_.offset()));
        size_t n = 14 + (p[13] & 7);
        if (!w_.ensure(n)) throw Error("truncated pack header at " + hex_off(w_.offset()));
        mpg_.write(w_.p(), n);
        w_.skip(n);
        ++info_.packs;
    }

    // PES packet with a 16-bit length. For 0xE0 the payload goes to `fn` as well.
    void copy_packet(void (Converter::*fn)(const uint8_t*, size_t)) {
        if (!w_.ensure(6)) throw Error("truncated packet at " + hex_off(w_.offset()));
        size_t n = 6 + (size_t(w_.p()[4]) << 8 | w_.p()[5]);
        if (!w_.ensure(n)) throw Error("truncated packet at " + hex_off(w_.offset()));
        const uint8_t* p = w_.p();
        if (fn) {
            size_t hl = pes_header(p, n);
            if (p[7] & 0x80) {
                int64_t ts = pes_ts(p + 9);
                if (info_.video_first_pts < 0) info_.video_first_pts = ts;
            }
            ++info_.video_packets;
            (this->*fn)(p + hl, n - hl);
        }
        mpg_.write(p, n);
        w_.skip(n);
    }

    // Validates an MPEG-2 PES header; returns the offset of the payload.
    size_t pes_header(const uint8_t* p, size_t n) {
        if (n < 9 || (p[6] & 0xC0) != 0x80 || size_t(9) + p[8] > n)
            throw Error("bad PES header at " + hex_off(w_.offset()));
        if ((p[7] & 0x80) && p[8] < 5) throw Error("bad PES timestamp at " + hex_off(w_.offset()));
        return 9 + size_t(p[8]);
    }

    void video_payload(const uint8_t* d, size_t n) {
        info_.video_bytes += n;
        if (seq_.size() < 4096) seq_.insert(seq_.end(), d, d + std::min(n, 4096 - seq_.size()));
        for (size_t i = 0; i < n; ++i) {
            uint8_t b = d[i];
            if (want_code_) {
                if (b == 0x00) ++info_.pictures;
                want_code_ = false;
            }
            if (b == 1 && zeros_ >= 2) want_code_ = true;
            zeros_ = b == 0 ? zeros_ + 1 : 0;
        }
    }

    void audio_packet() {
        if (!w_.ensure(6)) throw Error("truncated packet at " + hex_off(w_.offset()));
        size_t n = 6 + (size_t(w_.p()[4]) << 8 | w_.p()[5]);
        if (!w_.ensure(n)) throw Error("truncated packet at " + hex_off(w_.offset()));
        const uint8_t* p = w_.p();
        size_t hl = pes_header(p, n);
        if (n - hl < 4 || p[hl] != 0xFF || p[hl + 1] != 0xA0)
            throw Error("unknown private-stream-1 substream at " + hex_off(w_.offset()));
        if ((p[7] & 0x80) && info_.audio_first_pts < 0) info_.audio_first_pts = pes_ts(p + 9);
        ++info_.audio_packets;
        audio_bytes(p + hl + 4, n - hl - 4);
        // Same-size padding packet in the program stream.
        std::vector<uint8_t>& pad = pad_;
        pad.assign(n, 0xFF);
        pad[0] = 0;
        pad[1] = 0;
        pad[2] = 1;
        pad[3] = 0xBE;
        pad[4] = p[4];
        pad[5] = p[5];
        mpg_.write(pad.data(), n);
        w_.skip(n);
    }

    void audio_bytes(const uint8_t* d, size_t n) {
        while (n > 0) {
            if (ahdr_.size() < 40) {
                size_t c = std::min(n, 40 - ahdr_.size());
                ahdr_.insert(ahdr_.end(), d, d + c);
                d += c;
                n -= c;
                if (ahdr_.size() == 40) parse_audio_header();
                continue;
            }
            if (body_seen_ >= body_len_) return;  // trailing zero fill after SSbd
            size_t c = size_t(std::min<uint64_t>(n, body_len_ - body_seen_));
            c = std::min(c, block_.size() - block_fill_);
            std::memcpy(block_.data() + block_fill_, d, c);
            block_fill_ += c;
            body_seen_ += c;
            d += c;
            n -= c;
            if (block_fill_ == block_.size()) emit_block(block_fill_);
        }
    }

    void parse_audio_header() {
        const uint8_t* h = ahdr_.data();
        if (std::memcmp(h, "SShd", 4) != 0 || rd_le32(h + 4) != 24 || std::memcmp(h + 32, "SSbd", 4) != 0)
            throw Error("audio stream does not start with an SShd/SSbd header");
        uint32_t fmt = rd_le32(h + 8);
        info_.audio_rate = rd_le32(h + 12);
        info_.audio_channels = rd_le32(h + 16);
        info_.audio_interleave = rd_le32(h + 20);
        body_len_ = rd_le32(h + 36);
        if (fmt != 1) throw Error("unsupported SShd audio format " + std::to_string(fmt) + " (only 16-bit PCM)");
        if (info_.audio_rate < 8000 || info_.audio_rate > 192000 || info_.audio_channels < 1 ||
            info_.audio_channels > 8 || info_.audio_interleave < 2 || info_.audio_interleave % 2 ||
            info_.audio_interleave > 65536)
            throw Error("implausible SShd audio parameters");
        block_.assign(size_t(info_.audio_channels) * info_.audio_interleave, 0);
    }

    // De-interleaves one (possibly short, final) block: [ch0 x il][ch1 x il]... into frames.
    void emit_block(size_t bytes) {
        const size_t ch = info_.audio_channels;
        const size_t per = bytes / ch / 2;  // samples per channel in this block
        const size_t il = info_.audio_interleave;
        frames_.resize(per * ch * 2);
        for (size_t s = 0; s < per; ++s)
            for (size_t c = 0; c < ch; ++c) {
                const uint8_t* src = block_.data() + c * (bytes == block_.size() ? il : bytes / ch) + s * 2;
                frames_[(s * ch + c) * 2] = src[0];
                frames_[(s * ch + c) * 2 + 1] = src[1];
            }
        info_.audio_frames_in += per;
        block_fill_ = 0;
        put_frames(frames_.data(), per);
    }

    void put_frames(const uint8_t* d, size_t count) {
        if (!aligned_) {
            if (info_.video_first_pts < 0) {  // wait for the first video timestamp
                pending_.insert(pending_.end(), d, d + count * frame_bytes());
                return;
            }
            align();
            if (!pending_.empty()) {
                std::vector<uint8_t> p;
                p.swap(pending_);
                put_frames(p.data(), p.size() / frame_bytes());
            }
        }
        if (drop_ > 0) {
            size_t k = size_t(std::min<uint64_t>(drop_, count));
            drop_ -= k;
            d += k * frame_bytes();
            count -= k;
        }
        if (count == 0) return;
        wav_.write(d, count * frame_bytes());
        info_.audio_frames_out += count;
    }

    size_t frame_bytes() const { return size_t(info_.audio_channels) * 2; }

    void align() {
        aligned_ = true;
        if (info_.audio_first_pts < 0) throw Error("audio stream has no timestamp");
        // Frames between the first video PTS and the first audio PTS, at the stream rate.
        int64_t d = info_.audio_first_pts - info_.video_first_pts;
        int64_t f = (d * int64_t(info_.audio_rate) + (d >= 0 ? 45000 : -45000)) / 90000;
        info_.audio_shift_frames = f;
        if (f > 0) {
            std::vector<uint8_t> z(size_t(f) * frame_bytes(), 0);
            wav_.write(z.data(), z.size());
            info_.audio_frames_out += uint64_t(f);
        } else {
            drop_ = uint64_t(-f);
        }
    }

    void finish_audio() {
        if (ahdr_.size() < 40) throw Error("movie has no audio stream");
        if (body_seen_ < body_len_) throw Error("audio stream is shorter than its SSbd length");
        if (block_fill_ > 0) emit_block(block_fill_ - block_fill_ % frame_bytes());
        if (!aligned_) {
            if (info_.video_first_pts < 0) throw Error("video stream has no timestamp");
            put_frames(nullptr, 0);
        }
        uint64_t data = info_.audio_frames_out * frame_bytes();
        if (data > 0xFFFFFFFFull - 36) throw Error("audio too long for WAV");
        uint8_t h[44];
        std::memcpy(h, "RIFF", 4);
        le32(h + 4, uint32_t(36 + data));
        std::memcpy(h + 8, "WAVEfmt ", 8);
        le32(h + 16, 16);
        le16(h + 20, 1);  // PCM
        le16(h + 22, info_.audio_channels);
        le32(h + 24, info_.audio_rate);
        le32(h + 28, info_.audio_rate * uint32_t(frame_bytes()));
        le16(h + 32, uint32_t(frame_bytes()));
        le16(h + 34, 16);
        std::memcpy(h + 36, "data", 4);
        le32(h + 40, uint32_t(data));
        wav_.write_at(0, h, sizeof h);
    }

    // Reads width/height/rate from the first sequence header and its extension.
    void parse_sequence_header() {
        const std::vector<uint8_t>& s = seq_;
        size_t i = 0;
        auto find = [&](uint8_t code, size_t from) -> size_t {
            for (size_t k = from; k + 4 <= s.size(); ++k)
                if (s[k] == 0 && s[k + 1] == 0 && s[k + 2] == 1 && s[k + 3] == code) return k;
            return SIZE_MAX;
        };
        i = find(0xB3, 0);
        if (i == SIZE_MAX || i + 12 > s.size()) throw Error("video stream has no MPEG sequence header");
        const uint8_t* h = &s[i + 4];
        info_.width = (h[0] << 4) | (h[1] >> 4);
        info_.height = ((h[1] & 15) << 8) | h[2];
        info_.aspect_code = h[3] >> 4;
        info_.frame_rate_code = h[3] & 15;
        size_t e = find(0xB5, i + 4);
        if (e != SIZE_MAX && e + 6 <= s.size() && (s[e + 4] >> 4) == 1)
            info_.profile_level = ((s[e + 4] & 15) << 4) | (s[e + 5] >> 4);
        else
            throw Error("video stream is not MPEG-2 (no sequence extension)");
    }

    Window w_;
    Sink& mpg_;
    Sink& wav_;
    MovieInfo& info_;
    std::vector<uint8_t> pad_, seq_, ahdr_, block_, frames_, pending_;
    size_t block_fill_ = 0;
    uint64_t body_len_ = 0, body_seen_ = 0, drop_ = 0;
    bool aligned_ = false, want_code_ = false;
    int zeros_ = 0;
};

}  // namespace

const uint8_t* keystream() { return ks().b.data(); }

void descramble(uint8_t* buf, size_t len, uint64_t file_offset) {
    const uint8_t* k = ks().b.data();
    size_t o = size_t(file_offset % kSector);
    for (size_t i = 0; i < len; ++i) {
        buf[i] ^= k[o];
        if (++o == kSector) o = 0;
    }
}

uint32_t seed_from_stored_key(const uint8_t* key, size_t len) {
    uint8_t lanes[4] = {0, 0, 0, 0};
    uint8_t k = 0x3E;
    for (size_t i = 0; i < len && key[i]; ++i) {
        lanes[i % 4] = uint8_t(lanes[i % 4] + (key[i] ^ k));
        k = uint8_t(k * 13 + 1);
    }
    return uint32_t(lanes[0]) | uint32_t(lanes[1]) << 8 | uint32_t(lanes[2]) << 16 | uint32_t(lanes[3]) << 24;
}

bool convert_movie(const fs::path& in, const fs::path& out_mpg, const fs::path& out_wav, MovieInfo* info,
                   std::string* err) {
    MovieInfo local;
    MovieInfo& mi = info ? *info : local;
    mi = MovieInfo();
    try {
        FileSource src(in);
        std::unique_ptr<FileSink> mpg, wav;
        try {
            mpg = std::make_unique<FileSink>(out_mpg);
            wav = std::make_unique<FileSink>(out_wav);
            Converter(src, *mpg, *wav, mi).run();
        } catch (...) {
            mpg.reset();
            wav.reset();
            std::error_code ec;
            fs::remove(out_mpg, ec);
            fs::remove(out_wav, ec);
            throw;
        }
        return true;
    } catch (const std::exception& e) {
        if (err) *err = e.what();
        return false;
    }
}

bool convert_movie_memory(const uint8_t* data, size_t size, std::string* mpg, std::string* wav, MovieInfo* info,
                          std::string* err) {
    MovieInfo local;
    MovieInfo& mi = info ? *info : local;
    mi = MovieInfo();
    try {
        MemSource src(data, size);
        StringSink m(mpg), w(wav);
        Converter(src, m, w, mi).run();
        return true;
    } catch (const std::exception& e) {
        if (err) *err = e.what();
        return false;
    }
}

}  // namespace rgx::mvi
