/*  
    Author: Veronika Dmytryk
    Date: Fall 2019
    Description: A client program for testing Binary Search Tree functions
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "BinarySearchTree.h"
#include "FoodItem.h"
using namespace std;

int main(int argc, char *argv[]){
    BinarySearchTree<FoodItem> *tree = new BinarySearchTree<FoodItem>();
    ifstream file;
    clock_t t;
    
    file.open(argv[1]);                                             // gets the file name from the console

    string line;
    getline(file, line);                                            // skips the first line - header
    while(getline(file, line)){    
        FoodItem *item = new FoodItem();                            // creates a new FoodItem
        string token;
        istringstream ss(line);
        getline(ss, token, ',');
        item->setUPC(stoll(token));
        getline(ss, token);
        item->setDescription(token);
        tree->insert(*item);                                        // inserts the newly created FoodItem to the tree
    }

    string code;
    cout<<"Type Q to exit"<<endl;
    while(code != "Q" && code != "q"){                              // continues to run untill a user inputs "Q" or "q"
        cout<<"UPC code: ";
        cin>>code;
        t = clock();                                                // saves current time in miliseconds
        FoodItem neededItem;
        long long UPCcode;
        try{
            UPCcode = stoll(code);                                  // converts a string to long long
        } catch(exception e){
            if(code != "Q" && code != "q")
                cout<<"Invalid input"<<endl;
            continue;
        };
        neededItem.setUPC(UPCcode);
        FoodItem *foundItem = tree->searchNode(neededItem);         // searches for the item in the tree
        if(foundItem){
            t = clock() - t;                                        // calculates passed time in miliseconds
            cout<<foundItem->getDescription()<<endl;
            cout << "Lookup time: " << t << " miliseconds" << endl;
        } else {
            cout<<"Not found"<<endl;
        }
    }
    delete tree;                                                    // releasing the heap memory


    // // Code to check the destructor wierd behavior
    // BinarySearchTree<int> *tree = new BinarySearchTree<int>();
    // tree->insert(57);
    // tree->insert(85);
    // tree->insert(35);
    // tree->insert(9);
    // tree->insert(47);
    // tree->insert(20);
    // tree->insert(26);
    // tree->printInOrder();
    // delete tree;
    // tree->printInOrder();

    return 0; 
}