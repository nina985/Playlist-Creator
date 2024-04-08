#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->main_layout = new QHBoxLayout{this->centralWidget()};

//left pannel
    this->songs_layout=new QVBoxLayout{this};

    this->songs_label=new QLabel{"All songs"};
    this->songs_list = new QListWidget{};
    this->songs_layout->addWidget(this->songs_label);
    this->songs_layout->addWidget(this->songs_list);

  //form layout for completing info abt songs
    this->songs_imput = new QFormLayout{};

    this->title_label = new QLabel{"Title:"};
    this->title_line_edit = new QLineEdit{};

    this->artist_label = new QLabel{"Artist:"};
    this->artist_line_edit = new QLineEdit{};

    this->lyrics_label = new QLabel{"Lyrics:"};
    this->lyrics_line_edit = new QLineEdit{};

    this->year_label = new QLabel{"Year:"};
    this->year_line_edit = new QLineEdit{};
    year_line_edit->setValidator( new QIntValidator(0, 2023, this) );

    this->url_label = new QLabel{"Link:"};
    this->url_line_edit = new QLineEdit{};

    this->songs_imput->addRow(this->title_label,this->title_line_edit);
    this->songs_imput->addRow(this->artist_label,this->artist_line_edit);
    this->songs_imput->addRow(this->lyrics_label,this->lyrics_line_edit);
    this->songs_imput->addRow(this->year_label,this->year_line_edit);
    this->songs_imput->addRow(this->url_label,this->url_line_edit);

    this->songs_layout->addLayout(this->songs_imput);

  //grid layot for song list options buttons
    this->songs_buttons = new QHBoxLayout{};

    this->add_button=new QPushButton{"Add"};
    this->delete_button=new QPushButton{"Delete"};
    this->lyrics_button=new QPushButton{"Show Lyrics"};

    this->songs_buttons->addWidget(this->add_button);
    this->songs_buttons->addWidget(this->delete_button);
    this->songs_buttons->addWidget(this->lyrics_button);

    this->songs_layout->addLayout(this->songs_buttons);

  //grid layot for sorting song list buttons
    this->songs_sort= new QLabel{"Sort songs:"};
    this->songs_sort_buttons= new QGridLayout{};

    this->sort_title_AZ_button=new QPushButton{"by Title A-Z"};
    this->sort_title_ZA_button=new QPushButton{"by Title Z-A"};
    this->sort_artist_AZ_button=new QPushButton{"by Artist A-Z"};
    this->sort_artist_ZA_button=new QPushButton{"by Artist Z-A"};

    this->songs_sort_buttons->addWidget(this->sort_title_AZ_button,0,0);
    this->songs_sort_buttons->addWidget(this->sort_title_ZA_button,0,1);
    this->songs_sort_buttons->addWidget(this->sort_artist_AZ_button,1,0);
    this->songs_sort_buttons->addWidget(this->sort_artist_ZA_button,1,1);

    this->songs_layout->addWidget(this->songs_sort);
    this->songs_layout->addLayout(this->songs_sort_buttons);

  //adding song layout to main layout
    this->main_layout->addLayout(this->songs_layout);

//middle pannel
    this->middle_buttons= new QVBoxLayout{};

    this->add_to_playlist_button= new QPushButton{">"};
    this->remove_from_playlist_button= new QPushButton{"<"};

    this->middle_buttons->addStretch();
    this->middle_buttons->addWidget(this->add_to_playlist_button);
    this->middle_buttons->addWidget(this->remove_from_playlist_button);
    this->middle_buttons->addStretch();

    this->main_layout->addLayout(this->middle_buttons);

//right pannel
    this->playlist_layout= new QVBoxLayout{};

    this->playlist_label= new QLabel{"Playlist"};
    this->playlist_list= new QListWidget{};

    this->playlist_layout->addWidget(this->playlist_label);
    this->playlist_layout->addWidget(this->playlist_list);

    this->playlist_buttons= new QFormLayout{};

    this->random_playlist= new QLabel{"Number of songs:"};
    this->random_size= new QLineEdit{};

    this->randomize= new QPushButton{"Generate Random Playlist"};
    this->play_in_browser= new QPushButton{"Open Link in Browser"};

    this->playlist_buttons->addRow(this->random_playlist,this->random_size);
    this->playlist_buttons->addWidget(this->randomize);
    this->playlist_buttons->addWidget(this->play_in_browser);

    this->playlist_layout->addLayout(this->playlist_buttons);

    this->main_layout->addLayout(this->playlist_layout);

