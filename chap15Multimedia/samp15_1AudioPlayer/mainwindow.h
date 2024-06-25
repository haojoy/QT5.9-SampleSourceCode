#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QMainWindow>
#include    <QMediaPlayer>
#include    <QMediaPlaylist>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QMediaPlayer    *player;//播放器
    QMediaPlaylist  *playlist;//播放列表
    QSet<QString> songlist; //添加的歌曲，添加去重

    QString  durationTime;//总长度
    QString  positionTime;//当前播放到位置
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    //拖拽文件进入
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
private slots:
//自定义槽函数
    void onStateChanged(QMediaPlayer::State state);

    void onPlaylistChanged(int position);

    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

//
    void on_btnAdd_clicked();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_btnClear_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_btnSound_clicked();

//    void on_sliderPosition_valueChanged(int value);

//    void on_sliderPosition_sliderMoved(int position);

    void on_sliderPosition_valueChanged(int value);

    void on_btnRemove_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
