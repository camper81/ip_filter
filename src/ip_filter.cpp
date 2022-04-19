#include <cassert>
#include <iostream>

#include <string>

#include <algorithm>


#include <charconv>
#include <ranges>

#include "../include/ip_filter.h"

std::vector<std::vector<int>> ip_pool;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string_view> split_by(std::string_view str, char d)
{
    std::vector<std::string_view> result;
    while (!str.empty()) {
        size_t pos = str.find(d);
        result.emplace_back(str.substr(0, pos));
        str.remove_prefix(pos != str.npos ? pos + 1 : str.size());
    }
    return result;
}

std::vector<int> split(std::string_view str, char d)
{
    std::vector<int> result;
    int num;
    while (!str.empty()) {
        size_t pos = str.find(d);
        std::from_chars(str.data(), pos != str.npos ? str.data()+ pos : str.data()+ str.size(), num);
        result.emplace_back(num);
        str.remove_prefix(pos != str.npos ? pos + 1 : str.size());
    }
    return result;
}

void filter_by_one(const std::vector<std::vector<int>>& vec, int arg0){
    for(auto& v : vec | std::views::filter([&arg0](std::vector<int> num){

        return num[0] == arg0;}))
        std::cout << v[0] << "." << v[1] << "." << v[2] << "." << v[3] << std::endl;
}

void filter_by_two(const std::vector<std::vector<int>>& vec, int arg0, int arg1){
    for(auto& v : vec | std::views::filter([&arg0, &arg1](std::vector<int> num){

        return (num[0] == arg0 && num[1] == arg1);
    }))
        std::cout << v[0] << "." << v[1] << "." << v[2] << "." << v[3] << std::endl;
}

void filter_by_any(const std::vector<std::vector<int>>& vec, int arg){
    for(auto& v : vec | std::views::filter([&arg](std::vector<int> num){

        return (num[0] == arg || num[1] == arg || num[2] == arg || num[3] == arg);
    }))
        std::cout << v[0] << "." << v[1] << "." << v[2] << "." << v[3] << std::endl;
}

void filter(int arg) {
    filter_by_one(ip_pool, arg);
}

void filter(int arg0, int arg1) {
    filter_by_two(ip_pool, arg0, arg1);
}

void filter_any(int arg) {
    filter_by_any(ip_pool, arg);
}

void parse_string(const std::vector<std::string>& ip_strings) {
    for(auto& str : ip_strings)
    {
        std::vector<std::string_view> v = split_by(str, '\t');
        ip_pool.emplace_back(split(v.at(0), '.'));
    }

    std::sort(ip_pool.begin(), ip_pool.end(), [](std::vector<int>& lhs, std::vector<int>& rhs)
    {
        return std::tie(lhs[0],lhs[1],lhs[2],lhs[3]) > std::tie(rhs[0],rhs[1],rhs[2],rhs[3]);
    });

    print_all(ip_pool);
}

void print_all(const std::vector<std::vector<int>>& vec) {
    for(auto& v : vec)
        std::cout << v[0] << "." << v[1] << "." << v[2] << "." << v[3] << std::endl;
}