//already existing songs:
    this->allSongs.addToRepo("One Way Or Another","Blondie",1978,"One way, or another, I'm gonna find ya\n I'm gonna get ya, get ya, get ya, get ya\n One way, or another, I'm gonna find ya\n I'm gonna get ya, get ya, get ya, get ya\n One way, or another, I'm gonna see ya\n I'm gonna meet ya, meet ya, meet ya, meet ya\n One day, maybe next week\n I'm gonna meet ya, I'm gonna meet ya, I'll meet ya\n","https://www.youtube.com/watch?v=_zBwRDEFMRY");
    this->allSongs.addToRepo("Moonlight Beach","PIPER",1983,"Ooh Moonlight beach\n Ooh Midnight dream\n Silent night\n","https://www.youtube.com/watch?v=J-wYQ3ZxsvA");
    this->allSongs.addToRepo("Bullet with Butterfly Wings","The Smashing Pumpkins",1995,"Despite all my rage, I am still just a rat in a cage\n Despite all my rage, I am still just a rat in a cage\n Someone will say, 'What is lost can never be saved'\n Despite all my rage, I am still just a rat in a cage\n","https://www.youtube.com/watch?v=8-r-V0uK4u0");
    this->allSongs.addToRepo("Lords of the Boards","Guano Apes",1997,"And now I'm flying like an angel to the sun\n My feet are burning and I grab into another world\n With the lords of the boards you're come again around\n With the lords of the boards you're come again around\n","https://www.youtube.com/watch?v=2yfwePfD-iU");
    this->allSongs.addToRepo("Sligo River Blues","John Fahey",1959,"","https://www.youtube.com/watch?v=21HwdNkzYq0"); //pop up for song with no lyrics!!
    this->allSongs.addToRepo("Ecstasy(Apple of My Eye)","Strawberry Switchblade",1985,"In a kiss lies so much more than touch\n And my life has found a new temptation\n And ecstasy has meaning once again\n I find suddenly I'm closer to you\n And I find all my wildest dreams\n Have come true\n While I spin round\n My heart is beating for two\n And I am wishing\n It will always be you and I\n","https://www.youtube.com/watch?v=bz8D7MSY2bA");
    this->allSongs.addToRepo("Human Behaviour","Björk",1993,"If you ever get close to a human\n And human behaviour\n Be ready, be ready to get confused\n And me and my hereafter\n \n There's definitely, definitely, definitely no logic\n To human behaviour\nBut yet so, yet so irresistible\n And me and my fear cannot\n","https://www.youtube.com/watch?v=p0mRIhK9seg");
    this->allSongs.addToRepo("Night faces","Jessica Pratt",2012,"Some days are long and\n Summer days are hard\n I was dragging my feet across the parking lot\n I remember sad faces in the mirror behind me\n And I saw those blank places in the driver's seat\n You know I spent a million tears\n Trying to dig myself out all these years\n And I had a hard time to get me down\n \n No, I call you Delaney\n 'Cause the tears you rain down\nAnd you call me lady when the chips are down\n \n And you say, 'Cry no tears'\n I hear you sayin'\n 'Cry no tears' is the refrain\n 'Cry no tears' again\n","https://www.youtube.com/watch?v=FF1lESEpYrc");
    this->allSongs.addToRepo("Zoo","Limba Trip",2022,"","https://www.youtube.com/watch?v=JIXu_qoR1io");
    this->allSongs.addToRepo("Girl Goodbye","TOTO",1978,"So it's\n \n Goodbye girl, goodbye girl, girl goodbye\n It's so hard to see the truth with the sun in your eyes\n Goodbye girl, goodbye girl, girl goodbye\n Must be in the way that she cries, must be in the way that she cries\n Must be in the way that she cries\n \n Oh there's smoke in the air and there's blood everywhere\n But I'm hoping that the white man don't recognize me\n","https://www.youtube.com/watch?v=YqLjbeXkc_0");
    this->allSongs.addToRepo("A Nambra","Mong Tong",2020,"","https://www.youtube.com/watch?v=-1dlh-LXOnk");
    this->allSongs.addToRepo("Never Ending Night","Devil Master",2022,"","https://youtu.be/QS80-LjAIxI");

    reloadSongListData();

