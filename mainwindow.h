#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void drawMaze(const std::vector<std::vector<int>> &maze);

private slots:
    void startSimulation();
    void updateSimulation();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPushButton *startButton;
    QLabel *statusLabel;
    QTimer *timer;
    bool exploring;
};

#endif // MAINWINDOW_H