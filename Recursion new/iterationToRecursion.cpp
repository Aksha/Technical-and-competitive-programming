//Print all subsets of a set: 

#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > printAllSubsets(vector<int> arr)
{
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < arr.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( arr[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    return subset;
}

int main() {
    vector<int> arr = {1,2,3};
    vector<vector<int>> subset = printAllSubsets(arr);
    for(int i = 0; i < subset.size(); i++) {
        for(int j = 0; j < subset[i].size(); j++) {
            cout << subset[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}

/*Result:

1,
2,
1,2,
3,
1,3,
2,3,
1,2,3,
*/
