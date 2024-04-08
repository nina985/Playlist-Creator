#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H
#include "repository.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

class FileRepository: public Repository
{
private:
    std::string filepath;
public:
    FileRepository(std::string filepath); //in songs.txt the param are in order: ARTIST,TITLE,YEAR,URL,LYRICS ; all values are in "" except for the year :)
    void load(std::string loadFile); //loads from a file :)
    void save(std::string saveFile); //saves into a file

    void store(const Song& s) override;
    void remove(const Song& s) override;

    ~FileRepository(){this->Repository::~Repository();}
};

class FileRepoTest
{
public:
    static void testFileRepo()
    {
        FileRepository fR{"./songs2.txt"}; //songs2 is an empty file :)
        try
        {
            fR.find("Title","Artist");
        }
        catch(std::exception){} //exception that was thrown when the song list is empty

        try
        {
            fR.load("songs3.txt");
        }
        catch(std::invalid_argument){} //when load file can't be opened :)

        //fR.load("./songs1.txt");
        //i couldn't get qt creator to open from text files
        //it doesn't find the files and always throws an exception
    }
};

#endif // FILE_REPOSITORY_H
