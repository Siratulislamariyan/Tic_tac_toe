#include <emscripten/emscripten.h>

static int board[9]; // 0 empty, 1 X (player), 2 O (computer)

static int check_three(int a,int b,int c) {
    if (board[a]==board[b] && board[b]==board[c] && board[a]!=0) return board[a];
    return 0;
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
void reset_board() {
    for (int i=0;i<9;i++) board[i]=0;
}

EMSCRIPTEN_KEEPALIVE
int get_cell(int idx) {
    if (idx<0 || idx>8) return -1;
    return board[idx];
}

EMSCRIPTEN_KEEPALIVE
int check_winner() {
    int w;
    w = check_three(0,1,2); if (w) return w;
    w = check_three(3,4,5); if (w) return w;
    w = check_three(6,7,8); if (w) return w;
    w = check_three(0,3,6); if (w) return w;
    w = check_three(1,4,7); if (w) return w;
    w = check_three(2,5,8); if (w) return w;
    w = check_three(0,4,8); if (w) return w;
    w = check_three(2,4,6); if (w) return w;
    for (int i=0;i<9;i++) if (board[i]==0) return 0;
    return 3; // draw
}

EMSCRIPTEN_KEEPALIVE
int player_move(int idx) {
    if (idx<0 || idx>8) return -1;
    if (board[idx]!=0) return -1;
    board[idx]=1;
    return check_winner();
}

static int find_winning_move(int player) {
    for (int i=0;i<9;i++) if (board[i]==0) {
        board[i]=player;
        int w = check_winner();
        board[i]=0;
        if (w==player) return i;
    }
    return -1;
}

EMSCRIPTEN_KEEPALIVE
int computer_move() {
    if (check_winner()) return -1;
    // win if possible
    int mv = find_winning_move(2);
    if (mv!=-1) { board[mv]=2; return check_winner(); }
    // block player
    mv = find_winning_move(1);
    if (mv!=-1) { board[mv]=2; return check_winner(); }
    // center
    if (board[4]==0) { board[4]=2; return check_winner(); }
    // corners
    int corners[4] = {0,2,6,8};
    for (int i=0;i<4;i++) if (board[corners[i]]==0) { board[corners[i]]=2; return check_winner(); }
    // first empty
    for (int i=0;i<9;i++) if (board[i]==0) { board[i]=2; return check_winner(); }
    return check_winner();
}

} // extern "C"
