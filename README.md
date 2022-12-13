
# README file
Operating Systems and Networks Assignment 2 by Ishan Kavathekar (2022121003) for CS3.301

## Instructions to use
- Run the makefile using the make command.
- Run the ./shell command to run the shell.
- User can delete executable file using make clean command.
- User can exit the shell using exit command or CTRL+D
- The directory in which it is executed will be its home directory.

## Specifications 
### Specification 1:Display requirement<br>
- The shell displays the username and hostname in the prompt.
- User can input any command from prompt

### Specification 2:Builtin commands<br>
#### cd command:
- cd command is used to directory to a specific directory. Various different variations of cd supported in the shell.
- cd: changes directory to the home direcotry.
- cd . :changes directory to current working directory.
- cd .. : changes directory to parent directory.
- cd - : changes directory to previous directory.
- cd ~ : changes directory to the home direcotry.

#### echo command:
- echo command is used to output the string received by the user.
- echo : prints nothing
- echo {text} : prints the text after removing any extra tabs and spaces.

#### pwd command:
- pwd command returns the path of the current working directory.

### Specification 3: ls command<br>
- The ls command prints all the directories, files and executable files in the specified directory, file or executable.
- ls command takes two flags: -a and -l
- -a flag: This flag also outputs the hidden files and folders.
- -l flag: This flag outputs all the details of the files and folders in long format.

### Specification 4: System commands with and without arguments<br>
-The shell shoudl alsoexecute all commands like gedit, sleep and emacs.
- These commands can either executed in foreground or in the background.
- Any command ending with an '&' symbol is treated as a background command.
- Else it is considered as a foreground command.

### Specification 5:pinfo command<br>
- This command prints all the information about the given pid.
- The information printed is the pid, the status(running,sleep or zombie), memory and the executable path.

### Specification 6: Finished background process<br>
- This command prints if the background process exits normally or not.

### Specification 7: Discover command<br>
- discover command is a user defined command which outputs all the directories and files in the specified directory or file.
- This command takes two flags: -d and -f.
- -d flag: Searches for all directories.
- -f flag: Searches for all files.


### Specification 8:History command<br>
- history command outputs the last 10 commands given by the user.
- history command stores 20 commands but outputs only the latest 10 commands.

### Input Output Redirectoin<br>
- > is used for output redirection
- < is used for input redirection
- >> is used to append to the file
- It is assumed that the user will enter whitespace after every word.

### Command Pipeline
- Pipes used to communicated between processes

### Jobs<br>
- Lists all the jobs according to the flags.
- jobs -r : lists all the running jobs.
- jobs -s : lists all the stopped jobs.

### sig command<br>
- sig command takes two arguments: the process number and signal number.
- It executes the signal number on the given process.

### fg command<br>
- Brings background process corresponding to job number to the foreground.
- It throws an error if the given job number does not correspond to a valid job number.

### bg command<br>
- Changes state of stopped background job in running in the background.
- It throws an error if the given job number does not correspond to a valid job number.

### CTRL-Z<br>
- Pushes currrntly executing foreground job to background and changes it's state to stopped.

### CTRL-C <br>
- Interrupts any ongoing foreground process by sending it the SIGINT signal.

## Assumptions<br>
- The commands will be of maximum length 200.



