#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstddef>
#include <iostream>

//#define TEST

namespace hb {

class Log;

class String {
public:
    using size_type = size_t;
    using iterator = char*;

    iterator Begin(void);
    iterator End(void);

    void PrintAll(const char* name);

    ~String();

    String();
    String(const String& source);
    String(String&& source);
    String(const char* source);
    String(const char* source, size_type position,
           size_type length = no_position_);
    String(size_type length, char element);

    String& operator=(const String& source);
    String& operator=(String&& source);
    String& operator=(const char* source);
    String& operator=(char source);
    char& operator[](size_type position);
    const char& operator[](size_type position) const;

    String& operator+=(const String& new_source);
    String& operator+=(const char* new_source);
    String& operator+=(char new_source);

    const char* Data(void) const;
    size_type GetLength(void) const;
    bool IsEmpty(void) const;

    void GetLine(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const String& content);
    friend std::istream& operator>>(std::istream& is, String& target);
    friend bool operator==(const String& left, const String& right);
    friend bool operator==(const String& left, const char* right);
    friend bool operator==(const char* left, const String& right);
    friend String operator+(const String& left, const String& right);
    friend String operator+(const String& left, const char* right);
    friend String operator+(const char* left, const String& right);
    friend String operator+(const String& left, char right);
    friend String operator+(char left, const String& right);

private:
    size_type length_;
    char* string_;
    static const size_type kInputBufferSize = 1024;
    static const size_type no_position_ = -1;
};

std::ostream& operator<<(std::ostream& os, const String& content);
std::istream& operator>>(std::istream& is, String& target);
bool operator==(const String& left, const String& right);
bool operator==(const String& left, const char* right);
bool operator==(const char* left, const String& right);
String operator+(const String& left, const String& right);
String operator+(const String& left, const char* right);
String operator+(const char* left, const String& right);
String operator+(const String& left, char right);
String operator+(char left, const String& right);

} // namespace hb

#endif