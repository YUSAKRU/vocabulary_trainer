#include "vocabulary.hpp"
#include <iostream>

int main() {
    std::cout << "İngilizce Kelime Öğrenme Programına Hoş Geldiniz!\n";
    
    // 1. Adım: Kullanıcıdan 10 kelime ve karşılıklarını al
    std::vector<Word> words = getWordsFromUser();

    // 2. Adım: Rastgele kelimeleri sor
    quizUser(words);

    // 3. Adım: Sonuçları göster
    showResults(words);

    return 0;
}