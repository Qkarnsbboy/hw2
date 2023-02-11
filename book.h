#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"

class Book : public Product {
    public:
        Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
        ~Book();

        //keywords
        std::set<std::string> keywords() const;

        //ismatch
        bool isMatch(std::vector<std::string>& searchTerms) const;

        //displaystring
        std::string displayString() const;

        //dump
        void dump(std::ostream& os) const;

        //accessors and mutators
        std::string getISBN() const;
        std::string getAuthor() const;


    protected:
    std::string ISBN_;
    std::string author_;
        
};
#endif