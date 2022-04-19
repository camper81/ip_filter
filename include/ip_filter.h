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

void update_pool(const std::vector<std::string>& ip_strings);

std::ostream& print(std::ostream& os, const std::vector<int>& vec);
void print_pool();

void sort_pool();