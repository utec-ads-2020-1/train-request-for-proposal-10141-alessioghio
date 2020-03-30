#include <iostream>
#include <vector>
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
    vector<pair<int, string>> result;
    int numRFP = 0;
    int p, n;
    float d;
    int r;
    float compliance = 0;
    float maxComp;
    float minPrice;
    std::ifstream file("input.txt");

    while(getline(file, inputLine)){
        // line containing two integers: 0 < n <= 1000
        // n = the number of requirements
        // p = number of proposals
        bool strHasPeriod = find_if(inputLine.begin(), inputLine.end(), 
                            [](unsigned char c) { return (c=='.'); }) != inputLine.end();
        if(inputLine.size() <= 9){
            string::iterator strIter = find_if(inputLine.begin(), inputLine.end(), 
                            [](unsigned char c) { return (c==' '); });
            int index = distance(inputLine.begin(), strIter+1);
            if( !(strHasPeriod) && isdigit(inputLine.c_str()[0]) && isdigit(inputLine.substr(index).c_str()[0])){
                stringstream ss(inputLine);
                ss >> n >> p;
                if (n==0 && p == 0){ // The line 0 0 indicates there are no more RFPs
                    break;
                }
                numRFP++;
                result.push_back(make_pair(numRFP,""));
                maxComp = 0;
                minPrice = numeric_limits<float>::max();
                ss.clear();
                continue;
            }
        }
        if(strHasPeriod){
            d = stof(inputLine, &sz);
            r = stoi(inputLine.substr(sz));
            compliance = (float)r/(float)n;
            if (maxComp == compliance && minPrice > d){
                result[numRFP-1].second = lastInput;
                minPrice = d;
            }else if(maxComp < compliance){
                result[numRFP-1].second = lastInput;
                maxComp = compliance;
                minPrice = d;           
            }
            
        }  
        lastInput = inputLine;
    }
    int size = result.size()-1;
    for (int i = 0; i < size; i++){
        cout << "RFP #" << result[i].first << endl;
        cout << result[i].second << endl << endl;
    }
    cout << "RFP #" << result[size].first << endl;
    cout << result[size].second << endl;
    
    return EXIT_SUCCESS;
}