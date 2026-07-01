#include "common.hpp"
#include <cctype>
#include <charconv>
#include <climits>
#include <cstdint>
#include <cstring>
#include <iostream>

bool str2num(char const *str, int32_t &res) {
  if (!str)
    return false;

  bool neg = false;
  int64_t val = 0;

  // sign
  if (*str == '-') {
    neg = true;
    ++str;
  } else if (*str == '+') {
    ++str;
  }

  if (*str == '\0')
    return false;

  while (*str) {
    if (*str < '0' || *str > '9')
      return false;

    val = val * 10 + (*str - '0');

    // overflow check
    if (!neg && val > INT32_MAX)
      return false;
    if (neg && -val < INT32_MIN)
      return false;

    ++str;
  }

  res = neg ? -static_cast<int32_t>(val) : static_cast<int32_t>(val);

  return true;
}

bool str2numV2(char const *str, int32_t &res) {
  if (!str)
    return false;

  // skip leading spaces
  while (*str && std::isspace(static_cast<unsigned char>(*str)))
    ++str;

  const char *end = str + std::strlen(str);

  auto [ptr, ec] = std::from_chars(str, end, res);

  if (ec != std::errc()) {
    return false;
  }

  // skip trailing spaces
  while (ptr < end && std::isspace(static_cast<unsigned char>(*ptr)))
    ++ptr;

  return ptr == end;
}


bool is_vaild_port(int32_t port){
    return port <= 65535;
}

void error_handling(const char *msg) {
  std::cout << msg << " errno:" << errno << '\n';
  exit(-1);
}