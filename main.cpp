#include <iostream>
#include "Container.h"
#include "Algorithms.h"
#include "StreamItertor.h"
#include <initializer_list>
#include <fstream>
#include "Exceptions.h"


//объект для тестирования
struct Goods
{
    uint32_t    m_id;                // Код товара
    std::string m_name;              // Название
    std::string m_manufacturer;      // Производитель
    std::string m_warehouse_address; // Адрес склада
    double      m_weight;            // Вес
};


//функтор для 7 задания
class Function {
private:
public:
    bool operator()(const Goods& m_p) {
        return m_p.m_warehouse_address == "Moscow";
    }
};



int main() {

    try {
        std::cout << "task1:\n";
        std::cout << "------------------------------\n";
        auto f = [](Vector<Goods>::iterator it) {std::cout << "object of container:\nid -" << (*it).m_id << "\n"\
            << "name - " << (*it).m_name << "\n" << "facturer - " << (*it).m_manufacturer << "\n"\
            << "address - " << (*it).m_warehouse_address << "\n" << "wieght - " << (*it).m_weight << "\n\n";};
        Vector<Goods> cont1 = { {111111, "ball", "yan", "Moscow", 1.2345},\
        {222222, "squord", "kel", "Moscow", 5.789},\
        {111111, "game", "yan", "Moscow", 3.13333} };
        foreach(cont1.begin(), cont1.end(), f);
        std::cout << "task2:\n";
        std::cout << "------------------------------\n";
        Goods g1 = { 57575, "phone", "apple", "New York", 0.256 };
        Goods g2 = { 535, "pen", "cant", "Berlin", 0.11 };
        Goods g3 = { 222, "note", "cant", "Berlin", 0.33 };
        Vector<Goods> cont2 = { g1 };
        cont2.insert(cont2.begin(), g1);
        cont2.insert(cont2.begin() + 1, g2);
        cont2.insert(cont2.begin() + 2, g3);
        cont2.erase(cont2.begin() + 1);
        foreach(cont2.begin(), cont2.end(), f);
        std::cout << "task3:\n";
        std::cout << "------------------------------\n";
        cont1.insert(cont1.begin() + 1, cont2.begin(), cont2.end());
        foreach(cont1.begin(), cont1.end(), f);
        std::cout << "task4:\n";
        std::cout << "------------------------------\n";
        sort(cont1.begin(), cont1.end(), [](const Goods& p1, const Goods& p2) -> bool {return p1.m_name <= p2.m_name;});
        foreach(cont1.begin(), cont1.end(), f);
        std::cout << "task5:\n";
        std::cout << "------------------------------\n";
        auto ans = findIf(cont1.begin(), cont1.end(), [](const Goods& p) -> bool {return p.m_weight >= 2 and p.m_weight <= 6;});
        std::cout << "its id: " << (*ans).m_id << " with weight " << (*ans).m_weight << "\n";
        std::cout << "task6:\n";
        std::cout << "------------------------------\n";
        ans->m_warehouse_address = "Germany";
        foreach(cont1.begin(), cont1.end(), f);
        std::cout << "task7:\n";
        std::cout << "------------------------------\n";
        Vector<Goods> cont3(10);
        cont3.resize(2);
        copyIf(cont1.begin(), cont1.end(), cont3.begin(), Function());
        foreach(cont3.begin(), cont3.end(), f);
        std::cout << "homework protection:\n";
        std::cout << "------------------------------\n";
        Vector<double> cont4 = { 1.2222, -2.5, 4.78, -9.89, 10 };
        std::ostream& out = std::cout;
        StreamIterator<double> stream(out, '\n');
        copyIf(cont4.begin(), cont4.end(), stream, [](double a) -> bool {return a >= 0;});
        std::ofstream out2("test_output.txt");
        StreamIterator<double> stream2(out2, ' ');
        copyIf(cont4.begin(), cont4.end(), stream2, [](double a) -> bool {return a >= 0;});
        std::cout << "check file test_output.txt\n";
        cont1.clear();
        cont2.clear();
        cont3.clear();
        cont4.clear();
        std::cout << "all containers were clreared\n";
    }
    catch (std::exception exception) {
        std::cout << "an exception was called \nits description:\n" << exception.what() << "\n";
    }
    return 0;
}
