#pragma once
#include <array>

class Error {
    public:
        enum Code {
            kSuccess,
            kFull,
            kEmpty,
            kLastOfCode, 
        };

        // initializer list is a C++11 feature that allows the member variable code_ 
        // to be initialized directly with the value of code, 
        // which can improve performance and reduce memory usage.
        Error(Code code): code_{code} {};
        
        operator bool() const {
            return code_ != Code::kSuccess;
        }
        
        const char* Name() const {
            return code_names_[static_cast<int>(code_)];
        }

    private:
        // consexpr is a C++11 feature that allows the value of the variable to be evaluated at compile time,
        // which can improve performance and reduce memory usage. 
        // In this case, it allows the array of error code names to be stored in read-only memory
        // and accessed efficiently.
        static constexpr std::array<const char*, 3> code_names_ = {
            "kSuccess",
            "kFull",
            "kEmpty",
         };
        Code code_; // _ means private memmber variable.
};
