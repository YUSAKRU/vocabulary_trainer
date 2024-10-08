#ifndef VOCABULARY_HPP
#define VOCABULARY_HPP

#include <string>
#include <vector>

// Kelimeleri ve yanlış yapılan sayıları takip eden veri yapısı
struct Word {
    std::string english;
    std::string turkish;
    int incorrectCount;  // Yanlış yapılan sayılar
};

// Kullanıcıdan kelimeleri al
std::vector<Word> getWordsFromUser();

// Kelimeleri rastgele sırayla sor
void quizUser(std::vector<Word>& words);

// Skorları göster
void showResults(const std::vector<Word>& words);

#endif // VOCABULARY_HPP