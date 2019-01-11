/*
* Chess.h
* USAGE:
*	* Defining chess state
*	* Defining chess movement
*	* Defining chess board
*/
#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <cmath>
#include <vector>

#define LEVEL 3

using namespace std;

class chessBoard;

// Meta chess class
class chess{
public:
    chess(){
    	this->alive = true;
    }
	chess(int level_){
		this->level = level_;
		this->alive = true;
		if(level_ != 0){
            this->id = chess::ID++;
		}else {
			this->id = -1;
		}
	}
	int getLevel(){
		return this->level;
	}
	bool isAlive(){ return alive; }
	void setRowCol(int row_, int col_){
		row = row_;
		col = col_;
	}

    int level;
    bool alive;
    int row, col;
    int id;

    static int ID;

};

// Move info
struct moveInfo{
	int srcID, dstID;
	int srcRow, srcCol;
	int dstRow, dstCol;
	chess dstTemp;
};

// General(黑方将，红方帅) chess class
class general : public chess{
public:
	// Construct function, with playerSide(MIN) and AISide(MAX) judge 
	general(bool playerSide):chess(playerSide ? -7 : 7){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
	~general(){}
};

// Guard(黑方士，红方仕) chess class
class guard : public chess{
public:
	guard(bool playerSide):chess(playerSide ? -6 : 6){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Elephant(黑方象，红方相) chess class
class elephant : public chess{
public:
	elephant(bool playerSide):chess(playerSide ? -5 : 5){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Horse(黑方马，红方马) chess class
class horse : public chess{
public:
	horse(bool playerSide):chess(playerSide ? -4 : 4){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Rook(黑方车，红方车) chess class
class rook : public chess{
public:
	rook(bool playerSide):chess(playerSide ? -3 : 3){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Cannon(黑方炮，红方炮) chess class
class cannon : public chess{
public:
	cannon(bool playerSide):chess(playerSide ? -2 : 2){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Solider(黑方卒，红方兵) chess class
class solider : public chess{
public:
	solider(bool playerSide):chess(playerSide ? -1 : 1){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos);
};

// Empty-Chess class(空位)
class empty : public chess{
public:
	empty(bool playerSide):chess(0){}
    bool judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){}
};

// ChessBoard definition
class chessBoard{
public:
	chessBoard();
	void initBoard();
	chess getChess(pair<int, int> pos);
	int getLevel(pair<int, int> pos);
    bool playerMove(pair<int, int> srcPos, pair<int, int>dstPos);
    bool eatBlackChess(int x, int y);
	// AI Methods
	int AlphaBetaJudge(int level, int score);
	int EstimateValue();
    moveInfo* aiMove();
	// AI moving judge Methods
	moveInfo* getBestMove();
	void getAllPossibleMove(vector<moveInfo*>& steps);
	int getMaxScore(int level, int score);
    void saveMove(chess& src, chess& target, int row, int col, vector<moveInfo*>& steps);
	// Fake moving and unmoving
	void doMove(moveInfo* info);
	void undoMove(moveInfo* info);

    static bool gameOver;

private:
    vector<vector<chess> > board;
    vector<chess> chessList;
    bool playerSide = true;

};

#endif
