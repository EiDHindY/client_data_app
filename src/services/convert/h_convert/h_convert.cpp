// client_data_app/src/services/convert/h_convert/h_con_str_to_v_str.cpp


#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include "infrastructure.h"

namespace h_convert {

    void detect_delim(std::string_view str, std::string_view delim, std::vector<size_t>& indexes)
    {
        // Guard Clause: Check if the string is valid and large enough to contain the delimiter
        if (str.empty() || str.length() < delim.length()) 
        {
            return; // Impossible to find anything. Goodbye.
        }

        size_t str_size = str.length();
        size_t delim_size = delim.length();
        size_t i = 0;
        bool delim_found{};

        // Loop through the string, stopping when remaining characters are fewer than delimiter length
        while(i <= (str_size - delim_size))
        {
            delim_found = false;

            // Optimization: Check the first character match before starting the expensive inner loop
            if (str[i] == delim[0])
            {
                bool full_loop = true;
                // Inner Loop: Check the remaining characters of the delimiter
                for(size_t j = 1; j < delim_size; j++)
                {
                    if (str[i + j] != delim[j]) 
                    {
                        full_loop = false;
                        break; // Mismatch found, break early
                    }
                }
                if(full_loop) delim_found = true;
            }

            if (delim_found)
            {
                indexes.push_back(i); // Store the start index of the found delimiter
                i += delim_size;      // Jump forward by delimiter length to avoid overlapping checks
            }
            else 
            {
                i++; // Move to the next character
            }
        }
    }
   

    std::vector<std::string> h_conv_str_vstr(std::string_view str_record)
    {
        std::vector<std::string> vec_of_str{};
        if (str_record.empty()) return vec_of_str;
        std::vector<size_t> vec_of_idx{};
        std::string_view delim = infrastructure_names::SEPARATOR;

        h_convert::detect_delim(str_record, delim, vec_of_idx);

        size_t str_record_size = str_record.size();
        size_t vec_of_idx_size = vec_of_idx.size();
        size_t delim_size = delim.size();
        size_t start_word{};
        
        std::string word{};

        for(size_t i = 0; i < vec_of_idx_size; i++)
        {
            while(start_word != vec_of_idx[i])
            {
                word+=str_record[start_word];
                start_word++;
            }
            start_word+=delim_size;
            vec_of_str.push_back(word);
            word.clear();

        }
        while(start_word < str_record_size)
        {
            word+=str_record[start_word];
            start_word++;
        }
        vec_of_str.push_back(word);
        return vec_of_str;
    }
} // namespace h_convert