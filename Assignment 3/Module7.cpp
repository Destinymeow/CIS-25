//Gamer.h
//This file has the declaration of Gamer class, it stores information from the gaming addiction dataset from Kaggle snd displays the data.
#ifndef GAMER_H //class identification
#define GAMER_H

#include <string>
using namespace std;

class Gamer
{
private:
// Data that stores information from the CSV File.
    string userID;
    int age;
    string gender;
    string genre;
    double playtime;

public:
//Default constructor 
    Gamer();
    //Used to initialize all data
    Gamer(string id, int a, string g, string gen, double play);
    // Displays the info for one gamer
    void display();
};

#endif

//Gamer.cpp
//The file in the implementation of the Gamer Class, it defines the constructors and the display function.
#include "Gamer.h"
#include <iostream>
using namespace std;

//Default constructor starts variables.
Gamer::Gamer()
{
    userID = "";
    age = 0;
    gender = "";
    genre = "";
    playtime = 0;
}
//Parameter constructure that assigns the values from the CSV.
Gamer::Gamer(string id, int a, string g, string gen, double play)
{
    userID = id;
    age = a;
    gender = g;
    genre = gen;
    playtime = play;
}
//Displays one gamers information.
void Gamer::display()
{
    cout << "User ID: " << userID << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Preferred Genre: " << genre << endl;
    cout << "Daily Playtime: " << playtime << " hours" << endl;
    cout << "--------------------------------------" << endl;
}

//Main.cpp
//This the program of the gamer information, it reads data from the CSV file. It stores the first 10 records and displays them.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Gamer.h"

using namespace std;

int main()
{
    //Opens the CSV file.
    ifstream file("gaming_addiction.csv");
    //Check if the File was openeing without error.
    if (!file)
    {
        cout << "Error opening file." << endl;
        return 1;
    }
    //Vector used to store Gamer objects.
    vector<Gamer> gamers;

    string line;

    // Skip the header
    getline(file, line);
    //Reads the first 10 lines from the file.
    while (getline(file, line) && gamers.size() < 10)
    {
        //convert the line into a stream.
        stringstream ss(line);

        string userID;
        string ageStr;
        string gender;
        string country;
        string occupation;
        string income;
        string yearsGaming;
        string genre;
        string platform;
        string device;
        string rank;
        string playtimeStr;
        //Read each column (separated with commas)
        getline(ss, userID, ',');       // user_id
        getline(ss, ageStr, ',');       // age
        getline(ss, gender, ',');       // gender
        getline(ss, country, ',');      // skip
        getline(ss, occupation, ',');   // skip
        getline(ss, income, ',');       // skip
        getline(ss, yearsGaming, ',');  // skip
        getline(ss, genre, ',');        // preferred_genre
        getline(ss, platform, ',');     // skip
        getline(ss, device, ',');       // skip
        getline(ss, rank, ',');         // skip
        getline(ss, playtimeStr, ',');  // daily_playtime_hours
        //Convert string into numeric types.
        int age = stoi(ageStr);
        double playtime = stod(playtimeStr);
        //Create a gamer object using the data.
        Gamer gamer(userID, age, gender, genre, playtime);
        //Store the object in the vector.
        gamers.push_back(gamer);
    }
    //Closes the file.
    file.close();
    //Display, so it's known what is being shown.
    cout << "Gaming Addiction and Mental Health Dataset\n";
    cout << "=========================================\n\n";
    //Display all Gamer objects that were stored.
    for (int i = 0; i < gamers.size(); i++)
    {
        gamers[i].display();
    }

    return 0;
}
