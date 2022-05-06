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
    std::vector<std::string> lines;
    std::vector<std::string> five_letter_words;
    std::map<std::string, int> frequencies;

    std::map<std::string, int> get_frequencies(std::vector<std::string> lines) {
        std::map<std::string, int> frequencies;
        for (std::string line : lines) {
            std::string word = line.substr(0, line.find(" "));
            int count = std::stoi(line.substr(line.find(" ") + 1));
            frequencies[word] = count;
        }
        return frequencies;
    }

    bool contains_non_alpha(std::string word) {
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

    bool is_word_in_vector(std::string word, std::vector<std::string> words) {
        for (std::string w : words) {
            if (w == word) {
                return true;
            }
        }
        return false;
    }

    std::string
    get_top_word_by_freq(std::vector<std::string> words,
                         std::map<std::string, int> frequencies,
                         std::vector<std::string> previous_guesses) {
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
    std::vector<std::string> filter_words(std::vector<std::string> words,
                                          std::vector<int> result,
                                          std::string guess) {
        std::vector<std::string> filtered_words;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < result.size(); j++) {
                // If the letter is incorrect, remove the word if the word has
                // that letter
                if (result[j] == -1) {
                    if (contains_letter(words[i], guess[j])) {
                        break;
                    }
                } else if (result[j] == 0) {
                    // If the letter is correct but in the wrong place, remove
                    // the word if the word doesn't have that letter
                    if (!contains_letter(words[i], guess[j])) {
                        break;
                    }
                } else if (result[j] == 1) {
                    // If the letter is correct and in the correct place, but
                    // the guess letter at that place is not it.
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
        this->lines = read_text_file("five_letter_word_frequencies.txt");
        this->five_letter_words = get_words(lines);
        this->frequencies = get_frequencies(lines);
    }

    ~Solver() {}

    void solve() {
        // std::cout << "Initial guess: " << this->starting_guess;
        std::vector<int> guess_result = submit_guess(this->starting_guess);
        // Filter the list of words based on the result of the guess
        std::vector<std::string> filtered_words =
            filter_words(five_letter_words, guess_result, this->starting_guess);
        std::vector<std::string> previous_guesses;
        std::string top_word = "";
        int previous_number_of_options = filtered_words.size();
        while (!is_correct_guess(guess_result)) {
            top_word = get_top_word_by_freq(filtered_words, frequencies,
                                            previous_guesses);
            // std::cout << "Guess: " << top_word;
            guess_result = submit_guess(top_word);
            previous_guesses.push_back(top_word);
            previous_number_of_options = filtered_words.size();
            filtered_words =
                filter_words(filtered_words, guess_result, top_word);
        }
        std::cout << "Congratulations! You found the word: " << word_to_guess;
        std::cout << " in " << previous_guesses.size() + 1 << " guesses."
                  << std::endl;
    }

    void help_solve(std::vector<std::vector<int>> results,
                    std::vector<std::string> previous_guesses) {
        std::vector<std::string> filtered_words =
            filter_words(five_letter_words, results[0], previous_guesses[0]);
        for (int i = 1; i < results.size(); i++) {
            filtered_words =
                filter_words(filtered_words, results[i], previous_guesses[i]);
        }
        std::string top_word =
            get_top_word_by_freq(filtered_words, frequencies, previous_guesses);
        std::cout << "Recommended guess: " << top_word << std::endl;
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

    void set_starting_guess(std::string guess) { this->starting_guess = guess; }

    void set_word_to_guess(std::string word) { this->word_to_guess = word; }
};

int main() {
    std::vector<std::string> words_to_guess = {
        "cigar", "rebut", "sissy", "humph", "awake", "blush",
        "focal", "evade", "naval", "serve", "heath", "dwarf",
        "model", "karma", "stink", "grade", "quiet", "bench"};
    Solver solver = Solver(words_to_guess[0]);
    solver.solve();
    for (int i = 1; i < words_to_guess.size(); i++) {
        solver.set_word_to_guess(words_to_guess[i]);
        solver.solve();
    }
    // std::vector<std::string> previous_guesses;
    // std::vector<std::vector<int>> results;
    // previous_guesses.push_back("arose");
    // previous_guesses.push_back("march");
    // for (int i = 0; i < 2; i++) {
    //     results.push_back(solver.submit_guess(previous_guesses[i]));
    // }
    // solver.help_solve(results, previous_guesses);
    return 0;
}