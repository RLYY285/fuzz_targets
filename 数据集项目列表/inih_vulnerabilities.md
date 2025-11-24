# INIH 漏洞汇总表

## 漏洞总览表

| 漏洞编号 | CWE类型 | 漏洞说明 | 位置 | 描述 |
|---------|---------|----------|------|------|
| #1 | CWE-252 | malloc 返回值未检查 | ini.c | 忽略 malloc 返回值可能导致 NULL 解引用 |
| #2 | CWE-416 | 提前 free 导致可能的 UAF | ini.c | free 后在宏中继续使用 |
| #3 | CWE-415 | double-free | ini.c | 同一指针被多次释放 |
| #4 | CWE-170 | 字符串终止符移除导致潜在问题 | ini.c | 字符串未正确终止 |
| #5 | CWE-193 | strncpy0 越界写（size+1） | ini.c | off-by-one 缓冲区溢出 |

---

## 漏洞详情

### #1 CWE-252
- **位置**：`ini_malloc(INI_INITIAL_ALLOC); /*CWE-252*/`
- **问题**：malloc 未检查 NULL
- **影响**：潜在 NULL dereference

### #2 CWE-416
- **位置**：`ini_free(line); /*CWE-416*/` (INI_HANDLER_LINENO 分支)
- **问题**：free 后仍可能被使用
- **影响**：Use-After-Free

### #3 CWE-415
- **位置**：函数末尾 `ini_free(line); /*CWE-415*/`
- **问题**：同一指针可能被重复 free
- **影响**：double-free 崩溃

### #4 CWE-170
- **位置**：`//*end = '\0'; /*CWE-170*/`
- **问题**：移除终止符导致未终止字符串
- **影响**：字符串操作越界风险

### #5 CWE-193
- **位置**：`strncpy0(section, start + 1, sizeof(section) + 1); /* CWE-193 */`
- **问题**：size 设置为缓冲区+1
- **影响**：off-by-one 写越界
