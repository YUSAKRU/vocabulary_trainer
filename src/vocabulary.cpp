#include "vocabulary.hpp"
#include <iostream>
#include <algorithm>
#include <random>

// Kullanıcıdan 10 kelime ve Türkçe karşılıklarını alıyoruz
std::vector<Word> getWordsFromUser() {
    std::vector<Word> words;
    for (int i = 0; i < 10; i++) {
        Word word;
        std::cout << i+1 << ". İngilizce kelimeyi girin: ";
        std::cin >> word.english;
        std::cout << i+1 << ". Türkçe karşılığını girin: ";
        std::cin >> word.turkish;
        word.incorrectCount = 0;  // Başlangıçta yanlış sayısı 0
        words.push_back(word);
    }
    return words;
}

// Kelimeleri rastgele 3'er defa sor
void quizUser(std::vector<Word>& words) {
    std::random_device rd;
    std::mt19937 g(rd());

    // Her kelimeyi 3 kez sormak için listeyi çoğaltalım
    std::vector<Word> quizWords;
    for (const auto& word : words) {
        for (int i = 0; i < 3; i++) {
            quizWords.push_back(word);
        }
    }

    // Kelimeleri rastgele sıraya sok
    std::shuffle(quizWords.begin(), quizWords.end(), g);

    // Soruları sor
    for (auto& word : quizWords) {
        std::string answer;
        std::cout << word.english << " kelimesinin Türkçe karşılığını girin: ";
        std::cin >> answer;

        if (answer != word.turkish) {
            std::cout << "Yanlış! Doğru cevap: " << word.turkish << std::endl;
            // Yanlış sayısını artır
            for (auto& originalWord : words) {
                if (originalWord.english == word.english) {
                    originalWord.incorrectCount++;
                    break;
                }
            }
        } else {
            std::cout << "Doğru!" << std::endl;
        }
    }
}

// Sonuçları ekrana yazdır
void showResults(const std::vector<Word>& words) {
    std::cout << "\nSonuçlar:\n";
    for (const auto& word : words) {
        std::cout << word.english << " kelimesi için " << word.incorrectCount 
                  << " hata yaptınız." << std::endl;
    }
}