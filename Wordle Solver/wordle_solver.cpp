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
    std::string starting_guess;

    std::map<std::string, int> get_frequencies(std::vector<std::string> lines) {
        std::map<std::string, int> frequencies;
        for (std::string line : lines) {
            std::string word = line.substr(0, line.find(" "));
            int count = std::stoi(line.substr(line.find(" ") + 1));
            frequencies[word] = count;
        }
        return frequencies;
    }

    bool contains_non_alpha (std::string word) {
        for (char c : word) {
            if (!isalpha(c)) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::string> get_words(std::vector<std::string> lines) {
        std::vector<std::string> words;
        for (std::string line : lines) {
            std::string word = line.substr(0, line.find(" "));
            if (contains_non_alpha(word)) {
                continue;
            } else {
                words.push_back(word);
            }
        }
        return words;
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
        std::string best_word = "";
        for (std::string word : words) {
            if (is_word_in_vector(word, previous_guesses)) {
                continue;
            }
            if (frequencies[word] > frequencies[best_word]) {
                best_word = word;
            }
        }
        return best_word;
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
                    // If the letter is correct and in the correct place, but the guess letter at that place is not it.
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
        this->starting_guess = "arose";
    }

    ~Solver() {
    }

    void solve() {
        // Load the word counts
        std::vector<std::string> lines = read_text_file("five_letter_word_frequencies.txt");
        // Get a list of words from the dictionary
        std::vector<std::string> five_letter_words = get_words(lines);
        std::cout << "Initial guess: " << this->starting_guess;
        std::vector<int> guess_result = submit_guess(this->starting_guess);
        // Filter the list of words based on the result of the guess
        std::vector<std::string> filtered_words = filter_words(five_letter_words, guess_result, this->starting_guess);

        // Get the top word based on the frequency of the words
        std::map<std::string, int> frequencies = get_frequencies(lines);
        std::vector<std::string> previous_guesses;
        while (!is_correct_guess(guess_result)) {
            std::string top_word = get_top_word_by_freq(filtered_words, frequencies, previous_guesses);
            std::cout << "Guess: " << top_word;
            guess_result = submit_guess(top_word);
            previous_guesses.push_back(top_word);
            filtered_words = filter_words(filtered_words, guess_result, top_word);
        }
        std::cout << std::endl;
        std::cout << "Congratulations! You found the word: " << word_to_guess;
        std::cout << " in " << previous_guesses.size() + 1 << " guesses." << std::endl;
    }
};


int main() {
    Solver solver = Solver("atoll");
    solver.solve();

    return 0;
}