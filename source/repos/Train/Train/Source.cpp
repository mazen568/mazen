#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<sstream>
#include "Trains.h"

using namespace std;
class Trip {
public:
    string date;
    string dest;
    string board;
    int trainNumber;
    int fare;
    int seats;

    Trip(string date, string dest, string board, int trainNumber, int fare, int seats) {
        this->date = date;
        this->dest = dest;
        this->board = board;
        this->trainNumber = trainNumber;
        this->fare = fare;
        this->seats = seats;
    }
};

void writeTrainToFile(vector<Trains> &trains, string filename) {
    ofstream file(filename);

    for (int i = 0; i < trains.size(); i++) {
        file << trains[i].getName() << ' ' << trains[i].getNumber() << endl;
    }

    file.close();
}
void fillTrain() {
    vector<Trains> myclass;
    string name;
    int number;
    cout << "how many trains do you want to add :" << endl;
    int trainsize;
    cin >> trainsize;
    for (int i = 0; i < trainsize; i++) 
    {
        cout << "enter train name : " << endl;
        cin >> name;
        cout << "enter train number : " << endl;
        cin >> number;
        Trains tr(name, number);
        myclass.push_back(tr);
        cout << endl;
    }
    fstream file("trains.txt", ios_base::app);
    string line;
     for (int i = 0; i < myclass.size(); i++)
     {
            file << myclass[i].getName() << ' ' << myclass[i].getNumber() << endl;
     }
    
}

void readTrainFromFile(vector<Trains> &trains, string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string name;
        int number;
        size_t pos = line.find(' ');

        name = line.substr(0, pos);
        number = stoi(line.substr(pos + 1));

        Trains train(name, number);
        trains.push_back(train);
    }

    file.close();
}
vector<string> SplitTrip(string str, char seperator)
{
    int startIndex = 0, endIndex = 0;
    vector<string> strings;
    for (unsigned long int i = 0; i <= str.size(); i++)
    {
        if (str[i] == seperator || i == str.size())
        {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}
vector<string> split(const string& str, char delim) {
    vector<string> result;
    stringstream ss(str);
    string item;

    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}
void readTripFromFile(vector<Trip> &tripsArray, string filename)
{
    /*ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string date, dest, board;
        int trainNumber, fare, seats;
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        size_t pos4 = line.find(",", pos3 + 1);
        size_t pos5 = line.find(",", pos4 + 1);

        date = line.substr(0, pos1);
        dest = line.substr(pos1 + 1, pos2 - pos1 - 1);
        board = line.substr(pos2 + 1, pos3 - pos2 - 1);
        trainNumber = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        fare = stoi(line.substr(pos4 + 1, pos5 - pos4 - 1));
        seats = stoi(line.substr(pos5 + 1));

        Trip trip(date, dest, board, trainNumber, fare, seats);
        trips.push_back(trip);
    }

    file.close();
    */
    ifstream file(filename);
    string line;
    
        while (getline(file, line))
        {
            string date, dest, board;
            int trainNumber, fare, seats;
            vector<string> Splitted = SplitTrip(line,' ');
            date = Splitted[0];
            board = Splitted[1];
            dest = Splitted[2];
            trainNumber = stoi(Splitted[3]);
            seats = stoi(Splitted[4]);
            fare = stoi(Splitted[5]);
            Trip trip(date, dest, board, trainNumber, fare, seats);
            tripsArray.push_back(trip);
            
        }
        file.close();
}
void writeTripToFile(vector<Trip> &trips, string filename) {
    ofstream file(filename);

    for (int i = 0; i < trips.size(); i++) {
        file << trips[i].date << ' ' << trips[i].board << ' ' << trips[i].dest
            << ' ' << trips[i].trainNumber << ' ' << trips[i].seats << ' ' << trips[i].fare << endl;
    }

    file.close();
    
}

void deleteTrainFromVector()
{
    train:
    vector<Trip> trips;
    vector<Trains> trains;
    readTrainFromFile(trains, "trains.txt");
    readTripFromFile(trips, "trips.txt");
    int number;
    int trainDeleted = 1;
    cout << "enter train number: " << endl;
    cin >> number;
    bool trainFound = false;
    for (int i = 0; i < trains.size(); i++) {
        if (trains[i].getNumber() == number) {
            trains.erase(trains.begin() + i);
            trainDeleted = number;
            i--;
            trainFound = true;
        }
    }
    if (!trainFound)
    {
        cout << "this train does not exist!!!" << endl;
        goto train;
    }

    writeTrainToFile(trains, "trains.txt");

    for (int i = 0; i < trips.size(); i++) {
        if (trips[i].trainNumber == trainDeleted) {//lma by delete mn el train lazm y el trip el 3ndha el train dh
            trips.erase(trips.begin() + i);
            i--;
        }
    }
    writeTripToFile(trips, "trips.txt");
   /* bool replaceTrip = true;
    while (replaceTrip)
    {
        for (int i = 0; i < trains.size(); i++) {
            cout << "train " << i + 1 << " name : " << trains[i].getName() << " number :" << trains[i].getNumber() << endl;
        }
        cout << endl;
        int newNumber;
        cout << "Enter new train number: ";
        cin >> newNumber;
        bool tripFound = false;
        for (int i = 0; i < trips.size(); i++) {
            if (trips[i].trainNumber == trainDeleted) {
                trips[i].trainNumber = newNumber;
            }
        }

        writeTripToFile(trips, "trip.txt");

        cout << "Do you want to replace another trip? (y/n): ";
        char response;
        cin >> response;

        if (response != 'y' && response != 'Y') {
            replaceTrip = false;
        }
    }*/
}
void displayTrains() {
    vector<Trains> trains;
    readTrainFromFile(trains,"trains.txt");
    for (int i = 0; i < trains.size(); i++) {
        cout << "train " << i + 1 << " name : " << trains[i].getName() << " number :" << trains[i].getNumber() << endl;
    }
}
int main() {


    
    vector<Trip> trips;
    //fillTrain();
   //displayTrains();
    //deleteTrainFromVector();
    //readTripFromFile(trips,"trip.txt");
    //writeTripToFile(trips, "trains.txt");
    displayTrains();
    



    return 0;
}