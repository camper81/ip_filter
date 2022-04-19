#include <cassert>
#include <iostream>

#include <string>
#include <algorithm>

#include <charconv>
#include <ranges>

#include "ip_filter.h"

using IpPoolType = std::vector<std::array<int,4>>;
using IpParts = std::array<int,4>;

// pool to storage parts of ip
IpPoolType ip_pool;

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

IpParts split(std::string_view str, char d)
{
    std::array<int,4> result;
    int num, sp = 0;
    while (!str.empty()) {
        size_t pos = str.find(d);
        std::from_chars(str.data(), pos != str.npos ? str.data()+ pos : str.data()+ str.size(), num);
        result[sp++] = num;
        str.remove_prefix(pos != str.npos ? pos + 1 : str.size());
    }
    return result;
}

std::ostream& print(std::ostream& os, const IpParts& vec) {
    assert(vec.size() == 4);

    os << vec[0] << "." << vec[1] << "." << vec[2] << "." << vec[3];
    return os;
}

void print_pool() {
    for(auto& v : ip_pool)
        print(std::cout, v) << std::endl;
}

void filter_by_one(const IpPoolType& vec, int arg0){
    for(auto& v : vec | std::views::filter([&arg0](IpParts num){
        return num[0] == arg0;}))
        print(std::cout, v) << std::endl;
}

void filter_by_two(const IpPoolType& vec, int arg0, int arg1){
    for(auto& v : vec | std::views::filter([&arg0, &arg1](IpParts num){

        return (num[0] == arg0 && num[1] == arg1);
    }))
        print(std::cout, v) << std::endl;
}

void filter_by_any(const IpPoolType& vec, int arg){
    for(auto& v : vec | std::views::filter([&arg](IpParts num){

        return (num[0] == arg || num[1] == arg || num[2] == arg || num[3] == arg);
    }))
        print(std::cout, v) << std::endl;
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

void sort_pool() {
    std::sort(ip_pool.begin(), ip_pool.end(), [](IpParts& lhs, IpParts& rhs)
    {
        assert((lhs.size() & rhs.size()) == 4);

        return std::tie(lhs[0],lhs[1],lhs[2],lhs[3]) > std::tie(rhs[0],rhs[1],rhs[2],rhs[3]);
    });
}

void update_pool(const std::vector<std::string>& ip_strings) {
    for(auto& str : ip_strings)
    {
        std::vector<std::string_view> v = split_by(str, '\t');
        ip_pool.emplace_back(split(v.at(0), '.'));
    }
}
