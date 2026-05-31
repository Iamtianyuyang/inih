# ini_parser

这是一个整理后的纯 C INI 解析静态库工程，基于 `inih` 的 C 解析接口保留：

- `ini.c`
- `ini.h`

仓库已移除 C++ wrapper、示例程序和原始测试目录，只保留适合在 C 项目中直接链接使用的最小结构。

## 目录结构

```text
.
├── CMakeLists.txt
├── LICENSE.txt
├── README.md
├── include/
│   └── ini.h
├── src/
│   └── ini.c
└── test/
    ├── CMakeLists.txt
    ├── test.ini
    └── test_basic.c
```

## 特性

- 只使用 C 语言构建
- 生成静态库 `ini_parser`
- 保留原始 `inih` C 接口
- 不引入 C++ 文件
- 默认不构建测试
- 提供一个可选测试程序，用于打印解析结果并验证基本功能

## 构建静态库

```bash
cmake -S . -B build
cmake --build build
```

构建完成后会生成静态库：

```text
build/libini_parser.a
```

## 运行测试

开启测试构建：

```bash
cmake -S . -B build-test -DINI_PARSER_BUILD_TESTS=ON
cmake --build build-test
ctest --test-dir build-test --output-on-failure
```

也可以直接运行测试程序查看解析输出：

```bash
./build-test/test/ini_parser_test
```

示例输出：

```text
parsed: [database] host=127.0.0.1
parsed: [database] port=3306
parsed: [app] name=ini_parser_demo
summary:
database.host=127.0.0.1
database.port=3306
app.name=ini_parser_demo
ini_parser_test passed
```

## 在你的 C 项目中使用

你的业务工程只需要：

1. 包含头文件目录 `include/`
2. 链接生成的静态库 `libini_parser.a`
3. 在自己的代码中调用 `ini_parse()` 等原始 C 接口

例如：

```c
#include "ini.h"

static int handler(void* user, const char* section, const char* name, const char* value)
{
    /* 在这里把 section/name/value 写入你的配置结构体 */
    return 1;
}

int load_config(const char* path, void* user_data)
{
    return ini_parse(path, handler, user_data);
}
```

后续你可以在自己的业务项目里单独实现 `config.c` / `config.h`，这个仓库本身只提供底层 INI 解析能力。

## 许可证

本项目保留原始 `inih` 的许可证文件：

- `LICENSE.txt`
