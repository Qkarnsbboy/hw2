#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) :
    Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{

}

//getters
string Movie::getGenre() const
{
    return genre_;
}

string Movie::getRating() const 
{
    return rating_;
}

//keywords
set<string> Movie::keywords() const
{

    //1. get set of keywords from title
    set<string> keywordsAll = parseStringToWords(name_);

    //2. add genre to set
    keywordsAll.insert(convToLower(genre_));
    
    return keywordsAll;
}

//ismatch
bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

//displaystring
string Movie::displayString() const
{
    string priceString = to_string(price_);
    string shortPrice;

    for(unsigned int i = 0; i < priceString.length(); i++)
    {
        if(priceString[i] == '.')
        {
            shortPrice += priceString[i];
            shortPrice += priceString[i+1];
            shortPrice += priceString[i+2];
            break;
        }
        shortPrice += priceString[i];
    }

    string display = "";
    display += name_ + "\n";
    display += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
    display += shortPrice + " " + to_string(qty_) + " left.";

    return display;
}

//dump
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}




