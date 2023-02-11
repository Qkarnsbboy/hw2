#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) : 
    Product(category, name, price, qty)
{
    ISBN_ = ISBN;
    author_ = author;
}

Book::~Book()
{

}

//getters
std::string Book::getISBN() const
{
    return ISBN_;
}

std::string Book::getAuthor() const 
{
    return author_;
}

//keywords
set<string> Book::keywords() const
{
    //1. declare set of all keywords
    set<string> keywordsAll;

    //2. get set of keywords from title
    set<string> keywordsName = parseStringToWords(name_);

    //3. get set of keywords from author
    set<string> keywordsAuthor = parseStringToWords(author_);

    //4. combine sets using setUnion and setIntersection
    keywordsAll = setUnion(keywordsName, keywordsAuthor);

    //4. add ISBN to set
    keywordsAll.insert(ISBN_);

    return keywordsAll;

}

//ismatch
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

//displaystring
std::string Book::displayString() const
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
    display += "Author: " + author_ + " ISBN: " + ISBN_ + "\n";
    display += shortPrice + " " + to_string(qty_) + " left.";

    return display;
}

//dump
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}




