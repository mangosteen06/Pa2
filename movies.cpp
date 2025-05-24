#include "movies.h"
#include <iostream>
void Movie::insert(string movie, double rating){
    int i=0;
    char letter = movie[i];
    bool less= true;
    while(!isalpha(letter)){
        letter = movie[i];
        ++i;
    }
    int value = letter - 97; 
    show Show(movie,rating);
    if(bucket[value].size() == 0){
        bucket[value].push_back(Show);
    }else{
        for (auto it = bucket[value].begin(); it != bucket[value].end(); ++it) {
            if(movie.compare((*it).getName())<=0){
                bucket[value].insert(it,Show);
                less = false;
                break;
            }
        } 
        if(less){
            bucket[value].push_back(Show);
        }
    }
}
void Movie::insertRating(string movie, double rating){
    bool less= true;
    int value = rating;
    show Show(movie,rating);
    if(bucket[value].size() == 0){
        bucket[value].push_back(Show);
    }else{
        for(auto it = bucket[value].begin(); it != bucket[value].end(); ++it) {
            if(rating < (*it).getRating()){
                bucket[value].insert(it,Show);
                less = false;
                break;
            }else if(rating == (*it).getRating()){
                int i =0;
                char letter = movie[i];
                while(!isalpha(letter)){
                    letter = movie[i];
                    ++i;
                }
                if(movie.substr(i).compare((*it).getName())<=0){
                    bucket[value].insert(it,Show);
                 }else{
                    bucket[value].insert(it++,Show);
                 }
                 less = false;
                break;
            }
        } 
        if(less){
            bucket[value].push_back(Show);
        }
    }
}
void Movie::print(){
    for(int i = 0; i< 26; i++){
         for (auto it = bucket[i].begin(); it != bucket[i].end(); ++it) {
           (*it).print();
        } 
    }
    
}

void Movie::printR(){
    for(int i = 10; i>-1; i--){
        for (auto it = bucket[i].rbegin(); it != bucket[i].rend(); ++it) {
           (*it).print();
        } 
    }
    
}

Movie::show Movie::greatest(){
    for(int i = ; i>-1; i--){
        if(!bucket[i].empty()){
            return *prev((bucket[i].end())); 
        }
       
    }

}
bool Movie::prefix(string value, vector<Movie>& great){
    bool found = false;
    char letter = value[0];
    int index = letter -97;
    int length = value.length();
    Movie movie;
      for (auto it = bucket[index].begin(); it != bucket[index].end(); ++it) {
            if((*it).getName().substr(0,length)==value){
                movie.insertRating((*it).getName(),(*it).getRating());
                found = true;
            }
            if(value.compare((*it).getName().substr(0,length))< 0){
                break;
            }
        } 
    great.push_back(movie);
     movie.printR();
     return found;
}