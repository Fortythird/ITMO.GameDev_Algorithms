#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string input;
unsigned short population = 100, deaths = 0, immigrants = 0, square = 1000, age = 1, acreCost = 0, acresToBuy = 0,
acresToSell = 0, wheatForPeople = 0, acresToSow = 0;
float wheat_amount = 2800.0, wheatPerAcre = 0, wheat_income = 0, rats_damage = 0, avDeathPersent = 0, acresPerSitizen = 0;
bool isPlague = false, isCorrect = false, isExit = false;

void report()                                                                       // функция вывода ежегодного отчета
{
    cout << "\nBeginning of year " << age << ":\n\n";
    if (deaths) cout << "People dead of hunger: " << deaths << endl;
    if (immigrants) cout << "Population increase: +" << immigrants << " citizens\n";
    if (isPlague)
    {
        cout << "This year the plague killed half of population!\n";
        isPlague = false;
    }
    cout << "Current population: " << population << endl;
    cout << "Wheat income: " << wheat_income << endl;
    if (wheatPerAcre) cout << "Wheat per acre: " << wheatPerAcre << endl;
    cout << "Wheat was eaten by rats: " << rats_damage << endl;
    cout << "Current wheat amount: " << wheat_amount << endl;
    cout << "Current square: " << square << endl;
    cout << "Current acre cost: " << acreCost << endl << endl;
}

void score()                                                                        // функция вывода результатов в случае победы 
{
    cout << "Victory! Your stats:\n";
    cout << "Average death percent: " << avDeathPersent << endl;
    cout << "Acres per sitizen: " << acresPerSitizen << endl;
    if (avDeathPersent > 0.33 && acresPerSitizen < 7.0) cout << "Bad!\n";
    else if (avDeathPersent > 0.1 && acresPerSitizen < 9.0) cout << "Ok!\n";
    else if (avDeathPersent > 0.03 && acresPerSitizen < 10.0) cout << "Good!\n";
    else cout << "Great!\n";
}

unsigned short parse(string &st, unsigned short *var)                               // функция перевода строки в целочисленное значение
{
    if (st == "exit")                                                               // проверка поступления команды о выходе из игры
    {
        isExit = true;
        return 0;
    }
    else                                                                            // обработчик исключений
    {
        unsigned short result = 0;
        try
        {
            bool isNumber = true;
            for (int i = 0; i < st.size(); i++) if (st[i] < '0' || st[i] > '9') isNumber = false;
            if (!isNumber) throw invalid_argument("Invalid value!\n");
            else if (st[0] == '-') throw invalid_argument("Value cannot be negative!\n");
            else if (st.size() == 5)
            {
                bool isBigger = false;
                for (short i = st.size(); i > 0; i--)
                {
                    if (((short)st[st.size() - i] - (short)'0') > (unsigned short)(fmod(numeric_limits<unsigned short>::max(), pow(10, i)) / pow(10, i - 1)))
                    {
                        isBigger = true;
                        break;
                    }
                }
                if (st.size() > 5 || isBigger) throw invalid_argument("The value is too big!\n");
            }
            result = stoi(st);
            if (var == &acresToSell && result > square) throw invalid_argument("You have no so much acres!\n");
            else if (var == &acresToBuy && result * acreCost > wheat_amount) throw invalid_argument("You have no enough wheat!\n");
            isCorrect = true;
        }
        catch (exception e)
        {
            cout << e.what() << endl;
        }
        return result;
    }
}

unsigned short parse(string &st, float *var)                                        // функция перевода строки в целочисленное значение
{
    if (st == "exit")                                                               // проверка поступления команды о выходе из игры
    {
        isExit = true;
        return 0;
    }
    else
    {
        unsigned short result = 0;
        try                                                                         // обработчик исключений
        {
            bool isNumber = true;
            for (int i = 0; i < st.size(); i++) if (st[i] < '0' || st[i] > '9') isNumber = false;
            if (!isNumber) throw invalid_argument("Invalid value!\n");
            else if (st[0] == '-') throw invalid_argument("Value cannot be negative!\n");
            result = stoi(st);
            if (var == &wheat_amount && result > wheat_amount) throw invalid_argument("You have no so much wheat!\n");
            if (result < 0) throw invalid_argument("Value cannot be negative!\n");
            isCorrect = true;
        }
        catch (exception e)
        {
            cout << e.what() << endl;
        }
        return result;
    }
}

