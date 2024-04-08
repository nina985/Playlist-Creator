#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "song.h"
#include <vector>
#include <stdexcept>

class Playlist
{
protected:
    std::vector<Song> songsPlaylist;
public:
    Playlist(): songsPlaylist{*new std::vector<Song>}{}

    const std::vector<Song>& getAll(){return this->songsPlaylist;}
    void setAll(std::vector<Song> p){this->songsPlaylist=p;}

    void add(Song s);
    void clear();
    void remove(std::string title, std::string artist);
    void generateRandom(int n, std::vector<Song> songList);

    const Song& find(std::string t, std::string a)
    {
        if(this->songsPlaylist.size()!=0)
        {
            auto it =std::find_if(this->songsPlaylist.begin(), this->songsPlaylist.end(),[t,a](const Song& elem){return (elem.getArtist()==a && elem.getTitle()==t);});

            if(it!=this->songsPlaylist.end())
            {
                return *it;
            }
            else
            {
                std::string msg="The song "+t+" by "+a+" does not exists"; //if no songs with that title and artist are found :)
                throw SongException(msg.c_str());
            }
        }
        else
        {
            throw std::exception("list empty");
        }
    }
};

class PlaylistTest
{
public:
    static void testPlayList()
    {
        Song s1{"Song lul","the artist idk",985,"lyrics from song hehe ssssong music :)","https://video :)"};
        Song s2{"Title","Artist",2023,"uhh words lalalalala","Link lol"};
        Song s3{"A song","Name",2004,"AAAA words ;)","https://link"};
        Song s4("Title1","Artist",2023,"uhh words lalalalala","Link lol");
        Song s5("Title2","Artist",2023,"uhh words lalalalala","Link lol");
        Song s6("Title3","Artist",2023,"uhh words lalalalala","Link lol");

        std::vector<Song> s{s1,s2,s3,s4,s5,s6};//size of s is 6

        Playlist p;
        p.add(s1);
        p.add(s2);
        p.add(s3);

        assert(p.getAll().size()==3);  //size of p is 3
        assert(p.getAll()[0]==s1);

        p.remove("Title","Artist");
        assert(p.getAll().size()==2);  //size of p is 2
        assert(p.getAll()[1]==s3);

        try
        {
            p.remove("Title3","Artist");
        }
        catch(SongException){}

        p.generateRandom(3,s);
        assert(p.getAll().size()==3);
        try
        {
            p.generateRandom(-1,s);
        }
        catch(std::invalid_argument){}

        p.clear();
        assert(p.getAll().size()==0);
    }
};

#endif // PLAYLIST_H
