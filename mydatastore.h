#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
    public:
    //destructor
    virtual ~MyDataStore();

    //addproduct to data store
    void addProduct(Product* p);

    //adduser to data store
    void addUser(User* u);

    //search
    /* Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
    */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    //dump (Reproduce the database file from the current Products and User values)
    void dump(std::ostream& ofile);

    //addToCart
    void addToCart(std::string username, Product* p);

    //BUYCART
    void buyCart(std::string username);

    //VIEWCART
    void viewCart(std::string username);

    // helper functions

    //getUserPointer
    User* getUserPointer(std::string username);
    

    protected: //data members

    //map of keywords to set of products
    std::map<std::string, std::set<Product*> > keywordMap_;

    //usermap
    std::map<std::string, User*> userMap_;

    //cart
    std::map<std::string, std::vector<Product*> > cartMap_;

    //productvector
    std::vector<Product*> productVec_;


};
#endif
