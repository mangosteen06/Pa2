
// Serafina Wong, 5/22
#ifndef MOVIES_H
#define MOVIES_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

class Movie{
 private:
    struct show{
        double rating;
        string name;
        show(string movie, double rate) : rating(rate), name(movie) { }
        string getName(){
        return name;
        }   
        double getRating(){
        return rating;
        }    
        void print(){
            cout<< name <<", "<< rating<<endl;
        } 
    };
    
    vector<list<show>> bucket; 
 public:
    void insert(string movie,double rating);  
    void print();
    void printR();
    bool prefix(string value,vector<Movie>& great);
    show greatest();
    void insertRating(string movie, double rating);
    Movie(){
        bucket.resize(28);
    }
};

#endif