void main()
{
    ifstream isave;
    ofstream osave;
    isave.open("save.txt");
    if (isave)                                                                      // если сохранение существует, выводится вопрос о необходимости считывания 
    {                                                                               // данных из сохранения и продолжении ранее прерванной игры
        isCorrect = false;
        while (!isCorrect)
        {
            cout << "Would you like to load the last game process? (y/n)\n";
            cin >> input;
            if (input == "y" || input == "n")
            {
                isCorrect = true;
                if (input == "y") isave >> age >> population >> square >> wheat_amount;
            }
            else cout << "Your answer is not clear!\n\n";
        }
    }
    isave.close();

    for (age; age <= 10; age++)                                                     // игровой цикл
    {
        srand(static_cast <unsigned int>(time(0)));                                 // установка начала псевдослучайной последовательности по текущей дате
        acreCost = rand() % 10 + 17;                                                // вычисление псевдослучайной цены за акр
        report();

        isCorrect = false;
        while (!isCorrect && !isExit)                                               // ввод количества акров для покупки
        {
            cout << "Acres to buy: ";
            cin >> input;
            acresToBuy = parse(input, &acresToBuy);
        }
        square += acresToBuy;

        isCorrect = false;
        while (!isCorrect && !isExit)                                               // ввод количества акров для продажи
        {
            cout << "Acres to sell: ";
            cin >> input;
            acresToSell = parse(input, &acresToSell);
        }
        square -= acresToSell;

        isCorrect = false;
        while (!isCorrect && !isExit)                                               // ввод количества пшеницы для горожан
        {
            cout << "Wheat for people: ";
            cin >> input;
            wheatForPeople = parse(input, &wheatForPeople);
        }

        isCorrect = false;
        while (!isCorrect && !isExit)                                               // ввод площади под посев
        {
            cout << "Acres to sow: ";
            cin >> input;
            acresToSow = parse(input, &acresToSow);
        }

        if (isExit) break;                                                          // выход из игрового цикла, если игрок ввел "exit" в любом из полей

        wheat_amount += (acresToSell - acresToBuy) * acreCost - acresToSow * 0.5;   // вычисление количества пшеницы исходя из введенных данных

        if (rand() % 100 < 15)                                                      // розыгрыш сценария чумы
        {
            population /= 2;
            isPlague = true;
        }

        wheatPerAcre = rand() % 6 + 1;                                              // урожайность
        if (population * 10 >= square) wheat_income = acresToSow * wheatPerAcre;    // сборы урожая при полной обработки земель
        else  wheat_income = population * 10 * wheatPerAcre;                        // сборы урожая при неполной обработки земель

        rats_damage = (float)(rand() % 8) / 100 * wheat_amount;                     // ущерб от крыс

        wheat_amount += wheat_income - rats_damage;                                 // итого пшеницы на складах

        deaths = population - wheatForPeople / 20;                                  // количество голодных смертей (разница между населением и потенциальным 
                                                                                    // количеством человек, которых можно прокормить)
        if (deaths < 0) deaths = 0;                                                 // если еды хватает

        cout << wheatForPeople << endl;

        if ((float)deaths / population > 0.45f || population <= 0) break;

        avDeathPersent += (float)deaths / population;

        wheat_amount -= population * 20;                                            // итого пшеницы с учетом трат на продовольствие

        immigrants = deaths / 2 + (5 - wheatPerAcre) * wheat_amount / 600 + 1;      // вновь прибывшие
        if (immigrants < 0) immigrants = 0;
        else if (immigrants > 50) immigrants = 50;

        population += immigrants - deaths;                                          // итого населения

        osave.open("save.txt");                                                     // сохранение игрового прогресса в файл по окончанию хода
        osave.clear();
        osave << age << ' ' << population << ' ' << square << ' ' << wheat_amount;
        osave.close();
    }

    if (!isExit)                                                                    // если игра завершилась, удаляется сохранение и выводятся итоги
    {
        remove("save.txt");
        if (age <= 10)
        {
            age++;
            report();
            cout << "Defeat! The city's population reached the critical value!\n";
        }
        else
        {
            avDeathPersent /= 10;
            acresPerSitizen = (float)square / population;
            score();
        }
    }
}
