#include "bulls.hpp"
int main() {
    //Ai_Gamer a(new Ai(4));
    auto S = new Ai_Gamer(new Ai_Minimax(4));
    auto c = Cmd(S);
    c.game();
}
