#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//FUNCTIONS
bool doRepeat(char c)
{
    bool repeat;
    bool isValid;
    char r;
do
{
    isValid = true;

    if ((char) tolower(c) == 'y' || (char) tolower(r) == 'y')
    {
        repeat = true;
    }
    else if ((char) tolower(c) == 'n' || (char) tolower(r) == 'n')
    {
        repeat = false;
        exit(0);
    }
    else
    {
        cout << "Invalid input." << endl;
        cout << "Input again (y/n)" << endl;
        cin >> r;
        isValid = false;
    }

} while (!isValid);

    return repeat;
}


void firstComeAlgo( int n, vector<int> at, vector<int> bt)
{
    int arrivalTime[n];
    std::copy(at.begin(), at.end(), arrivalTime);

    int burstTime[n];
    std::copy(bt.begin(), bt.end(), burstTime);

    int waitingTime[n];
    int completionTime[n];
    int turnAroundTime[n];
    int processes[n];

    int temp;
    float aveWT = 0;
    float aveTT = 0;


//SORT ARRIVAL TIME

    for( int i = 0; i <= n; i++ )
    {
        processes[i] = i + 1;
    }

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( arrivalTime[j] > arrivalTime[j + 1] )
            {
                swap( arrivalTime[j], arrivalTime[j + 1] );
                swap( burstTime[j], burstTime[j + 1] );

                swap( processes[j], processes[j + 1] );
            }
        }
    }

    cout << "\nPROCESSES SORTED\n";

    for ( int p : processes )
    {
        cout << p << " ";
    }

//WAITING TIME

    waitingTime[0] = 0;
    completionTime[0] = arrivalTime[0] + burstTime[0];

    for ( int i = 1; i < n; i++)
    {
        waitingTime[i] = completionTime[i-1] - arrivalTime[i];

        if ( waitingTime[i] < 0 )
        {
            waitingTime[i] = 0;
        }
        
        completionTime[i] = burstTime[i] + arrivalTime[i] + waitingTime[i];

    }

//TURNAROUND TIME

    for( int i = 0; i < n; i++)
    {
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
    }

//UNSORT PROCESSES

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( processes[j] > processes[j + 1] )
            {
                swap( processes[j], processes[j + 1] );

                swap( turnAroundTime[j], turnAroundTime[j + 1] );
                swap( waitingTime[j], waitingTime[j + 1] );
                swap( completionTime[j], completionTime[j + 1]);
            }
        }
    }

//DISPLAY RESULTS

    cout << "\nWaiting Time\t Turnaround Time";

    for ( int i = 0; i < n; i++ )
    {
        aveWT += waitingTime[i];
        aveTT += turnAroundTime[i];

        cout << "\nP" << i + 1 << ": " << waitingTime[i]
        << "\t\tP" << i + 1 << ": " << turnAroundTime[i];
    }

    aveWT /= n;
    aveTT /= n;
    cout << "\n\nAverage Waiting Time: " << aveWT;
    cout << "\nAverage Turnaround Time: " << aveTT;
}


//SHORTEST JOB FIRST

void shortestJobAlgo( int n, vector<int> at, vector<int> bt)
{
    int arrivalTime[n];
    std::copy(at.begin(), at.end(), arrivalTime);

    int burstTime[n];
    std::copy(bt.begin(), bt.end(), burstTime);

    int waitingTime[n];
    int completionTime[n];
    int turnAroundTime[n];
    int processes[n];

    int temp;
    int tempBT;
    float aveWT = 0;
    float aveTT = 0;


//SORT ARRIVAL TIME

    for( int i = 0; i <= n; i++ )
    {
        processes[i] = i + 1;
    }

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( arrivalTime[j] > arrivalTime[j + 1])
            {
                swap( arrivalTime[j], arrivalTime[j + 1] );
                swap( burstTime[j], burstTime[j + 1] );

                swap( processes[j], processes[j + 1] );
            }
            else if ( arrivalTime[j] == arrivalTime[j + 1] ) //condition for equal arrival times
            {
                if ( burstTime[j] > burstTime[j + 1] )
                {
                    swap( arrivalTime[j], arrivalTime[j + 1] );
                    swap( burstTime[j], burstTime[j + 1] );

                    swap( processes[j], processes[j + 1] );
                }
            }
        }
    }

