#include <fstream>
#include <cstdlib>

int
main()
{
    std::ofstream out("test/gigabin.bin", std::ios::binary);
    for (int i = 0; i < 1024 * 1024 * 1024; i++)
        out << char(rand() * 255);
    return 0;
}