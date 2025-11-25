// src/file_ops/file_ops.cpp
#include <fstream>
#include <iostream>
#include "file_ops/file_ops.h"
namespace file_ops
{
    std::vector<std::string> get_all_clients(const std::filesystem::path& file_path)
    {
        std::ifstream file(file_path); // CPU: Opens file. Memory: allocates file stream object.
        if (!file.is_open())
        {
            // File failed to open (missing file, bad path, access denied).
            // Returns empty vector immediately.
            // - Memory: No storage allocated except local return vector.
            // - CPU: Function exits early.
            return {};
        }

        std::string line;               // Allocate buffer for each file line read.
        std::vector<std::string> all_clients{}; // Vector to store client lines, initially empty.
        // Loop reads the file line by line.
        while (std::getline(file, line))
        {
            // Each successful read allocates (copies) a new string for memory storage.
            // CPU: Reads each line from file into memory, pushes back into vector, grows vector as needed.
            // Memory: std::vector dynamically resizes as new lines are appended (uses doubling strategies internally).
            all_clients.push_back(line);
        }
        // At end-of-file, file stream reaches EOF state.
        // CPU: Returns vector. If vector was not empty, memory holds N strings.
        return all_clients;
        // Memory: Vector copies/moves to caller; destructor cleans up 'file', 'line', and local vector.
    }

}