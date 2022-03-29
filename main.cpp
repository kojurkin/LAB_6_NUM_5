#include <iostream>
#include <fstream>
#include <ctime>

double random (double lower_range_limit, double upper_range_limit)
{
    return lower_range_limit + (rand() * 1. / RAND_MAX) * (upper_range_limit - lower_range_limit);
}

int main()
{
    srand(time(0));
    int n;
    std::cout << "Enter count of numbers in binary file (n)" << std::endl;
    std::cin >> n;
    double high_r, low_r;
    std::cout << "Enter range of random(low high)" << std::endl;
    std::cin >> low_r >> high_r;

    int rows, cols;

    if ((rows * cols) > n)
    {
        std::cout << "ERROR: file is too small";
        return 1;
    }

    std::cout << "Enter sizes of array (rows cols)" << std::endl;
    std::cin >> rows >> cols;
    double **array = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        array[i] = new double[cols];
    }

    std::ofstream output ("RealNumber.bin", std::ios::out |  std::ios::binary);
    for (int i = 0; i < n; i++)
    {
        double num;
        num = random(low_r, high_r);
        std::cout << std::endl << num;
        output.write(reinterpret_cast<const char *>(&num), sizeof num);
    }
    output.close();

    std::ifstream input ("RealNumber.bin", std::ios::binary);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double tmp;
            input.read(reinterpret_cast<char *>(&tmp), sizeof tmp);
            array[i][j] = tmp;
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] array[i];
    }
    delete[] array;

    input.close();
    return 0;
}