# Dotfiles backup
Simple C program for backup dotfiles (or any other files) in a github (or other git server) repo. \
The program takes n arguments rapresenting all the dotfiles name to backup. 

### I recommend to use the program in combination with ```find```

An example: 
``` bash
    $ gh repo create ... # create your dotfiles backup repo
    $ make # compile the program
    $ ./main $(find ~ -maxdepth 1 -type f -name ".*") # backup all dotfiles in the home directory
```

If you call the program without arguments it call: 
 - git add -A
 - git commit -m "Update dotfiles, date: Day-Mounth-Year Hours:Minutes:Seconds"
 - git push

