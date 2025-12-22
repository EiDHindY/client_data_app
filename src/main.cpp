// CDA.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include "controller/helper/h_handle_file_exist.h"
#include "platform_ops/paths/paths.h"
#include <iostream>

int main() {

  auto path = platform_ops_paths::get_exe_dir_path();
  std::cout << "exe path: " << path << '\n';

  h_controller::handle_file_exist(path);
  auto full_path = platform_ops_paths::get_original_file_path(path);

  if (platform_ops_paths::is_file_exist(full_path)) {
    std::cout << "success\n";
    std::cout << "found in: " << full_path;
  } else
    std::cout << "failed";
}
