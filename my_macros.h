#ifndef MY_HELPERS_H
#define MY_HELPERS_H

/* Prompt to print */
#define MY_PROMPT_MSG "$" /* Needs works with signal */

/* Returns from unused attribute */
#define MY_UNUSED __attribute__((unused))

/* buffer size for every read call in _getline */
#define MY_BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define MY_HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change to shell working directory.\n\n"\
"	If no argument is provided to 'cd', the command will be interpreted as follows:\n"\
"	as cd $HOME.\n"\
"	if the argument help is - (cd -), the command will be decoded\n"\
"	as cd $OLDPWD.\n\n"\

#define MY_HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit the simple-shell.\n\n"\
"	Exits shell with a status of N.  If N is removed, the exit status\n"\
"	if that of the last command executed.\n\n"

#define MY_HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will print a complete list of enviroment variables.\n\n"

#define MY_HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Modify or add an environment variable.\n\n"\
"	If no argument is provided with the 'cd' command, it will be handled in the following way:\n\
"	If no correct total number of arguments print err message.\n\n"

#define MY_HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function removes one variable from the environment.\n\n"\
"	If no correct total number of arguments print err message.\n\n"

#define MY_HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Show information about builtin commands.\n\n"\
"	Outlines brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	Specified, offers comprehensive guidance on commands that match BUILTIN_NAME,\n\
"	if not the list of help topics is printed BUILTIN_NAME list.\n\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
