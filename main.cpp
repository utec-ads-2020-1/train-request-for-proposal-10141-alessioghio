#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
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
    float maxComp = 0;

    while(getline(cin, inputLine)){
        // line containing two integers: 0 < n <= 1000
        // n = the number of requirements
        // p = number of proposals
        if(inputLine.size() == 3 && isdigit(inputLine.c_str()[0]) && isdigit(inputLine.c_str()[2])){
            stringstream ss(inputLine);
            ss >> n >> p;
            if (n==0 && p == 0){ // The line 0 0 indicates there are no more RFPs
                break;
            }
            numRFP++;
            result.push_back(make_pair(numRFP,""));
            ss.clear();
            continue;
        }
        bool strHasFloat = find_if(inputLine.begin(), inputLine.end(), 
                            [](unsigned char c) { return (c=='.'); }) != inputLine.end();
        if(strHasFloat){
            d = stof(inputLine, &sz);
            r = stoi(inputLine.substr(sz));
            compliance = (float)r/(float)n;
        }
        if(maxComp < compliance){
            result[numRFP-1].second = lastInput;
            maxComp = compliance;
        }
        lastInput = inputLine;
        // Each requirement is a string up to 80 characters long
        // terminated by the end of line
    }
    
    for (int i = 0; i < result.size(); i++){
        cout << "RFP #" << result[i].first << endl;
        cout << result[i].second << endl << endl;
    }
    
    return EXIT_SUCCESS;
}