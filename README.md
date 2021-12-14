# C Shell

## How to run the shell
1. Open the directory containing files in terminal.
2. run make.
3. run ./shell.
4. run 'exit' in shell/press *CTRL+D* to quit.
   
The directory in which it is executed will be its home directory.

---
## Commands:

#### pwd command
* pwd : prints the absolute path of the current directory.

#### cd command
* cd  : goes to home directory(~/)
* cd ~/ < pathname > : goes to ~/< pathname >
* cd .. : goes to parent directory.
* cd . : stays in the same directory.
* cd - : goes to previous directory.

#### echo command
* echo : prints empty line.
* echo text : prints text.

#### ls command
* ls takes arguments as flags and directories.
* It lists the files of the directory mentioned.
* ls : lists all the files.
* ls -l : long list(Here the time is replaced by year if the file's date is more than 6 months old.)
* ls -a : also displays hidden files.
* ls -al/-la/-a -l/-l -a : long list with hidden files.


#### Foreground processes
* The shell waits till the current process to finish.

#### Background processes
* Use '&' at the end of the command for invoking a background process.
* The process will then run(a pid is shown when started) in the background and when exited, a message will be shown.

#### pinfo command
* pinfo : prints process info of the shell.
* pinfo pid : prints process info of given pid.

#### repeat command
* repeats command N times.


#### Input/Output redirection
* Ouput of a command can be redirected to a file.
* Input for an command can be taken from a file.
* Both these can be performed simultaneously.


#### Redirection using Pipes
* Multiple commands can be piped.
* Piping and Input/Output redirection can be done together.


#### jobs command
* Prints the list of all the background processes with their state.
* jobs -r : For running processes.
* jobs -s : For stopped processes.

#### sig command
* Sends a signal number to a process with job number.

#### fg command
* Brings a running or a stopped background job with given job number to foreground.

#### bg command
* Changes a stopped background job to a running background job.

#### Signals
* **CTRL+Z** : makes the foreground process a background process and changes its state to stopped.
* **CTRL+C** : Interrupts any currently running foreground job by sending SIGINT signal.
* **CTRL+D** : Logs out of shell.

#### replay command
* This executes a command after fixed time intervals for given period.

---
## Files-
The program has different files for each commad with name commandName.c

The different files are:

* redirection.c
* main.c
* shell
* background.c
* ls.c
* makefile
* jobs.c
* pwd.c
* headers.h
* pinfo.c
* fg.c
* README.md
* cd.c
* prompt.c
* echo.c
* sig.c
* pipe.c
* signals.c
* replay.c
* repeat.c
* foreground.c
* bg.c


---
### Assumptions:
* The commands given in a line will not be more than 200 and length of each commad is maximum 200 characters. 
* In ls -l, the time is replaced by year if the file's date is more than 6 months old.
* The length of path of working directory of shell will not be more than 1000 characters.