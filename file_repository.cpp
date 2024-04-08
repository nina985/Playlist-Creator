#include "file_repository.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

FileRepository::FileRepository(std::string filepath) :Repository{} //in songs.txt the param are in order: ARTIST,TITLE,YEAR,URL,LYRICS ; all values are in "" ecept for the year :)
{
    this->filepath=filepath;
}

void FileRepository::load(std::string loadFile)
{
    std::ifstream MyFile;
    MyFile.open(loadFile);

    if (!MyFile)
    {
        throw std::invalid_argument("File not found");
        //return;
    }

    //loadFile.copy(this->filepath ,loadFile.size()); //filePath becomes loadFile as that is now where the repo is from and where it will continue being updated

    std::string artist, title, lyrics,url;
    int year;
    std::string text;

    while (!MyFile.eof()) //reads file line by line; text=1line
    {
        getline(MyFile, text);
        if (text.find("ARTIST") != -1)
        {
            int poz = text.find("ARTIST");
            poz += 8; //skips over ARTIST="
            std::string word = " ";

            for (int i = poz; text[i] != '\"'; i++)//until it finds closing quotaion mark
                    if ((text[i] >= 'a' and text[i] <= 'z') or text[i] == ' ' or (text[i] >= 'A' and text[i] <= 'Z'))
                    word += text[i];
            artist += word;
        }
        if (text.find("TITLE") != -1)
        {
            int poz = text.find("TITLE");
            poz += 7;
            std::string word = " ";

            for (int i = poz; text[i] != '\"'; i++)
                    if ((text[i] >= 'a' and text[i] <= 'z') or text[i] == ' ' or (text[i] >= 'A' and text[i] <= 'Z'))
                    word += text[i];
            title += word;
        }
        if (text.find("YEAR") != -1)
        {
            int poz = text.find("YEAR");
            poz+= 5; //skips over YEAR=

            std::string number ="";
            for (int i = poz; text[i] != '\n'; i++)//until it finds newline
                    if (text[i] >= '0' and text[i] <= '9')
                    number += text[i];

            year=std::stoi(number);
        }
        if (text.find("URL") != -1)
        {
            int poz = text.find("URL");
            poz += 5; //skips URL="
            std::string word = " ";

            for (int i = poz; text[i] != '\"'; i++)//until it finds closing quotaion mark
                    word += text[i];
            url += word;
        }

        if (text.find("LYRICS") != -1)
        {
            for(int i=8;i<text.size();i++)
                    if ((text[i] >= 'a' and text[i] <= 'z') or text[i] == ' ' or (text[i] >= 'A' and text[i] <= 'Z'))
                    lyrics += text[i];
            lyrics += " "; //replace "\n" with a space
            while (text != "\"")
            {
                    getline(MyFile, text);
                    lyrics += " ";
                    lyrics += text;
            }
        }

        if (artist != "" && title != "" && lyrics != "" && url !="" && year>0)
        {
            this->songsRepo.push_back(Song{ title, artist, year,lyrics,url });
            artist = ""; title = ""; lyrics = ""; url=""; year=0;
        }
    }
    MyFile.close();
}

void FileRepository::save(std::string saveFile)
{
    std::ofstream outputFile(saveFile , std::ios::app); //append mode
    if (!outputFile) {
        throw std::runtime_error("Couldn't save to file");
        return;
    }
    for (const Song& element : this->songsRepo) {
        outputFile <<"ARTIST=\""+element.getArtist()<<"\"\n"; // " \" " is how to write quotation marks in c++ <3
        outputFile <<"TITLE=\""+element.getTitle()<<"\"\n";
        outputFile <<"YEAR="+element.getYear()<<"\n";
        outputFile <<"URL=\""+element.getUrl()<<"\"\n";
        outputFile <<"LYRICS=\"";
        for (const std::string& word : element.getLyrics()){
            outputFile<<word+' ';
        }
        outputFile <<"\"\n";
    }
    outputFile.close();
}

void FileRepository::store(const Song& s)
{
    this->Repository::store(s);
    this->save(this->filepath);
}
void FileRepository::remove(const Song& s)
{
    this->Repository::remove(s);
    this->save(this->filepath);
}
