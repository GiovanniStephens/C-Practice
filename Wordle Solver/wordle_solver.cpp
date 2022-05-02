/** This program is a basic solver to guess the 
 * Wordle puzzle of the day.
 * 
 * Author:  Giovanni Stephens
 * Date:    02/05/2022
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

std::vector<std::string> read_text_file(std::string filename) {
    std::ifstream infile;
    infile.open(filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();
    return lines;
}

class Solver {
private:
    std::string word_to_guess;

    std::map<std::string, int> get_frequencies(std::string filename) {
        std::map<std::string, int> frequencies;
        std::vector<std::string> lines = read_text_file(filename);
        for (std::string line : lines) {
            std::string word = line.substr(0, line.find(" "));
            int count = std::stoi(line.substr(line.find(" ") + 1));
            frequencies[word] = count;
        }
        return frequencies;
    }
    
    std::vector<std::string> get_five_letter_words(std::vector<std::string> words) {
        std::vector<std::string> five_letter_words;
        for (std::string word : words) {
            if (word.length() == 5) {
                five_letter_words.push_back(word);
            }
        }
        return five_letter_words;
    }

    std::map<char, int> get_letter_counts(std::vector<std::string> words) {
        std::map<char, int> letter_counts;
        for (std::string word : words) {
            for (char letter : word) {
                if (letter_counts.find(letter) == letter_counts.end()) {
                    letter_counts[letter] = 1;
                } else {
                    letter_counts[letter] += 1;
                }
            }
        }
        return letter_counts;
    }

    std::vector<int> get_word_ranking(std::vector<std::string> words, std::map<char, int> letter_counts) {
        std::vector<int> word_ranking;

        for (std::string word : words) {
            // Get unique letters in the word
            std::map<char, int> unique_letters;
            for (char letter : word) {
                if (unique_letters.find(letter) == unique_letters.end()) {
                    unique_letters[letter] = 1;
                } else {
                    unique_letters[letter] += 1;
                }
            }
            int word_score = 0;            
            for (char letter : word) {
                if (unique_letters[letter] > 0) {
                    word_score += letter_counts[letter];
                    unique_letters[letter] = 0;
                }
            }
            word_ranking.push_back(word_score);
        }
        return word_ranking;
    }

    std::string get_top_word(std::vector<std::string> words, std::vector<int> word_ranking) {
        int top_word_index = 0;
        for (int i = 1; i < word_ranking.size(); i++) {
            if (word_ranking[i] > word_ranking[top_word_index]) {
                top_word_index = i;
            }
        }
        return words[top_word_index];
    }

    bool is_word_in_vector(std::string word, std::vector<std::string> words) {
        for (std::string w : words) {
            if (w == word) {
                return true;
            }
        }
        return false;
    }

    std::string get_top_word_by_freq(std::vector<std::string> words, std::map<std::string, int> frequencies, std::vector<std::string> previous_guesses) {
        int top_word_index = 0;
        for (int i = 1; i < words.size(); i++) {
            if (frequencies[words[i]] > frequencies[words[top_word_index]] && !is_word_in_vector(words[i], previous_guesses)) {
                top_word_index = i;
            }
        }
        return words[top_word_index];
    }

    // Function to submit a guess to the Wordle puzzle
    // Returns an array with 0's for correct letters but wrong places
    // and 1's for correct letters in the correct places
    // -1 for incorrect guesses
    std::vector<int> submit_guess(std::string guess) {
        std::vector<int> result;
        for (int i = 0; i < guess.length(); i++) {
            if (guess[i] == word_to_guess[i]) {
                result.push_back(1);
            } else if (word_to_guess.find(guess[i]) != std::string::npos) {
                result.push_back(0);
            } else {
                result.push_back(-1);
            }
        }
        return result;
    }

    // Function to check if the input work contains a letter
    bool contains_letter(std::string word, char letter) {
        for (char c : word) {
            if (c == letter) {
                return true;
            }
        }
        return false;
    }

    // Function to filter the list of words based on the result of a guess
    std::vector<std::string> filter_words(std::vector<std::string> words, std::vector<int> result, std::string guess) {
        std::vector<std::string> filtered_words;
        std::cout << std::endl;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < result.size(); j++) {
                // If the letter is incorrect, remove the word if the word has that letter
                if (result[j] == -1) {
                    if (contains_letter(words[i], guess[j])) {
                        break;
                    }
                } else if (result[j] == 0) {
                    // If the letter is correct but in the wrong place, remove the word if the word doesn't have that letter
                    if (!contains_letter(words[i], guess[j])) {
                        break;
                    }
                } else if (result[j] == 1) {
                    if (words[i][j] != guess[j]) {
                        break;
                    }
                }
                // Passed all the tests, add the word to the filtered list
                if (j == result.size() - 1) {
                    filtered_words.push_back(words[i]);
                }
            }
        }
        return filtered_words;
    }

    bool is_correct_guess(std::vector<int> result) {
        for (int i : result) {
            if (i == -1 || i == 0) {
                return false;
            }
        }
        return true;
    }

public:
    Solver(std::string word_to_guess) {
        this->word_to_guess = word_to_guess;
    }

    ~Solver() {
    }

    void solve() {
        // Get a list of words from the dictionary
        std::vector<std::string> words = read_text_file("words_alpha.txt");
        // Filter down to words that are 5 letters long
        std::vector<std::string> five_letter_words = get_five_letter_words(words);
        // Get the letter counts
        std::map<char, int> letter_counts = get_letter_counts(five_letter_words);
        // Get the ranking of each word based on the letter counts
        std::vector<int> word_ranking = get_word_ranking(five_letter_words, letter_counts);
        // Get the first top word based on the ranking
        std::string top_word = get_top_word(five_letter_words, word_ranking);

        std::cout << "Initial guess: " << top_word;
        std::vector<int> guess_result = submit_guess(top_word);
        // Filter the list of words based on the result of the guess
        std::vector<std::string> filtered_words = filter_words(five_letter_words, guess_result, top_word);

        // Get the top word based on the frequency of the words
        std::map<std::string, int> frequencies = get_frequencies("five_letter_word_frequencies.txt");
        std::vector<std::string> previous_guesses;
        while (!is_correct_guess(guess_result)) {
            std::string top_word = get_top_word_by_freq(filtered_words, frequencies, previous_guesses);
            std::cout << "Guess: " << top_word;
            guess_result = submit_guess(top_word);
            previous_guesses.push_back(top_word);
            filtered_words = filter_words(filtered_words, guess_result, top_word);
        }
        std::cout << std::endl;
        std::cout << "Congratulations! You found the word: " << word_to_guess << std::endl;
        

        
        // std::string top_word_by_freq = get_top_word_by_freq(filtered_words, frequencies);
        // std::cout << top_word_by_freq << std::endl;
        // std::vector<int> second_guess = submit_guess(top_word_by_freq);
        // std::vector<std::string> second_filtered_words = filter_words(filtered_words, second_guess, top_word_by_freq);

        // // get top word based on frequency
        // std::string top_word_by_freq_2 = get_top_word_by_freq(second_filtered_words, frequencies);
        // std::cout << top_word_by_freq_2 << std::endl;
        // std::vector<int> third_guess = submit_guess(top_word_by_freq_2);
        // std::vector<std::string> third_filtered_words = filter_words(second_filtered_words, third_guess, top_word_by_freq_2);

        // // get top word based on frequency
        // std::string top_word_by_freq_3 = get_top_word_by_freq(third_filtered_words, frequencies);
        // std::cout << top_word_by_freq_3 << std::endl;
        // std::vector<int> fourth_guess = submit_guess(top_word_by_freq_3);
        // std::vector<std::string> fourth_filtered_words = filter_words(third_filtered_words, fourth_guess, top_word_by_freq_3);

    }
};


int main() {
    Solver solver = Solver("olive");
    solver.solve();

    return 0;
}