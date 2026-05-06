#pragma once
#include <array>

class Error {
 public:
  enum Code {
    kSuccess,
    kFull,
    kEmpty,
    kNoEnoughMemory,
    kIndexOutOfRange,
    kHostControllerNotHalted,
    kInvalidSlotID,
    kPortNotConnected,
    kInvalidEndpointNumber,
    kTransferRingNotSet,
    kAlreadyAllocated,
    kNotImplemented,
    kInvalidDescriptor,
    kBufferTooSmall,
    kUnknownDevice,
    kNoCorrespondingSetupStage,
    kTransferFailed,
    kInvalidPhase,
    kUnknownXHCISpeedID,
    kNoWaiter,
    kLastOfCode,
  };

  // initializer list is a C++11 feature that allows the member variable code_
  // to be initialized directly with the value of code,
  // which can improve performance and reduce memory usage.
  Error(Code code, const char* file, int line)
      : code_{code}, file_{file}, line_{line} {};

  operator bool() const { return code_ != Code::kSuccess; }

  const char* Name() const { return code_names_[static_cast<int>(code_)]; }

  Code Cause() const { return code_; }
  const char* File() const { return file_; }
  int Line() const { return line_; }

 private:
  // consexpr is a C++11 feature that allows the value of the variable to be
  // evaluated at compile time, which can improve performance and reduce memory
  // usage. In this case, it allows the array of error code names to be stored
  // in read-only memory and accessed efficiently.
  static constexpr std::array code_names_ = {
      "kSuccess",
      "kFull",
      "kEmpty",
      "kNoEnoughMemory",
      "kIndexOutOfRange",
      "kHostControllerNotHalted",
      "kInvalidSlotID",
      "kPortNotConnected",
      "kInvalidEndpointNumber",
      "kTransferRingNotSet",
      "kAlreadyAllocated",
      "kNotImplemented",
      "kInvalidDescriptor",
      "kBufferTooSmall",
      "kUnknownDevice",
      "kNoCorrespondingSetupStage",
      "kTransferFailed",
      "kInvalidPhase",
      "kUnknownXHCISpeedID",
      "kNoWaiter",
  };
  static_assert(Error::kLastOfCode == code_names_.size());

  Code code_;         // _ means private memmber variable.
  int line_;          // line number where the error is created.
  const char* file_;  // file name where the error is created.
};

#define MAKE_ERROR(code) Error((code), __FILE__, __LINE__)

template <class T>
struct WithError {
  T value;
  Error error;
};