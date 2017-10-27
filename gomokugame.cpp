#include "gomokugame.h"
#include "game.h"

GomokuGame::GomokuGame(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    game_frame->set_game_model(modelCbx->currentIndex());

    connect(modelCbx, SIGNAL(activated(int)), this, SLOT(select_game_model(int)));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(clicked_undo_btn()));
    connect(peaceButton, SIGNAL(clicked()), this, SLOT(clicked_peace_btn()));
    connect(giveupButton, SIGNAL(clicked()), this, SLOT(clicked_giveup_btn()));
    connect(startButton, SIGNAL(clicked()), this, SLOT(clicked_start_btn()));
    connect(game_frame, SIGNAL(change_status(int)), this, SLOT(update_status_bar(int)));

}

GomokuGame::~GomokuGame()
{
}


void GomokuGame::select_game_model(int)
{
    game_frame->set_game_model(modelCbx->currentIndex());
}

void GomokuGame::clicked_undo_btn()
{
    game_frame->chess_undo();
}

void GomokuGame::clicked_peace_btn()
{

}

void GomokuGame::clicked_giveup_btn()
{

}

void GomokuGame::clicked_start_btn()
{
    startButton->setText("Restart");
    modelCbx->setEnabled(false);
    game_frame->chess_start();
}

void GomokuGame::update_status_bar(int type)
{
    if (game_frame->WHITE_PIECES == type) {
        status_bar->showMessage("White chess should go");

        //statusBar->setToolTip("Çë°×ÆåÂä×Ó");
    } else if (game_frame->BLACK_PIECES == type) {
        //statusBar()->setToolTip("ÇëºÚÆåÂä×Ó");
        status_bar->showMessage("Black chess should go");
    }

}
