//Myznikov Fedor Denisovich
//st129282@student.spbu.ru
//LabWork2

#include<iostream>
#include<ostream>
#include<string>
#include<random>

int random(int from, int to)
{

    std::random_device randomDevice;
    std::mt19937_64 mt(randomDevice());
    std::uniform_real_distribution<> distribution(from, to);
    return distribution(mt);

}

int main(int argc, char **argv) {
    std::random_device randomDevice;
    std::cout << randomDevice()%23;
}
