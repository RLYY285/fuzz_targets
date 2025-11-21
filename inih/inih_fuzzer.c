#include "ini.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // 确保 malloc/free 可用

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // 复制输入数据，因为 ini_parse_string 可能会修改 buffer
    char *input_copy = (char*)malloc(size + 1);
    if (!input_copy) return 0;
    
    memcpy(input_copy, data, size);
    input_copy[size] = '\0'; 

    // 核心调用：ini_parse_string 会触发你植入的 5 个漏洞
    ini_parse_string(input_copy, NULL, NULL);

    free(input_copy);
    return 0;
}