//show lyrics
    connect(this->lyrics_button,&QPushButton::clicked, [this](){
        QList<QListWidgetItem*> selectedItems = songs_list->selectedItems();
        if(!selectedItems.isEmpty()){
            showLyrics_Clicked();
        }
        else{
            currentNotSelected_PopUp();
        }
    });

//add to song list
    connect(this->add_button, SIGNAL(clicked()), this, SLOT(addToSongList_Clicked()));

//remove from song list
    connect(this->delete_button,&QPushButton::clicked, [this](){
        QList<QListWidgetItem*> selectedItems = songs_list->selectedItems();
        if(!selectedItems.isEmpty()){
            removeFromSongList_Clicked();
        }
        else{
            currentNotSelected_PopUp();
        }
    });

//sort
    connect(this->sort_artist_AZ_button, &QPushButton::clicked, [this](){sortSongList("artist","INCR");});
    connect(this->sort_artist_ZA_button, &QPushButton::clicked, [this](){sortSongList("artist","DECR");});
    connect(this->sort_title_AZ_button, &QPushButton::clicked, [this](){sortSongList("title","INCR");});
    connect(this->sort_title_ZA_button, &QPushButton::clicked, [this](){sortSongList("title","DECR");});


//add and remove from playlist button functionality:
    connect(this->remove_from_playlist_button,&QPushButton::clicked, [this](){
        QList<QListWidgetItem*> selectedItems = playlist_list->selectedItems();
        if(!selectedItems.isEmpty()){
            removeFromPlaylist_Clicked();
        }
        else{
            currentNotSelected_PopUp();
        }
    });

    connect(this->add_to_playlist_button,&QPushButton::clicked, [this](){
        QList<QListWidgetItem*> selectedItems = songs_list->selectedItems();
        if(!selectedItems.isEmpty()){
            addToPlaylist_Clicked();
        }
        else{
            currentNotSelected_PopUp();
        }
    });

//generate random playlist button:
    connect(this->randomize,SIGNAL(clicked()),this,SLOT(generateRandom()));

//open current in browser
    connect(this->play_in_browser ,&QPushButton::clicked, [this](){
        QList<QListWidgetItem*> selectedItems = playlist_list->selectedItems();
        if(!selectedItems.isEmpty()){
            openLinkInBrowser();
        }
        else{
            currentNotSelected_PopUp();
        }
    });
}

void MainWindow::reloadSongListData()
{
    this->songs_list->clear();
    int i=0;
    if(this->allSongs.getAllSongs().size()!=0)
        for( auto& song: this->allSongs.getAllSongs())
        {
            std::string msg= song.getArtist()+" - "+song.getTitle();
            this->songs_list->insertItem(++i,new QListWidgetItem{msg.c_str()});
        }
    random_size->setValidator( new QIntValidator(0, allSongs.getAllSongs().size() , this) );
}

void MainWindow::reloadPlaylistData()
{
    this->playlist_list->clear();
    int i=0;
    if(this->playlist.getAll().size()!=0)
        for( auto& song: this->playlist.getAll())
        {
            std::string msg= song.getArtist()+" - "+song.getTitle();
            this->playlist_list->insertItem(++i,new QListWidgetItem{msg.c_str()});
        }
}

