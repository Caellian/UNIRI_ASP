#include <ios>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

// Izvor: https://github.com/Caellian/Reference/tree/master/algorithms/sorting/quicksort
int partition(int *a, size_t lo, size_t hi)
{
  std::cout << "Particioniranje raspona indeksa: [" << lo << ", " << hi << "]\n";

  int i = lo, j = hi+1;         // left and right scan indices
  int v = a[lo];                // partitioning item
  int buff;
  std::cout << "Pivot je prvi element particije: " << v << "\n";

  while (true)
  { // Scan right, scan left, check for scan complete, and swap.
    std::cout << "Pomicanje lijevog pokazivaća udesno do vrijednosti veće od: " << v << '\n';
    while (a[++i] < v) {if (i == hi) {
        std::cout << "Lijevi pokazivać je došao do kraja particije.\n";
        break;
    }};
    if (i != hi) {
        std::cout << "Lijevi pokazivać je zastao na indeksu: "<< i << " (" << a[i] << ").\n";
    }
    std::cout << "Pomicanje desnog pokazivaća ulijevo do vrijednosti manje od: " << v << '\n';
    while (v < a[--j]) if (j == lo) {
        std::cout << "Desni pokazivać je došao do kraja particije.\n";
        break;
    };
    if (j != lo) {
        std::cout << "Desni pokazivać je zastao na indeksu: "<< j << " (" << a[j] << ").\n";
    }

    if (i >= j) {
        std::cout << "i >= j; izlaz iz petlje\n";
        break;
    };

    std::cout << "Zamjena vrijednosti na indeksima: " << i << " (" << a[i] << ") i " << j << " (" << a[j] << ")\n";
    buff = a[i];
    a[i] = a[j];
    a[j] = buff;
  }

  std::cout << "Zamjena pivota "<< lo << " (" << a[lo] <<") sa j: " << j << " (" << a[j] << ")" << std::endl;
  buff = a[lo];
  a[lo] = a[j];
  a[j] = buff;
  return j;
}

void quicksort(int *a, size_t lo, size_t hi)
{
  if (hi <= lo) return;
  int j = partition(a, lo, hi);
  std::cout << "Nova granica za podparticije je: " << j << '\n';
  // tu je bila pogreška npr. i nju sam ispravio dok sam kopirao sada

  std::cout << "Sortiranje lijeve podparticije: ["<<lo<<", "<<j-1<<"]\n";
  quicksort(a, lo, j - 1);
  std::cout << "Sortiranje desne podparticije: ["<<j+1<<", "<<hi<<"]\n";
  quicksort(a, j + 1, hi);
}

int main() {
    std::vector<int> data;

    std::ifstream data_in {"data.in"};

    if (!data_in.is_open()) {
        std::cerr << "'data.in' ne postoji.\n";
        return 1;
    }

    // read comma separated data from data_in into data array
    std::string token;
    while (std::getline(data_in, token, ',')) {
        int number = std::stoi(token);
        data.push_back(number);
    }
    data_in.close();
    data.shrink_to_fit();

    std::cout << "Učitano " << data.size() << " vrijednosti:\n";
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i];
        if (i + 1 == data.size()) break;
        std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Sortiranje...\n";
    quicksort(data.data(), 0, data.size() - 1);

    std::cout << "Sortirano " << data.size() << " vrijednosti:\n";
    auto sorted = std::ofstream("data.out");
    for (int i = 0; i < data.size(); i++) {
        sorted << data[i];
        std::cout << data[i];
        if (i + 1 == data.size()) break;
        sorted << ',';
        std::cout << ", ";
    }
    sorted << std::endl;
    sorted.close();
    std::cout << std::endl;

    return 0;
}
