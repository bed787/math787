std::vector<std::vector<int>> getPermutations(size_t n) {
    //      формируем числа {0, 1, ..., n}
    std::vector<int> values(n);
    for (int i = 0; i < n; i++) {
        values[i] = i;
    }
    std::vector<std::vector<int>> result;
    //      ищем точку роста из value и сохраняем его индекс в counter
    for (int i = factorial(n) - 1; i > 0; i--) {
        int counter = n - 1;
        result.push_back(values);
        while (counter >= 0) {
            counter--;
            if ((values[counter]) < (values[counter + 1])) {
                break;
            }
        }

        //      проходимся по суффиксу справа налево и ищем первый элемент, больший точки роста
        int right = n - 1;
        while (counter != right) {
            if (values[right] > values[counter]) {
                std::swap(values[right], values[counter]);
                break;
            }
            right--;
        }

        //      переворачиваем суффикс
        int right2 = n - 1;
        counter++;
        while (counter < (right2)) {
            std::swap(values[counter], values[right2]);
            counter++;
            right2--;
        }
    }
    result.push_back(values);
    return result;



}