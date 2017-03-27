#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Initialize MultiMedia
    player = new QMediaPlayer();
    playList = new QMediaPlaylist();
    dataMap = new QMap<QString, QString>();
    player->setPlaylist(this->playList);
    player->setNotifyInterval(1000);
    player->setVolume(20);

    //A bunch of connect
    connect(ui->removeButton, SIGNAL(clicked(bool)), this, SLOT(onRemoveButtonClickSlot()));
    connect(ui->addMusicButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClickSlot()));
    connect(ui->previousButton, SIGNAL(clicked(bool)), this, SLOT(onPreviousButtonClickSlot()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayButtonClickSlot()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(onStopButtonClickSlot()));
    connect(ui->nextButton, SIGNAL(clicked(bool)), this, SLOT(onNextButtonClickSlot()));
    connect(ui->songsListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListItemDoubleClickedSlot()));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayStateChangedSlot()));
    connect(playList, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChangedSlot()));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onPlayDurationChangedSlot()));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPlayPositonChangedSlot()));
    connect(ui->positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(onSeekedSlot()));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSeekedSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete playList;
    delete dataMap;
}

//Implements of Slots
void MainWindow::onAddButtonClickSlot()
{
    QFileDialog* file = new QFileDialog();
    file->setFileMode(QFileDialog::ExistingFiles);
    if(file->exec() == QFileDialog::Accepted)
    {
        QStringList sl = file->selectedFiles();
        foreach (QString path, sl)
        {
            QString name = QFileInfo(path).fileName();
            dataMap->insert(name, path);
            ui->songsListWidget->addItem(name);
            playList->addMedia(QMediaContent(QUrl::fromLocalFile(path)));
        }
        ui->playButton->setEnabled(true);
    }
    delete file;
}

void MainWindow::onRemoveButtonClickSlot()
{
    QListWidgetItem* item = ui->songsListWidget->takeItem(ui->songsListWidget->currentRow());
    dataMap->remove(item->text());
    playList->removeMedia(ui->songsListWidget->currentRow());
    delete item;
}

void MainWindow::onPreviousButtonClickSlot()
{
//    if(playList->mediaCount()>0)
//    {
//        if(playList->currentIndex()<=playList->mediaCount())
//        {
//            playList->setCurrentIndex(playList->mediaCount());
//        }
//        else
//        {
//            playList->setCurrentIndex(playList->currentIndex()-1);
//        }
//        player->play();
//    }
    playList->previous();
    player->play();
}

void MainWindow::onPlayButtonClickSlot()
{
    if(player->state() == QMediaPlayer::StoppedState)
    {
        player->play();
    }
    else if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
    }
    else if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
    }
}

void MainWindow::onStopButtonClickSlot()
{
    if(player->isAvailable() && player->state() != QMediaPlayer::StoppedState)
    {
        player->stop();
        ui->stopButton->setEnabled(false);
    }
}

void MainWindow::onNextButtonClickSlot()
{
//    if(playList->mediaCount()>0)
//    {
//        if(playList->currentIndex()>=playList->mediaCount())
//        {
//            playList->setCurrentIndex(1);
//        }
//        else
//        {
//            playList->setCurrentIndex(playList->currentIndex()+1);
//        }
//        player->play();
//    }
    playList->next();
    player->play();
}

void MainWindow::onListItemDoubleClickedSlot()
{
    int a = ui->songsListWidget->currentRow();
    player->playlist()->setCurrentIndex(a);
    player->play();
}

void MainWindow::onPlayStateChangedSlot()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        ui->playButton->setText("Pause");
        ui->stopButton->setEnabled(true);
    }
    else if(player->state() == QMediaPlayer::PausedState)
    {
        ui->playButton->setText("Play");
    }
    else if(player->state() == QMediaPlayer::StoppedState)
    {
        ui->playButton->setText("Play");
        ui->stopButton->setEnabled(false);
    }
}

void MainWindow::onCurrentIndexChangedSlot()
{
    ui->songsListWidget->setCurrentRow(playList->currentIndex());
}

void MainWindow::onPlayDurationChangedSlot()
{
//    QString str = QTime::fromMSecsSinceStartOfDay(this->player->duration()).toString("mm : ss");
//    qDebug() << "time:"<<str;
    ui->durationLabel->setText(QTime::fromMSecsSinceStartOfDay(this->player->duration()).toString("mm : ss"));
    ui->positionSlider->setMaximum(this->player->duration());
    ui->positionSlider->setMinimum(0);
}

void MainWindow::onPlayPositonChangedSlot()
{
//    qDebug() << "position:"<<player->position();
    ui->positionSlider->setValue(player->position());
    ui->positionLabel->setText(QTime::fromMSecsSinceStartOfDay(player->position()).toString("mm : ss"));
}

void MainWindow::onSeekedSlot()
{
    player->setPosition(ui->positionSlider->value());
}

void MainWindow::onVolumeSeekedSlot()
{
   player->setVolume(ui->volumeSlider->value());
}
