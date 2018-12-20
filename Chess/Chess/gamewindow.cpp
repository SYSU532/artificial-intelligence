#include "gamewindow.h"
#include "ui_gamewindow.h"


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    clickTarget = chess(0);
    board = new chessBoard();
    ui->setupUi(this);

    mapper = new QSignalMapper(this);
    indexMapper = new QSignalMapper(this);
    blackBtnMapper = new QSignalMapper(this);

    initActions();
    playerSide = true;
    turn = 0;
}

GameWindow::~GameWindow()
{
    delete ui;
    delete board;
    delete mapper;
    delete indexMapper;
}

void GameWindow::showGame(){
    this->show();
}

void GameWindow::initActions(){
    board->initBoard();

    int index = 0;
    // Red btns init
    btn[index++] = ui->redRook1;  btn[index++] = ui->redHorse1;
    btn[index++] = ui->redElephant1;  btn[index++] = ui->redGuard1;
    btn[index++] = ui->redGeneral;  btn[index++] = ui->redGuard2;  
    btn[index++] = ui->redElephant2;  btn[index++] = ui->redHorse2;  
    btn[index++] = ui->redRook2;  btn[index++] = ui->redCannon1;
    btn[index++] = ui->redCannon2;  btn[index++] = ui->redSolider1;
    btn[index++] = ui->redSolider2;  btn[index++] = ui->redSolider3;
    btn[index++] = ui->redSolider4;  btn[index++] = ui->redSolider5;
    // Black btns init
    index = 0;
    blackBtn[index++] = ui->blackRook1;  blackBtn[index++] = ui->blackHorse1;
    blackBtn[index++] = ui->blackElephant1;  blackBtn[index++] = ui->blackGuard1;
    blackBtn[index++] = ui->blackGeneral;  blackBtn[index++] = ui->blackGuard2;  
    blackBtn[index++] = ui->blackElephant2;  blackBtn[index++] = ui->blackHorse2;  
    blackBtn[index++] = ui->blackRook2;  blackBtn[index++] = ui->blackCannon1;
    blackBtn[index++] = ui->blackCannon2;  blackBtn[index++] = ui->blackSolider1;
    blackBtn[index++] = ui->blackSolider2;  blackBtn[index++] = ui->blackSolider3;
    blackBtn[index++] = ui->blackSolider4;  blackBtn[index++] = ui->blackSolider5;
    for(int i=0; i<16; i++){
        blackBtnMapper->setMapping(blackBtn[i], i);
        connect(blackBtn[i], SIGNAL(clicked()), blackBtnMapper, SLOT(map()));
        connect(blackBtnMapper, SIGNAL(mapped(int)), this, SLOT(blackBtnPress(int)));
    }

    // Red btns image path init
    index = 0;
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RR.GIF);border-radius:50%;}");
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RN.GIF);border-radius:50%;}");
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RB.GIF);border-radius:50%;}");
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RA.GIF);border-radius:50%;}");
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RK.GIF);border-radius:50%;}");
    image[index++] = image[3];   image[index++] = image[2];  image[index++] = image[1];   image[index++] = image[0];
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RC.GIF);border-radius:50%;}");
    image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RC.GIF);border-radius:50%;}");
    for(int i=0; i<5; i++){
        image[index++] = QString("QPushButton{background-image:url(:/Sample/images/WOOD/RP.GIF);border-radius:50%;}");
    }

    index = 0;
    // Init Red chesses locations
    for(int i=0; i<=8; i++){
        mapper->setMapping(btn[index++], QString::number(9*10 + i));
    }
    mapper->setMapping(btn[index++], QString::number(7*10 + 1));
    mapper->setMapping(btn[index++], QString::number(7*10 + 7));
    for(int i=0; i<=8; i+=2){
        mapper->setMapping(btn[index++], QString::number(6*10 + i));
    }

    for(int i=0; i<16; i++){
        connect(btn[i], SIGNAL(clicked()), mapper, SLOT(map()));
        connect(btn[i], SIGNAL(clicked()), indexMapper, SLOT(map()));
        indexMapper->setMapping(btn[i], i);
    }
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(clickOnChess(QString)));
    connect(indexMapper, SIGNAL(mapped(int)), this, SLOT(setButton(int)));
}

bool GameWindow::isGameOver(){
    string result;
    if(playerSide == true){
        result = "游戏结束，玩家获胜";
    }else {
        result = "游戏结束，AI获胜";
    }
    int res = QMessageBox::question(NULL, "Game Over", result.c_str(), QMessageBox::Yes);

    this->close();
}

void GameWindow::setGameOver(bool over){
    if(over){
        player.setSource(QUrl("qrc:/audios/Win.wav"));
        player.play();
        isGameOver();
    }
}

void GameWindow::aiMove(){
    moveInfo* result = board->aiMove();
    if(result->dstID != -1)
        btn[result->dstID - 16]->hide();
    int realX = result->dstRow, realY = result->dstCol;
    blackBtn[result->srcID]->setGeometry(realY*58, realX*58, 57, 57);
    blackBtnMapper->setMapping(blackBtn[result->srcID], QString::number(realX*10 + realY));
    // Check game over
    if(chessBoard::gameOver == true){
        player.setSource(QUrl("qrc:/audios/Loss.wav"));
        player.play();
        isGameOver();
    }
    playerSide = !playerSide;
    delete result;
}

