#include "game.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <string.h>
#include <stdlib.h>

Game::Game(QWidget *parent) :
    QFrame(parent)
{
    white_pieces_pic.load(":/newPrefix/img/white.png");
    black_pieces_pic.load(":/newPrefix/img/black.png");

    pieces_pos = (char (*)[100])calloc(sizeof(char), 100*100);
    pieces_queue = (QPoint *)calloc(sizeof(QPoint), 1000);

    start_flag = false;
}

Game::~Game()
{
    free(pieces_pos);
    free(pieces_queue);
}

void Game::chess_undo()
{
    int x, y;
    QPoint point(0, 0);

    if (pieces_cnt <= 1) {
        return;
    }

    coord_phy_to_logic(pieces_queue[pieces_cnt-1], x, y);
    pieces_pos[y][x] = 0;
    pieces_queue[pieces_cnt-1] = point;
    pieces_cnt --;

    if (WHITE_PIECES == last_opt) {
        last_opt = BLACK_PIECES;
        emit change_status(WHITE_PIECES);
        qDebug() << "white";
    } else {
        last_opt = WHITE_PIECES;
        emit change_status(BLACK_PIECES);
        qDebug() << "black";
    }

    update();
}

void Game::chess_start()
{
    start_flag = true;

    pieces_cnt = 1;
    pieces_queue[0] = coord_logic_to_phy(9, 9);
    pieces_pos[9][9] = BLACK_PIECES;
    last_opt = BLACK_PIECES;
    // ´Ë´¦×´Ì¬À¸ÏÔÊ¾  ¡°Çë°×ÆåÂä×Ó¡±
    emit change_status(WHITE_PIECES);

    update();
}

void Game::coord_phy_to_logic(QPoint point, int &x, int &y)
{
    x = point.x() / OFFSET - 1;
    y = point.y() / OFFSET - 1;
}

QPoint Game::coord_logic_to_phy(int x, int y)
{
    QPoint point;

    point.setX((x+1) * OFFSET);
    point.setY((y+1) * OFFSET);

    return point;
}

int Game::get_pieces_type(int i)
{
    int x, y;
    coord_phy_to_logic(pieces_queue[i], x, y);

    return pieces_pos[y][x];
}

QRect Game::get_target_rect(int i)
{
    int x = pieces_queue[i].x();
    int y = pieces_queue[i].y();
    QRect tar(x-PIECES_SIZE/2, y-PIECES_SIZE/2, PIECES_SIZE, PIECES_SIZE);

    return tar;
}

void Game::set_game_model(int model)
{
    if (0==model || 1==model) {
        game_model = model;
    }

    qDebug() << "model" << model;
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();

    width = width / OFFSET * OFFSET;
    height = height / OFFSET * OFFSET;

    painter.setPen(QPen(QColor(0, 0, 0)));
    for (int y=0; y<=height; y+=OFFSET) {
        painter.drawLine(0, y, width, y);
    }

    for (int x=0; x<=width; x+=OFFSET) {
         painter.drawLine(x, 0, x, height);
    }

    QRect src(0, 0, PIECES_SIZE, PIECES_SIZE);

    QRect tar;

    for (int i=0; i<pieces_cnt; i++) {
        tar = get_target_rect(i);
        if (WHITE_PIECES == get_pieces_type(i)) {
            painter.drawPixmap(tar, white_pieces_pic, src);
        } else if (BLACK_PIECES == get_pieces_type(i)) {
            painter.drawPixmap(tar, black_pieces_pic, src);
        }
    }
}

void Game::coord_correct(QPoint &pos)
{
    int x = pos.x();
    int y = pos.y();

    x = (x+OFFSET-PIECES_SIZE/2) / OFFSET * OFFSET;
    y = (y+OFFSET-PIECES_SIZE/2) / OFFSET * OFFSET;

    pos.setX(x);
    pos.setY(y);
}

bool Game::check_point(QPoint point)
{
    if (0==point.x() || 0==point.y()) {
        return false;
    }

    for (int i=0; i<pieces_cnt; i++) {
        if (pieces_queue[i] == point) {
            return false;
        }
    }

    return true;
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || false == start_flag) {
        return;
    }

    QPoint pos = event->pos();
    qDebug() << pos.x() << pos.y();
    coord_correct(pos);
    qDebug() << pos.x() << pos.y();

    if (false == check_point(pos)) {
        return;
    }

    int x, y;
    pieces_queue[pieces_cnt] = pos;
    coord_phy_to_logic(pos, x, y);
    if (WHITE_PIECES == last_opt) {
        pieces_pos[y][x] = BLACK_PIECES;
        last_opt = BLACK_PIECES;
        emit change_status(WHITE_PIECES);
        qDebug() << "white";
    } else {
        pieces_pos[y][x] = WHITE_PIECES;
        last_opt = WHITE_PIECES;
        emit change_status(BLACK_PIECES);
        qDebug() << "black";
    }

    pieces_cnt ++;

    update();
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{

}
