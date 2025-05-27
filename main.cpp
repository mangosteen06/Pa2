// Winter'24
// Instructor: Diba Mirza
// Student name: Serafina Wong
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include<chrono>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
    
    
    // Create an object of a STL data-structure to store all the movies
    Movie movie;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){

            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movie.insert(movieName,movieRating);
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            movie.print();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    auto start = chrono::high_resolution_clock::now();
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    vector<Movie> great;
    vector<string> got;
    for(int i=0; i< prefixes.size();i++){
        bool found= movie.prefix(prefixes.at(i),great);
        if(!found){
             cout << "No movies found with prefix "<<prefixes.at(i);
        }else{
            got.push_back(prefixes.at(i));
        }
        cout<<endl;
        
    }
    
    for(int i =0; i < great.size(); i++){
        cout << "Best movie with prefix " << got.at(i) << " is: " <<great.at(i).greatest().getName() << " with rating " << std::fixed << std::setprecision(1) << great.at(i).greatest().getRating() << endl;
    }
    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    auto end = chrono::high_resolution_clock::now();
    double time_ms = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block
  Time complexity: 
Let p be all movies that either start with the same letter as the prefix and let r  be all movies that have the same prefix and have all the same ratings when floored (for example 9.7 and 9.6).  
For part two we are finding the worst case.
I iterate over every prefix so its O(m) and every time I do so, I call the function prefix which at most iterates over every movie that starts with the same letter until we make it to the movies that have the prefix so it at most iterates over all movies with the same letter(O(p)). Every time I do this I print the all the prefixes (O(k)) and call insertRating which iterates over all ratings in those prefix that when floored are the same (O(r))and I insert it into the hash map which should be O(1). I also compare the two movies to see which one comes first alphabetically if they have the same rating so O(l).I also then iterate over all the prefixes again and call to find the greatest one( however this is only O(1) since the hash map would be empty up until we find the greatest rating).In total this means that I have O(m*p*k*r*l +k). 
Actual numbers: (randomized sets)
For the prefix_large: we have 2869.0 ms for the 76920.csv 310 for 1000 csv, 312 for 100 csv, and 208.9 for the 20 csv
For prefix_medium: we have 1072.7 for the 76920.csv 5.8for 1000 csv 0.6 for 100 csv 0.3 for the 20 csv
For prefix_small: we have 188.2 for the 76920.csv 1.1 for 1000 csv 0.1 for 100 csv 0.1  for the 20 csv

Space complexity: 
Since we assume that the prefixes and movies are already stored, the only new things I store is two vectors (one to store the hash maps of the movies that start with the prefix, and another to store the prefixes themselves). So the space complexity is O(mk+k) since a hashmap is O(k) and and the vectors are all O(k)

Briefly state how you designed your algorithm from part 2 of the assignment for the task at hand. More specifically, answer this question:
* Did you design your algorithm for a low time complexity, a low space complexity, or both? What were your target complexities? 
My target was a low time complexity 
Based on your answer to the question above, answer one of the following:
1. If you designed your algorithm for a low time complexity,
    * Were you able to achieve a low space complexity as well?
    * Why or why not?
My space complexity was relatively low but I could’ve probably reduced it even more by using a different data structure instead of two vectors (one holding a hash map as well). However I thought that trying to reduce it even more would increase the time complexity so I decided to stick with this  
*/
//2869.0 310 312 208.9 large 17576
//1072.7 5.8 .6 .3 medium 27
//188.2 1.1 .1 .1 small 3
bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}