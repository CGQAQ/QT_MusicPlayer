#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMap>
#include <QFileDialog>
#include <QList>
#include <QMediaContent>
#include <QTime>
#include <QDebug>
#include <QtXml/qxml.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QMediaPlaylist* playList;
    QMap<QString, QString>* dataMap;

private slots:
    void onRemoveButtonClickSlot();
    void onAddButtonClickSlot();
    void onPreviousButtonClickSlot();
    void onPlayButtonClickSlot();
    void onStopButtonClickSlot();
    void onNextButtonClickSlot();
    void onListItemDoubleClickedSlot();
    void onPlayStateChangedSlot();
    void onCurrentIndexChangedSlot();
    void onPlayDurationChangedSlot();
    void onPlayPositonChangedSlot();
    void onSeekedSlot();
    void onVolumeSeekedSlot();
};

#endif // MAINWINDOW_H
