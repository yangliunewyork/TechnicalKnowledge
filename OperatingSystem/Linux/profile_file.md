# What is a profile file?

A profile file is a start-up file of an UNIX user, like the autoexec.bat file of DOS. When a UNIX user tries to login to his account, the operating system executes a lot of system files to set up the user account before returning the prompt to the user.

In addition to the system settings, the user might wish to have some specific settings for his own account. To achieve this in UNIX, at the end of the login process, the operating system executes a file at the user level, if present. This file is called profile file.

The name of the profile file varies depending on the default shell of the user. The profile file, if present, should always be in the home directory of the user.

The specific settings which an unix user usually does is:

* Setting of any environment variable
* Setting of any alias.(Though it is always recommended to keep the aliases in a separate file).
* Setting of PATH variable or any other path variables.

Any changes made to the profile file will reflect by either of the following ways:
  
1. Login to the user account again.
2. Source the profile file. Sourcing the profile file means running the profile file at the command prompt.
