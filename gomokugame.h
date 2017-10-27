#ifndef GOMOKUGAME_H
#define GOMOKUGAME_H

#include <QMainWindow>

#include "ui_gomokugame.h"

namespace Ui {
class GomokuGame;
}

class GomokuGame : public QMainWindow, public Ui::GomokuGame
{
    Q_OBJECT

public:
    explicit GomokuGame(QWidget *parent = 0);
    ~GomokuGame();

    
private slots:
    void select_game_model(int);
    void clicked_undo_btn();
    void clicked_peace_btn();
    void clicked_giveup_btn();
    void clicked_start_btn();
    void update_status_bar(int);
};

#endif // GOMOKUGAME_H
