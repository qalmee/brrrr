
#include "Service.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <functional>

long double Service::anyEntropy(const std::wstring &s, size_t width, bool binaryLog, std::wofstream *fout) {
    std::function<long double(const long double)> logX;
    if (binaryLog) {
        logX = ::log2l;
    } else {
        logX = Service::log3;
    }
    std::wstring sequence;
    std::unordered_map<std::wstring, uint32_t> m;
    m.reserve(1U << 10U);
    m.max_load_factor(0.5);
    for (size_t j = 0; j < width && j < s.size(); j++) {
        sequence.push_back(s[j]);
    }
    for (size_t i = width; i < s.size(); i++) {
        m[sequence]++;
        sequence.erase(sequence.begin());
        sequence.push_back(s[i]);
    }
    m[sequence]++;
    std::vector<Service::schemaAnyItem> v;
    for (const auto &t : m) {
        v.push_back({t.first, t.second, (long double) t.second / (s.size() - width + 1)});
    }
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.count > b.count;
    });

    long double h = 0;
    for (const auto &t : v) {
        h += t.p * logX(t.p);
        if (fout != nullptr)
            *fout << t.sequence << L" " << t.p << L" " << t.count << std::endl;
    }
    h /= width;
    h *= -1;
    return h;
}

std::wstring Service::prepString(const std::wstring &in) {
    std::wstring s;
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

double Service::avgLenOfCode(const std::unordered_map<wchar_t, std::pair<int64_t, double>> &symbols,
                             const std::unordered_map<wchar_t, std::list<bool>> &codes) {
    //std::unordered_map<std::pair<wchar_t, wchar_t >, int> mp;
    double avgLen = 0;
    for (const auto &pr : codes) {
        avgLen += pr.second.size() * symbols.at(pr.first).second;
    }
    return avgLen;
}

double Service::avgLenOfCode(const std::map<std::wstring, std::pair<int64_t, double>> &symbols,
                             const std::map<std::wstring, std::list<bool>> &codes) {
    //std::unordered_map<std::pair<wchar_t, wchar_t >, int> mp;
    double avgLen = 0;
    for (const auto &pr : codes) {
        avgLen += pr.second.size() * symbols.at(pr.first).second;
    }
    return avgLen;
}

void Service::gen() {
    std::ofstream fout("f3.txt");
    const int32_t size = 30000;
    std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    auto rng = std::bind(distribution, generator);
    std::vector<double> chances;
    chances.push_back(0.5);
    chances.push_back(0.5);
    std::vector<char> v;
    v.reserve(size);
    for (int32_t i = 0; i < size; i++) {
        double p = rng();
        for (size_t j = 0; j < chances.size(); j++) {
            if (p - chances[j] <= 0 || j == chances.size() - 1) {
                v.push_back((char) ('0' + j));
                break;
            }
            p -= chances[j];
        }
    }
    shuffle(v.begin(), v.end(), generator);
    for (auto ch : v) {
        fout << ch;
    }
    fout.close();
}

wchar_t Service::to_lower(wchar_t ch) {
    static std::unordered_map<wchar_t, wchar_t> m;
    static const std::wstring s = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    static const std::wstring s1 = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    static const std::wstring se = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::wstring se1 = L"abcdefghijklmnopqrstuvwxyz";
    for (static size_t i = 0; i < s.size(); i++) {
        m[s[i]] = s1[i];
    }
    for (static size_t i = 0; i < se.size(); i++) {
        m[se[i]] = se1[i];
    }
    if (m.count(ch)) {
        return m[ch];
    }
    return ch;
}

long double Service::log3(const long double x) {
    return log(x) / log(3.0);
}