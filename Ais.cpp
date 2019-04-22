#include "bulls.hpp"

    void Ai_Minimax::recount(int removed) {
        for (int i = 0; i < vec.size(); ++i) {
            --vec[i][compare(removed, i + g.start)];
        }
    }
    void Ai_Minimax::analyse (CompareObj c, int num) {
        for (auto i = possible.begin(); i != possible.end();){
            if (compare(num, *i) != c) {
                recount(*i);
                i = possible.erase(i);
            }
            else ++i;
        }
    }
    int Ai_Minimax::choose() {
        int mn = INT_MAX, ma;
        bool min_in_sure = false;
        for (int i = g.start; i < g.end; ++i) {
            if (!check(i)) continue;
            int mx = 0;
            //printf("i:%i | ", i);
            for (int j : possible) {
                int tmp = vec[i - g.start][compare(j, i)];
                //printf("%i(%i) ", j, tmp);
                if (tmp > mx) {
                    mx = tmp;
                }
            }
            //cout << endl;
            if (mx < mn) {
                mn = mx;
                ma = i;
                min_in_sure = false;
            }
            else if(mx == mn && !min_in_sure && possible.find(i) != possible.end()){
                mn = mx;
                ma = i; 
                min_in_sure = true;
            }
        }
        return ma;
        //auto it = possible.begin();
        //advance(it, rand() % possible.size());
        //return *it;
    }
    Ai_Minimax* Ai_Minimax::copy() {
        Ai_Minimax* tmp = new Ai_Minimax;
        *tmp = *this;
        return tmp;
    }
    Ai_Minimax::Ai_Minimax(int len) : g(len) {
        vec.resize(g.end - g.start);
        for (int i = g.start; i < g.end; ++i) {
            if (check(i)) possible.insert(i);
        }
        for (int i : possible) {
            for (int j : possible) {
                ++(vec[i - g.start][compare(i, j)]);
            }
        }
    }

    Stupid_Ai::Stupid_Ai(int len) : g(len) {
        for (int i = g.start; i < g.end; ++i) {
            if (check(i)) possible.insert(i);
        }
    }
    void Stupid_Ai::analyse (CompareObj c, int num) {
        for (auto i = possible.begin(); i != possible.end();){
            if (compare(num, *i) != c) {
                i = possible.erase(i);
            }
            else ++i;
        }
    }
    int Stupid_Ai::choose() {
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<> d(0, possible.size() - 1);
        auto it = possible.begin();
        advance(it, d(gen));
        return *it;
    }
    Stupid_Ai* Stupid_Ai::copy() {
        Stupid_Ai* tmp = new Stupid_Ai;
        *tmp = *this;
        return tmp;
    }
