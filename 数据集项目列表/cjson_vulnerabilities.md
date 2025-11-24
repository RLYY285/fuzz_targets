# cJSON 漏洞汇总表

## 漏洞总览表

| 漏洞编号 | CWE类型 | 位置 | 描述 |
|---------|---------|------|------|
| #1 | CWE-134 | cJSON_Version() | sprintf 使用无格式化字符串，可能导致格式化字符串注入 |
| #2 | CWE-415 | cJSON_Delete() | 对同一 valuestring 指针进行双重释放 |
| #3 | CWE-120 | cJSON_SetValuestring() | strcpy 未检查缓冲区长度，存在缓冲区溢出风险 |
| #4 | CWE-416 | parse_string (fail 路径) | output 被释放后 output_pointer 被继续访问 |
| #5 | CWE-252 | ensure() realloc | 未检查 realloc 返回值是否为 NULL |
| #6 | CWE-170 | print_number() | 移除终止符写入，导致潜在的字符串越界 |

---

## 漏洞详情

### #1 CWE-134  
**位置**：`cJSON_Version()`  
**代码**：  
```c
sprintf(version, CJSON_VERSION_MAJOR, CJSON_VERSION_MINOR, CJSON_VERSION_PATCH); /*CWE-134*/
```  
**问题**：格式化字符串缺失，`sprintf` 第一个参数必须为格式化字符串。  
**风险**：可能导致格式化字符串漏洞或未定义行为。

---

### #2 CWE-415  
**位置**：`cJSON_Delete()`  
```c
global_hooks.deallocate(item->valuestring);
global_hooks.deallocate(item->valuestring); /*CWE-415*/
```  
**问题**：同一指针被释放两次。  
**风险**：double-free，可能被利用进行堆破坏。

---

### #3 CWE-120  
**位置**：`cJSON_SetValuestring()`  
```c
strcpy(object->valuestring, valuestring); /* CWE-120 */
```  
**问题**：未检查目标缓冲区大小。  
**风险**：缓冲区溢出，可导致 RCE 或程序崩溃。

---

### #4 CWE-416  
**位置**：`parse_string()` fail 分支  
```c
input_buffer->hooks.deallocate(output);
if (output_pointer[0] == 'A') {} /*CWE-416*/
```  
**问题**：`output` 已释放，`output_pointer` 仍被访问。  
**风险**：Use-After-Free。

---

### #5 CWE-252  
**位置**：`ensure()`  
```c
p->buffer = newbuffer; /*CWE-252*/
```  
**问题**：未检查 realloc 是否返回 NULL。  
**风险**：后续使用 NULL 指针导致崩溃。

---

### #6 CWE-170  
**位置**：`print_number()`  
```c
/*output_pointer[i] = '\0';*/ // CWE-170
```  
**问题**：字符串未写入终止符。  
**风险**：导致越界读取或未定义行为。

