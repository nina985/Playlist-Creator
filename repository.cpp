#include <algorithm>
#include <utility>
#include "repository.h"

Repository::Repository(){}

Repository::Repository(Repository&& other)
{
    this->songsRepo=other.songsRepo;
}

void Repository::store(const Song &s){
    if(this->songsRepo.size()!=0)//if not empty
    {
        for(auto elem = this->songsRepo.begin(); elem != this->songsRepo.end(); ++elem)
            if(s.getTitle()==elem->getTitle() && s.getArtist()==elem->getArtist())
            {
                std::string msg="A song "+s.getTitle()+" by "+s.getArtist()+" already exists";
                throw SongException(msg.c_str());
            }
    }
    songsRepo.push_back(s);
}

const Song& Repository::find(std::string t, std::string a)
{
    if(this->songsRepo.size()!=0)
    {
        auto it =std::find_if(this->songsRepo.begin(), this->songsRepo.end(),[t,a](const Song& elem){return (elem.getArtist()==a && elem.getTitle()==t);});

        if(it!=this->songsRepo.end())
        {
            return *it;
        }
        else
        {
            std::string msg="The song "+t+" by "+a+" does not exists"; //if no songs with that title and artist r found :)
            throw SongException(msg.c_str());
        }
    }
    else
    {
        throw std::exception("list empty");
    }
}
void Repository::remove(const Song& s){
    std::vector<Song>::iterator poz =std::find(this->songsRepo.begin(), this->songsRepo.end(),s);
    if(poz!=this->songsRepo.end())
        this->songsRepo.erase(poz);
    else
    {
        std::string msg="The song "+s.getTitle()+" by "+s.getArtist()+" does not exists"; //if no songs with that title and artist r found :)
        throw SongException(msg.c_str());
    }
}
