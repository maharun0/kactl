// Tools -> Build System -> New Build System (write script & save)
// Tools -> Build System (select recently created script)
{
"cmd" : ["g++ -std=c++20 $file_name -o $file_base_name && timeout 10s ./$file_base_name < input.txt > output.txt 2> debug.txt && rm $file_base_name"], 
"selector" : "source.cpp",
"shell": true,
"working_dir" : "$file_path"
}

// Press `Alt + Shift + 4` to split window in 4 parts.
// save 'inputf.in', 'outputf.in', 'debugf.in'
// Press `Ctrl + B` to run code.

/// Precompile HeaderFile
// just go to file explorer and serach 'stdc++.h'
// go to that folder and open folder in terminal
// sudo g++ -std=c++20 stdc++.h
// stdc++.h.gch is created precompile done

// preferences -> settings add "save_on_window_deactivation": true

// windows
"cmd": [ "g++.exe", "-std=c++14", "${file}", "-o", "${file_base_name}.exe", "&&", "${file_base_name}.exe", 
"<", "input.txt", ">", "output.txt", "2>", "debug.txt", "&&", "del", "${file_base_name}.exe"],