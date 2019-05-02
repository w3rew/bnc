#ifndef AI_HPP
#define AI_HPP
#include "game.hpp"
class Ai {
    public:
        virtual void analyse(CompareObj, int) = 0;
        virtual int choose() = 0;
        virtual int size() = 0;
        virtual Ai* copy() = 0;
};

class Ai_Minimax :public Ai {
    protected:
        Game g;
        set<int> possible;
        vector<cmap> vec;
        virtual void recount(int removed);
    public:
        int size() {return possible.size();}
        void analyse (CompareObj c, int num);
        virtual int choose() ;
        virtual Ai_Minimax* copy() ;
        Ai_Minimax() : g(-1) {}
        Ai_Minimax(int len);
};
class Stupid_Ai : public Ai{
    set<int> possible;
    protected:
    Game g;
    public:
    Stupid_Ai () : g(-1) {}
    Stupid_Ai(int len);
    void analyse (CompareObj c, int num);
    int choose() ;
    Stupid_Ai* copy();
    int size() {return possible.size();}
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
    pair<int, bool>  mkmove();
    void getmove(CompareObj c);
    void new_game();
};
#endif
