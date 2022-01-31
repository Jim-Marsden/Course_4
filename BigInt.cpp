//
// Created by snizzfox on 1/29/22.
//

#include <algorithm>
#include <functional>
#include "BigInt.h"
using Project1::BigInt;


Project1::BigInt::BigInt(long long int)
{

}

Project1::BigInt::BigInt(const std::string&)
{

}

const BigInt& Project1::BigInt::operator=(const BigInt&)
{
    return *this;
}

const BigInt& Project1::BigInt::operator+=(const BigInt&)
{
    return *this;
}

const BigInt& Project1::BigInt::operator-=(const BigInt&)
{
    return *this;
}

std::string
Project1::adder(std::string addend1, std::string addend2)
{
    std::string rrv;
    bool over_flow{false};

    std::size_t larger_size{0}, smaller_size{0};
    if(addend1.size() < addend2.size()){larger_size = addend2.size(); smaller_size = addend1.size();}
    else if(addend2.size() < addend1.size()){larger_size = addend1.size(); smaller_size = addend2.size();}
    addend2 += std::string(larger_size - smaller_size + 1,  '0');
    addend1 += std::string(larger_size - smaller_size + 1, '0') ;
    auto current_it1 = addend1.begin() ;
    auto current_it2 = addend2.begin() ;



    while(current_it1 != addend1.end() && current_it2 != addend2.end()) {

        auto r =  (*current_it1-'0')+(*current_it2-'0');
        if(over_flow){
            over_flow = false;
            r++;
        }
        if(r >= 10){
            r -= 10;
            over_flow = true;
        }
        rrv = std::to_string(r) + rrv;
        ++current_it1;
        ++current_it2;
    }
    if(rrv.front() == '0'){rrv.erase( std::remove(rrv.begin(), rrv.begin() + 1, '0'), rrv.begin() + 1);}
//    if(current_it1 != addend1.rend()) { rrv += std::string(current_it1, addend1.rend());}
//    if(current_it2 != addend2.rend()) { rrv += std::string(current_it2, addend2.rend());}
//    std::reverse(rrv.begin(), rrv.end());
    return rrv;
}