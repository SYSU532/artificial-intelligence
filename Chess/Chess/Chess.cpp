#include "Chess.h"

int chess::ID = 0;
bool chessBoard::gameOver = false;

bool general::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
    int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// General can only move one step a time
	bool stepFlag = (distX * distX + distY * distY == 1);
	// General move border judgement
	bool borderFlag = (dstPos.first % 7 >= 0 && dstPos.first % 7 <= 2) 
                        && (dstPos.second >= 3 && dstPos.second <= 5);

	return moveFlag && stepFlag && borderFlag;
}

bool guard::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Guard can only move one step according the diagonal one time
	bool stepFlag = (distX * distX + distY * distY == 2);
	// Guard move border judgement
	bool borderFlag = (dstPos.first % 7 >= 0 && dstPos.first % 7 <= 2) 
                        && (dstPos.second >= 3 && dstPos.second <= 5);

	return moveFlag && stepFlag && borderFlag;
}

bool elephant::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Elephant can only move across the 田, forwarding or backwarding
	bool stepFlag = (distX * distX + distY * distY == 8);
	// Elephant move border judgement 1: Don't across to enemy's half-part
	bool borderFlag1 = (srcPos.first / 5 == dstPos.first / 5);
	// Elephant move border judgement 2: Cannot across 田 when a chess is in the center
	bool borderFlag2 = (cb.getLevel(make_pair(srcPos.first + distX/2, srcPos.second + distY / 2)) == 0);
	return moveFlag && stepFlag && borderFlag1 && borderFlag2;
}

bool horse::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Horse can only move across the 日, forwarding or backwarding
	bool stepFlag = (distX * distX + distY * distY == 5);
	// Horse move border judgement: Cannot across 日 when a chess is in your front
	bool borderFlag = (cb.getLevel(make_pair(srcPos.first + distX/2, srcPos.second + distY / 2)) == 0);
	return moveFlag && stepFlag && borderFlag;
}

bool rook::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Rook must walk in a line, keeping x or y no change, but no both
    bool walkFlag = (distX == 0 && distY != 0)|| (distY == 0 && distX != 0);;
	// Rook move border judge ment : Cannot walk to destination if other chess stops you
	if(moveFlag && walkFlag){
		if(distX == 0){ // Walk in y-dir
			int sign = distY > 0 ? 1 : -1;
			for(int i=1; i<abs(distY); i++)
				if(cb.getLevel(make_pair(srcPos.first, srcPos.second + sign * i)) != 0)
					return false;
		}else { // Walk in x-dir
			int sign = distX > 0 ? 1 : -1;
			for(int i=1; i<abs(distX); i++)
				if(cb.getLevel(make_pair(srcPos.first + sign * i, srcPos.second)) != 0)
					return false;
		}
		return true;
	}
	return false;
}

bool cannon::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Cannon must walk in a line, keeping x or y no change, but no both
    bool walkFlag = (distX == 0 && distY != 0)||(distY == 0 && distX != 0);
    // Cannon move judgement: Walk in a line like rook, but can also across one chess jumping
    int midChessNum = 0;
	if(moveFlag && walkFlag){
		if(distX == 0){ // Walk in y-dir
			int sign = distY > 0 ? 1 : -1;
			for(int i=1; i<abs(distY); i++)
				if(cb.getLevel(make_pair(srcPos.first, srcPos.second + sign * i)) != 0)
					midChessNum++;
		}else {// Walk in x-dir
			int sign = distX > 0 ? 1 : -1;
			for(int i=1; i<abs(distX); i++)
				if(cb.getLevel(make_pair(srcPos.first + sign * i, srcPos.second)) != 0)
					midChessNum++;
		}
    }else {
        return false;
    }
	// Check for dest position is empty or not
	if(dstLevel == 0){
		return (midChessNum == 0);
	} else {
		return (midChessNum == 1);
	}
}

bool solider::judge_move(chessBoard& cb, pair<int, int> srcPos, pair<int, int> dstPos){
	int srcLevel = cb.getLevel(srcPos), dstLevel = cb.getLevel(dstPos);
	int distX = dstPos.first - srcPos.first, distY = dstPos.second - srcPos.second;
	// Empty Position jump or eat enemy's chess jump judgement
	bool moveFlag = (srcLevel * dstLevel <= 0);
	// Solider can only move forwarding, or move in y-dir
	bool forwardFlag = (srcLevel * distX >= 0);
	// 1. When no across the river, solider can only move forward
	// 2. When across the river, solider can move forward or walk in y-dir
	if(moveFlag && forwardFlag){
		if(abs(distX) == 1 && distY == 0){ // Walk forward, always allow
			return true;
		} else if(abs(distY) == 1 && distX == 0){ // Walk in y-dir, when across the river
			return ((srcPos.first / 5 == 0 && srcLevel < 0) || (srcPos.second / 5 == 0 && srcLevel > 0));
		}
	}
    return false;
}

