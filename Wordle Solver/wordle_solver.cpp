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

/** This function takes a string and returns a vector of
 * strings, where each element is a line from the text file.
 * 
 * @param file_name The name of the file to be read.
 * @return A vector of strings, where each element is a line from the text file.
 */
std::vector<std::string> read_text_file(std::string filename) {
    std::ifstream infile;
    try {    
        infile.open(filename);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
        return lines;
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return std::vector<std::string>();
    }
}

std::vector<std::string> read_past_answers_from_csv(std::string filename) {
    std::vector<std::string> lines;
    std::vector<std::string> answers;
    lines = read_text_file(filename);
    std::string delimiter = ",";
    for (auto line : lines) {
        // Grab the second element in the line, which is the answer
        std::string answer = line.substr(line.find(delimiter) + 1);
        answer = answer.substr(0, answer.find(delimiter));
        answers.push_back(answer);
    }
    return answers;
}


/** This class contains the solver functions to 
 * guess the Wordle puzzle of the day.
 */
class Solver {
  private:
    // For is you have an input word to try to guess.
    std::string word_to_guess;
    // This is the starting guess.
    // (Based on a word that maximises the probability of guessing the word.)
    std::string starting_guess;
    std::vector<std::string> lines;
    std::vector<std::string> five_letter_words;
    std::map<std::string, int> frequencies;

    /** This function takes the lines from the text file and
     * splits the lines into words and their count based on Wiki data.
     * 
     * @param lines The lines from the text file.
     * @return A map of words and their count.
     */
    std::map<std::string, int> get_frequencies(std::vector<std::string> lines) {
        std::map<std::string, int> frequencies;
        for (std::string line : lines) {
            std::string word = line.substr(0, line.find(" "));
            int count = std::stoi(line.substr(line.find(" ") + 1));
            frequencies[word] = count;
        }
        return frequencies;
    }

    /** Takes a string and checks if there are any 
     * non-alphabetical characters in it.
     * 
     * @param word The string to check.
     * @return True if there are no non-alphabetical characters, false otherwise.
     */
    bool contains_non_alpha(std::string word) {
        for (char c : word) {
            if (!isalpha(c)) {
                return true;
            }
        }
        return false;
    }

    /** Takes the lines from the input file and splits them into
     * words.
     * 
     * @param lines The lines from the input file.
     * @return A vector of strings, where each element is a word.
     * @see get_frequencies
     */
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

    /** Checks that a word is in the words vector.
     * 
     * @param word The word to check.
     * @param words The vector of words to check against.
     * @return True if the word is in the vector, false otherwise.
     */
    bool is_word_in_vector(std::string word, std::vector<std::string> words) {
        for (std::string w : words) {
            if (w == word) {
                return true;
            }
        }
        return false;
    }

    /** Gets the top word based on how frequenctly is appears 
     * on Wikipedia.
     * 
     * @param words The vector of words to pick from.
     * @param frequencies The map of words and their frequencies.
     * @param previous_guess The previous guess so that we do not 
     *                   pick the same word twice. 
     * @return The top word.
     */
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

    /** Checks if a word contains a certain letter.
     * 
     * @param word The word to check.
     * @param letter The letter to check for.
     * @return True if the word contains the letter, false otherwise.
     */
    bool contains_letter(std::string word, char letter) {
        for (char c : word) {
            if (c == letter) {
                return true;
            }
        }
        return false;
    }

    /** Filters a vector of words to only contain words that
     * could possibly fit the result of the previous guess.
     * 
     * @param words The vector of words to filter.
     * @param result The previous guess' result, which is a vector containing ints between -1 and 1.
     * @param previous_guess The previous guess.
     * @return A vector of words that could possibly fit the result of the previous guess.
     */
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

    /** Check that the resulting vector from the guess
     * is the correct answer. 
     * 
     * @param result The result of the guess, which is a vector containing ints between -1 and 1.
     * @return True if the result is correct, false otherwise.
     * @see submit_guess
     */
    bool is_correct_guess(std::vector<int> result) {
        for (int i : result) {
            if (i == -1 || i == 0) {
                return false;
            }
        }
        return true;
    }

  public:
    /** Constructor.
     * 
     * @param word_to_guess The word to guess.
     */
    Solver(std::string word_to_guess) {
        this->word_to_guess = word_to_guess;
        this->starting_guess = "arose";
        this->lines = read_text_file("five_letter_word_frequencies.txt");
        this->five_letter_words = get_words(lines);
        this->frequencies = get_frequencies(lines);
    }

    /** Destructor.*/
    ~Solver() {
        lines.clear();
        lines.shrink_to_fit();
        five_letter_words.clear();
        five_letter_words.shrink_to_fit();
        frequencies.clear();        
    }

    /** Solves the puzzle.*/
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

    /** Makes a recommendation for the next word to guess.
     * 
     * @param results a vector of vectors containing the results of the previous guesses.
     * @param previous_guesses a vector of the previous guesses.
     * @return the next word to guess.
     * @see get_top_word_by_freq
     */
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

    /** Submits a guess to get the results from the guess.
     * 
     * The results are a vector of ints between -1 and 1.
     * -1 means the letter is incorrect, 0 means the letter is correct but in the wrong place,
     * and 1 means the letter is correct and in the correct place.
     * 
     * (NOTE: The results differ from Wordle in that Wordle will 
     * tell you that one letter is correct in the correct place, and 
     * any repitition of that letter will be counted as incorrect if the correct
     * word only has one of that letter. 
     * In contrast, if your letter is in the right place, the repitition will be
     * counted as correct but in the wrong place.)
     * 
     * @param guess The guess to submit.
     * @return The results of the guess.
     * @see is_correct_guess
     */ 
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

    /** Sets the starting guess.
     * 
     * @param guess The starting guess.
    */
    void set_starting_guess(std::string guess) { this->starting_guess = guess; }

    /** Set the word to guess.
     * 
     * @param word The word to guess.
     */
    void set_word_to_guess(std::string word) { this->word_to_guess = word; }
};

int main() {
    // std::vector<std::string> words_to_guess = {
    //     "cigar", "rebut", "sissy", "humph", "awake", "blush",
    //     "focal", "evade", "naval", "serve", "heath", "dwarf",
    //     "model", "karma", "stink", "grade", "quiet", "bench"};
    // Solver solver = Solver(words_to_guess[0]);
    // solver.solve();
    // for (int i = 1; i < words_to_guess.size(); i++) {
    //     solver.set_word_to_guess(words_to_guess[i]);
    //     solver.solve();
    // }
    // Solver solver = Solver("cigar");
    // std::vector<std::string> previous_guesses;
    // std::vector<std::vector<int>> results;
    // previous_guesses.push_back("shape");
    // previous_guesses.push_back("stout");
    // previous_guesses.push_back("grist");
    // previous_guesses.push_back("twist");
    // results = {{0,-1,-1,-1,-1}, {0,0,-1,-1,1}, {-1,-1,0,1,1}, {0,-1,0,1,1}};
    // solver.help_solve(results, previous_guesses);
    std::vector<std::string> past_answers = read_past_answers_from_csv("wordle_answers.csv");
    Solver solver(past_answers[1]);
    solver.solve();
    for (int i = 2; i < past_answers.size(); i++) {
        solver.set_word_to_guess(past_answers[i]);
        solver.solve();
    }
    return 0;
}