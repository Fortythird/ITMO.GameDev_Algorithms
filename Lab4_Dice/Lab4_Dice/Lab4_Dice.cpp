#include <iostream>
#include <string>
using namespace std;

int roll(string st)
{
    string data = "";                                                       // ѕеременна€ дл€ сборки данных о кубиках
    int num = 0, diceType = 0, mod = 1, sum = 0, pos = 0;
    bool hasMod = false;
    while (pos < st.size())                                                 // ѕока переменна€ pos не будет больше длины строки, анализируем данные
    {
        if (st[pos] == 'd')                                                 // ≈сли встретилс€ символ d, то записываем количество 
        {                                                                   // кубиков (записано до 'd') и очищаем data
            num = stoi(data);
            data = "";
        }
        else if (st[pos] == '+' || st[pos] == '-')                          // ≈сли встретилс€ знак модификатора, то записываем
        {                                                                   // количество граней кубика, переключаем bool переменную в true,
            hasMod = true;                                                  // что сигнализирует о наличии модификатора и очищаем data
            diceType = stoi(data);
            data = "";
            if (st[pos] == '-') mod = -1;                                   // Ёто значение (1 или -1) далее будет множетелем к значению модификатора
        }
        else if (st[pos] == ' ')                                            // ѕробел сигнализирует об окончании информации о кубиках одного типа
        {
            if (hasMod) mod *= stoi(data);
            else
            {
                mod = 0;
                diceType = stoi(data);
            }
            for (int i = 0; i < num; i++) sum += rand() % diceType + 1;     // Ѕроски кубиков указанного типа
            sum += mod;
            hasMod = false;                                                 // —брос значений (по умолчанию)
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