// Chess board construct
chessBoard::chessBoard(){
	for(int i=0; i<10; i++){
        vector<chess> temp;
		for(int j=0; j<9; j++)
            temp.push_back(empty(0));
        board.push_back(temp);
	}
}

// Init and put all chess on board
void chessBoard::initBoard(){
	// AI side
	board[0][0] = rook(0);		board[0][1] = horse(0);
	board[0][2] = elephant(0);	board[0][3] = guard(0);
	board[0][4] = general(0);	board[0][5] = guard(0);
	board[0][6] = elephant(0);	board[0][7] = horse(0);
	board[0][8] = rook(0);		board[2][1] = cannon(0);
	board[2][7] = cannon(0);	board[3][0] = solider(0);
	board[3][2] = solider(0);	board[3][4] = solider(0);
	board[3][6] = solider(0);	board[3][8] = solider(0);
	// Player Side
	board[9][0] = rook(1);		board[9][1] = horse(1);
	board[9][2] = elephant(1);	board[9][3] = guard(1);
	board[9][4] = general(1);	board[9][5] = guard(1);
	board[9][6] = elephant(1);	board[9][7] = horse(1);
	board[9][8] = rook(1);		board[7][1] = cannon(1);
	board[7][7] = cannon(1);	board[6][0] = solider(1);
	board[6][2] = solider(1);	board[6][4] = solider(1);
	board[6][6] = solider(1);	board[6][8] = solider(1);
	// Push into vector list
	for(int i=0; i<=8; i++){
		board[0][i].setRowCol(0, i);
		chessList.push_back(board[0][i]);
	}
	board[2][1].setRowCol(2, 1);  board[2][7].setRowCol(2, 7);
	chessList.push_back(board[2][1]);  chessList.push_back(board[2][7]);
	for(int i=0; i<=8; i+=2){
		board[3][i].setRowCol(3, i);
		chessList.push_back(board[3][i]);
	}
	for(int i=0; i<=8; i++){
        board[9][i].setRowCol(9, i);
		chessList.push_back(board[9][i]);
	}
    board[7][1].setRowCol(7, 1);  board[7][7].setRowCol(7, 7);
	chessList.push_back(board[7][1]);  chessList.push_back(board[7][7]);
	for(int i=0; i<=8; i+=2){
        board[6][i].setRowCol(6, i);
		chessList.push_back(board[6][i]);
	}
}

chess chessBoard::getChess(pair<int, int> pos){
    return board[pos.first][pos.second];
}

int chessBoard::getLevel(pair<int, int> pos){
    return (getChess(pos).getLevel());
}

bool chessBoard::playerMove(pair<int, int> srcPos, pair<int, int> dstPos){
    int originX = srcPos.first,  originY = srcPos.second;
    int dstX = dstPos.first,  dstY = dstPos.second;
    chess tmp = board[originX][originY];
    int id = tmp.id;
    board[originX][originY] = empty(0);
    board[dstX][dstY] = tmp;
    chessList[id].setRowCol(dstX, dstY);

    playerSide = !playerSide;

    return true;
}

bool chessBoard::eatBlackChess(int x, int y){
    int level = board[x][y].getLevel(), id = board[x][y].id;
    board[x][y] = empty(0);
    chessList[id].alive = false;
    if(level == 7){
        return true;
    }
    return false;
}

// AI Methods
int chessBoard::getMaxScore(int level, int score){
	if(level == 0)
		return EstimateValue();

	vector<moveInfo*> steps;
	getAllPossibleMove(steps);
	// Max-Min
	int initScore = -1000000;

    while(steps.size() > 0){
        moveInfo* temp = steps.back();
        steps.pop_back();

        doMove(temp);
        int minScore = AlphaBetaJudge(level-1, initScore);
        undoMove(temp);
        delete temp;

        if(minScore >= score){
            while(steps.size() > 0){
                moveInfo* step = steps.back();
                steps.pop_back();
                delete step;
            }
            return minScore;
        }
        if(minScore > initScore){
            initScore = minScore;
        }
    }
	return initScore;
}

int chessBoard::AlphaBetaJudge(int level, int score){
	if(level == 0)
		return EstimateValue();
	vector<moveInfo*> steps;
	getAllPossibleMove(steps);
	// Make Max
	int alpha = 1000000;
    while(steps.size() > 0){
        moveInfo* temp = steps.back();
        steps.pop_back();

        doMove(temp);
        int beta = getMaxScore(level-1, alpha);
        undoMove(temp);
        delete temp;
        // Alpha-Beta Cut
        if(beta <= score){
            while(steps.size() > 0){
                moveInfo* step = steps.back();
                steps.pop_back();
                delete step;
            }
            return beta;
        }
        if(beta < alpha){
            alpha = beta;
        }
    }
	return alpha;
}

