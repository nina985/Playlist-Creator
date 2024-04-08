#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "song.h"
#include <vector>
#include <assert.h>

class Repository
{
protected:
    std::vector<Song> songsRepo;

public:
    Repository();
    Repository(const Repository &other)=delete; //copy constructor
    Repository & operator=(const Repository &other)=delete; //asignment operator

    Repository(Repository&& other); //move constructor
    Repository & operator=(Repository&& other)=default; //move operator

    const std::vector<Song>& getAll(){return this->songsRepo;}
    void setAll(std::vector<Song> r){this->songsRepo=r;}

    virtual void store(const Song& s);
    const Song& find(std::string t, std::string a);
    virtual void remove(const Song& s);

    virtual ~Repository(){std::vector<Song>().swap(songsRepo);}
};

class RepoTest
{
public:
    static void testRepo()
    {
        Repository r;
        Song s1{"song lul","artist idk",985,"lyrics from song hehe ssssong music :)","https://video :)"};
        Song s2{"Title","Artist",2023,"uhh words lalalalala","Link lol"};
        Song s3;

        r.store(s1);
        r.store(s2);
        assert(r.getAll()[0]==s1);
        assert(r.getAll()[1]==s2);
        assert(r.find("Title","Artist")==s2);
        assert(r.find("song lul","artist idk").getYear()==985);
        r.remove(s2);
        try
        {
            std::string s= r.find("Title","Artist").getArtist();
            r.remove(s3);
        }
        catch(SongException){}
    }
};

#endif // REPOSITORY_H
