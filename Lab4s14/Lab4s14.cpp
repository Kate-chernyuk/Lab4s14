#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <cmath>
using namespace std;


int main()
{
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите число посадочных мест на плате\n";
    cin >> n;

    int m;
    cout << "Введите число имеющихся элементов\n";
    cin >> m;

    vector < vector <int> > matrix(m);
    vector <int> to_matrix(m);

    vector<int>::iterator it1, it3, it0;
    vector<vector<int>>::iterator it2;

    int i = 1;
    for (it2 = matrix.begin(); it2 != matrix.end(); it2++) {
        cout << "Введите последовательно информацию о числе связей элемента v" << i << " с каждым из " << m << " элементов" << endl; i++;
        int kol_sv;
        for (it1 = to_matrix.begin(); it1 != to_matrix.end(); it1++) {
            cin >> kol_sv;
            (*it1) = kol_sv;
        }
        (*it2) = to_matrix;
    }

    cout << "\nВведённая матрица мультиграфа:\n    ";
    for (int j = 0; j < matrix[0].size(); j++) {
        cout << "v" << j + 1 << "\t";
    }
    cout << "\n";
    for (int i = 0; i < matrix.size(); i++) {
        cout << "v" << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
    int n1 = ceil(sqrt(n));


    vector<vector<int>> plat(n1, vector<int>(n1, 0));

    vector <int> free_elems(m);
    vector <int> in_plat;
    iota(free_elems.begin(), free_elems.end(), 1);
    int elem;

    cout << "Введите номер элемента, который хотите поместить в левый нижний угол\n";
    cin >> elem;
    plat[n1 - 1][0] = elem;
    in_plat.push_back(elem);
    it1 = find(free_elems.begin(), free_elems.end(), elem);
    free_elems.erase(it1);

    cout << "Введите номер элемента, который хотите поместить в правый нижний угол\n";
    cin >> elem;
    plat[n1 - 1][n1 - 1] = elem;
    in_plat.push_back(elem);
    it1 = find(free_elems.begin(), free_elems.end(), elem);
    free_elems.erase(it1);

    for (int i = 0; i < plat.size(); i++) {
        for (int j = 0; j < plat.size(); j++) {
            cout << plat[i][j] << " ";
        }
        cout << "\n";
    }

    vector <int> sums(m);

    int sc0;

    for (int n0 = 2; n0 < n; n0++) {
        for (int i = 0; i < matrix.size(); i++) {
            it1 = find(free_elems.begin(), free_elems.end(), i + 1);
            sc0 = 0;
            if (it1 != free_elems.end()) {
                for (int j = 0; j != in_plat.size(); j++) {
                    sc0 += matrix[i][in_plat[j] - 1];

                }
                sums[i] = sc0;
            }
            else {
                sums[i] = -1;
            }
        }


        it0 = max_element(sums.begin(), sums.end());

        int res = count(sums.begin(), sums.end(), *it0);

        if (res == 1) {
            it3 = find(sums.begin(), sums.end(), *it0);
            elem = distance(sums.begin(), it3) + 1;
        }
        else {
            vector <int> sums_min(m);
            int mx = *it0;

            for (int i = 0; i < m; i++) {
                if (sums[i] == mx) {
                    it1 = find(free_elems.begin(), free_elems.end(), i + 1);
                    sc0 = 0;
                    if (it1 != free_elems.end()) {
                        for (int j = 0; j < m; j++) {
                            it3 = find(free_elems.begin(), free_elems.end(), j + 1);
                            if (it3 != free_elems.end()) {
                                sc0 += matrix[i][j];
                            }
                        }
                        if (sc0 >= 0) {
                            sums_min[i] = sc0;
                        }
                    }
                    else {
                        sums_min[i] = m * m * m;
                    }
                }
                else {
                    sums_min[i] = m * m * m;
                }
            }

            it0 = min_element(sums_min.begin(), sums_min.end());
            elem = distance(sums_min.begin(), it0) + 1;
        }

        int max_sv_with = in_plat[0], sravn_el, i_plat_el = -1, j_plat_el = -1;

        for (int i = 0; i < in_plat.size(); i++) {
            sravn_el = matrix[in_plat[i] - 1][elem - 1];

            if ((sravn_el > matrix[max_sv_with - 1][elem - 1])) {
                max_sv_with = in_plat[i];
            }


            for (int j = 0; j < n1; j++) {
                for (int k = 0; k < n1; k++) {
                    if (plat[j][k] == max_sv_with) {
                        i_plat_el = j;
                        j_plat_el = k;
                        break;
                    }
                }
            }
        }

        int i_min_rasst, j_min_rasst, rasst = n + n + 2, i_rasst, j_rasst;

        for (int i = 0; i < plat.size(); i++) {
            for (int j = 0; j < plat[i].size(); j++) {
                if (plat[i][j] == 0) {
                    i_rasst = abs(i_plat_el - i);
                    j_rasst = abs(j_plat_el - j);
                    if (i_rasst + j_rasst < rasst) {
                        rasst = i_rasst + j_rasst;
                        i_min_rasst = i;
                        j_min_rasst = j;
                    }
                }
            }
        }

        plat[i_min_rasst][j_min_rasst] = elem;
        in_plat.push_back(elem);
        it1 = find(free_elems.begin(), free_elems.end(), elem);
        free_elems.erase(it1);

        cout << "Добавляем элемент " << elem << ". Плата принимает вид:\n";
        for (int i = 0; i < plat.size(); i++) {
            for (int j = 0; j < plat.size(); j++) {
                cout << plat[i][j] << " ";
            }
            cout << "\n";
        }
    }

    cout << "Плата:\n";
    for (int i = 0; i < plat.size(); i++) {
        for (int j = 0; j < plat.size(); j++) {
            cout << plat[i][j] << " ";
        }
        cout << "\n";
    }

    sort(in_plat.begin(), in_plat.end());

    cout << "Суммарная длина соединений до перестановок:\n";
    int sum_dl_soed = 0, rasst_betw, to_sumds;
    vector <vector <int>> coords;
    vector <int> to_coords;
    vector<int> el_dl_soed;


    for (int i = 0; i < in_plat.size(); i++) {
        for (int j = 0; j < plat.size(); j++) {
            it1 = find(plat[j].begin(), plat[j].end(), in_plat[i]);
            if (it1 != plat[j].end()) {
                to_coords.push_back(j + 1);
                to_coords.push_back(distance(plat[j].begin(), it1));
                coords.push_back(to_coords);
                to_coords.clear();
            }
        }
    }

    for (int i = 0; i < coords.size(); i++) {
        to_sumds = 0;
        for (int j = i + 1; j < coords.size(); j++) {
            rasst_betw = abs(coords[i][0] - coords[j][0]) + abs(coords[i][1] - coords[j][1]);
            to_sumds += rasst_betw * matrix[plat[coords[i][0] - 1][coords[i][1]] - 1][plat[coords[j][0] - 1][coords[j][1]] - 1];
        }
        sum_dl_soed += to_sumds;
    }
    cout << sum_dl_soed << endl;


    int i_rasst, j_rasst, j_min_rasst = -1, i_min_rasst = -1, tmp;
    for (int i = 0; i < coords.size(); i++) {
        for (int j = 0; j < coords.size(); j++) {
            if (i != j) {
                rasst_betw = abs(coords[i][0] - coords[j][0]) + abs(coords[i][1] - coords[j][1]);
                if ((rasst_betw > 0) && (matrix[plat[coords[i][0] - 1][coords[i][1]] - 1][plat[coords[j][0] - 1][coords[j][1]] - 1] != 0)) {
                    // cout << in_plat[i] << " " << in_plat[j] << " " << rasst_betw << endl;
                    if (rasst_betw > 1) {
                        i_min_rasst = coords[j][0] - 1;
                        j_min_rasst = coords[j][1];
                        // cout << in_plat[i] << " " << in_plat[j] << " " << rasst_betw << endl;
                        // cout << i_min_rasst << " " << j_min_rasst << endl;

                        for (int h = 0; h < plat.size(); h++) {
                            for (int k = 0; k < plat[h].size(); k++) {
                                if (plat[h][k] == 0) {
                                    i_rasst = abs(coords[i][0] - 1 - h);
                                    j_rasst = abs(coords[i][1] - k);
                                    if (i_rasst + j_rasst <= rasst_betw) {
                                        rasst_betw = i_rasst + j_rasst;
                                        i_min_rasst = h;
                                        j_min_rasst = k;
                                    }
                                }
                            }
                        }


                        //   cout << i_min_rasst << " " << j_min_rasst << endl;

                        if ((i_min_rasst != coords[j][0] - 1) || (j_min_rasst != coords[j][1])) {
                            plat[i_min_rasst][j_min_rasst] = in_plat[j];
                            plat[coords[j][0] - 1][coords[j][1]] = 0;
                            coords[j][0] = i_min_rasst + 1;
                            coords[j][1] = j_min_rasst;
                        }


                    }
                }
            }

        }
    }

    cout << "Плата после перестановок:\n";
    for (int i = 0; i < plat.size(); i++) {
        for (int j = 0; j < plat.size(); j++) {
            cout << plat[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Суммарная длина соединений после перестановок:\n";
    sum_dl_soed = 0;
    for (int i = 0; i < coords.size(); i++) {
        to_sumds = 0;
        for (int j = i + 1; j < coords.size(); j++) {
            rasst_betw = abs(coords[i][0] - coords[j][0]) + abs(coords[i][1] - coords[j][1]);
            to_sumds += rasst_betw * matrix[plat[coords[i][0] - 1][coords[i][1]] - 1][plat[coords[j][0] - 1][coords[j][1]] - 1];
        }
        sum_dl_soed += to_sumds;
    }
    cout << sum_dl_soed << endl;

}


