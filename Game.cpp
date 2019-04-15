#include "bulls.hpp"

    vector<int> Game::digits(int num) {
        vector <int> res;
        res.reserve((int) (log10(num) + 1));
        while (num > 0) {
            res.push_back(num % 10);
            num -= num % 10;
            num /= 10;
        }
        //reverse(all(res)); не влияет на сравнение
        return res;
    }
    Game::Game(int len) {
        start = pow(10, len - 1);
        end = pow(10, len);
    }

    CompareObj Game::compare(int a, int b) {
        vector<int> da = digits(a), db = digits(b);
        assert(da.size() == db.size());
        vector<bool> first_contains_cows(10);
        vector<bool> second_contains_cows(10);
        int bulls = 0, cows = 0;
        for(int i = 0; i < da.size(); ++i) {
            if (da[i] == db[i]) ++bulls;
            else{
                first_contains_cows[da[i]] = true;
                second_contains_cows[db[i]] = true;
            }
        }
        for (int i = 0; i < 10; ++i) if (first_contains_cows[i] == true && second_contains_cows[i]==true) cows++;
        /*
        sort(all(da));
        sort(all(db));
        vector<int> tmp(da.size());
        cows = (set_intersection(all(da), all(db), tmp.begin())
                - tmp.begin()) - bulls;
                */
        return CompareObj(bulls, cows);
    }
    bool Game::check(int i) {
        auto tmp = digits(i);
        sort(all(tmp));
        return unique(all(tmp)) == tmp.end();
        }
