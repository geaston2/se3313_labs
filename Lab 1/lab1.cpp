#include <iostream>
#include <unistd.h>
#include <fstream>
#include <signal.h>
#include <sys/wait.h> // for waitpid()
#include <string>

int main() {
    std::string userData;
    pid_t children[200];
    int count = 0;

    while (true) {
        std::cout << "Please input a string (type 'done' to exit):" << std::endl;
        std::cin >> userData;

        // Fork
        int pid = fork();

        if (pid == 0) {
            // Child process
            // Create .txt
            int pID = getpid();
            std::string fileName = "process_" + std::to_string(pID) + ".txt";

            std::ofstream outfile(fileName);

            // Write userData to txt
            while (true) {
                // Wait 1 second
                sleep(1);
                outfile << userData << std::endl;
            }

            // Close the file
            outfile.close();

            // Exit the child process
            exit(0);
        } else {
            // Parent process
            children[count++] = pid;
        }

        if (userData == "done") {
            // Kill all child processes
            for (int i = 0; i < count; i++) {
                if (children[i] != 0) {
                    kill(children[i], SIGKILL);
                    // Wait for child process to terminate
                    waitpid(children[i], NULL, 0);
                }
            }
            break;
        }
    }
    return 0;
}

