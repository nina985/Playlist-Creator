#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDesktopServices>
#include <QKeyEvent>

#include <string>

#include "song.h"
#include "controller.h"
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void reloadSongListData();
    void reloadPlaylistData();

    void currentNotSelected_PopUp(){
        QMessageBox::warning(this, tr("Message"), tr("Select an item to complete this action."));
    }

    void addToSongList_Clicked();
    void removeFromSongList_Clicked();
    void showLyrics_Clicked();
    void sortSongList(std::string type, std::string ord); //type= title/artist; ord=INCR/DECR

    void addToPlaylist_Clicked();
    void removeFromPlaylist_Clicked();

    void generateRandom();

    void openLinkInBrowser();
    void keyPressEvent(QKeyEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QHBoxLayout* main_layout;

//left pannel:
    QVBoxLayout* songs_layout;

    QLabel* songs_label;
    QListWidget* songs_list;

    QFormLayout* songs_imput;

    QLabel* title_label;
    QLabel* artist_label;
    QLabel* year_label;
    QLabel* lyrics_label;
    QLabel* url_label;

    QLineEdit* title_line_edit;
    QLineEdit* artist_line_edit;
    QLineEdit* year_line_edit;
    QLineEdit* lyrics_line_edit;
    QLineEdit* url_line_edit;


    QHBoxLayout* songs_buttons;

    QPushButton* add_button;
    QPushButton* delete_button;
    QPushButton* lyrics_button;


    QLabel* songs_sort;
    QGridLayout* songs_sort_buttons;

    QPushButton* sort_title_AZ_button;
    QPushButton* sort_title_ZA_button;
    QPushButton* sort_artist_AZ_button;
    QPushButton* sort_artist_ZA_button;

//middle pannel:
    QVBoxLayout* middle_buttons;

    QPushButton* add_to_playlist_button;
    QPushButton* remove_from_playlist_button;

//right pannel:
    QVBoxLayout* playlist_layout;

    QLabel* playlist_label;
    QListWidget* playlist_list;

    QFormLayout* playlist_buttons;

    QLabel* random_playlist;
    QLineEdit* random_size;
    QPushButton* randomize;
    QPushButton* play_in_browser;

  //song repository and playlist:
    SongController allSongs;
    Playlist playlist;
};
#endif // MAINWINDOW_H
