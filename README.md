# my-string

该小项目重写了 C++ `std::string` 类的部分功能，主要有：
- RAII 析构函数；
- 各种构造函数，包括移动构造函数；
- 各种运算符重载；
- 简单模拟迭代器。

在文件 my_string.h 中去掉 `#define TEST` 的注释即可进入 debug 模式，打印被调用的函数名。
