#include "raylib.h"
#include "vocabulary.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

// Pencere boyutu
const int screenWidth = 800;
const int screenHeight = 450;

// Uygulama durumları
enum AppState {
    MENU,     // Kelime girişi
    QUIZ,     // Soru sorulan bölüm
    RESULTS   // Sonuçlar gösteriliyor
};

int main() {
    // Raylib'i başlat
    InitWindow(screenWidth, screenHeight, "Ingilizce Kelime Ogrenme");

    AppState appState = MENU;  // Başlangıçta ana menüdeyiz
    std::vector<Word> words;   // Kelime listesi
    int wordIndex = 0;         // Hangi kelimeyi gösterdiğimizi takip eder
    std::string currentAnswer = "";  // Kullanıcının girdiği cevap
    char inputBuffer[64] = ""; // Kullanıcıdan kelime girişi için buffer

    // Klavyeden girdi alma
    int letterCount = 0;
    SetTargetFPS(60); // Kare hızını 60'a sabitle

    // Ana döngü
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (appState == MENU) {
            // Kelime giriş ekranı
            DrawText("10 Ingilizce kelime ve karsiliklarini girin:", 50, 50, 20, DARKGRAY);

            if (wordIndex < 10) {
                // İngilizce kelimeyi al
                DrawText("Ingilizce kelimeyi girin:", 50, 100, 20, DARKGRAY);
                DrawText(inputBuffer, 300, 100, 20, BLUE);

                // Kullanıcıdan karakter girişi al
                int key = GetKeyPressed();
                if ((key >= 32) && (key <= 125) && (letterCount < 63)) {
                    inputBuffer[letterCount] = (char)key;
                    inputBuffer[letterCount + 1] = '\0'; // Dizi sonuna null karakter koyuyoruz
                    letterCount++;
                }

                // Backspace ile karakter silme
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (letterCount > 0) {
                        letterCount--;
                        inputBuffer[letterCount] = '\0';
                    }
                }

                // 'Enter' ile kelimeyi kaydet
                if (IsKeyPressed(KEY_ENTER)) {
                    Word word;
                    word.english = inputBuffer;
                    word.incorrectCount = 0;
                    words.push_back(word);  // Kelimeyi listeye ekle
                    wordIndex++;
                    letterCount = 0;
                    strcpy(inputBuffer, "");  // Buffer'ı temizle
                }

            } else {
                DrawText("Kelimeler girildi. Quiz'e baslamak icin 'Enter' tusuna bas.", 50, 200, 20, DARKGRAY);
                if (IsKeyPressed(KEY_ENTER)) {
                    appState = QUIZ;
                    wordIndex = 0;  // Quiz başlarken sıfırlıyoruz
                }
            }
        } else if (appState == QUIZ) {
            // Quiz ekranı: Kullanıcıya kelime soruluyor
            if (wordIndex < words.size()) {
                DrawText(words[wordIndex].english.c_str(), 50, 100, 20, DARKGRAY);
                DrawText("Turkce karsiligini girin:", 50, 150, 20, DARKGRAY);
                DrawText(currentAnswer.c_str(), 300, 150, 20, BLUE);

                if (IsKeyPressed(KEY_ENTER)) {
                    if (currentAnswer != words[wordIndex].turkish) {
                        words[wordIndex].incorrectCount++;
                    }
                    currentAnswer = "";
                    wordIndex++;
                }

                // Kullanıcıdan karakter girişlerini al
                int key = GetKeyPressed();
                if (key >= 32 && key <= 126) {
                    currentAnswer += (char)key;
                }
            } else {
                appState = RESULTS;
            }
        } else if (appState == RESULTS) {
            // Sonuç ekranı
            DrawText("Sonuclar:", 50, 50, 20, DARKGRAY);
            int yOffset = 100;
            for (const auto& word : words) {
                std::string result = word.english + ": " + std::to_string(word.incorrectCount) + " hata";
                DrawText(result.c_str(), 50, yOffset, 20, RED);
                yOffset += 30;
            }
            DrawText("Cikmak icin 'ESC' tusuna bas", 50, screenHeight - 50, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}