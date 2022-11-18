#include <iostream>
#include <string>
using namespace std;

int roll(string st)
{
    string data = "";                                                       // ���������� ��� ������ ������ � �������
    int num = 0, diceType = 0, mod = 1, sum = 0, pos = 0;
    bool hasMod = false;
    while (pos < st.size())                                                 // ���� ���������� pos �� ����� ������ ����� ������, ����������� ������
    {
        if (st[pos] == 'd')                                                 // ���� ���������� ������ d, �� ���������� ���������� 
        {                                                                   // ������� (�������� �� 'd') � ������� data
            num = stoi(data);
            data = "";
        }
        else if (st[pos] == '+' || st[pos] == '-')                          // ���� ���������� ���� ������������, �� ����������
        {                                                                   // ���������� ������ ������, ����������� bool ���������� � true,
            hasMod = true;                                                  // ��� ������������� � ������� ������������ � ������� data
            diceType = stoi(data);
            data = "";
            if (st[pos] == '-') mod = -1;                                   // ��� �������� (1 ��� -1) ����� ����� ���������� � �������� ������������
        }
        else if (st[pos] == ' ')                                            // ������ ������������� �� ��������� ���������� � ������� ������ ����
        {
            if (hasMod) mod *= stoi(data);
            else
            {
                mod = 0;
                diceType = stoi(data);
            }
            for (int i = 0; i < num; i++) sum += rand() % diceType + 1;     // ������ ������� ���������� ����
            sum += mod;
            hasMod = false;                                                 // ����� �������� (�� ���������)
            mod = 1;
            data = "";
            num = 0;
            diceType = 0;
        }
        else data += st[pos];
        pos++;
    }
    return sum;
}

void main()
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 3000; i++) cout << roll("3d10 ") << endl;
}
