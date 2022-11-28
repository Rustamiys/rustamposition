#include <vector>
#include <string>

using namespace std;

vector<int> knut_morris_pratt(string text, string subtext) {
    vector<int> wordPositions;

    int subt_len = subtext.length();
    int text_len = text.length();
	
	// если подстрока это пустая строка
    if (subt_len == 0) {
        wordPositions.push_back(0);
        return wordPositions;
    }

	// если длина текста меньше длины подстроки
    if (text_len < subt_len) {
        return wordPositions;
    }

    // next[i] сохраняет индекс следующего лучшего частичного совпадения
    
    vector<int> next(subt_len + 1, 0);
    
 
    for (int i = 1; i < subt_len; i++) {
        int j = next[i + 1];
 
        while (j > 0 && subtext[j] != subtext[i]) {
            j = next[j];
        }
 
        if (j > 0 || subtext[j] == subtext[i]) {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < text_len; i++) {
        if (text[i] == subtext[j]) {
            if (++j == subt_len) {
                wordPositions.push_back(i - j + 1);
            }
        }
        else if (j > 0) {
            j = next[j];
            i--;
        }
    }
    
    return wordPositions;
}