void GameWindow::resetBoardChessImg(){
    for(int i=0; i<16; i++){
        btn[i]->setStyleSheet(image[i]);
    }
}

void GameWindow::setButton(int index){
    // Judge whether is player turn
    if(!playerSide){
        return;
    }
    button = btn[index];
    targetIndex = index;
    resetBoardChessImg();
    // Set select background image
    switch(targetLevel){
        case -1:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RPS.GIF);border-radius:50%;}");
            break;
        case -2:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RCS.GIF);border-radius:50%;}");
            break;
        case -3:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RRS.GIF);border-radius:50%;}");
            break;
        case -4:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RNS.GIF);border-radius:50%;}");
            break;
        case -5:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RBS.GIF);border-radius:50%;}");
            break;
        case -6:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RAS.GIF);border-radius:50%;}");
            break;
        default:
            button->setStyleSheet("QPushButton{background-image:url(:/Sample/images/WOOD/RKS.GIF);border-radius:50%;}");
    }
}

void GameWindow::clickOnChess(QString a){
    // Judge whether is player turn
    if(!playerSide){
        return;
    }
    qDebug() << a;
    int number = a.toInt();
    int x = number / 10, y = number % 10;
    int level = board->getLevel(make_pair(x, y));
    if(level == 0){
        return;
    }
    player.setSource(QUrl("qrc:/audios/Choose.wav"));
    player.play();
    targetPos = make_pair(x, y);
    targetLevel = level;
    clickTarget = board->getChess(targetPos);
}

void GameWindow::mousePressEvent(QMouseEvent* event){
    if(clickTarget.getLevel() == 0 || !playerSide){
        return;
    }
    int x = event->x(), y = event->y();
    int realY = round(x / GAP), realX = round(y / GAP);
    // Transform chess to special class
    chess* pointer = &clickTarget;
    bool judgeMove = false;
    solider* ss;  cannon* sc;  rook* sr;
    horse* sh;  elephant* se; guard* sg; general* sl;
    qDebug() << realX << realY;
    switch(pointer->getLevel()){
        case -1:
            ss = static_cast<solider*>(pointer);
            judgeMove = ss->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -2:
            sc = static_cast<cannon*>(pointer);
            judgeMove = sc->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -3:
            sr = static_cast<rook*>(pointer);
            judgeMove = sr->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -4:
            sh = static_cast<horse*>(pointer);
            judgeMove = sh->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -5:
            se = static_cast<elephant*>(pointer);
            judgeMove = se->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -6:
            sg = static_cast<guard*>(pointer);
            judgeMove = sg->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -7:
            sl = static_cast<general*>(pointer);
            judgeMove = sl->judge_move(*board, targetPos, make_pair(realX, realY));
            break;

        default:
            return;
    }
    qDebug() << judgeMove;
    resetBoardChessImg();
    // Judge Move
    if(judgeMove){
        button->setGeometry(realY*58, realX*58, 57, 57);
        mapper->setMapping(btn[targetIndex], QString::number(realX*10 + realY));
        board->playerMove(targetPos, make_pair(realX, realY));
        player.setSource(QUrl("qrc:/audios/Move.wav"));
        playerSide = false;
        QTimer::singleShot(100, this, SLOT(aiMove()));
    }else {
        player.setSource(QUrl("qrc:/audios/Forbid.wav"));
    }
    player.play();
    // Reset clickTarget
    clickTarget = empty(0);
}

void GameWindow::blackBtnPress(int index){
    if(clickTarget.getLevel() == 0 || !playerSide){
        return;
    }
    // Judge eat enable
    QPushButton* target = blackBtn[index];
    int x = target->x(), y = target->y();
    int realX = round(y / GAP), realY = round(x / GAP);
    // Judge move
    chess* pointer = &clickTarget;
    bool judgeMove = false;
    solider* ss;  cannon* sc;  rook* sr;
    horse* sh;  elephant* se; guard* sg; general* sl;
    qDebug() << realX << realY;
    switch(pointer->getLevel()){
        case -1:
            ss = static_cast<solider*>(pointer);
            judgeMove = ss->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -2:
            sc = static_cast<cannon*>(pointer);
            judgeMove = sc->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -3:
            sr = static_cast<rook*>(pointer);
            judgeMove = sr->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -4:
            sh = static_cast<horse*>(pointer);
            judgeMove = sh->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -5:
            se = static_cast<elephant*>(pointer);
            judgeMove = se->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -6:
            sg = static_cast<guard*>(pointer);
            judgeMove = sg->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        case -7:
            sl = static_cast<general*>(pointer);
            judgeMove = sl->judge_move(*board, targetPos, make_pair(realX, realY));
            break;
        default:
            return;
    }
    qDebug() << judgeMove;
    resetBoardChessImg();
    // Judge Move
    if(judgeMove){
        button->setGeometry(realY*58, realX*58, 57, 57);
        mapper->setMapping(btn[targetIndex], QString::number(realX*10 + realY));
        bool over = board->eatBlackChess(realX, realY);
        board->playerMove(targetPos, make_pair(realX, realY));
        player.setSource(QUrl("qrc:/audios/Move.wav"));
        player.play();
        blackBtn[index]->hide();
        setGameOver(over);
        playerSide = false;
        QTimer::singleShot(100, this, SLOT(aiMove()));
    }else {
        player.setSource(QUrl("qrc:/audios/Forbid.wav"));
        player.play();
    }
    // Reset clickTarget
    clickTarget = empty(0);
}
