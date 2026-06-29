#ifndef COMMON_HPP
#define COMMON_HPP
#include <cstdint>
constexpr int BUF_SIZE {1024};

bool str2num(char const* str, int32_t& res);
bool str2numV2(char const* str, int32_t& res);
bool is_vaild_port(int32_t port);
void error_handling(char const* msg);
#endif