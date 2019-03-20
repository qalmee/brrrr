#include <vector>
#include <queue>
#include <fstream>
#include <functional>
#include <iomanip>
#include <bitset>
#include <random>
#include "codes/Huffman.h"
#include "codes/Fano.h"
#include "codes/ShannonImpl.h"
#include "codes/HilbertMoore.h"
#include "codes/TernaryHuffman.h"
#include "service/Service.h"

#define input ios_base::sync_with_stdio(0)
#define itn int
#define vecotr vector
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;




int main() {
    setlocale(LC_ALL, "Russian");
    wifstream fin("war and peace.txt");
    wofstream fout("out.txt");
    wstring s((istreambuf_iterator<wchar_t>(fin)), (istreambuf_iterator<wchar_t>()));
    s = Service::prepString(s);
    Huffman huffman(s);
    HilbertMoore hilbertMoore(s);
    Fano fano(s);
    ShannonImpl shannon(s);
    TernaryHuffman ternaryHuffman(s);

    double H1 = Service::anyEntropy(s, 1, true);
    double H2 = Service::anyEntropy(s, 1, false);

    fout << L"Huffman:" << endl;
    const auto &symbols = huffman.getSymbolsTable();
    auto mp = huffman.getSortedCodes();
    fout.precision(11);
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }
    double avgLen = Service::avgLenOfCode(huffman.getSymbolsTable(), huffman.getCodes());
    fout << "H = " << H1 << endl;
    fout << "L(avg) = " << avgLen << endl;

    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;

    fout << L"Fano:" << endl;
    mp = fano.getSortedCodes();
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }
    avgLen = Service::avgLenOfCode(fano.getSymbolsTable(), fano.getCodes());
    fout << "H = " << H1 << endl;
    fout << "L(avg) = " << avgLen << endl;

    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;
    fout << L"Shannon:" << endl;
    mp = shannon.getSortedCodes();
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }
    avgLen = Service::avgLenOfCode(shannon.getSymbolsTable(), shannon.getCodes());
    fout << "H = " << H1 << endl;
    fout << "L(avg) = " << avgLen << endl;

    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;

    fout << L"Ternary Huffman:" << endl;
    auto mp1 = ternaryHuffman.getSortedTernaryCodes();
    for (const auto &x : mp1) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }
    avgLen = Service::avgLenOfCode(ternaryHuffman.getSymbolsTable(), ternaryHuffman.getCodes());
    fout << "H = " << H2 << endl;
    fout << "L(avg) = " << avgLen / 2.0 << endl;

    fout.close();
    fin.close();

    return 0;
}