//Song repo
void MainWindow::addToSongList_Clicked(){
    if(this->artist_line_edit->text()!="" && this->title_line_edit->text()!="" )
    {
        try
        {
            this->allSongs.addToRepo(title_line_edit->text().toStdString(),artist_line_edit->text().toStdString(),year_line_edit->text().toInt(), lyrics_line_edit->text().toStdString(), url_line_edit->text().toStdString());
            reloadSongListData();

            this->artist_line_edit->clear();
            this->title_line_edit->clear();
            this->year_line_edit->clear();
            this->lyrics_line_edit->clear();
            this->url_line_edit->clear();
        }
        catch(SongException){
            std::string msg="The song \""+title_line_edit->text().toStdString()+"\" by "+artist_line_edit->text().toStdString()+" is already in the repository";
            QMessageBox::warning(this, tr("Message"), tr(msg.c_str()));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Message"), tr("Please input at least a title and an artist to add a song."));
    }
}

void MainWindow::removeFromSongList_Clicked(){
    std::string::size_type pos = this->songs_list->currentItem()->text().toStdString().find('-');

    std::string artist = this->songs_list->currentItem()->text().toStdString().substr(0,pos-1);
    std::string title = this->songs_list->currentItem()->text().toStdString().substr(pos+2);

    Song s = this->allSongs.searchSong(title,artist);

    this->allSongs.removeFromRepo(s);
    reloadSongListData();
}

void MainWindow::showLyrics_Clicked(){
    QWidget *wdg = new QWidget;
    std::string::size_type pos = this->songs_list->currentItem()->text().toStdString().find('-');

    std::string artist = this->songs_list->currentItem()->text().toStdString().substr(0,pos-1);
    std::string title = this->songs_list->currentItem()->text().toStdString().substr(pos+2);

    Song s = this->allSongs.searchSong(title,artist);

    std::string l{""};

    if(s.getLyrics()[0]=="")
        l+="No lyrics for the selected song.";
    else
        for(int i=0;i<s.getLyrics().size();i++)
            l+=s.getLyrics()[i]+" ";

    QLabel *lyrics = new QLabel{l.c_str()};
    QHBoxLayout *wdgLayout = new QHBoxLayout{wdg};
    wdgLayout->addWidget(lyrics);
    wdg->setLayout(wdgLayout);

    std::string wdgTitle=title+" ("+std::to_string(s.getYear())+") - Lyrics";
    wdg->setWindowTitle(wdgTitle.c_str());
    wdg->show();
}

void MainWindow::sortSongList(std::string type, std::string ord) //type= "title"/"artist"; ord="INCR"/"DECR"
{
    if(type=="title"){
        this->allSongs.setAllSongs(this->allSongs.ordByTitle(ord));
    }
    else if(type=="artist"){
        this->allSongs.setAllSongs(this->allSongs.ordByArtist(ord));
    }
    reloadSongListData();
}


//Playlist
void MainWindow::addToPlaylist_Clicked(){
    std::string::size_type pos = this->songs_list->currentItem()->text().toStdString().find('-');

    std::string artist = this->songs_list->currentItem()->text().toStdString().substr(0,pos-1);
    std::string title = this->songs_list->currentItem()->text().toStdString().substr(pos+2);

    Song s = this->allSongs.searchSong(title,artist);
    this->playlist.add(s);
    reloadPlaylistData();
}

void MainWindow::removeFromPlaylist_Clicked(){
    std::string::size_type pos = this->playlist_list->currentItem()->text().toStdString().find('-');

    std::string artist = this->playlist_list->currentItem()->text().toStdString().substr(0,pos-1);
    std::string title = this->playlist_list->currentItem()->text().toStdString().substr(pos+2);

    this->playlist.remove(title,artist);
    reloadPlaylistData();
}

void MainWindow::generateRandom()
{
    if(this->allSongs.getAllSongs().size() > 0)
    {
        int ammount = this->random_size->text().toInt();
        try{
            this->playlist.generateRandom(ammount,this->allSongs.getAllSongs());
            reloadPlaylistData();
        }
        catch(std::invalid_argument){
            QMessageBox::warning(this, tr("Message"), tr("Can't generate playlist with 0 songs"));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Message"), tr("Song repository is empty."));
    }
}

void MainWindow::openLinkInBrowser(){
    std::string::size_type pos = this->playlist_list->currentItem()->text().toStdString().find('-');

    std::string artist = this->playlist_list->currentItem()->text().toStdString().substr(0,pos-1);
    std::string title = this->playlist_list->currentItem()->text().toStdString().substr(pos+2);

    Song s{this->playlist.find(title,artist)};
    if(QDesktopServices::openUrl (QUrl(s.getUrl().c_str()))){}
    else
    {
        QMessageBox::warning(this, tr("Message"), tr("Couldn't open link."));
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->type() == QKeyEvent::KeyPress) {

        if(event->matches(QKeySequence::Undo)){
            try{
                this->allSongs.undo();
                reloadSongListData();
            }
            catch(SongException)
            {
                QMessageBox::warning(this, tr("Message"), tr("Can't undo."));
            }
        }
        if(event->matches(QKeySequence::Redo)){
            try{
                this->allSongs.redo();
                reloadSongListData();
            }
            catch(SongException)
            {
                QMessageBox::warning(this, tr("Message"), tr("Can't redo."));
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