//SORT BY CURRENT TIME

    int minimumBT = burstTime[0];

    for( int startIndex = 1; startIndex < n; startIndex++ )
    {
        int endIndex = startIndex;

        if ( minimumBT > n ) //burst time should not exceed array
        {
            minimumBT = n;
        }

        while ( arrivalTime[endIndex] <= minimumBT )
        {
            for( int i = startIndex; i <= endIndex; i++ )
            {
                for( int j = startIndex; j <= endIndex - i; j++ )
                {
                    if( burstTime[j] > burstTime[j + 1] )
                    {
                        swap( burstTime[j], burstTime[j + 1] );
                        swap( arrivalTime[j], arrivalTime[j + 1] );

                        swap( processes[j], processes[j + 1] );
                    }
                }
            }
            endIndex++;
        }

        minimumBT = burstTime[endIndex];
    }

    cout << "\nPROCESSES SORTED\n";

    for ( int p : processes )
    {
        cout << p << " ";
    }
    
//WAITING TIME

    waitingTime[0] = 0;
    completionTime[0] = arrivalTime[0] + burstTime[0];

    for ( int i = 1; i < n; i++)
    {
        waitingTime[i] = completionTime[i-1] - arrivalTime[i];

        if ( waitingTime[i] < 0 )
        {
            waitingTime[i] = 0;
        }
        
        completionTime[i] = burstTime[i] + arrivalTime[i] + waitingTime[i];

    }

//TURNAROUND TIME

    for( int i = 0; i < n; i++)
    {
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
    }

//UNSORT PROCESSES

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( processes[j] > processes[j + 1] )
            {
                swap( processes[j], processes[j + 1] );

                swap( turnAroundTime[j], turnAroundTime[j + 1] );
                swap( waitingTime[j], waitingTime[j + 1] );
                swap( completionTime[j], completionTime[j + 1]);
            }
        }
    }

//DISPLAY RESULTS

    cout << "\nWaiting Time\t Turnaround Time";

    for ( int i = 0; i < n; i++ )
    {
        aveWT += waitingTime[i];
        aveTT += turnAroundTime[i];

        cout << "\nP" << i + 1 << ": " << waitingTime[i]
        << "\t\tP" << i + 1 << ": " << turnAroundTime[i];
    }

    aveWT /= n;
    aveTT /= n;
    cout << "\n\nAverage Waiting Time: " << aveWT;
    cout << "\nAverage Turnaround Time: " << aveTT;
}

//PRIORITY

void priorityAlgo( int n, vector<int> at, vector<int> bt, vector<int> pn )
{
    int arrivalTime[n];
    std::copy(at.begin(), at.end(), arrivalTime);

    int burstTime[n];
    std::copy(bt.begin(), bt.end(), burstTime);

    int priorityNum[n];
    std::copy(pn.begin(), pn.end(), priorityNum);

    int waitingTime[n];
    int completionTime[n];
    int turnAroundTime[n];
    int processes[n];

    int temp;
    int tempBT;
    float aveWT = 0;
    float aveTT = 0;


//SORT ARRIVAL TIME

    for( int i = 0; i <= n; i++ )
    {
        processes[i] = i + 1;
    }

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( arrivalTime[j] > arrivalTime[j + 1])
            {
                swap( arrivalTime[j], arrivalTime[j + 1] );
                swap( burstTime[j], burstTime[j + 1] );
                swap( priorityNum[j], priorityNum[j + 1] );

                swap( processes[j], processes[j + 1] );
            }
            else if ( arrivalTime[j] == arrivalTime[j + 1] ) //condition for equal arrival times
            {
                if ( priorityNum[j] > priorityNum[j + 1] )
                {
                    swap( priorityNum[j], priorityNum[j + 1] );
                    swap( arrivalTime[j], arrivalTime[j + 1] );
                    swap( burstTime[j], burstTime[j + 1] );

                    swap( processes[j], processes[j + 1] );
                }
            }
        }
    }

//SORT BY CURRENT TIME

    int minimumBT = burstTime[0];

    for( int startIndex = 1; startIndex < n; startIndex++ )
    {
        int endIndex = startIndex;

        if ( minimumBT > n ) //burst time should not exceed array
        {
            minimumBT = n;
        }

        while ( arrivalTime[endIndex] <= minimumBT )
        {
        // std::sort( burstTime + startIndex, burstTime + endIndex );

            for( int i = startIndex; i <= endIndex; i++ )
            {
                for( int j = startIndex; j <= endIndex - i; j++ )
                {
                    if( priorityNum[j] > priorityNum[j + 1] )
                    {
                        swap( priorityNum[j], priorityNum[j + 1] );
                        swap( burstTime[j], burstTime[j + 1] );
                        swap( arrivalTime[j], arrivalTime[j + 1] );

                        swap( processes[j], processes[j + 1] );
                    }
                }
            }
            endIndex++;
        }

        minimumBT = burstTime[endIndex];
    }

    cout << "\nPROCESSES SORTED\n";

    for ( int p : processes )
    {
        cout << p << " ";
    }
    
