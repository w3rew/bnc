#ifndef BENCH_HPP
#define BENCH_HPP
#include "game.hpp"
struct BenchObj :  T{
    BenchObj(const T& t) : T(t) {}
    vector<int> res(){return get<0>(*this);}
    int minimum(){return get<1>(*this);}
    int maximum(){return get<2>(*this);}
    double mean(){return get<3>(*this);}
};

class Benchmark {
    Gamer* g;
    Master m;
    int len;
    int game(bool out) ;
    public:
    Benchmark (Gamer* g, int len) {
        this -> len = len;
        this -> g = g;
    }
    BenchObj bench(int num, bool out) ;
};
ostream& operator<< (ostream& os, BenchObj o);
#endif
