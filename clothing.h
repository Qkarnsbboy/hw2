#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
    public:
        Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
        ~Clothing();

        //keywords
        std::set<std::string> keywords() const;

        //ismatch
        bool isMatch(std::vector<std::string>& searchTerms) const;

        //displaystring
        std::string displayString() const;

        //dump
        void dump(std::ostream& os) const;

        //accessors and mutators
        std::string getSize() const;
        std::string getBrand() const;


    protected:
    std::string size_;
    std::string brand_;
        
};
#endif