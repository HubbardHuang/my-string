#include "my_string.h"
#include <cctype>
#include <cstdio>
#include <cstring>

namespace hb {

void
String::PrintAll(const char* name) {
    printf("%s:\n", name);
    printf("length_ = %lu\n", length_);
    printf("string_ = \"");
    if (string_ == nullptr) {
        printf("nullptr");
    } else {
        for (size_type i = 0; i <= length_; i++) {
            if (string_[i] == '\0') {
                printf("\\0");
            } else {
                printf("%c", string_[i]);
            }
            if (i != length_) {
                printf(" ");
            }
        }
    }
    printf("\"\n\n");
}

String::iterator
String::Begin(void) {
    return string_;
}

String::iterator
String::End(void) {
    return string_ + length_;
}

String::~String() {
#ifdef TEST
    printf("call ~String().\n");
#endif
    delete[] string_;
}

String::String()
  : length_(0)
  , string_(new char[length_ + 1]) {
    string_[length_] = '\0';
#ifdef TEST
    printf("call String().\n");
#endif
}

String::String(const String& source)
  : length_(source.length_)
  , string_(new char[length_ + 1]) {
    strncpy(string_, source.string_, length_);
    string_[length_] = '\0';
#ifdef TEST
    printf("call String(const String& source).\n");
#endif
}

String::String(String&& source)
  : length_(source.length_)
  , string_(source.string_) {
    source.length_ = 0;
    source.string_ = nullptr;
#ifdef TEST
    printf("call String(String&& source).\n");
#endif
}

String::String(const char* source)
  : length_((source == nullptr) ? 0 : strlen(source))
  , string_(new char[length_ + 1]) {
    if (length_ != 0) {
        strncpy(string_, source, length_);
    }
    string_[length_] = '\0';
#ifdef TEST
    printf("call String(const char* source).\n");
#endif
}

String::String(const char* source, size_type position, size_type length) {
    if (source == nullptr) {
        length_ = 0;
    } else {
        size_type source_length = strlen(source);
        if (position >= source_length) {
            // TODO: record the error
            exit(-1);
        }
        length_ = length + position > source_length ? source_length : length;
    }
    string_ = new char[length_ + 1];
    strncpy(string_, source + position, length_);
    string_[length_] = '\0';
#ifdef TEST
    printf("call String(const char* source, size_type position, size_type "
           "length).\n");
#endif
}

String::String(size_type length, char element)
  : length_(length)
  , string_(new char[length_ + 1]) {
    for (size_type i = 0; i < length_; i++) {
        string_[i] = element;
    }
    string_[length_] = '\0';
#ifdef TEST
    printf("call String(size_type length, char element).\n");
#endif
}

String&
String::operator=(const String& source) {
#ifdef TEST
    printf("call operator=(const String& source).\n");
#endif
    if (&source == this) {
        return *this;
    }

    length_ = source.length_;
    string_ = new char[length_ + 1];
    strncpy(string_, source.string_, length_);
    string_[length_] = '\0';

    return *this;
}

String&
String::operator=(String&& source) {
#ifdef TEST
    printf("call operator=(String&& source).\n");
#endif
    length_ = source.length_;
    string_ = source.string_;
    source.length_ = 0;
    source.string_ = nullptr;
    return *this;
}

String&
String::operator=(const char* source) {
#ifdef TEST
    printf("call operator=(const char* source).\n");
#endif
    if (source == nullptr) {
        length_ = 0;
    } else {
        size_type source_length = strlen(source);
        length_ = source_length;
    }
    string_ = new char[length_ + 1];
    strncpy(string_, source, length_);
    string_[length_] = '\0';
    return *this;
}

String&
String::operator=(char source) {
#ifdef TEST
    printf("call operator=(char source).\n");
#endif
    length_ = 1;
    string_ = new char[length_ + 1];
    string_[0] = source;
    string_[length_] = '\0';
    return *this;
}

char& String::operator[](size_type position) {
    if (position >= length_) {
        // TODO: record error
        exit(-1);
    }
    return string_[position];
}

const char& String::operator[](size_type position) const {
    if (position >= length_) {
        // TODO: record error
        exit(-1);
    }
    return string_[position];
}

String&
String::operator+=(const String& new_source) {
#ifdef TEST
    printf("call operator+=(const String& new_source).\n");
#endif
    char* string_original = string_;
    size_type length_original = length_;

    length_ += new_source.length_;
    string_ = new char[length_ + 1];
    strncpy(string_, string_original, length_original);
    if (&new_source != this) {
        strncpy(string_ + length_original, new_source.string_,
                new_source.length_);
    } else {
        strncpy(string_ + length_original, string_original, length_original);
    }
    string_[length_] = '\0';

    delete[] string_original;
    return *this;
}

String&
String::operator+=(const char* new_source) {
#ifdef TEST
    printf("call operator+=(const char* new_source).\n");
#endif
    char* string_original = string_;
    size_type length_original = length_;

    size_type new_source_length = strlen(new_source);
    length_ += new_source_length;
    string_ = new char[length_ + 1];
    strncpy(string_, string_original, length_original);
    strncpy(string_ + length_original, new_source, new_source_length);
    string_[length_] = '\0';

    delete[] string_original;
    return *this;
}

String&
String::operator+=(char new_source) {
#ifdef TEST
    printf("call operator+=(char new_source).\n");
#endif
    char* string_original = string_;
    size_type length_original = length_;

    length_ += 1;
    string_ = new char[length_ + 1];
    stpncpy(string_, string_original, length_original);
    string_[length_original] = new_source;
    string_[length_] = '\0';

    delete[] string_original;
    return *this;
}

const char*
String::Data(void) const {
    return string_;
}

String::size_type
String::GetLength(void) const {
    return length_;
}

bool
String::IsEmpty(void) const {
    return length_ == 0 ? true : false;
}

void
String::GetLine(std::istream& is) {
    delete[] string_;
    length_ = 0;
    char buffer[kInputBufferSize] = { 0 };
    char* buffer_iterator = buffer;

    while (buffer_iterator != buffer + kInputBufferSize) {
        char c = is.get();
        if (c == '\n') {
            break;
        }
        *buffer_iterator = c;
        ++length_;
        ++buffer_iterator;
    }
    string_ = new char[length_ + 1];
    strncpy(string_, buffer, length_);
    string_[length_] = '\0';
}

std::ostream&
operator<<(std::ostream& os, const String& content) {
    if (content.length_ != 0) {
        os << content.string_;
    }
    return os;
}

std::istream&
operator>>(std::istream& is, String& target) {
    delete[] target.string_;
    target.length_ = 0;

    char buffer[String::kInputBufferSize] = { 0 };
    char* buffer_iterator = buffer;

    while (buffer_iterator != buffer + String::kInputBufferSize) {
        char c = is.get();
        if (isspace(c)) {
            break;
        }
        *buffer_iterator = c;
        ++target.length_;
        ++buffer_iterator;
    }
    target.string_ = new char[target.length_ + 1];
    strncpy(target.string_, buffer, target.length_);
    target.string_[target.length_] = '\0';
}

bool
operator==(const String& left, const String& right) {
    if (strcmp(left.string_, right.string_) == 0) {
        return true;
    } else {
        return false;
    }
}

bool
operator==(const String& left, const char* right) {
    String temp(right);
    return operator==(left, temp);
}

bool
operator==(const char* left, const String& right) {
    String temp(left);
    return operator==(temp, right);
}

String
operator+(const String& left, const String& right) {
    String result;
    result.length_ = left.length_ + right.length_;
    result.string_ = new char[result.length_ + 1];
    strncpy(result.string_, left.string_, left.length_);
    strncpy(result.string_ + left.length_, right.string_, right.length_);
    result.string_[result.length_] = '\0';
    return result;
}

String
operator+(const String& left, const char* right) {
    return operator+(left, String(right));
}

String
operator+(const char* left, const String& right) {
    return operator+(String(left), right);
}

String
operator+(const String& left, char right) {
    return operator+(left, String(1, right));
}

String
operator+(char left, const String& right) {
    return operator+(String(1, left), right);
}

} // namespace hb