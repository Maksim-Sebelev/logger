#include "lib/log.hpp"


int main()
{
    OPEN_LOG();
    LOG_COLOR(Red);

    LOG_COLOR(Green);
    LOG_PRINT(Blue, "pobeda!");

    LOG_PRINT(Red, "log made in:");
    LOG_PLACE(Red);

    int arr[150] = {};
    for (int i = 0; i < 27; i++) 
    {
        arr[i] = i*i + 2*i + 1;
    }


    LOG_COLOR(Yellow);

    for (size_t i = 0; i < 27; i++)
    {
        LOG_ADC_INT_ARRAY(arr, i, 2);
    }

    LOG_ALL_INT_ARRAY(Green, arr, 27, 2);

    LOG_PLACE(Blue);

    CLOSE_LOG();

    return 0;
}