//WAITING TIME

    waitingTime[0] = 0;
    completionTime[0] = arrivalTime[0] + burstTime[0];

    for ( int i = 1; i < n; i++)
    {
        waitingTime[i] = completionTime[i-1] - arrivalTime[i];

        if ( waitingTime[i] < 0 )
        {
            waitingTime[i] = 0;
        }
        
        completionTime[i] = burstTime[i] + arrivalTime[i] + waitingTime[i];

    }

//TURNAROUND TIME

    for( int i = 0; i < n; i++)
    {
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
    }

//UNSORT PROCESSES

    for( int i = 0; i < n - 1; i++ )
    {
        for( int j = 0; j < n - i - 1; j++ )
        {
            if( processes[j] > processes[j + 1] )
            {
                swap( processes[j], processes[j + 1] );

                swap( turnAroundTime[j], turnAroundTime[j + 1] );
                swap( waitingTime[j], waitingTime[j + 1] );
                swap( completionTime[j], completionTime[j + 1]);
            }
        }
    }

//DISPLAY RESULTS

    cout << "\nWaiting Time\t Turnaround Time";

    for ( int i = 0; i < n; i++ )
    {
        aveWT += waitingTime[i];
        aveTT += turnAroundTime[i];

        cout << "\nP" << i + 1 << ": " << waitingTime[i]
        << "\t\tP" << i + 1 << ": " << turnAroundTime[i];
    }

    aveWT /= n;
    aveTT /= n;
    cout << "\n\nAverage Waiting Time: " << aveWT;
    cout << "\nAverage Turnaround Time: " << aveTT;
}


int main()
{
    int n;
    vector<int> arrivalTime;
    vector<int> burstTime;
    vector<int> priorityNum;

//get number of processes

    cout << "Input no. of processes [2-9]: ";
    cin >> n;

//get arrival times

    cout << "Input individual arrival time:" << endl;

    for (int i = 0; i < n; i++)
    {
        int at;

        cout << "AT" << i+1 << ": ";
        cin >> at;

        arrivalTime.push_back(at);
    }

    cout << "Arrival times are: ";

//get burst times

    cout << "\nInput individual burst time:" << endl;

    for (int i = 0; i < n; i++)
    {
        int bt;

        cout << "BT" << i+1 << ": ";
        cin >> bt;

        burstTime.push_back(bt);
    }

//get algorithm of choice

    char choice;
    char repeat;
    bool isValid;
    bool end;

do {

    isValid = true;

    cout << "\nCPU Scheduling Algorithm:" << endl;
    cout << "[A] First Come First Serve (FCFS)" << endl;
    cout << "[B] Shortest Job First (SJF)" << endl;
    cout << "[C] Priority (Prio)" << endl;
    cout << "[D] Exit" << endl;

    cin >> choice;

    switch ((char) toupper(choice))
    {
    case 'A':
        cout << "First Come First Serve" << endl;

        firstComeAlgo(n, arrivalTime, burstTime);

        cout << "\nInput again (y/n)" << endl;
        cin >> repeat;

        isValid = !doRepeat(repeat);

        break;
    
    case 'B':
        cout << "Shortest Job First" << endl;

        shortestJobAlgo(n, arrivalTime, burstTime);

        cout << "\nInput again (y/n)" << endl;
        cin >> repeat;

        isValid = !doRepeat(repeat);

        break;

    case 'C':
        cout << "Priority" << endl;
        cout << "Input individual priority number:" << endl;

        for (int i = 0; i < n; i++)
        {
            int pn;

            cout << "Prio" << i+1 << ": ";
            cin >> pn;

            priorityNum.push_back(pn);
        }

        cout << "Priority numbers are: ";

        for ( auto p : priorityNum )
        {

            cout << p << " ";
        }
        
        priorityAlgo(n, arrivalTime, burstTime, priorityNum);

        cout << "\nInput again (y/n)" << endl;
        cin >> repeat;

        isValid = !doRepeat(repeat);

        break;

    case 'D':
        cout << "Exited" << endl;
        exit(0);
        break;

    default:
        cout << "Invalid input." << endl;
        isValid = false;
        break;
    }

}  while ( !isValid );
}