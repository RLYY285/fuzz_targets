#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // 核心：尝试用 xmlReadMemory 解析输入的原始数据
    xmlDocPtr doc = xmlReadMemory((const char*)Data, (int)Size, "noname.xml", NULL, XML_PARSE_NONET);

    // 清理 (会触发你埋在 tree.c 里的 Double Free 和 UAF)
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }

    return 0;
}
