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
    void coord_phy_to_logic(QPoint, int &, int&);   // �������굽�߼�����
    QPoint coord_logic_to_phy(int, int);            // �߼����굽��������
    void coord_correct(QPoint &pos);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QPixmap white_pieces_pic, black_pieces_pic;
    int game_model;          // 0:˫�˶��� 1���˻�����
    char (*pieces_pos)[100]; // �ѷ������б�
    QPoint *pieces_queue;    // ������ӷ���˳������
    int pieces_cnt;          // Ŀǰ���ӵ��ܸ���
    int last_opt;            // ��һ����˭�����
    bool start_flag;         // ��ʼ��־λ

signals:
    void change_status(int type);
    
public slots:
    
};

#endif // GAME_H