// Simple chess values adding to estimate
int chessBoard::EstimateValue(){
	int redScore = 0, blackScore = 0;
    int chessScore[7] = {15, 80, 100, 60, 20, 20, 1000};
	// Calculate Black values
	for(int i=0; i<16; i++){
		if(!chessList[i].isAlive()) continue;
        blackScore += chessScore[chessList[i].level-1];
	}
	// Calculate Red values
	for(int i=16; i<32; i++){
		if(!chessList[i].isAlive()) continue;
        redScore += chessScore[-chessList[i].level-1];
	}
	return blackScore - redScore;
}

moveInfo* chessBoard::aiMove(){
    cout << "AI Move" << endl;
	moveInfo* bestMove = getBestMove();
    cout << bestMove->srcRow << ' ' << bestMove->srcCol << ' ' << bestMove->dstRow << ' ' << bestMove->dstCol << endl;

	// Make black chess in board move
	board[bestMove->dstRow][bestMove->dstCol] = board[bestMove->srcRow][bestMove->srcCol];
	board[bestMove->srcRow][bestMove->srcCol] = empty(0);
	if(bestMove->dstID != -1)
		chessList[bestMove->dstID].alive = false;
	chessList[bestMove->srcID].row = bestMove->dstRow;
	chessList[bestMove->srcID].col = bestMove->dstCol;
	// Check Gameover
	if(!chessList[20].isAlive()){
		chessBoard::gameOver = true;
	}

    playerSide = !playerSide;
	return bestMove;
}

// Use MaxMin-Search and alpha-beta to judge best move for AI
moveInfo* chessBoard::getBestMove(){
	vector<moveInfo*> steps;
	getAllPossibleMove(steps);
	// Make Min
	int initScore = -1000000;
	moveInfo* temp = NULL;
    cout << steps.size() << endl;
    while(steps.size() > 0){
        moveInfo* tmp = steps.back();
        steps.pop_back();

        doMove(tmp);
        int minScore = AlphaBetaJudge(LEVEL, initScore);
        undoMove(tmp);
        // Judge Alpha-Beta
        if(minScore > initScore){
            initScore = minScore;
            if(temp != NULL)  delete temp;
            temp = tmp;
        }else {
            delete tmp;
        }
    }
    cout << initScore << endl;
	return temp;
}

// MaxMin-search for all possible moves
void chessBoard::getAllPossibleMove(vector<moveInfo*>& steps){
	int min, max;
	if(playerSide == true){
		min = 16;
		max = 32;
	}else {
		min = 0;
		max = 16;
	}
	for(int i=min; i<max; i++){
		if(!chessList[i].isAlive())
			continue;
		for(int row=0; row<=9; row++){
			for(int col=0; col<=8; col++){
				chess target = getChess(make_pair(row, col));
                if(playerSide && target.getLevel() < 0)
                    continue;
                else if(!playerSide && target.getLevel() > 0)
                    continue;
				saveMove(chessList[i], target, row, col, steps);
			}
		}
	}
}

// Save one step to mocing list
void chessBoard::saveMove(chess& src, chess& target, int row, int col, vector<moveInfo*>& steps){
	int level = src.getLevel();
	bool judgeMove = false;
	solider* ss;  cannon* sc;  rook* sr;
    horse* sh;  elephant* se; guard* sg; general* sl;
	switch(level){
		case 1:
        case -1:
			ss = static_cast<solider*>(&src);
			judgeMove = ss->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
		case 2:
        case -2:
			sc = static_cast<cannon*>(&src);
			judgeMove = sc->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
		case 3:
        case -3:
			sr = static_cast<rook*>(&src);
			judgeMove = sr->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
		case 4:
        case -4:
			sh = static_cast<horse*>(&src);
			judgeMove = sh->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
		case 5:
        case -5:
			se = static_cast<elephant*>(&src);
			judgeMove = se->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
		case 6:
        case -6:
			sg = static_cast<guard*>(&src);
			judgeMove = sg->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
			break;
        case 7:
        case -7:
			sl = static_cast<general*>(&src);
			judgeMove = sl->judge_move(*this, make_pair(src.row, src.col), make_pair(row, col));
	}
    if(judgeMove){
        //cout << src.row << ' ' << src.col << ' ' << row << ' ' << col << endl;
        // Appending
        moveInfo* step = new moveInfo();
        step->srcID = src.id;    step->dstID = target.id;
        step->srcRow = src.row;  step->srcCol = src.col;
        step->dstRow = row;  step->dstCol = col;

        steps.push_back(step);
    }
}

// Do moving
void chessBoard::doMove(moveInfo* info){
	if(info->dstID != -1)
		chessList[info->dstID].alive = false;
    chessList[info->srcID].row = info->dstRow;
    chessList[info->srcID].col = info->dstCol;

	playerSide = !playerSide;
}

// Undo moving
void chessBoard::undoMove(moveInfo* info){
	if(info->dstID != -1)
		chessList[info->dstID].alive = true;
    chessList[info->srcID].row = info->srcRow;
    chessList[info->srcID].col = info->srcCol;

	playerSide = !playerSide;
}
