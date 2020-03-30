#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
using namespace std;

int main(){
    string inputLine;
    string lastInput;
    string::size_type sz;
    string bestProp;
    int numRFP = 0;
    int p, n;
    float d;
    int r;
    float compliance;
    float maxComp;
    float minPrice;
    // fstream file("input.txt");

    while(getline(cin, inputLine)){
        // line containing two integers: 0 < n <= 1000
        // n = the number of requirements
        // p = number of proposals
        if(isdigit(inputLine.c_str()[0])){
            bool strHasPeriod = find(inputLine.begin(), inputLine.end(),'.') != inputLine.end();
            if (!(strHasPeriod)){
                stringstream ss(inputLine);
                ss >> n >> p;
                if (n==0 && p == 0){ // The line 0 0 indicates there are no more RFPs
                    cout << "RFP #" << numRFP << endl << bestProp << endl;
                    break;
                }
                if (numRFP!=0){
                    cout << "RFP #" << numRFP << endl << bestProp << endl << endl;
                }
                numRFP++;
                maxComp = 0;
                minPrice = numeric_limits<float>::max();
                ss.clear();
                continue;
            }else{
                d = stof(inputLine, &sz);
                r = stoi(inputLine.substr(sz));
                compliance = (float)r/(float)n;
                if (maxComp == compliance && minPrice > d){
                    bestProp = lastInput;
                    minPrice = d;
                }else if(maxComp < compliance){
                    bestProp = lastInput;
                    maxComp = compliance;
                    minPrice = d;           
                }
            }            
        }     
        lastInput = inputLine;
    }
    return EXIT_SUCCESS;
}