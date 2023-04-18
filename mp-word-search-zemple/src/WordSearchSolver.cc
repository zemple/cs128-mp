#include "WordSearchSolver.hpp"
#include "WordLocation.hpp"
#include "CharPositions.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const vector<vector<char>>& puzzle) : puzzle_(puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::Horizontal(const string& word) {
  vector<CharPositions> positions;

  for (size_t row = 0; row < puzzle_height_; row++) { 
    for (size_t col = 0; col < puzzle_width_  - word.size() + 1; col++) {
      for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == puzzle_.at(row).at(col + i) && LocationInBounds(row, col + i)) { 
          CharPositions p = {word[i], row, col + i}; 
          positions.push_back(p);
          if (positions.size() == word.size()) {
            return WordLocation {word, positions};
          }
        } else {
          positions.clear();
        }
      }
    }
  }
  return WordLocation{}; 
}

WordLocation WordSearchSolver::Vertical(const string& word) {
  vector<CharPositions> positions;

  for (size_t col = 0; col < puzzle_width_; col++) { 
    for (size_t row = 0; row < puzzle_height_ - word.size() + 1; row++) {
      for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == puzzle_.at(row + i).at(col) && LocationInBounds(row + i, col)) { 
          CharPositions p = {word[i], row + i, col}; 
          positions.push_back(p);
          if (word.size() == positions.size()) {
            return WordLocation {word, positions}; 
          }
        } else {
          positions.clear();
        }
      }
    }
  }
  return WordLocation{}; 
}  

WordLocation WordSearchSolver::RightDiag(const string& word) {
  vector<CharPositions> positions;

  for (size_t row = 0; row < puzzle_height_ -word.size() + 1; row++) { 
    for (size_t col = 0; col < puzzle_width_ - word.size() + 1 ; col++) {
      positions.clear();
      for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == puzzle_.at(row + i).at(col + i) && LocationInBounds(row + i, col + i)) { 
          CharPositions p = {word[i], row + i, col + i}; 
          positions.push_back(p);
          if (positions.size() == word.size()) {
            return WordLocation{word, positions};
          }
        } else {
          positions.clear();
        }
      }
    }
  }
  return WordLocation{}; 
}

WordLocation WordSearchSolver::LeftDiag(const string& word) {
  vector<CharPositions> positions;

  for (size_t row = 0; row < puzzle_height_ - word.size() + 1; row++) { 
    for (size_t col = word.size() - 1; col < puzzle_width_; col++) {
      for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == puzzle_.at(row + i).at(col - i) && LocationInBounds(row + i, col - i)) { 
          CharPositions p = {word[i], row + i, col - i}; 
          positions.push_back(p);
          if (positions.size() == word.size()) {
            return WordLocation {word, positions}; 
          }
        } else {
          positions.clear();
        }
      }
    }
  }
  return WordLocation{}; 
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {

  if (direction == CheckDirection::kHorizontal) {
    return Horizontal(word);
  }
  if (direction == CheckDirection::kVertical) {
    return Vertical(word);
  }
  if (direction == CheckDirection::kRightDiag) {
    return RightDiag(word);
  }
  if (direction == CheckDirection::kLeftDiag) {
    return LeftDiag(word);
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (FindWord(word, CheckDirection::kHorizontal).word == word) {
    return FindWord(word, CheckDirection::kHorizontal);
  }
  if (FindWord(word, CheckDirection::kVertical).word == word) {
    return FindWord(word, CheckDirection::kVertical);
  }
  if (FindWord(word, CheckDirection::kLeftDiag).word == word) {
    return FindWord(word, CheckDirection::kLeftDiag);
  }
  if (FindWord(word, CheckDirection::kRightDiag).word == word) {
    return FindWord(word, CheckDirection::kRightDiag);
  }
  return WordLocation{};
}



