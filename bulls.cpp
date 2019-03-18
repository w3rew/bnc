#include <bits/stdc++.h>
#define all(a) (a).begin(), (a).end()
using namespace std;
typedef pair<int, int> P;
struct CompareObj : public P {
    CompareObj(const P &p) : P(p) {}
    CompareObj(int a, int b) : P(a, b) {}
    int bulls() const {
        return this -> first;
   }
    int cows() const {
        return this -> second;
    }
};
class Game {
    private:
    static vector<int> digits(int num) {
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
    protected:
    int start; //[start, end)
    int end;
    Game(int len) {
        start = pow(10, len - 1);
        end = pow(10, len);
    }
    friend ostream& operator<<(ostream& os, const CompareObj& o);
    static CompareObj compare(int a, int b) {
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
    bool check(int i) {
        auto tmp = digits(i);
        sort(all(tmp));
        return unique(all(tmp)) == tmp.end();
        }
};
typedef map<CompareObj, int> cmap;
ostream& operator<<(ostream& os, const CompareObj& o) {
    return (os << "Bulls: " << o.bulls() << endl << "Cows: " << o.cows());
}
class Ai {
    public:
        virtual void analyse(CompareObj, int) = 0;
        virtual int choose() = 0;
        virtual int size() = 0;
        virtual Ai* copy() = 0;
};
class Ai_Minimax : public Game, public Ai {
    protected:
    set<int> possible;
    vector<cmap> vec;
    virtual void recount(int removed) {
        for (int i = 0; i < vec.size(); ++i) {
            --vec[i][compare(removed, i + start)];
        }
    }
    public:
    int size() {return possible.size();}
    void analyse (CompareObj c, int num) {
        for (auto i = possible.begin(); i != possible.end();){
            if (compare(num, *i) != c) {
                recount(*i);
                i = possible.erase(i);
            }
            else ++i;
        }
    }
    virtual int choose() {
        int mn = INT_MAX, ma;
        bool min_in_sure = false;
        for (int i = start; i < end; ++i) {
            if (!check(i)) continue;
            int mx = 0;
            //printf("i:%i | ", i);
            for (int j : possible) {
                int tmp = vec[i - start][compare(j, i)];
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
    virtual Ai_Minimax* copy() {
        Ai_Minimax* tmp = new Ai_Minimax;
        *tmp = *this;
        return tmp;
    }
    Ai_Minimax() : Game(-1) {}
    Ai_Minimax(int len) : Game(len) {
        vec.resize(end - start);
        for (int i = start; i < end; ++i) {
            if (check(i)) possible.insert(i);
        }
        for (int i : possible) {
            for (int j : possible) {
                ++(vec[i - start][compare(i, j)]);
            }
        }
    }
};
class Stupid_Ai : public Ai, public Game {
    set<int> possible;
    public:
    Stupid_Ai () : Game(-1) {}
    Stupid_Ai(int len) : Game(len) {
        for (int i = start; i < end; ++i) {
            if (check(i)) possible.insert(i);
        }
    }
    void analyse (CompareObj c, int num) {
        for (auto i = possible.begin(); i != possible.end();){
            if (compare(num, *i) != c) {
                i = possible.erase(i);
            }
            else ++i;
        }
    }
    int choose() {
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<> d(0, possible.size() - 1);
        auto it = possible.begin();
        advance(it, d(gen));
        return *it;
    }
    Stupid_Ai* copy() {
        Stupid_Ai* tmp = new Stupid_Ai;
        *tmp = *this;
        return tmp;
    }
    int size() {return possible.size();}
};

class Gamer{
    public:
        virtual int get_counter() = 0;
        virtual pair<int, bool> mkmove() = 0;
        virtual void getmove(CompareObj) = 0;
        virtual void new_game() = 0;
};
class Ai_Gamer : public Gamer {
    int lastmove;
    int counter = 0;
    bool wonflag;
    Ai* g;
    Ai* tmp = nullptr;
    public:
    ~Ai_Gamer() {
        delete tmp;
    }
    int get_counter() {return counter;}
    Ai_Gamer(Ai* g) {
        this -> g = g;
        new_game();
    }
    pair<int, bool>  mkmove() {
        ++counter;
        lastmove = tmp -> choose();
        return make_pair(lastmove, wonflag);
    }
    void getmove(CompareObj c) {
        tmp -> analyse(c, lastmove);
        if (tmp -> size() == 1) wonflag = true;
    }
    void new_game() {
        delete tmp; //вроде бы это норма
        tmp = g -> copy();
        tmp -> choose();
        wonflag = false;
        counter = 0;
    }
};
class Master : private Game {
    int number;
    public:
    Master() : Game(-1) {}
    Master(int len) : Game(len){
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<> d(start, end - 1);
        do{
            number = d(gen);
        } while (!check(number));
        //printf("Number: %i\n", number);
    }
    CompareObj try_number(int c) {
        return compare(number, c);
    }
};
typedef tuple<vector<int>, int, int, double> T;
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
    int game(bool out) {
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
    public:
    Benchmark (Gamer* g, int len) {
        this -> len = len;
        this -> g = g;
    }
    BenchObj bench(int num, bool out) {
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
};
ostream& operator<< (ostream& os, BenchObj o) {
    os << "Results: ";
    for (int i : o.res()) {
            os << i << ' ';
    }
    os << endl << "Minimum : " << o.minimum() << endl <<  "Maximum: " << o.maximum() << endl <<
            "Mean: " << o.mean();
    return os;
}


class Cmd { //переписать с интерфейсом
    Gamer* g;
    public:
    Cmd(Gamer* t) {
        g = t;
    }
    void game() {
        int counter = 1;
        while(true) {
            cout << "Choosing" << endl;
            auto move = g -> mkmove();
            cout << counter << " : " << move.first << endl;
            if (move.second) break;
            cout << "B C" << endl;
            int b, c;
            cin >> b >> c;
            cout << "Analysing" << endl;
            g -> getmove(make_pair(b, c));
            ++counter;
        }
    }
};
int main() {
    //Ai_Gamer a(new Ai(4));
    auto S = new Ai_Gamer(new Ai_Minimax(4));
    auto c = Cmd(S);
    c.game();
}
