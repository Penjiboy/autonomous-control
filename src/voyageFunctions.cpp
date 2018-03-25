


// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math>

using namespace std;

ifstream mainPoints ("wayPoints.txt");
ifstream upperPoints ("upperPoints.txt");
ifstream lowerPoints ("lowerPoints.txt");

queue<vector<double>> lowerQueue;
queue<vector<double>> lowerQueue;
queue<vector<double>> mainQueue;

void main () {

string line
double latitude;
double longitude;

/*--------------Making main queue--------*/
 if (mainPoints.is_open()) {

    while (getline(mainPoints,line)){
     //Reading Longitude and Longitde
    istringstream iss(line);
    int flag = 1;
    do
    {
        string subs;
        iss >> subs;

        if (flag == 1){
        latitude = std::stod(subs);
        flag = 2;
        }
        else
        longitude = std::stod(subs);

    } while (iss); 

   //Creating Coordinate 
   vector<double> coordinates;
   coordinates.push_back(latitude);
   coordinates.push_back(longitude);
  
   //Adding coordinate to queue
   mainQueue.push(coordinates);
   
   }
}
mainPoints.close();

/*--------------Making upper queue--------*/
 if (upperPoints.is_open()) {

    while (getline(upperPoints,line)){
     //Reading Longitude and Longitde
    istringstream iss(line);
    int flag = 1;
    do
    {
        string subs;
        iss >> subs;

        if (flag == 1){
        latitude = std::stod(subs);
        flag = 2;
        }
        else
        longitude = std::stod(subs);

    } while (iss); 

   //Creating Coordinate 
   vector<double> coordinates;
   coordinates.push_back(latitude);
   coordinates.push_back(longitude);
  
   //Adding coordinate to queue
   upperQueue.push(coordinates);
   
   }
}
upperPoints.close();


/*--------------Making lower queue--------*/
 if (lowerPoints.is_open()) {

    while (getline(lowerPoints,line)){
     //Reading Longitude and Longitde
    istringstream iss(line);
    int flag = 1;
    do
    {
        string subs;
        iss >> subs;

        if (flag == 1){
        latitude = std::stod(subs);
        flag = 2;
        }
        else
        longitude = std::stod(subs);

    } while (iss); 

   //Creating Coordinate 
   vector<double> coordinates;
   coordinates.push_back(latitude);
   coordinates.push_back(longitude);
  
   //Adding coordinate to queue
   lowerQueue.push(coordinates);
   
   }
}
lowerPoints.close();


//Check every 20 m once gps is pinged 
if(!checkLine)
rudderAngle =  newRudderAngle(gps, lower, upper,main); //send this angle to rudder control


}







/*
*  Method that finds the distance between two coordinates
*/
double distance(vector<double> gps, vector<double> dest){

return sqrt( (dest[1] - gps[1])*(dest[1] - gps[1]) 
          + (dest[0]- gps[0])*(dest[0] - gps[0]));
 

}

double deviatationAngle(vector<double> gps, vector<double> dest){


return arctan(slope(gps,dest));



}

/*
* Method that checks whether the point lies on the same line formed by point1 and point 2
*/
bool checkLine( vector<double> point, vector<double> point1, vector<double> point2){

    return slope(point1, point2) == slope(point, point1);




}

/*
* Method that returns the slope between point1 and point2
*/
double slope(vector<double> point1, vector<double> point2){
   
   return (point2[1] - point1[1]) / (point2[0] - point1[0]) ;


}


/*
* Method that reurns the new rudder angle that the rudder should turn to when deviated due to cuurents
*
*/
double newRudderAngle(vector<double> gps, vector<double> lower, vector<double> upper, vector<double> main){

  if(slope(gps, main) > 0 ){

   if(distance(gps,lower) < distance(gps, main))
      return deviatationAngle(gps, lower); //send this angle to rudder control to the turn the ship in this angle
   else
      return deviatationAngle(gps, main);
   }
else{
   
    if(distance(gps,upper) < distance(gps, main))
      return deviatationAngle(gps, upper); //send this angle to rudder control to the turn the ship in this angle
   else
      return deviatationAngle(gps, main);
   }

}