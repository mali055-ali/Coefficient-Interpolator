#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



void readData(const string & fileName, vector<double> & flightPath, vector<double> & coefLift){
    ifstream inF(fileName);
    double num;

    if(!inF.is_open()){
        cout << "Error opening " << fileName << endl;
      exit(EXIT_FAILURE);
    }

    while(inF >> num){
        flightPath.push_back(num);
        inF >> num;
        coefLift.push_back(num);
        inF.ignore();
    }

    inF.close();
}

double interpolation(double angle, const vector<double> & flightPath, const vector<double> & coefLift){
    double b = angle;
    
    if (angle < flightPath.front() || angle > flightPath.back()) {
        cout << "Not within bounds" << endl;
        exit(EXIT_FAILURE);
    }

    //returns if there is already a tested case
    for (unsigned i = 0; i < flightPath.size(); i++){
        if(angle == flightPath.at(i)){
            return coefLift.at(i);
        }
    }

    unsigned i = 0;
    while(flightPath.at(i) < angle){
        i++;
    }

    double a = flightPath.at(i - 1);
    double fa = coefLift.at(i - 1);

    double c = flightPath.at(i);
    double fc = coefLift.at(i);

    double result = fa + ((b - a)/(c - a))*(fc - fa);

    return  result;
}

bool isOrdered(const vector<double> & flightPath){
    for (unsigned i = 1; i < flightPath.size(); i++){
        if(flightPath.at(i - 1) > flightPath.at(i)){
            //cout << "is not in order" << endl;
            return false;
        }
    }
    //cout << "is in order"<< endl;
    return true;
}

void reorder(vector<double> & flightPath, vector<double> & coefLift){
   unsigned i;
   unsigned j;
   unsigned indexSmallest;
   double temp; 

   if (flightPath.empty() || coefLift.empty()) {
      return;
   }
    
   
   for (i = 0; i < flightPath.size() - 1; ++i) {
      
      indexSmallest = i;
      for (j = i + 1; j < flightPath.size(); ++j) {
         
         if (flightPath.at(j) < flightPath.at(indexSmallest)) {
            indexSmallest = j;
         }
      }
      
      temp = flightPath.at(i);
      flightPath.at(i) = flightPath.at(indexSmallest);
      flightPath.at(indexSmallest) = temp;

      temp = coefLift.at(i);
      coefLift.at(i) = coefLift.at(indexSmallest);
      coefLift.at(indexSmallest) = temp;
   }
}





int main(int argc, char *argv[]) {
    string fileName;
    vector<double> flightPath;
    vector<double> coefLift;
    double angle;
    string ask;
    
    fileName = argv[1];

    readData(fileName, flightPath, coefLift);

    // for(unsigned i = 0; i < flightPath.size(); i++){
    //     cout << flightPath.at(i) << ' ' << coefLift.at(i) << endl;

    // }

    if(isOrdered(flightPath) == false){
        reorder(flightPath, coefLift);
    }
    
    // for(unsigned i = 0; i < flightPath.size(); i++){
    //     cout << flightPath.at(i) << ' ' << coefLift.at(i) << endl;

    // }
    
    
    cin >> angle;
    cout << interpolation(angle, flightPath, coefLift) << endl;
    
    cin >> ask;

    while(ask == "Yes" || ask == "yes" || ask == "y"){
        cin >> angle;
        cout << interpolation(angle, flightPath, coefLift) << endl;
        cin >> ask;
    }

    
    return 0;

}