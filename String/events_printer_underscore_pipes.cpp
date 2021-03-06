/**

Events Printer

Step 1 - Print one event:
Given an event (start time, end time), print this event in the form of a timeline on the screen. The timeline is represented by a series of ‘|’ characters. For example, if an event runs during instants 2-4 (inclusive), there will be ‘|’ on positions 2,3,4 and ‘_’ otherwise. Timeline starts at Instant 0.
Examples:
When input is (3, 5), output should be:
___|||
When input is (1, 4), output should be:
_||||

Step 2 - Print multiple events:
Now that we can print one event, we will move on to printing multiple events. A list of Event tuples will be provided as input and output should be a combined timeline of all events with each event on a new line. The timeline is padded to the right with ‘_’ characters so that all the events extend upto the same point on the screen.
For example, if input list is:
[(3, 5), (1, 4), (7, 10)]
Output is: 
___|||_____
_||||______
_______||||

Step 3 - Merge events:
We will now create a single merged view of all events. So, given a list of events, for any given instant, print a ‘|’ if there is at least one event occurring at that instant or '_' if not
For example, when input is [(3, 5), (1, 4), (7, 10)], output for above will be -
_|||||_||||
Note that we are taking the list of events as input here and not the output from step 2.

[(3, 5), (1, 4), (7, 10)] - sort

[(1,4), (3,5), (7,10)] - merge overlapping intervals

[(1,5),(7,10)]




*/

#include <iostream>
#include <vector>


using namespace std;

string print_event(int start_time, int end_time, int maximum_end_time) {
    string events = "";
    if(start_time < 0 || end_time < 0 || start_time > end_time) {
        return events;
    }
    if(start_time == 0 && end_time == 0) {
        return events;
    }
    for(int i = 0; i <= maximum_end_time; i++) {
        /*cout << "start_time : " << start_time << endl;
        cout << "end_time : " << end_time << endl;*/
        if(i < start_time || i > end_time) {
            events += "_"; // _
        }
        else {
            events += "|"; // _||||
        }
    }
    return events;
}

vector<string> print_multiple_events(vector<pair<int,int>> input) {
    int n = input.size();
    vector<string> events_aggregator;
    if(n == 0)
        return events_aggregator;
    int maximum_end_time = 0;
    for(int i = 0; i < n;i++) {
        if(maximum_end_time < input[i].second){
            maximum_end_time = input[i].second;
        }
    }
    for(int i = 0; i < n; i++) {
        int start_time = input[i].first;
        int end_time = input[i].second;
        //cout << "s "  << start_time << " e " << end_time << endl;
        string events = print_event(start_time,end_time,maximum_end_time);
        events_aggregator.push_back(events);
    }

    //input validation : negative, start time > end time (empty array), only integers, {0,0}
    return events_aggregator;

}

string merge_events(vector<pair<int,int>> input) {
    int n = input.size();
    int maximum_end_time = 0;
    for(int i = 0; i < n;i++) {
        if(maximum_end_time < input[i].second){
            maximum_end_time = input[i].second;
        }
    }
    string events(maximum_end_time+1,-1);
    for(int i = 0; i < n; i++) {
        int start_time = input[i].first;
        int end_time = input[i].second;
        for(int j = 0; j <= maximum_end_time; j++) {
            if((j < start_time || j > end_time) && events[j] != '|' ) {
                events[j] = '_';
            }
            else {
                events[j] = '|';
            }
        }
    }
    return events;
}

int main() {
    vector<pair<int,int>> input_events = {{3, 5}, {1, 4}, {7, 10}};
    vector <string> events_aggregator = print_multiple_events(input_events);
    int n = events_aggregator.size();
    for(int i = 0; i < n; i++) {
        cout << events_aggregator[i] << endl;
    }
    string result = merge_events(input_events);
    cout << "Result : " << result << endl;

    return 0;
}
