#include "playlist.h"
#include <random>
#include <algorithm>

void Playlist::add(Song s){
    this->songsPlaylist.push_back(s);
}
void Playlist::clear(){
    this->songsPlaylist.clear();
}
void Playlist::remove(std::string title, std::string artist){

    auto poz =std::find_if(this->songsPlaylist.begin(), this->songsPlaylist.end(),[title,artist](const Song& elem){return (elem.getArtist()==artist && elem.getTitle()==title);});

    if(poz!=this->songsPlaylist.end())
        this->songsPlaylist.erase(poz);
    else
    {
        std::string msg="The song "+title+" by "+artist+" does not exists"; //if no songs with that title and artist r found :)
        throw SongException(msg.c_str());
    }
}
void Playlist::generateRandom(int n, std::vector<Song> songList){ //if n is greater than or equal to the number of songs already in the song list, this will just return a permutation of the song list
    if(n<=0)
        throw std::invalid_argument("n has to be a pozitive value");
    else
    {
        std::random_device rd;
        std::mt19937 generator(rd());

        std::vector<Song> temp=songList;
        std::shuffle(temp.begin(),temp.end(),generator);

        this->songsPlaylist.clear();
        for(int i=0; i<n && i<temp.size();i++)
        {
            this->songsPlaylist.push_back(temp[i]);
        }
    }
}
