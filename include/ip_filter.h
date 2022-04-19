#pragma once
#include <vector>
#include <string_view>

std::vector<std::string_view> split_by(std::string_view str, char d);
std::vector<int> split(std::string_view str, char d);
void filter_by_one(const std::vector<std::vector<int>>& vec, int arg0);
void filter_by_two(const std::vector<std::vector<int>>& vec, int arg0, int arg1);
void filter_by_any(const std::vector<std::vector<int>>& vec, int arg);
void filter(int arg);
void filter(int arg0, int arg1);
void filter_any(int arg);
void parse_string(const std::vector<std::string>& ip_strings);
void print_all(const std::vector<std::vector<int>>& vec);