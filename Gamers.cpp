#include "Ai.hpp"
    pair<int, bool>  Ai_Gamer::mkmove() {
        ++counter;
        lastmove = tmp -> choose();
        return make_pair(lastmove, wonflag);
    }
    void Ai_Gamer::getmove(CompareObj c) {
        tmp -> analyse(c, lastmove);
        if (tmp -> size() == 1) wonflag = true;
    }
    void Ai_Gamer::new_game() {
        delete tmp; //вроде бы это норма
        tmp = g -> copy();
        tmp -> choose();
        wonflag = false;
        counter = 0;
    }


    void Cmd::game() {
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
