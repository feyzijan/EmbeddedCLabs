# Lab 1 - Getting started and Digital IO

## Learning outcomes

By the end of this lab you should be able to:
- Compile a C program in MPLAB X and download and run on the PIC chip
- Know the basics of version control with Git (cloning a repository, committing changes, pushing commits to a GitHub remote repository)
- Understand how to control the output of individual pins to control LEDs
- Understand how to poll the state of an input pin connected to a button

## Prerequisites

If you have not already done so, download and install the following:

[MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide) - this is the main development environment (scroll down to the Downloads tab and select the download for your system)

[MPLAB XC8 Compiler](https://www.microchip.com/mplab/compilers) - needed to compile code for the microcontroller (scroll halfway down the page and there is a set of tabs, select **Compiler Downloads** tab and choose the XC8 compiler for your system)

[Git](https://git-scm.com/downloads) - software for version control (optional but recommended)

[Github desktop](https://desktop.github.com/) - graphical interface for common Git tasks (optional but recommended)

## Your first project - the microcontroller "Hello world!"

### Generate a personal access token on GitHub
To increase security GitHub no longer allows the use of your GitHub password to directly access repositories from git (or apps like MPLAB X). This means we must jump through an extra hoop to get things working, but at least we can be more confident that no one will steal/hack our source code! We need to create a personal access token (PAT) on the GitHub site by following the instructions here https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token. Use the following options when creating your token:
1. In the **Note** field you can put anything you want - but something like "ECM PAT" will do
1. In **Expiration** put a custom date which extends beyond the end of the course. After this date you will need a new token to access your repos from git (you can still see them on the GitHub site)
1. In scope select the **repo - Full control of private repositories** box
1. Hit **Generate token** and **make a note of the token - you will not be able to see it again**. It is essentially a password and you should treat it as such. I recommend storing it safely in a password mananger. If you lose your token you will need to repeat the above and update all your MPLAB X projects to use it

### Cloning from GitHub using MPLAB:
1. In MPLAB select Team -> Git -> Clone
1. Copy your repository URL i.e. https://github.com/ME3-HECM/labname-gitusername and enter your GitHub email and the PAT that you created above 
1. Hit next (don't worry about the directory for now) and select the master\* branch (should be selected by default)
1. Select a directory to store the cloned repository
1. Add **.X** to the clone name (:warning: **very Important** - your life will be more difficult if you don't do this...)
1. MPLAB should ask you if you want to create a new project, click yes

![Cloning GitHub repo using MPLAB X](gifs/git_clone.gif)

### Creating new MPLAB project:
1. Select Microchip Embedded and Stand-alone Project
1. Select Family Advanced 8bit MCUs (PIC18) and Device PIC18F67K40, if you have connected the PICKIT select it here, if not just leave it as No Tool
1. Select XC8 Compiler
1. The Project Folder box needs to match the folder name of the Git clone. Select directory and enter project name. MPLAB automatically adds .X to the project name 
1. :warning: **Double check** the Project Folder matches the Git folder you created previously and hit finish

![Creating new project in MPLAB X](gifs/mplab_new_proj.gif)

### Adding source file and compiling/programming:
1. Right click the source files icon in the projects tab and select add existing item - select main.c
1. Click on the main.c file under the source files icon and open to view/edit the code
1. Hit Build Main Project or Clean and build, the code should compile and you'll see a BUILD SUCCESSFUL message in the output tab
1. Connect the PICKIT to the board and hit Make and Program Device (ensure board is connected to USB and powered on)
1. You should see the LED light up when you press the button
1. Well done :+1:, that's the difficult bit over!

![Make and program device](gifs/make_and_prog.gif)

### Working with git:
Now is a good time to commit your first changes to your local git repository, and then push them to GitHub

1. Right click on the project name in the projects tab and select Git -> Commit...
1. Write a useful message to go with your commit (i.e "MPLABX Project creation"), select author and committer as your GitHub user/email 
1. Hit Commit - you're changes are now committed to your local git repository - each commit forms a historical record of changes made to the code
1. To push the changes (commits) to GitHub, select Git -> Remote -> Push to Upstream
1. Check on GitHub to see your commits online - that's the basic git workflow for source code management, we'll expand on this later in the module

![Commits and Push to GitHub in MPLAB X](gifs/git_commit_and_push.gif)

## Exercises:
After you have got the basic "Hello world!" example working, complete the below exercises. Remember to Commit changes using Git after each excercise and Push the changes to GitHub.

1. Microcontroller "Hello world!" working :white_check_mark:
1. Make the second LED (pin RH3) come on when the other LED (RD7) is not 
1. Enable input on the second button (RF3) and require both buttons to be pressed to change the state of LEDs
1. Change the code so that the each button controls its respective LED
1. Complete the comments in main.c to explain the purpose of each section of code
