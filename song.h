#ifndef SONG_H
#define SONG_H
#include <string>
#include <vector>
#include <assert.h>

class Song
{
private:
    std::string title;
    std::string artist;
    int year;
    std::vector<std::string> lyrics;
    std::string url;

public:
    Song();
    Song(std::string t, std::string a, int y,std::string l, std::string u); //makes lyric vector from string

    std::string getTitle() const {return this->title;}
    std::string getArtist() const {return this->artist;}
    std::vector<std::string> getLyrics() const {return this->lyrics;}
    int getYear() const {return this->year;}
    std::string getUrl() const {return this->url;}

    friend bool operator== (const Song& s1, const Song& s2)
    {
        if (s1.getArtist() == s2.getArtist() and s1.getLyrics() == s2.getLyrics() and s1.getTitle() == s2.getTitle() && s1.getYear() == s2.getYear() && s1.getUrl() == s2.getUrl())
            return true;
        else
            return false;
    }
    friend bool operator!= (const Song& s1, const Song& s2)
    {
        return !(s1 == s2);
    }
};

class SongException: public std::exception
{
private:
    const char* message;
public:
    SongException(const char * msg) : message(msg) {}
    const char* what(){
        return message;
    }
};


class SongTest
{
public:
    static void testSong()
    {
        std::string t,a,l,u;
        a="artist idk";
        t="song lul";
        l="lyrics from song hehe ssssong music :)";
        u="https://video :)";
        int y=985;
        Song s{t,a,y,l,u};

        assert(s.getArtist()=="artist idk");
        assert(s.getYear()==985);
        assert(s.getLyrics().size()==7);
        assert(s.getLyrics()[1]=="from");
    }
};

#endif // SONG_H
