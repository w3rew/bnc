#ifndef BULLS_HPP
#define BULLS_HPP
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
vector<int> digits(int num) ;
CompareObj compare(int a, int b);
bool check(int i);
/*ostream& operator<<(ostream& os, const CompareObj& o) {
  return (os << "Bulls: " << o.bulls() << endl << "Cows: " << o.cows());
  }*/
class Game {
    public:
        int start; //[start, end)
        int end;
        Game(int len);
        //friend ostream& operator<<(ostream& os, const CompareObj& o);
};

class Gamer{
    public:
        virtual int get_counter() = 0;
        virtual pair<int, bool> mkmove() = 0;
        virtual void getmove(CompareObj) = 0;
        virtual void new_game() = 0;
};

class Master {
    int number;
    Game g;
    public:
    Master() : g(-1) {}
    Master(int len) ;
    CompareObj try_number(int c) {
        return compare(number, c);
    }
};

class Cmd { //переписать с интерфейсом
    Gamer* g;
    public:
    Cmd(Gamer* t) {
        g = t;
    }
    void game();
};
#endif
