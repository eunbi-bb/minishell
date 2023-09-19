# minishell
*This project is about creating a simple shell, especially **bash**. Implementing processes and file descriptors.*   



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
- Using an environmental pointer to find and luanch commands or executables.  


## Implementation

### *Shell_loop*
When **minishell** program is exeucted, **shell_loop** implement **readline()** in order to show up a command prompt. \
Once a line has been typed, the line will be checked if there is any unclosed quotes by *match_quotes()* inside of **shell_loop**. \
If no issue has been detected in *match_quotes()*, **shell_loop** executes **lLxer**, **Parser** and **Executor**. \
Depending on a return value of **Executor**, looping will be decided.

---

### *Lexer, Parser and Executor*
![Minishell](https://github.com/eunbi-bb/minishell/assets/80834766/e0db69ab-bb64-4854-9257-a7397e47a200)
![Minishell(1)](https://github.com/eunbi-bb/minishell/assets/80834766/ccfe4e7f-f520-46d0-b631-14bdf5a9df2b)
![Minishell(2)](https://github.com/eunbi-bb/minishell/assets/80834766/372d0d35-17dc-44a1-9479-de008c24cae1)


*More information about each program is below.*

---

### *Lexer*
*Lexical Analyzer, also called as the tokenizer.* \
\
It takes the line from the **shell_loop** and split the line by white spaces.\
After splitting the line, it devides tokens(*`|`, `<`, `<<`, `>`, or `>>`*) and word(*DEFAULT*). Then it adds to **t_tokens** linked list.

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
Parser loops through the **token linst** using **pipe**(*`|`*) as delimiters.\
Then it takes all nodes before **pipe** as one command and adds to **t_cmd** doubly linked list.

```C
typedef struct	s_cmd
{
	char			**data;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;
```
If the command contains **redirection tokens**, additionally adds the **token** to **t_redir** linked list. \
Always a word after the **redirection token** will be **file_name**.
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
Execept **builtins**, the commands that returns from **Parser** are executed in **Executor**. Depending on child process status, **shell_loop** will be decided to be continued or stop the loop.

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
When **heredoc** is executed in **Executor**, the **file_name** is stored as a delimiter. And replace the **file_name** to a temporary file name. The temporary file name will be used to write the input to. Afterwards, in the redirection function, the temporary file is redirected and unlink after finishing heredoc.
```
Minishell% << delimiter
hi	//Writing inputs into the temporary heredoc file until delimiter is typed.
hello
delimiter
Minishell%
```
