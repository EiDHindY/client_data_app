// client_data_app/src/services/convert/h_convert/h_con_str_to_v_str.cpp

#include "infrastructure.h"
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace h_convert {

void detect_delim(std::string_view str, std::string_view delim,
                  std::vector<size_t> &indexes) {
  // Guard Clause: Check if the string is valid and large enough to contain the
  // delimiter
  if (str.empty() || str.length() < delim.length()) {
    return; // Impossible to find anything. Goodbye.
  }

  size_t str_size = str.length();
  size_t delim_size = delim.length();
  size_t i = 0;
  bool delim_found{};

  // Loop through the string, stopping when remaining characters are fewer than
  // delimiter length
  while (i <= (str_size - delim_size)) {
    delim_found = false;

    // Optimization: Check the first character match before starting the
    // expensive inner loop
    if (str[i] == delim[0]) {
      bool full_loop = true;
      // Inner Loop: Check the remaining characters of the delimiter
      for (size_t j = 1; j < delim_size; j++) {
        if (str[i + j] != delim[j]) {
          full_loop = false;
          break; // Mismatch found, break early
        }
      }
      if (full_loop)
        delim_found = true;
    }

    if (delim_found) {
      indexes.push_back(i); // Store the start index of the found delimiter
      i += delim_size; // Jump forward by delimiter length to avoid overlapping
                       // checks
    } else {
      i++; // Move to the next character
    }
  }
}

std::vector<std::string> h_conv_str_vstr(std::string_view str_record) {
  // 1. Initialize an empty vector to store the split words (our output).
  std::vector<std::string> vec_of_str{};

  // 2. Guard Clause: If the input string is empty, we have no work to do.
  // Return the empty vector immediately to avoid errors later.
  if (str_record.empty())
    return vec_of_str;

  // 3. Prepare a vector to hold the indexes (positions) where we find
  // delimiters.
  std::vector<size_t> vec_of_idx{};

  // 4. Define what our delimiter looks like (e.g., "#//#").
  // We get this from our infrastructure configuration.
  std::string_view delim = infrastructure_names::SEPARATOR;

  // 5. Helper Call: Scan the string and fill `vec_of_idx` with the locations of
  // all delimiters. Example: If str is "1001#//#Eid", it finds the index of the
  // first '#'.
  h_convert::detect_delim(str_record, delim, vec_of_idx);

  // 6. Cache the sizes to avoid calling .size() repeatedly in loops.
  size_t str_record_size = str_record.size();
  size_t vec_of_idx_size = vec_of_idx.size();
  size_t delim_size = delim.size();

  // 7. `start_word`: This is our "Current Reading Position" (or Anchor).
  // It points to the start of the next word we are about to extract.
  size_t start_word{};

  // 8. Temporary buffer to build each word character-by-character.
  std::string word{};

  // 9. PHASE 1: Extract words based on found delimiters.
  // We loop through each delimiter position we found.
  for (size_t i = 0; i < vec_of_idx_size; i++) {
    // Inner Loop: "Walk" from our current position (`start_word`) up to the
    // next delimiter (`vec_of_idx[i]`). We copy characters one by one until we
    // hit the delimiter.
    while (start_word != vec_of_idx[i]) {
      word += str_record[start_word];
      start_word++; // Move forward
    }

    // At this point, `start_word` is sitting exactly at the start of the
    // delimiter. We successfully built one full word.

    // 10. Jump the Anchor over the delimiter.
    // If we are at index 4 and delimiter is 4 chars, new start is 8.
    start_word += delim_size;

    // 11. Save the word we just built into our results vector.
    vec_of_str.push_back(word);

    // 12. Clear the buffer so it's ready for the NEXT word.
    word.clear();
  }

  // 10. PHASE 2: The "Leftover" Word.
  // After the last delimiter, there is still one word left (or at least valid
  // text) until the end of the string. This loop copies everything from the
  // last known position to the very end of the string.
  while (start_word < str_record_size) {
    word += str_record[start_word];
    start_word++;
  }

  // 11. Push this final word into the vector.
  // This ensures the last field (e.g., "5000.50") is not lost.
  vec_of_str.push_back(word);

  // 12. Return the completed list of words.
  return vec_of_str;
}

client_data_structure::stClientData
h_conv_vstr_struct(std::vector<std::string> vstr) {
  client_data_structure::stClientData result{};

  result.account_number = vstr[0];
  result.pass_code = vstr[1];
  result.phone_no = vstr[2];
  result.name = vstr[3];
  result.account_balance = std::stod(vstr[4]);

  return result;
}
} // namespace h_convert