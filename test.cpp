#include "log.h"
#include "my_string.h"
#include <cstdio>
#include <vector>

void TestConstructor(void);
void TestOperator(void);
void TestIO(void);
void TestCompare(void);
void TestStl(void);
hb::String ReturnHbString(void);
void TestIterator(void);

int
main(int argc, char const* argv[]) {
    // TestConstructor();
    // TestOperator();
    // TestIO();
    // TestCompare();
    TestStl();
    // TestIterator();

    return 0;
}

void
TestConstructor(void) {
    hb::String s0;
    s0.PrintAll("s0");

    hb::String s1(nullptr);
    s1.PrintAll("s1");

    hb::String s2(s1);
    s2.PrintAll("s2");

    hb::String s3(hb::String("GGGGG"));
    s3.PrintAll("s3");

    hb::String s4(nullptr, 0);
    s4.PrintAll("s4");

    hb::String s5(5, 'N');
    s5.PrintAll("s5");

    hb::String s6(std::move(s1));
    s6.PrintAll("s6");
    s1.PrintAll("s1");
}

void
TestOperator(void) {
    hb::String s0("ABCDEFG");
    s0 = s0;
    s0.PrintAll("s0");

    hb::String s1 = s0;
    s1.PrintAll("s1");

    hb::String s2 = "ZXCVBNM";
    s2.PrintAll("s2");

    hb::String s3 = hb::String("POIUY");
    s3.PrintAll("s3");

    s0 += s2 += s3 += hb::String("000") += 'A';
    s0 += 'A';
    s0.PrintAll("s0");

    s0 += s0;
    s0.PrintAll("s0");

    s1 = hb::String("huang") + 'C' + s2 + hb::String(".");
    s1.PrintAll("s1");
}

void
TestIO(void) {
    hb::String s0;
    s0.GetLine(std::cin);
    s0.PrintAll("s0");

    std::cin >> s0;
    s0.PrintAll("s0");
    std::cout << s0 << std::endl;
}

void
TestCompare(void) {
    hb::String s0 = "iii";
    hb::String s1 = "iii";

    if (s0 == s1) {
        printf("s0 == s1\n");
    } else {
        printf("s0 != s1\n");
    }

    if (s0 == "iii") {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}

hb::String
ReturnHbString(void) {
    hb::String s("return value");
    return s;
}

void
TestStl(void) {
    hb::String s0("ABC");
    std::vector<hb::String> v;
    v.push_back("12345");
    v.push_back(s0);
    v.push_back(hb::String("OK"));
    v.push_back(ReturnHbString());

    for (auto i : v) {
        std::cout << i << std::endl;
    }
}

void
TestIterator(void) {
    hb::String s("Hubbard Huang");
    for (auto i = s.Begin(); i != s.End(); i++) {
        printf("%c", *i);
    }
    printf("\n");
}