#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>

class Game : public QFrame
{
    Q_OBJECT
public:
enum {
    WHITE_PIECES = 1,
    BLACK_PIECES = 2,
    OFFSET = 40,
    PIECES_SIZE = 32,
};

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    virtual void paintEvent(QPaintEvent *event);
    void set_game_model(int model);
    void chess_undo();
    void chess_start();

private:
    bool check_point(QPoint);
    int get_pieces_type(int i);
    QRect get_target_rect(int i);
    void coord_phy_to_logic(QPoint, int &, int&);   // 物理坐标到逻辑坐标
    QPoint coord_logic_to_phy(int, int);            // 逻辑坐标到物理坐标
    void coord_correct(QPoint &pos);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap white_pieces_pic, black_pieces_pic;
    int game_model;          // 0:双人对弈 1：人机对弈
    char (*pieces_pos)[100]; // 已放棋子列表
    QPoint *pieces_queue;    // 存放棋子放置顺序坐标
    int pieces_cnt;          // 目前棋子的总个数
    int last_opt;            // 上一步是谁走棋的
    bool start_flag;         // 开始标志位

signals:
    void change_status(int type);
    
public slots:
    
};

#endif // GAME_H
