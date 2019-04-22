#include "bulls.hpp"
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

    Master::Master(int len) : g(len){
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<> d(g.start, g.end - 1);
        do{
            number = d(gen);
        } while (!check(number));
        //printf("Number: %i\n", number);
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
