#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include <queue>

using namespace std;

MyDataStore::~MyDataStore(){
    //1. delete products
    for(unsigned int i = 0; i < productVec_.size(); i++)
    {
        delete productVec_[i];
    }

    //2. delete users
    typename map<string,User*>::iterator it;
    for(it = userMap_.begin(); it != userMap_.end(); ++it)
    {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    //1. push_back on productVec
    productVec_.push_back(p);

    //2. create a set of keys and save product's keywords
    set<string> keys = p->keywords();

    //3. iterate thorugh keys
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        //check in keywordMap
        //4. if keyword already exists
        if(keywordMap_.find(*it) != keywordMap_.end())
        {
            //add product to existing vector
            keywordMap_.find(*it)->second.insert(p);
        }
        //5. otherwise put in keywordMap
        else {
            set<Product*> product_list;
            product_list.insert(p);
            keywordMap_.insert(make_pair(*it, product_list));
        }
    }

}

void MyDataStore::addUser(User* u) {
    //1. if user already exists --> do nothing
    if(userMap_.find(u->getName()) != userMap_.end())
    {
        return;
    }
    //2. else --> add user to userMap_ with (name, User*)
    else{
        userMap_.insert(make_pair(u->getName(), u));

        //add username to cartmap too (w/ empty cart)
        vector<Product*> cartList;
        cartMap_.insert(make_pair(u->getName(), cartList));
    }
    
}

//ADDCART
void MyDataStore::addToCart(string username, Product* p)
{
    //exit if no user
    if(userMap_.find(username) == userMap_.end())
    {
        cout << "Invalid request" << endl;
        return;
    }

     //1. find username
    if(userMap_.find(username) != userMap_.end())
    {
        //3. add to cart (aka product vector)
        cartMap_.find(username)->second.push_back(p);
    }
    else{ //cant find username
        cout << "Invalid username" << endl;
        return;
    }

}

//BUYCART
void MyDataStore::buyCart(string username){

    //exit if no user
    if(userMap_.find(username) == userMap_.end())
    {
        cout << "Invalid username" << endl;
        return;
    }

    //1. find userPointer
    User* u = getUserPointer(username);

    //find users cart
    if(cartMap_.find(username) != cartMap_.end())
    {
        //2. iterate through cart
        for(unsigned int i = 0; i < cartMap_.find(username)->second.size(); i++)
        {
            //if item in stock
            if(cartMap_.find(username)->second[i]->getQty() > 0)
            {
                //&& user has enough money
                if(u->getBalance() > cartMap_.find(username)->second[i]->getPrice())
                {
                    //product price debited from user
                    u->deductAmount(cartMap_.find(username)->second[i]->getPrice());

                    //qty reduced by 1
                    cartMap_.find(username)->second[i]->subtractQty(1);
                }
                else{
                    //remove from cart
                    cartMap_.find(username)->second.erase(cartMap_.find(username)->second.begin()+i);
                } 
            }
            
        }
    }
    else { //couldnt find user
        cout << "Invalid request" << endl;
        return;
    }
    //deallocate product from cart
}
    
//VIEWCART
void MyDataStore::viewCart(string username) {

    //exit if no user
    if(userMap_.find(username) == userMap_.end())
    {
        cout << "Invalid username" << endl;
        return;
    }

    //1. find users cart
    if(cartMap_.find(username) != cartMap_.end())
    {
        //3. iterate through cart
        for(unsigned int i = 0; i < cartMap_.find(username)->second.size(); i++)
        {
            cout << "Item " << (i+1) << endl;
            cout << cartMap_.find(username)->second[i]->displayString() << endl;
        }
    }
    //couldnt find user
    else
    {
        cout << "Invalid username" << endl;
        return;
    }
}

//getUserPointer helper function
User* MyDataStore::getUserPointer(string username)
{
    //1. iterate through usermap
    for(map<string,User*>::iterator it = userMap_.begin(); it != userMap_.end(); ++it)
    {
        //2. find username
        if(it->first == username)
        {
            return it->second;
        }
    }
    
    // cout << "Couldn't find user" << endl;
    return nullptr;
}

/* Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
*/
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {

    // cout << "Search function: " << endl;

    // cout << "Printing keyword map" << endl;
    // //print out keywordMap
    // for( map<string, set<Product*> >::iterator it = keywordMap_.begin(); it != keywordMap_.end(); ++it)
    // {
    //     cout << it->first << ", " << it->second.size() << endl;
    // }   

    //declare result vector
    vector<Product*> results;
    
    //declare result product set
    set<Product*> intersect;

    //create temp set
    set<Product*> temp;
    
    //1. If type 0 --> AND search (intersection of results)
    if(type == 0)
    {
        //empty terms vector
        if(terms.size()==0){
            cout << "empty terms vector!" << endl;
            return results;
        }

        //set temp to product vector for first keyword
        temp = keywordMap_[terms[0]];
        //A. iterate through terms vector
        for(unsigned int i = 0; i < terms.size(); i++)
        {
            //find term in keyword map
            map<string,set<Product*>>:: iterator it = keywordMap_.find(terms[i]);
            if(it != keywordMap_.end())
            {
                //intersect = product vector of that keyword
                intersect = it->second;

                //and both the intersect and temp
                temp = setIntersection(intersect, temp);
            }

        } 
        //B. iterate through temp and add to result vector
        for(set<Product*>::iterator it2 = temp.begin(); it2 != temp.end(); ++it2)
        {
            // --> add current product to end of vector
            results.push_back(*it2);
        }
    }
    //2. If type 1 --> OR search (union of results)
    else{
        //empty terms vector
        if(terms.size()==0){
            cout << "Empty terms vector!" << endl;
            return results;
        }

        //set temp to product vector for first keyword
        temp = keywordMap_[terms[0]];
        //A. iterate through terms vector
        for(unsigned int i = 0; i < terms.size(); i++)
        {
            //find term in keyword map
            map<string,set<Product*>>:: iterator it = keywordMap_.find(terms[i]);
            if(it != keywordMap_.end())
            {
                //intersect = product vector of that keyword
                intersect = it->second;

                //and both the intersect and temp
                temp = setUnion(intersect, temp);
            }

        } 
        //B. iterate through temp and add to result vector
        for(set<Product*>::iterator it2 = temp.begin(); it2 != temp.end(); ++it2)
        {
            // --> add current product to end of vector
            results.push_back(*it2);
        }
    }

    return results;
}

//QUIT
void MyDataStore::dump(std::ostream& ofile) {
    //1. print all products (using their dump)
    ofile << "<products>" << endl;
    //1a. iterate through productvector
    for(unsigned int i = 0; i < productVec_.size(); i++)
    {
        //dump products into ofile
        productVec_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;

    //2. print out all users
    ofile << "<users>" << endl;
    typename map<string,User*>::iterator it;
    for(it = userMap_.begin(); it != userMap_.end(); ++it)
    {
        //dump user* into ofile
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;


}