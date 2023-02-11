#include <sstream>
#include <iomanip>
#include <cctype>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing()
{

}

//getters
std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const 
{
    return brand_;
}

//keywords
std::set<std::string> Clothing::keywords() const
{

    //1. get set of keywords from title
    set<string> keywordsAll = parseStringToWords(name_);

    //2. add brand to set
    keywordsAll.insert(convToLower(brand_));
    
    return keywordsAll;
}

//ismatch
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

//displaystring
std::string Clothing::displayString() const
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
    display += "Size: " + size_ + " Brand: " + brand_ + "\n";
    display += shortPrice + " " + to_string(qty_) + " left.";

    return display;
}

//dump
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}




