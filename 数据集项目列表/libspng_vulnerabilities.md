

### 📝 Project 1: libspng 漏洞注入总结 (Ground Truth)

| ID | 项目名称 | 基础版本 | 漏洞类型 (Type) | 注入文件:行号 (Location) | 注入函数 (Function) | 触发原因 (Root Cause) | 对应的 CVE (模拟) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | libspng | **v0.7.2** | **Stack Buffer Overflow** | `spng.c`: ~2283 | `read_ihdr` | 使用 `sprintf` 将超长 `Width` 值写入 16 字节栈缓冲区。 | Sim-CVE-001 |
| **2** | libspng | **v0.7.2** | **Double Free** | `spng.c`: ~5040 | `spng_ctx_free` | 在销毁上下文中重复调用 `free(ctx->row_buf)`。 | Sim-CVE-002 |
| **3** | libspng | **v0.7.2** | **Use-After-Free** | `spng.c`: ~4989 | `spng_ctx_free` | 释放 `stream_buf` 后未置空并立即访问其内容。 | Sim-CVE-003 |
| **4** | libspng | **v0.7.2** | **Null Pointer Deref** | `spng.c`: ~3619  | `spng_decode_image` | 模拟逻辑错误，在 `buf` 为 NULL 时强制访问 `buf[0]`。 | Sim-CVE-004 |
| **5** | libspng | **v0.7.2** | **Format String** | `spng.c`: ~2619 | `spng_strerror` | 错误地将不可控的字符串变量直接作为 `printf` 的格式化参数。 | Sim-CVE-005 |


