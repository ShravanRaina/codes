#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

char buff[40];
char M[100][4];
char R[4];
char IR[4];

int IC;
int C;

int SI = 0;
string line;

void initialise()
{
    IC = 0;
    C = 0;

    cout << "Initailising the memory" << endl;
    for (int i = 0; i < 40; i++)
    {
        buff[i] = '0';
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '0';
        }
    }

    for (int i = 0; i < 4; i++)
    {
        IR[i] = '0';
        R[i] = '0';
    }
}

void load(string line, int count)
{
    if (count == 1)
    {
        for (int i = 0; i < line.length(); i++)
        {
            buff[i] = line[i];
        }

        cout << "Moving data from buffer to memory: " << endl
             << "Block 0:" << endl;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                do
                {
                    M[i][j] = buff[4 * i + j];
                    cout << M[i][j];
                    break;
                } while (buff[4 * i + j] != 'H');
            }
            cout << endl;
        }
        cout << "Program Block executed.." << endl
             << endl;
    }

    else if (count == 3)
    {
        for (int i = 0; i < 40; i++)
        {
            buff[i] = '0';
        }
        for (int i = 0; i < line.length(); i++)
        {
            buff[i] = line[i];
        }
    }
}

void Read()
{
    IR[3] = '0';
    string line1;

    for (int i = 0; i < 4; i++)
    {
        line1[i] = IR[i];
    }

    int num = int(IR[2] - '0') * 10;

    int a = 0;
    for (int i = num; i < num + 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            do
            {
                M[i][j] = buff[4 * a + j];
                break;
            } while (buff[4 * a + j] != '0');
        }
        a++;
    }
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 0)
        {
            cout << "BLOCK " << i / 10 << endl;
        }
        for (int j = 0; j < 4; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void Write()
{
    fstream file;
    file.open("output.txt", ios::out);

    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    string out;

    int num = int(IR[2] - '0') * 10;
    int a = 0;

    for (int i = num; i < num + 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (M[i][j] != '0')
            {
                file << M[i][j];
            }
        }
    }
    file.close();
}

void terminateProgram()
{
    cout << endl
         << "Program execution end" << endl;
}

void masterMode()
{
    switch (SI)
    {
    case 1:
        Read();
        break;
    case 2:
        Write();
        break;
    case 3:
        break;

    default:
        cout << "------";
        break;
    }
    SI = 0;
}

void startExecution()
{
    cout << "Execution starts.." << endl;
    while (true)
    {
        if (IC == 100)
        {
            break;
        }

        IR[0] = M[IC][0];
        IR[1] = M[IC][1];
        IR[2] = M[IC][2];
        IR[3] = M[IC][3];

        IC++;

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            masterMode();
        }

        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            masterMode();
        }

        else if (IR[0] == 'H')
        {
            SI = 3;
            masterMode();
        }

        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            string line1;

            for (int i = 0; i < 4; i++)
            {
                line1[i] = IR[i]; //LR21
            }
            string t1 = to_string(int(IR[2] - '0'));
            string t2 = to_string(int(IR[3] - '0'));

            string t = t1 + t2; //21
            int num = stoi(t); // int 21

            R[0] = M[num][0];
            R[1] = M[num][1];
            R[2] = M[num][2];
            R[3] = M[num][3];

            cout << endl
                 << endl;
            cout << "Register values at LR function:  ";
            for (int i = 0; i < 4; i++)
            {
                cout << R[i];
            }
            cout << endl;
        }

        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            string line1;

            for (int i = 0; i < 4; i++)
            {
                line1[i] = IR[i];
            }
            string t1 = to_string(int(IR[2] - '0'));
            string t2 = to_string(int(IR[3] - '0'));

            string t = t1 + t2;
            int num = stoi(t);

            M[num][0] = R[0];
            M[num][1] = R[1];
            M[num][2] = R[2];
            M[num][3] = R[3];

            cout << endl
                 << endl;
            cout << "Register values at SR function:  ";
            for (int i = 0; i < 4; i++)
            {
                cout << R[i];
            }
            cout << endl;

            cout << "Memory values at SR function:  " << endl;
            cout << "Block " << (num / 10) << endl;
            for (int i = ((num / 10) * 10); i < ((num / 10) * 10) + 10; i++) // 20 -> 29
            {
                for (int j = 0; j < 4; j++)
                {
                    cout << M[i][j];
                }
                cout << endl;
            }
        }

        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            string line1;

            for (int i = 0; i < 4; i++)
            {
                line1[i] = IR[i];
            }
            string t1 = to_string(int(IR[2] - '0')); //3
            string t2 = to_string(int(IR[3] - '0')); //4

            string t = t1 + t2;
            int num = stoi(t); //34

            if (M[num][0] == R[0] && M[num][3] == R[3] && M[num][2] == R[2] && M[num][1] == R[1])
            {
                C = 1;
                cout << endl
                     << endl
                     << "Same values at comparison!" << endl;
            }
            else
            {
                C = 0;
                cout << endl
                     << endl
                     << "Different values at comparison!" << endl;
            }
        }

        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == 1)
            {
                string line1;

                for (int i = 0; i < 4; i++)
                {
                    line1[i] = IR[i];
                }
                string t1 = to_string(int(IR[2] - '0'));
                string t2 = to_string(int(IR[3] - '0'));

                string t = t1 + t2;
                int num = stoi(t);

                IC = num;
                C = 0;
            }
        }
    }
}

void readFile()
{
    ifstream file;
    file.open("input.txt");

    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
        return;
    }

    char ch;
    string s;
    int count = 0;
    while (getline(file, line))
    {
        if (line[0] == '$')
        {
            for (int i = 1; i < 4; i++)
            {
                s[i - 1] = line[i];
            }

            if (s[0] == 'A' && s[1] == 'M' && s[2] == 'J')
            {
                initialise();
                count = 0;
            }
            else if (s[0] == 'D' && s[1] == 'T' && s[2] == 'A')
            {
                for (int i = 0; i < line.length(); i++)
                {
                    buff[i] = '0';
                }
                cout << endl;
                count = 2;
            }
            else if (s[0] == 'E' && s[1] == 'N' && s[2] == 'D')
            {
                terminateProgram();
            }

            count++;
            continue;
        }

        if (count == 1)
        {
            load(line, count);
        }
        if (count == 3)
        {
            load(line, count);
            startExecution();
            cout << endl;
        }
    }

    file.close();
}

int main()
{
    readFile();
    return 0;
}