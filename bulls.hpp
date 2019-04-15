#include<vector>
#include<utility>
#include<tuple>
#include<map>
#include<iostream>
#include<set>
#include<algorithm>
#include<random>
#include<climits>
#include<cassert>

#define all(a) (a).begin(), (a).end()
using namespace std;
typedef pair<int, int> P;
typedef tuple<vector<int>, int, int, double> T;
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
typedef map<CompareObj, int> cmap;
/*ostream& operator<<(ostream& os, const CompareObj& o) {
    return (os << "Bulls: " << o.bulls() << endl << "Cows: " << o.cows());
}*/
class Game {
    private:
    static vector<int> digits(int num) ;
    protected:
    int start; //[start, end)
    int end;
    Game(int len);
    //friend ostream& operator<<(ostream& os, const CompareObj& o);
    static CompareObj compare(int a, int b);
    static bool check(int i);
};

class Master : private Game {
    int number;
    public:
    Master() : Game(-1) {}
    Master(int len) ;
    CompareObj try_number(int c) {
        return compare(number, c);
    }
};

class Ai {
    public:
        virtual void analyse(CompareObj, int) = 0;
        virtual int choose() = 0;
        virtual int size() = 0;
        virtual Ai* copy() = 0;
};

class Gamer{
    public:
        virtual int get_counter() = 0;
        virtual pair<int, bool> mkmove() = 0;
        virtual void getmove(CompareObj) = 0;
        virtual void new_game() = 0;
};

class Ai_Minimax : public Game, public Ai {
    protected:
    set<int> possible;
    vector<cmap> vec;
    virtual void recount(int removed);
    public:
    int size() {return possible.size();}
    void analyse (CompareObj c, int num);
    virtual int choose() ;
    virtual Ai_Minimax* copy() ;
    Ai_Minimax() : Game(-1) {}
    Ai_Minimax(int len);
};
class Stupid_Ai : public Ai, public Game {
    set<int> possible;
    public:
    Stupid_Ai () : Game(-1) {}
    Stupid_Ai(int len);
    void analyse (CompareObj c, int num);
    int choose() ;
    Stupid_Ai* copy();
    int size() {return possible.size();}
};

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
    pair<int, bool>  mkmove();
    void getmove(CompareObj c);
    void new_game();
};


class Cmd { //переписать с интерфейсом
    Gamer* g;
    public:
    Cmd(Gamer* t) {
        g = t;
    }
    void game();
};
