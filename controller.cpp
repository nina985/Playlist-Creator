#include "controller.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

void SongController::addToRepo(std::string t, std::string a, int y, std::string l, std::string u){
    Song s{t,a,y,l,u};
    this->repo.store(s);
    this->undoActions.push(new ActionAdd{repo, s});
    this->redoActions.push(new ActionAdd{repo, s});
}
const Song& SongController::searchSong(std::string t, std::string a){
    return this->repo.find(t,a);
}

void SongController::removeFromRepo(Song s)
{
    this->repo.remove(s);
    this->undoActions.push(new ActionRemove{repo, s});
    this->redoActions.push(new ActionRemove{repo, s});
}

std::vector<Song> SongController::ordByArtist(std::string ord)
//capital letters < lowercase letters; this function does not account for capitalisation
{
    std::vector<Song> byArtist{this->repo.getAll()};
    if(ord == "INCR")
    {
        std::sort(byArtist.begin(),byArtist.end(),[](const Song& x,const Song& y){return x.getArtist() < y.getArtist();});
        return byArtist;
    }
    else if(ord == "DECR")
    {
        std::sort(byArtist.begin(),byArtist.end(),[](const Song& x,const Song& y){return x.getArtist() > y.getArtist();});
        return byArtist;
    }
    else{
        throw std::invalid_argument("Order can only be INCR or DECR");
    }
}

std::vector<Song> SongController::ordByTitle(std::string ord)
//capital letters < lowercase letters; this function does not account for capitalisation
{
    std::vector<Song> byTitle{this->repo.getAll()};
    if(ord == "INCR")
    {
        std::sort(byTitle.begin(),byTitle.end(),[](const Song& x,const Song& y){return x.getTitle() < y.getTitle();});
        return byTitle;
    }
    else if(ord == "DECR")
    {
        std::sort(byTitle.begin(),byTitle.end(),[](const Song& x,const Song& y){return x.getTitle() > y.getTitle();});
        return byTitle;
    }
    else{
        throw std::invalid_argument("Order can only be INCR or DECR");
    }
}

void SongController::undo(){
    if(!this->undoActions.empty()){
        Action* a = undoActions.top();
        undoActions.pop();
        a->undo();
        delete a;
    }
}

void SongController::redo(){
    if(!this->redoActions.empty()){
        Action* a = redoActions.top();
        redoActions.pop();
        a->redo();
        delete a;
    }
}
