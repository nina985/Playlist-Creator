#include "song.h"

Song::Song()
{
    this->title="None";
    this->artist="None";
    this->year=0;
    this->url="None";
}

Song::Song(std::string t, std::string a, int y, std::string l, std::string u)
{
        this->title=t;
        this->artist=a;
        this->year=y;
        this->url=u;

        std::string word;
        unsigned int wordCount = 0;
        for (auto x : l)
        {
            if (!((x >= 'a' and x <= 'z')or(x >= 'A' and x <= 'Z') or x=='\n') and x != ' ')
                continue;
            if (x == ' ')
            {
                this->lyrics.push_back(word);
                wordCount++;
                word = "";
            }
            else {
                word += x;
            }
        }
        this->lyrics.push_back(word);
        wordCount++;
}
