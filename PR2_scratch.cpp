//
// Created by james on 3/5/2022.
//

#include "dlist.h"

#include <iostream>
#include <numeric>





void reverseString(std::string &s) {
    reverse(s.begin(), s.end());
}

void main1(){
    using Project2::dlist;
    const short EXPECTED_DATA[] = {1, 3};
    short data[] = {1, 2, 3};
    dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

    dlist<short>::iterator i = ++ls.begin();

//    for(auto e : ls){
//        std::cout << e << '\n';
//    }
    i = ls.erase(i);

//    for(auto e : ls){
//        std::cout << e << '\n';
//    }
    std::cout << ls.size() << " == 2\n";

    for(auto e : ls){
        std::cout << e << '\n';
    }
    auto r = (*i = 3);
    for(auto e : ls){
        std::cout << e << '\n';
    }
    std::cout << "r: " << r << '\n';
    std::cout << "Equals: " << equal(ls.begin(), ls.end(), EXPECTED_DATA) << '\n';

    for(auto e : ls){
        std::cout << e << '\n';
    }
    //std::for_each(ls.begin(), ls.end(), [](auto const & e){std::cout << e << '\n';});
    std::cout << std::endl;

    std::cout << "size " <<  ls.size() << '\n';
}



auto main4(){
    using Project2::dlist;
    short data[] = {1, 2, 3};


    dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

    auto end_v = ls.end();
    auto r = *(end_v--);

    std::cout << r << '\n';
}

auto main3(){
    using Project2::dlist;
    dlist<short> ls1;
    std::cout << ls1.size() << '\n';
    ls1.push_back(1);
    std::cout << ls1.size() << '\n';

    ls1.push_back(2);
    std::cout << ls1.size() << '\n';

    ls1.push_back(3);
    std::cout << ls1.size() << '\n';

    dlist<short> ls2;
    std::cout << ls2.size() << '\n';

    ls2 = ls1;
    std::cout << ls2.size() << '\n';

//
//
//    CHECK(ls2.size() == 3);
//    CHECK(ls2.front() == 1);
//    ls2.pop_front();
//    CHECK(ls2.front() == 2);
//    ls2.pop_front();
//    CHECK(ls2.front() == 3);
}


void main66(){

    using Project2::dlist;

    dlist<int> fuck;
    fuck.push_back(1);
    fuck.push_back(2);
    fuck.push_back(3);
    fuck.push_back(4);



    int data[] = {1, 2 ,3 ,4 ,5, 6, 7 ,8 ,9, 10};
    dlist<int> dl(data, data + sizeof(data) / sizeof(*data));


    std::cout << std::accumulate(dl.begin(), dl.end(), 0) << '\n';

    std::string inputData[] = {"the", "quick", "brown", "fox"};
    dlist<std::string> dlInput(inputData, inputData + 4);
    std::string resultData[] = {"eht", "kciuq", "nworb", "xof"};
    dlist<std::string> dlResult(resultData, resultData + 4);

    for_each(dlInput.begin(), dlInput.end(), reverseString);

    std::cout << "asdfasdfasdf: "  << (dlResult == dlInput) << '\n';


//    for(auto & e: dlInput){
//        std::cout << e << '\n';
//    }
    dlist<int> dl2;
    dlist<int>::iterator i;

    i = dl2.insert(dl.begin(), 5);
    i = dl2.insert(i, 4);
    i = dl2.insert(i, 3);
    i = dl2.insert(i, 2);
    i = dl2.insert(i, 1);
    dl2.insert(dl.end(), 6);
    dl2.insert(dl.end(), 7);
    dl2.insert(dl.end(), 8);
    dl2.insert(dl.end(), 9);
    dl2.insert(dl.end(), 10);


    for(auto & e: dl2){
        std::cout << e << '\n';
    }
    std::cout << "************************************************************\n";
    std::cout << std::accumulate(dl2.begin(), dl2.end(), 0) << '\n';

}

void erase_tests(){
    using Project2::dlist;
    const short EXPECTED_DATA[] = { 1, 3 };
    short data[] = { 1, 2, 3 };
    dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

    dlist<short>::iterator i = ++ls.begin();
    i = ls.erase(i);

    for(auto const & e : ls){
        std::cout << e << ", ";
    }
    std::cout << '\n';

    std::cout << (ls.size() == 2) << '\n';
    std::cout << (*i = 3) << '\n';

    for(auto const & e : ls){
        std::cout << e << ", ";
    }
    std::cout << '\n';

    std::cout << (equal(ls.begin(), ls.end(), EXPECTED_DATA)) << '\n';
}

int main(){
    erase_tests();
}