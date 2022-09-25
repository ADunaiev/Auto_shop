#include <algorithm>
#include <iostream>
#include <list>
#include<string.h>
#include<fstream>
using namespace std;
//Задание 1.
//Создайте приложение для работы автосалона.Необходимо
//хранить информацию о продаваемых автомобилях(название, 
//    год выпуска, объем двигателя, цену).Реализуйте
//интерфейс для добавления данных, удаления данных,
//отображения данных, сортировке данных по различным
//параметрам, поиску данных по различным параметрам.
//При реализации используйте контейнеры, функторы
//и алгоритмы.

class Auto
{
    string name;
    int prod_year;
    int engine_volume;
    double price;
public:
    Auto(string nameP, int prod_yearP, int engine_volumeP, double priceP);
    Auto();
    string get_name() const;
    int get_prod_year() const;
    int get_engine_volume() const;
    double get_price() const;
    void set_name(string nameP);
    void set_prod_year(int prod_yearP);
    void set_engine_volume(int engine_volumeP);
    void set_price(double priceP);
    void show_car();
   
};
Auto::Auto(string nameP, int prod_yearP, int engine_volumeP, double priceP) :
    name{ nameP }, prod_year{ prod_yearP }, engine_volume{ engine_volumeP },
    price{ priceP }{}
Auto::Auto() : Auto("", 0, 0, 0){}
string Auto::get_name() const { return name; }
int Auto::get_prod_year() const { return prod_year; }
int Auto::get_engine_volume() const { return engine_volume; }
double Auto::get_price() const { return price; }
void Auto::set_name(string nameP) { name = nameP; }
void Auto::set_prod_year(int prod_yearP) { prod_year = prod_yearP; }
void Auto::set_engine_volume(int engine_volumeP) { engine_volume = engine_volumeP; }
void Auto::set_price(double priceP) { price = priceP; }
void Auto::show_car() {
    cout << "Car information:\n";
    cout << "Model: " << name << endl;
    cout << "Year of production: " << prod_year << endl;
    cout << "Engine volume: " << engine_volume << endl;
    cout << "Price, USD: " << price << endl;
    cout << endl;
}


void SaveToFile(list<Auto> l_auto)
{
    remove("Autos.txt");
    int size; char* temp = nullptr;
    double size_d;

    fstream f("Autos.txt", ios::out | ios::binary | ios::app);

    if (!f)
    {
        throw "\nFile is not opened for writing!\n";
    }

    for (auto var : l_auto)
    {
        if (temp != nullptr)
            delete[] temp;

        size = var.get_name().size();
        f.write((char*)&size, sizeof(int));
        temp = new char[size + 1];
        strcpy_s(temp, size + 1, var.get_name().c_str());     
        f.write((char*)temp, size*sizeof(char));

        size = var.get_prod_year();
        f.write((char*)&size, sizeof(int));

        size = var.get_engine_volume();
        f.write((char*)&size, sizeof(int));

        size_d = var.get_price();
        f.write((char*)&size_d, sizeof(double));
    }

    f.close();
    delete[] temp;
}
list<Auto> LoadFromFile() {
    fstream f("Autos.txt", ios::in | ios::binary);
    if (!f) {
        throw "\nFile is not opened for reading!\n\n";
    }
    char* temp = nullptr;
    int size; double size_d; 
    int i = 0;
    list<Auto> auto_temp;

    while (f.read((char*)&size, sizeof(int))) 
    {
        Auto a_temp;

        if (temp != nullptr)
            delete[] temp;

        temp = new char[size + 1];
        f.read((char*)temp, size * sizeof(char));
        temp[size] = '\0';
        a_temp.set_name(temp);

        f.read((char*)&size, sizeof(int));
        a_temp.set_prod_year(size);

        f.read((char*)&size, sizeof(int));
        a_temp.set_engine_volume(size);

        f.read((char*)&size_d, sizeof(double));
        a_temp.set_price(size_d);

        auto_temp.push_back(a_temp);
    }

    delete[] temp;

    return auto_temp;
}

void show_all(const list<Auto> v) 
{
    for (auto var : v)
        var.show_car();
}

int Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to see all autos\n";
    cout << " 2 - to add new auto\n";
    cout << " 3 - to edit auto\n";
    cout << " 4 - to delete auto\n";
    cout << " 5 - to sort data\n";
    cout << " 6 - to find auto\n";
    cout << " 0 - to exit programm\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}
int Sort_Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to sort by name\n";
    cout << " 2 - to sort by production year\n";
    cout << " 3 - to sort by engine volume\n";
    cout << " 4 - to sort by price\n";
    cout << " 0 - to exit programm\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}
int Find_Menu()
{
    int temp;
    cout << "\nPlease make your choice:\n";
    cout << " 1 - to find by name\n";
    cout << " 2 - to find by production year\n";
    cout << " 3 - to find by engine volume\n";
    cout << " 4 - to find by price\n";
    cout << " 0 - to exit programm\n";
    cout << "\nYour choice is - ";
    cin >> temp;

    return temp;
}

int main()
{
    //Auto a1{ "Land Cruiser 300", 2017, 4500, 53000 };
    //Auto a2{ "VW Golf", 2013, 1600, 12500 };
    //Auto a3{ "VW Touareg", 2021, 3000, 74000 };
    //Auto a4{ "Nissan Quashqai", 2008, 2000, 8000 };
    //Auto a5{ "Tesla", 2020, 0, 46000 };


    //list<Auto> auto_l;
    //auto_l.push_back(a1);
    //auto_l.push_back(a2);
    //auto_l.push_back(a3);
    //auto_l.push_back(a4);
    //auto_l.push_back(a5);

    //SaveToFile(auto_l);
    
    list<Auto> autos = LoadFromFile();

    try {
        int t;

        do {
            switch (Menu()) {
            case 1:
                show_all(autos);
                break;
            case 2:
            {
                break;
            }
            case 3:
            {

                break;
            }
            case 4:
            {

                break;
            }
            case 0:
                cout << "Good Buy!\n";
                return 0;
            default:
                cout << "Wrong choice!\n";
            }
        } while (1);
    }
    catch (char* su) {
        std::cout << "\n\nException!!!\n\n";
    }

    return 0;
}