#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <functional>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <set>
#include <cmath>
#include <map>
#include <unordered_set>
#include <bitset>
#include <random>
#include <chrono>
#include "codes/Huffman.h"
#include "codes/Fano.h"
#include "codes/ShannonImpl.h"
#include "codes/HilbertMoore.h"

#define input ios_base::sync_with_stdio(0)
#define itn int
#define vecotr vector
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

struct schemaPairItem {
    wchar_t first, second;
    int count;
    double p;
};

struct schemaItem {
    wchar_t ch;
    int count;
    double p;
};

wchar_t to_lower(wchar_t ch) {
    static unordered_map<wchar_t, wchar_t> m;
    static const wstring s = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    static const wstring s1 = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    static const wstring se = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const wstring se1 = L"abcdefghijklmnopqrstuvwxyz";
    for (static int i = 0; i < (int) s.size(); i++) {
        m[s[i]] = s1[i];
    }
    for (static int i = 0; i < (int) se.size(); i++) {
        m[se[i]] = se1[i];
    }
    if (m.count(ch)) {
        return m[ch];
    }
    return ch;
}

void gen() {
    freopen("f2.txt", "w", stdout);
    const int size = 20000;
    std::mt19937_64 generator(chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    auto rng = std::bind(distribution, generator);
    vector<double> chances;
    chances.push_back(0.96);
    chances.push_back(0.01);
    chances.push_back(0.01);
    chances.push_back(0.02);
    vector<char> v;
    v.reserve(size);
    for (int i = 0; i < size; i++) {
        double p = rng();
        for (int j = 0; j < (int) chances.size(); j++) {
            if (p - chances[j] <= 0 || j == (int) chances.size() - 1) {
                v.push_back((char) ('a' + j));
                break;
            }
            p -= chances[j];
        }
    }
    shuffle(v.begin(), v.end(), generator);
    for (auto ch : v) {
        cout << ch;
    }
}

double singleEntropy(const wstring &s, wofstream *fout = nullptr) {
    unordered_map<wchar_t, int> m;
    m.reserve(1U << 10);
    double h = 0;
    for_each(s.begin(), s.end(), [&m](const wchar_t ch) {
        m[ch]++;
    });
    vector<schemaItem> v;
    v.reserve(m.size());
    for_each(m.begin(), m.end(), [&h, &s, &v](auto &t) {
        double p = t.second * 1.0 / s.size();
        h += p * log2(p);
        v.push_back({t.first, t.second, p});
    });
    sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.count < b.count;
    });
    if (fout != nullptr)
        for_each(v.begin(), v.end(), [&fout](const auto &t) {
            *fout << fixed << t.ch << L" " << t.p << L" " << t.count << endl;
        });
    h *= -1;
    return h;
}

double doubleEntropy(const wstring &s, wofstream *fout = nullptr) {
    pair<wchar_t, wchar_t> par;
    unordered_map<std::pair<wchar_t, wchar_t>, std::pair<int, double>> m;
    m.reserve(1U << 12);
    for (int i = 0; i < (int) s.size() - 1; i++) {
        if (s[i + 1] == ' ' || s[i + 1] == 27) {
            i++;
            continue;
        }
        par.first = s[i];
        par.second = s[i + 1];
        m[par].first++;
    }
    vector<schemaPairItem> v;
    for (const auto &t : m) {
        v.push_back({t.first.first, t.first.second, t.second.first, t.second.first * 1.0 / s.size()});
    }
    sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.count < b.count;
    });
    double h = 0;
//    for (auto &t : m){
//        t.second.second = t.second.first * 1.0 / s.size();
//        h += t.second.second * log2(t.second.second);
//        if (fout != nullptr) *fout<<t.first.first<<t.first.second<<" "<<t.second.second<<" "<<log2(t.second.second)<<" "<<t.second.second * log2(t.second.second)<<endl;
//    }
    for (auto &t : v) {
        h += t.p * log2(t.p);
        if (fout != nullptr)
            *fout << t.first << t.second << L" " << t.p << L" " << t.count << endl;
    }
    h /= -2.0;
    return h;
}

wstring prepString(const wstring &in) {
    wstring s;
    s.reserve(in.size());
    for (const wchar_t ch : in) {
        wchar_t t = to_lower(ch);
        if (t == L'.' || t == L',' || t == L'!' || t == L'?'
            || t == L'(' || t == L')' || t == L'[' || t == L']'
            || t == L'\"' || t == L'<' || t == L'>' || t == L'`'
            || t == L'\'' || t == L'{' || t == L'}' || t == L'*'
            || t == L'-' || t == L'_' || t == L'=' || t == L';'
            || t == L':' || t == L'/' || t == L'”' || t == L'“'
            || t == L'’' || t == L'‘' || t == L'^' || t == L'#'
            || t == L'%' || t == L'№' || t == L'&' || t == L'$'
            || t == L'@' || t <= 31 || t == 171 || t == 187
            || t == 8230 || t == 160 || t == 8212) {
            t = L'.';
        }
        if (t == L'ё') t = L'е';
        if (t == L'Ъ') t = L'ь';
        s.push_back(t);
    }
    return s;
}

void tmp() {
    wcout << L"Do you need to process the text to remove capital letters and some other stuff? y/n" << endl;
    wchar_t ch;
    wcin >> ch;
    wcin.clear();
    wcout << L"Input number to choose which file do you want to parse. 1/2/3" << endl;
    int number;
    wcin >> number;
    wcin.clear();
    wifstream fin;
    switch (number) {
        case 1:
            fin.open("hero.txt");
            break;
        case 2:
            fin.open("f2.txt");
            break;
        case 3:
            fin.open("war and peace.txt");
            break;
        default:
            return;
    }
    wofstream fout("out.txt");
    wstring s((istreambuf_iterator<wchar_t>(fin)), (istreambuf_iterator<wchar_t>()));
    if (ch == L'y' || ch == L'Y') {
        s = prepString(s);
    }
    double h;
    h = singleEntropy(s, &fout);
    fout << L"H = " << h << endl;
    h = doubleEntropy(s, &fout);
    fout << L"H = " << h << endl;

    fout.close();
    fin.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    wifstream fin("war and peace.txt");
    wofstream fout("out.txt");
    wstring s((istreambuf_iterator<wchar_t>(fin)), (istreambuf_iterator<wchar_t>()));
    s = prepString(s);
    Huffman huffman(s);
    Fano fano(s);
    ShannonImpl shannon(s);
    HilbertMoore hilbertMoore(s);

    fout << endl;
    fout << endl;
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
    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;

    mp = fano.getSortedCodes();
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }

    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;

    mp = shannon.getSortedCodes();
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }

    fout << endl;
    fout << endl;
    fout << endl;
    fout << endl;

    mp = hilbertMoore.getSortedCodes();
    for (const auto &x : mp) {
        fout << fixed << x.first << L"  " << symbols.at(x.first).second << L"  "
             << setw(5) << symbols.at(x.first).first << L"  ";
        for (const auto &bl : x.second) {
            fout << bl;
        }
        fout << endl;
    }
    fout.close();
    fin.close();

    return 0;
}