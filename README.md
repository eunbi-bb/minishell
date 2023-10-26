# minishell
*This project aims to create a simple shell, inspired by **bash**, and focuses on implementing processes and file descriptors.*



## Usage
*In MacOS*
```
$ make
```
*In Linux*
```
$ make LINUX=1
```
```
Minishell% ls -l
```
```
Minishell% < infile grep "Hi" | wc -l outfile >
```
```
Minishell% cat << heredoc1 << heredoc2
```
```
Minishell% cat << heredoc1 > heredoc_file
```
*To exit minishell*
```
Minishell% exit
```
## Requirements
- Displaying a prompt while waiting for a new command. -> **shell loop**
- Handling quotation marks like in bash.
- Implementing **redirections**:
	- `<`	(LESSER)		: redirect input.
	- `>`	(GREATER)		: redirect output.
	- `<<`	(HERE DOC)	: generate a temporary file and redirect standrad input to the temporary file.
	- `>>`	(APPEND)		: redirect output in append mode.
- Implementing **pipes**
- Using an environmental pointer to find and launch commands or executables.  


## Implementation

### *Shell_loop*
When the **minishell** program is executed, the **shell_loop** function implements **readline()** to display a command prompt. \
Once a line has been typed, shell_loop executes **Lexer**, **Parser**, and **Executor**. \
Depending on the return value of **Executor**, the loop's behavior will be determined.

---

### *Lexer, Parser and Executor*
![Minishell](https://github.com/eunbi-bb/minishell/assets/80834766/ff57e94c-c462-4bac-aaf2-b8b4c0364caa)
![Minishell(1)](https://github.com/eunbi-bb/minishell/assets/80834766/1ba69bb6-e66e-4ffa-b05b-2413a311b2db)
![Minishell(2)](https://github.com/eunbi-bb/minishell/assets/80834766/0db05778-acd6-414b-bacd-c1d17cd9af71)

*More information about each program is below.*

---

### *Lexer*
*Lexical Analyzer, also called as the tokenizer.* \
\
It takes the line from the **shell_loop** and split the line by white spaces.\
After splitting the line, it devides tokens(*`|`, `<`, `<<`, `>`, or `>>`*) and word(*DEFAULT*). Then it adds to **t_tokens** linked list.

*Lexical Analyzer, also known as the tokenizer.* \
\
It takes the line from the **shell_loop** and splits the line by white spaces. \
After splitting the line, it divides tokens (*`|`, `<`, `<<`, `>`, or `>>`*) and words (*DEFAULT*). Then, it adds them to the **t_tokens** linked list.

```C
typedef enum types
{
	DEFAULT = -1,
	PIPE,
	LESSER,
	GREATER,
	HERE_DOC,
	APPEND
}	t_types;
```

```C
typedef	struct	s_tokens
{
	char			*data;
	t_types			token;
	struct s_tokens	*next;
}	t_tokens;
```

---

### *Parser*
*Generating commands and sending it to Executor.* \
\
Parser loops through the **token list** using **pipe**(*`|`*) as delimiters.\
Then it takes all nodes before **pipe** as one command and adds to **t_cmd** doubly linked list.

```C
typedef struct	s_cmd
{
	char			**data;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;
```
If the command contains **redirection tokens**, it additionally adds the **token** to **t_redir** linked list. \
Always, a word after the **redirection token** will be **file_name**.
```C
typedef struct s_redir
{
	char		*file_name;
	t_types		redir_type;
	struct s_redir *next;
}	t_redir; 
```
---

### *Executor*
*Executing, and handling command pipelines, including input/output redirections. It also manages the communication between the commands using pipes.* \
\
Execept for **builtins**, the commands that returns from **Parser** are executed in **Executor**. Depending on child process status, **shell_loop** will be decided to be continued or stop the loop.

---

### *Expander*
*Expander takes variables, identified by `$`, and replaces them with their value from environment.*
```
Minishell% echo "$USER"
eunbi
```
---

### *Heredoc*
*A "heredoc" (here-document) is a way to input multiple lines of text interactively into a command, usually used as input for commands or scripts, allowing multiline input without escaping characters.* \
\
When **heredoc** is executed in **Executor**, the **file_name** is stored as a delimiter. And replaces the **file_name** to a temporary file name. The temporary file name will be used to write the input to. \
Afterwards, in the redirection function, the temporary file is redirected and unlinked after finishing heredoc.
```
Minishell% << delimiter
hi	//Writing inputs into the temporary heredoc file until delimiter is typed.
hello
delimiter
Minishell%
```
