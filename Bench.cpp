#include "Bench.hpp"

int Benchmark::game(bool out) {
    m = Master(len);
    while (true) {
        auto move = g -> mkmove();
        auto ans = m.try_number(move.first);
        if (out) printf("%i : %i\nB C\n%i %i\n", g -> get_counter(), move.first, ans.bulls(), ans.cows());
        if (move.second || ans.bulls() == len) {
            if (out) printf("Game finished, %i moves\n", g -> get_counter());
            return g -> get_counter();
        }
        g -> getmove(ans);
    }
}
BenchObj Benchmark::bench(int num, bool out) {
    int sum = 0;
    int mn = INT_MAX, mx = 0;
    vector<int> res(num);
    for (int i = 0; i < num; ++i) {
        int tmp = game(out);
        sum += tmp;
        res[i] = tmp;
        mn = min(mn, tmp);
        mx = max(mx, tmp);
        if ( i!= num - 1) g -> new_game();
    }
    return make_tuple(res, mn, mx, (double) sum / num);
}
ostream& operator<< (ostream& os, BenchObj o) {
    os << "Results: ";
    for (int i : o.res()) {
        os << i << ' ';
    }
    os << endl << "Minimum : " << o.minimum() << endl <<  "Maximum: " << o.maximum() << endl <<
        "Mean: " << o.mean();
    return os;
}
