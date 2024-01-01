# Description

# Linux Shell Replica
This project presents a thorough recreation of a Unix-like shell, commonly referred to as a command-line interface or terminal. It faithfully mimics the functionality and visual aspects of conventional shells, while also enhancing their capabilities through various added features.

## Prompt

The shell prompt mimics the structure of a Unix-style shell, offering an intuitive interface for users. It manifests as <username@system_name:curr_dir>, continuously adjusting to showcase the present working directory.

## User-Implemented Commands

### Warp (cd)

The "warp" command represents an advanced iteration of the cd command in the Bash shell, providing an array of flags and accommodating both absolute and relative paths. This command boasts the following flag functionalities:

- ~: Effortlessly traverse to the user's home directory.
- ..: Ascend to the parent directory.
- .: Remain within the present directory.
- -: Conveniently return to the preceding directory.

### Peek (ls)


The "peek" command provides a comprehensive listing of files and directories within a designated directory or directories, sorted alphabetically. By default, it omits hidden files from the display. The "peek" command offers the following options:

- "-l": Presents additional details pertaining to files and directories.
- "-a": Exhibits all files, encompassing hidden ones.

### Seek (find)

The "seek" command is a versatile tool for locating files or directories, whether you want to search within a specific target directory or within the current working directory if none is specified. It provides a result list containing relative paths to matching files (displayed in green) and directories (displayed in blue), with each entry separated by newline characters.

Here are the available options:

- Use -d to exclusively search for directories, disregarding any matching file names.
- Employ -f to exclusively search for files, disregarding any matching directory names.
- The -e flag comes into play when a single file or a single directory with the specified name is found:
        If only one file (and no directories) is located, the command prints the result.
        If only one directory (and no files) is discovered, it alters the current working directory to match it.
        Otherwise, the flag has no impact.
    The -e flag can be used in conjunction with both the -d and -f flags.

Additionally, the "peek" and "seek" commands recognize the following symbols to specify directories:

- .: Denotes the current directory.
- ..: Represents the parent directory.
- ~: Signifies the user's home directory.

### Past Events (history)
The pastevents command offers users a retrospective glimpse into their past interactions with the shell, displaying a detailed history of previously executed shell commands, their respective outcomes, and any encountered error messages. This functionality aids users in monitoring and resolving issues related to their shell interactions.

- Flags and Arguments for pastevents:

    - No argument: Displays the most recent 15 commands executed by the user.
    - Purge: Erases the entire command history.
    - Execute <index>: Executes the command located at the specified position within the pastevents       history, ordered from the latest to the oldest entries.

### Foreground and Background Processes
This versatile shell allows you to execute processes in either the foreground or the background. Here are two illustrative scenarios:

- When you execute a command, such as 'vi,' in the foreground, the shell will wait for its execution to finish before accepting any further input.

- Alternatively, by appending '&' to the end of a command, it becomes a background process, permitting you to seamlessly continue entering additional commands.

### Output and Input Redirection
The shell allows you to redirect the output of commands to files and read input data from files. Error handling is in place, including checks for non-existent input files. Examples include:

- Output redirection: `diff file1.txt file2.txt > output.txt`
- Input redirection: `sort < lines.txt`
- Input-Output redirection: `sort < lines.txt > sorted-lines.txt`

### Pipelines
The shell facilitates the creation of pipelines by utilizing the | symbol, allowing for the sequential execution of multiple commands. It supports an unrestricted number of pipes, as demonstrated in the following examples:

- Utilizing two commands: more file.txt | wc
- Employing three commands: grep "new" temp.txt | cat somefile.txt | wc

### Process and Job Management
proclore: This command displays process-related details for the current shell program.

- activities: It provides a list of all currently active jobs, with a focus on background tasks, sorted by their creation time.

- ping <jobNumber> <signalNumber>: Use this command to send a signal to a running job, specifying the job number and signal number as arguments.

- fg <jobNumber>: This command allows you to bring a background job to the foreground, making it the active process.

- bg <jobNumber>: Use this command to initiate the execution of a background process associated with a specific job number.

### iMan
Introducing the iMan command, a valuable enhancement to this shell that empowers users to effortlessly access manual pages encompassing a wide array of commands and utilities. This feature offers comprehensive insights into command utilization, available options, and practical examples, facilitating a seamless and efficient shell navigation experience.

### neonate
The "neonate" command represents a robust functionality that streamlines repetitive actions, enabling users to devise and run personalized scripts within the shell environment. This feature elevates the shell's scripting potential, granting users the ability to automate intricate processes effortlessly.

### Additional commands

Here are some essential keyboard shortcuts for controlling processes in a shell environment:

- "CTRL-Z": This shortcut allows you to transition the current job's status to "stopped" and moves it to the background.

- "CTRL+D": Use this key combination to exit the shell gracefully.

- "CTRL+C": This key combination emulates the functionality of the bash shell and can be employed to terminate a running process.

## Usage
To run the shell, follow these steps:

1. Clone the repository.
2. Run `make` in the cloned directory to compile the code.(if `make` does not work use `make -B main`)
3. Execute `./a.out` to start the shell.

# Assumptions
1. Input redirection has been handeled for user defined commands too.
2. Atleast one whitespace character is required when inputting symbols for pipelining, I/O redirection, ; &
3. When code is exitted through signal then exit won't be listed in pastevents but if exit is typed then it will be listed in pastevents.
4. The spaces between the arguments of echo (enclosed by double quotes) are not taken into consideration.
    For example: echo "Lorem        Epsum" will output Loren Epsum
5. When an input of type "Lorem Ipsum" is typed output will be "Lorem Ipsum" and nor Lorem ipsum and commands like wc will also consider inverted comma as a character
6. Sed command is not supported by piping.
7. For SIGQUIT both CTRL + D and CTRL + '\ works.
8. Given priority to piping over I/O redirection
9. Peek and Seek won't work for '-' as it was told in doubt document.
10. Background processes with pipelining have not been handeled as per given in the Doubt Document and it has been assumed that such type of command won't be given as an input
11. The pastevents history is updated in the history.txt file time to time and also when the program gets exited using either "exit" in the terminal or CTRL + D is pressed . When the program is run then the histroy is restored.
12. For the commands made by us in other specs , foreground background isn't considered , they are run directly.
13. for Ping , if you send kill signal(9) to the terminal process itself , then it only prints "Killed" and not the whole statement "Sent signal _ to process with pid _ "
14. It is assumed that no command of type cmd_1 | will be inputted.
