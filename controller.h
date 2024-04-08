#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "repository.h"
#include "song.h"

#include <assert.h>
#include <utility>
#include <stack>

class Action;

class SongController
{
private:
    Repository& repo;
    std::stack<Action*> undoActions;
    std::stack<Action*> redoActions;

public:
    SongController() :repo{*new Repository{}} {}
    void addToRepo(std::string t, std::string a, int y, std::string l, std::string u);
    const Song& searchSong(std::string t, std::string a);
    void removeFromRepo(Song s);

    std::vector<Song> ordByArtist(std::string ord); //ord represents the order in which the songs will be ordered : increasing or decreasing :)
    std::vector<Song> ordByTitle(std::string ord);

    const Repository& getRepo(){return this->repo;}
    const std::vector<Song>& getAllSongs(){return this->repo.getAll();}
    void setAllSongs(std::vector<Song> r){this->repo.setAll(r);}

    void undo();
    void redo();
    const std::stack<Action*>& getUndo(){return this->undoActions;}
    const std::stack<Action*>& getRedo(){return this->redoActions;}
};

class ControllerTest
{
public:
    static void testController()
    {
        Song s1{"Song lul","the artist idk",985,"lyrics from song hehe ssssong music :)","https://video :)"};
        Song s2{"Title","Artist",2023,"uhh words lalalalala","Link lol"};

        SongController c;
        c.addToRepo("Song lul","the artist idk",985,"lyrics from song hehe ssssong music :)","https://video :)");
        c.addToRepo("Title","Artist",2023,"uhh words lalalalala","Link lol");
        c.addToRepo("","",0,"","");

        assert(c.getAllSongs()[0]==s1);
        assert(c.getAllSongs().size()==3);

        c.addToRepo("A song","Name",2004,"AAAA words ;)","https://link");
        assert(c.getAllSongs().size()==4);

        c.removeFromRepo(Song{"","",0,"",""});
        assert(c.getAllSongs().size()==3);

        assert(c.searchSong("A song","Name").getYear()==2004);
        try
        {
            c.addToRepo("Title","Artist",2025,"lll","uuu");
            c.searchSong("ttt","aaa");
            c.removeFromRepo(Song{"ttt","aaa",7,"",""});
        }
        catch(SongException){}

        std::vector<Song> artistINCR = c.ordByArtist("INCR"); //Artist, Name, the artist idk
        assert(artistINCR[0]==s2);
        assert(artistINCR.size()==3);

        std::vector<Song> artistDECR = c.ordByArtist("DECR");//the artist idk, Name, Artist
        assert(artistDECR[1].getYear()==2004);

        std::vector<Song> titleINCR = c.ordByTitle("INCR");//A song, Song lul, Title
        assert(titleINCR[2]==s2);

        std::vector<Song> titleDECR = c.ordByTitle("DECR");//Title, Song lul,A song
        assert(titleDECR[1]==s1);

    }
};

class Action{
public:
    Action(Repository& r, Song s):repo{r}, song{s}{}
    virtual ~Action() = default;
    virtual void undo() = 0;
    virtual void redo() = 0;

protected:
    Repository& repo;
    Song song;
};

class ActionAdd: public Action{
public:
    ActionAdd(Repository& r, Song s):Action{r, s}{}
    void undo() override{
        repo.remove(song);
    }
    void redo() override{
        repo.store(song);
    }
};

class ActionRemove: public Action{
public:
    ActionRemove(Repository& r, Song s):Action{r, s}{}
    void undo() override{
        repo.store(song);
    }
    void redo() override{
        repo.remove(song);
    }
};

#endif // CONTROLLER_H
