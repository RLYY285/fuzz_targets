好的，这是针对 **libspng 项目（Project 1）** 的详细漏洞注入和验证的报告内容，完全采用我们之前确认过的格式。

libspng 是你的第一个项目，其核心流程和修正方案为后续所有项目（尤其是 `cJSON` 和 `miniz`）打下了基础。

### 📝 Project 1: libspng 漏洞注入总结 (Ground Truth)

| ID | 项目名称 | 基础版本 | 漏洞类型 (Type) | 注入文件:行号 (Location) | 注入函数 (Function) | 触发原因 (Root Cause) | 对应的 CVE (模拟) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | libspng | **v0.7.2** | **Stack Buffer Overflow** | `spng.c`: ~3606 | `spng_decode_image` | 使用 `sprintf` 将超长 `Width` 值写入 16 字节栈缓冲区。 | Sim-CVE-001 |
| **2** | libspng | **v0.7.2** | **Double Free** | `spng.c`: ~5040 | `spng_ctx_free` | 在销毁上下文中重复调用 `free(ctx->row_buf)`。 | Sim-CVE-002 |
| **3** | libspng | **v0.7.2** | **Use-After-Free** | `spng.c`: ~4989 | `spng_ctx_free` | 释放 `stream_buf` 后未置空并立即访问其内容。 | Sim-CVE-003 |
| **4** | libspng | **v0.7.2** | **Null Pointer Deref** | `spng.c`: ~5975 | `spng_set_png_buffer` | 模拟逻辑错误，在 `buf` 为 NULL 时强制访问 `buf[0]`。 | Sim-CVE-004 |
| **5** | libspng | **v0.7.2** | **Format String** | `spng.c`: ~2619 | `spng_strerror` | 错误地将不可控的字符串变量直接作为 `printf` 的格式化参数。 | Sim-CVE-005 |

---

### 模块回顾：libspng 关键配置与修正总结

| 阶段 | 关键操作 | 解决的问题 |
| :--- | :--- | :--- |
| **1. Harness 准备** | **创建 `miniz_fuzzer.c`**：手动创建 `LLVMFuzzerTestOneInput` 函数，并使用 `spng_set_png_buffer` 来喂数据。 | 解决了源码仓库中缺少 Fuzzer 入口的问题。 |
| **2. 编译依赖修正** | 在 `libspng/Dockerfile` 中添加 **`zlib1g-dev`** 包。 | 解决了编译时找不到 `zlib.h` 头文件的错误。 |
| **3. 链接器修正** | 在 `build.sh` 中链接时添加 **`-lz`** 和 **`-lm`** 旗标。 | 解决了链接器找不到 zlib 和数学库的错误。 |
| **4. Fuzzing 路径修正** | 发现 Fuzzer 无法触发漏洞。 | 确认了 `run_fuzzer` 需要 **Seed Corpus** 来绕过 `libxml2` 基础的非法字符检查。 |
| **5. 最终产物** | **ASAN/Coverage/Release** 三版本可执行文件。 | 满足了 Buttercup 系统的最终交付要求。 |
